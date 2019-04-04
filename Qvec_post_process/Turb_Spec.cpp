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

#include "json.h"



#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "PostProcessing_Dims.hpp"
#include "Inline.hpp"
#include "Qvec_Calculations.hpp"
#include "Turb_spec.hpp"





void load_temporal_spectrum(const std::string &temporal_data_points_path, std::vector<turbSpec_point> &turbSpec_points) {


    if (temporal_data_points_path != ""){

        //If the turb spec points were saved as a json file during running


        std::ifstream in(temporal_data_points_path.c_str());
        Json::Value dim_json;
        in >> dim_json;
        in.close();


        for( Json::Value::const_iterator itr = dim_json.begin() ; itr != dim_json.end() ; itr++ ) {

            turbSpec_point pt;
            pt.name = itr.key().asString();
            pt.i = (*itr)["i"].asInt();
            pt.j = (*itr)["j"].asInt();
            pt.k = (*itr)["k"].asInt();


            turbSpec_points.push_back(pt);

        }

        
    }
}




void search_and_output_turbSpec_points(const std::vector<std::string> &dirs, bool print_to_screen, const std::vector<turbSpec_point> &turbSpec_points) {


    if (turbSpec_points.size() == 0) {
        std::cout << "No points loaded" << std::endl;
    }



    for (const auto& p : turbSpec_points) {

        //starts new file, ie wipes out the old one.
        std::ofstream outfile;
        outfile.open(p.name, std::ios_base::out);
        outfile << "filename:" << p.name << std::endl;
        outfile << " i:" << p.i << " j:" << p.j << " k:" << p.k << std::endl;
        outfile << std::endl;
        outfile << std::endl;
        outfile.close();
    }



    Input_FILES_V4 input;



    for (auto load_dir : dirs) {

        std::cout << "Looking for points in " << load_dir << std::endl;

        Handle_PP_Dims handle_pp;
        PP_Dims pp = handle_pp.get_from_node000_from_filepath(load_dir);



        tQvec* plane = (tQvec *)malloc(sizeof(tQvec) * pp.total_height * pp.total_width * pp.Q_output_length);



        for (int idi = 0; idi < pp.ngx; idi++){
            for (int idj = 0; idj < pp.ngy; idj++){
                for (int idk = 0; idk < pp.ngz; idk++){


                    Node_Dims xnode;
                    xnode.idi = idi;
                    xnode.idj = idj;
                    xnode.idk = idk;
                    Grid_Dims grid;


                    Node_Bounds nb = get_node_bounds(xnode, grid);


                    std::string Qvec_filepath = input.get_Qvec_filename(load_dir, "Qvec", idi, idj, idk);


                    std::vector<turbSpec_point> points_in_file;
                    for (const auto& p : turbSpec_points) {
                        if (grid_ijk_on_node(p.i, p.j, p.k, nb)) {

                            points_in_file.push_back(p);

                            if (print_to_screen) std::cout << Qvec_filepath << " should have point " << p.i << " " << p.j << " " << p.k << std::endl;

                        }
                    }

                    if (points_in_file.size() == 0) continue;



                    if (print_to_screen) std::cout << "Attempting to load " << Qvec_filepath << std::endl;



                    //axis
//                    input.allocate_and_orient_plane_from_filepath("XZplane", pp, Qvec_filepath, plane);


                }}}



        for (const auto& p : turbSpec_points) {


            std::ofstream outfile;

            //appends to file
            outfile.open(p.name, std::ios_base::app);

            //p.j should be constant

            tNi pos = p.i * (pp.total_height * 4) + p.k * 4;


            outfile << pp.step << "," << std::scientific << plane[pos + 1] << "," << plane[pos + 2] << "," << plane[pos + 3] << std::endl;

            outfile.close();


            if (print_to_screen) {
                tQvec rho = plane[ pos + 0];
                std::cout << p.name << "  " << "  q1 " << plane[ pos + 1]/rho <<"  q2 " << plane[ pos + 2]/rho <<"  q3 " << plane[ pos + 3]/rho << std::endl;
            }

        }//end of if points


    }//end of load dirs


}










