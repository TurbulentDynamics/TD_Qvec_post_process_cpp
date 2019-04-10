//
//  output_plots.cpp
//  stirred-tank-3d-xcode-cpp
//
//  Created by Niall P. O'Byrnes on 17/3/1.
//  Copyright © 2017 Niall P. O'Byrnes. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

#include <fstream>
#include <iostream>
#include <cfloat>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif



#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "Base_Dims.hpp"
#include "Input_FILES_V4.hpp"




template <typename tDisk>
tDisk *malloc_and_load(const Qvec_Dims &q, const std::string &qvec_path) {
    tDisk *tmp = (tDisk*)malloc(q.bin_file_size_in_structs * sizeof(tDisk));

    FILE *fp = fopen(qvec_path.c_str(), "r");
    fread(tmp, sizeof(tDisk), q.bin_file_size_in_structs, fp);
    fclose(fp);
    return tmp;
}





void Input_FILES_V4::allocate_and_orient_plane_from_filepath(const std::string plotname, PP_Dims pp, const std::string filepath, tQvec *plane, bool is_F){




    Handle_Qvec_Dims handle_q;

    if (handle_q.Qvec_json_file_exists(filepath)){

        std::cout<< "Attempting to load " << filepath << std::endl;

        Qvec_Dims q = handle_q.get_from_Qvec_filepath(filepath);



        if (q.struct_name == "tDisk_colrow_Q3_V4") Disk_colrow_Q3 = malloc_and_load<tDisk_colrow_Q3_V4>(q, filepath);
        else if (q.struct_name == "tDisk_grid_colrow_Q3_V4") Disk_grid_colrow_Q3 = malloc_and_load<tDisk_grid_colrow_Q3_V4>(q, filepath);

        else if (q.struct_name == "tDisk_colrow_Q4_V4") Disk_colrow_Q4 = malloc_and_load<tDisk_colrow_Q4_V4>(q, filepath);
        else if (q.struct_name == "tDisk_grid_colrow_Q4_V4") Disk_grid_colrow_Q4 = malloc_and_load<tDisk_grid_colrow_Q4_V4>(q, filepath);

        else if (q.struct_name == "tDisk_colrow_Q19_V4") Disk_colrow_Q19 = malloc_and_load<tDisk_colrow_Q19_V4>(q, filepath);
        else if (q.struct_name == "tDisk_grid_colrow_Q19_V4") Disk_grid_colrow_Q19 = malloc_and_load<tDisk_grid_colrow_Q19_V4>(q, filepath);

//        else if (q.struct_name == "tDisk_colrow_Q27_V4") Disk_colrow_Q27 = malloc_and_load<tDisk_colrow_Q27_V4>(q, filepath);
//        else if (q.struct_name == "tDisk_grid_colrow_Q27_V4") Disk_grid_colrow_Q27 = malloc_and_load<tDisk_grid_colrow_Q27_V4>(q, filepath);



        else std::cout << "ERROR struct not found: " << q.struct_name << std::endl;




        for (int u = 0; u < q.bin_file_size_in_structs; u++){


            if (is_F){
                tNi length = 3;
                //                std::cout << "=======" << Disk_colrow_Q3[u].s[0] << " " << Disk_colrow_Q3[u].s[1] << " " << Disk_colrow_Q3[u].s[2] << std::endl;

                if (q.struct_name == "tDisk_colrow_Q3_V4"){


                    tNi col = Disk_colrow_Q3[u].col;
                    tNi row = Disk_colrow_Q3[u].row;


                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 0] = Disk_colrow_Q3[u].s[0];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 1] = Disk_colrow_Q3[u].s[1];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 2] = Disk_colrow_Q3[u].s[2];

                }
                else if (q.struct_name == "tDisk_grid_colrow_Q3_V4"){

                    tNi col = Disk_grid_colrow_Q3[u].col;
                    tNi row = Disk_grid_colrow_Q3[u].row;

                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 0] = Disk_grid_colrow_Q3[u].s[0];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 1] = Disk_grid_colrow_Q3[u].s[1];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 2] = Disk_grid_colrow_Q3[u].s[2];

                }


            }else{

                tNi length = pp.Q_output_length;

                //                std::cout <<"%%%%%" << Disk_colrow_Q4[u].s[0] << " " << Disk_colrow_Q4[u].s[1] << " " << Disk_colrow_Q4[u].s[2] << " " << Disk_colrow_Q4[u].s[3] <<std::endl;

                if (q.struct_name == "tDisk_colrow_Q4_V4"){


                    tNi col = Disk_colrow_Q4[u].col;
                    tNi row = Disk_colrow_Q4[u].row;


                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 0] = Disk_colrow_Q4[u].s[0];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 1] = Disk_colrow_Q4[u].s[1];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 2] = Disk_colrow_Q4[u].s[2];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 3] = Disk_colrow_Q4[u].s[3];

                } else if (q.struct_name == "tDisk_grid_colrow_Q4_V4"){


                    tNi col = Disk_grid_colrow_Q4[u].col;
                    tNi row = Disk_grid_colrow_Q4[u].row;


                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 0] = Disk_grid_colrow_Q4[u].s[0];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 1] = Disk_grid_colrow_Q4[u].s[1];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 2] = Disk_grid_colrow_Q4[u].s[2];
                    plane[ twoD_colrow_len(col, row, pp.total_height, length) + 3] = Disk_grid_colrow_Q4[u].s[3];


                }

            }

        }






    }//end of for

}//end of func














