//
//  main_Qvec_pp.cpp
//  TD-Qvec-post-process
//
//  Created by Nile Ó Broin on 02/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <string>


#ifdef _OPENMP
#include <omp.h>
#endif


#include <boost/program_options.hpp>



#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "Qvec_Dims.hpp"
#include "PostProcessing_Dims.hpp"

#include "Inline.hpp"
#include "Qvec_Calculations.hpp"
#include "Turb_Spec.hpp"


#include "Input_FILES_V4.hpp"





namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}
using namespace std;












int main(int argc, const char * argv[]) {

    int avail_nthreads = 1;
#ifdef _OPENMP
    avail_nthreads = omp_get_max_threads();
#endif



    int req_threads = 0;

    bool print_to_screen = 0;
    bool overwrite = 0;

    bool vort = 0;
    bool single = 0;


    std::string temporal_data_points_path = "";

    std::vector<std::string> dirs;

    std::vector<turbSpec_point> turbSpec_points;


    try
    {
        namespace po = boost::program_options;

        po::options_description desc{"Options"};
        desc.add_options()
        ("help,h", "Lots of Arguments")
        ("nthreads,n", po::value<int>(&req_threads), "Request number of OpenMP threads ")
        ("overwrite,o", po::bool_switch(&overwrite), "Overwrite files if they exist ")
        ("print,p", po::bool_switch(&print_to_screen), "Print")

        ("vort,v", po::bool_switch(&vort), "Vorticity (use center plane cut directory)")

        ("uxuyuz,u", po::bool_switch(&single), "Single Vector Files")


        //("dirs,d", po::value<std::vector<std::string>>(&dirs)->multitoken()->required(), "Directories")

        ("dirs,d", po::value<std::vector<std::string>>(&dirs)->multitoken(), "Directories")


        ("temporal_data_points_path,t", po::value<std::string>(&temporal_data_points_path), "Temporal Data Points file for Spectrum")
        ;



        po::variables_map vm;
        try {
            po::store(po::parse_command_line(argc, argv, desc), vm);

            if ( vm.count("help")  )
            {
                std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl;
                return SUCCESS;
            }

            // throws on error, so do after help in case there are any problems
            po::notify(vm);

        } catch (po::error& e) {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }

    //-------------------------------------------------------------



    int nthreads = 1;
#if _OPENMP
    if (req_threads == 0) nthreads = avail_nthreads;
    else if (req_threads > avail_nthreads) nthreads = avail_nthreads;
    else nthreads = req_threads;

    //Too many threads usually crash because of disk access
    omp_set_num_threads(nthreads);
#endif
    std::cout << "nthreads " << nthreads << std::endl;







    if (temporal_data_points_path != "")
    {
        load_temporal_spectrum(temporal_data_points_path, turbSpec_points);

        search_and_output_turbSpec_points(dirs, print_to_screen, turbSpec_points);
    }




    Input_FILES_V4 input;


    for (auto load_dir : dirs) {


        Handle_PP_Dims handle_pp;
        PP_Dims pp = handle_pp.get_from_node000_from_filepath(load_dir);

        std::string plotname = input.get_plot_type_from_directory(load_dir);



        tQvec* Q_plane[5];
        tQvec* F_plane[5];

        tQvec* rho[5];
        tQvec* ux[5];
        tQvec* uy[5];
        tQvec* uz[5];


        int num_layers = 1;
        if (vort && plotname == "rotational_capture") num_layers = 5;
        else if (vort) num_layers = 3;


        for (int layer = 0; layer < num_layers; layer++){
            Q_plane[layer] = (tQvec *)calloc(pp.total_height * pp.total_width * pp.Q_output_length, sizeof(tQvec));
            F_plane[layer] = (tForce *)calloc(pp.total_height * pp.total_width * 3, sizeof(tForce));


            rho[layer]  = (tQvec *)calloc(pp.total_height * pp.total_width, sizeof(tQvec));

            ux[layer]   = (tQvec *)calloc(pp.total_height * pp.total_width, sizeof(tQvec));
            uy[layer]   = (tQvec *)calloc(pp.total_height * pp.total_width, sizeof(tQvec));
            uz[layer]   = (tQvec *)calloc(pp.total_height * pp.total_width, sizeof(tQvec));
        }

        tQvec* uxyz_log_vort = (tQvec *)malloc(sizeof(tQvec) * pp.total_height * pp.total_width);



        input.load_plane(num_layers, load_dir, Q_plane, F_plane, pp);


        calc_rho_ux_uy_uz(num_layers, Q_plane, F_plane, rho, ux, uy, uz, pp);



        if (vort) calc_vorticity(input, load_dir, pp, ux, uxyz_log_vort, uy, uz);





        int output = 0;

        write_file_with_border(0, load_dir, "Qvec_rho.bin", rho[output], pp);

        write_file_with_border(0, load_dir, "Qvec_ux.bin", ux[output], pp);
        write_file_with_border(0, load_dir, "Qvec_uy.bin", uy[output], pp);
        write_file_with_border(0, load_dir, "Qvec_uz.bin", uz[output], pp);


        write_file_with_border(1, load_dir, "Qvec_uxyz_log_vort.bin", uxyz_log_vort, pp);






//        write_file_with_border_in_TEXT(1, load_dir, "Qvec_rho.text", rho[output], pp);
//
//        write_file_with_border_in_TEXT(1, load_dir, "Qvec_ux.text", ux[output], pp);
//        write_file_with_border_in_TEXT(1, load_dir, "Qvec_uy.text", uy[output], pp);
//        write_file_with_border_in_TEXT(1, load_dir, "Qvec_uz.text", uz[output], pp);
//
//
//        write_file_with_border_in_TEXT(1, load_dir, "Qvec_uxyz_log_vort.text", uxyz_log_vort, pp);



    }//end of dirs



}//end of main