bool xpath_exists(std::string path) {

    if (FILE *file = fopen(path.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


bool xfile_exists(std::string path) {
    return xpath_exists(path);
}




void Input_FILES_V4::load_plane(int num_layers, const std::basic_string<char> &load_dir, tQvec **Q_plane, tForce **F_plane, const PP_Dims &pp) {


    std::string plotname = get_plot_type_from_directory(load_dir);


    std::string dir[5] = {"", "", "", "", ""};
    std::string root[5], root_F[5];


    if (plotname == "rotational_capture") {
        dir[0] = load_dir; root[0] = "Qvec"; root_F[0] = "Qvec.F3";

        dir[1] = load_dir; root[1] = "Qvec.im1"; root_F[1] = "Qvec.F3.im1";
        dir[2] = load_dir; root[2] = "Qvec.ip1"; root_F[2] = "Qvec.F3.ip1";

        dir[3] = load_dir; root[3] = "Qvec.km1"; root_F[3] = "Qvec.F3.km1";
        dir[4] = load_dir; root[4] = "Qvec.kp1"; root_F[4] = "Qvec.F3.kp1";

    } else {

        dir[0] = load_dir;                    root[0] = "Qvec"; root_F[0] = "Qvec.F3";
        dir[1] = get_dir_delta(-1, load_dir); root[1] = "Qvec"; root_F[1] = "Qvec.F3";
        dir[2] = get_dir_delta(+1, load_dir); root[2] = "Qvec"; root_F[2] = "Qvec.F3";
    }





#pragma omp parallel for collapse(3) schedule(dynamic)
    for (int idi = 0; idi < pp.ngx; idi++){
        for (int idj = 0; idj < pp.ngy; idj++){
            for (int idk = 0; idk < pp.ngz; idk++){


                for (int layer = 0; layer < num_layers; layer++){



                    std::string Qvec_filepath = get_Qvec_filename(dir[layer], root[layer], idi, idj, idk);

                    std::string F_filepath = get_Qvec_filename(dir[layer], root_F[layer], idi, idj, idk);


                    //                    std::cout<<__func__ << " func trying "<< " " << Qvec_filepath << std::endl;


                    if (xfile_exists(Qvec_filepath)) {


                        allocate_and_orient_plane_from_filepath(plotname, pp, Qvec_filepath, Q_plane[layer]);

                    }
                    if (xfile_exists(F_filepath)) {

                        bool is_F = true;
                        allocate_and_orient_plane_from_filepath(plotname, pp, F_filepath, F_plane[layer], is_F);


                    }
                    //                    else {
                    //                        std::cout << "file " << Qvec_filepath << " or " << F_filepath << " does not exist." << std::endl;
                    //                    }




                }//end of layer

            }}}



}









