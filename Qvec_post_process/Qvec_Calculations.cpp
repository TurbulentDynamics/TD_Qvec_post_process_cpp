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




#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "PostProcessing_Dims.hpp"
#include "Inline.hpp"
#include "Qvec_Calculations.hpp"





void write_file_with_border(tNi b, std::string dir, std::string filename, tQvec *data, const PP_Dims &pp) {

    std::string filepath = dir + "/" + filename;

    FILE *fp_output = fopen(filepath.c_str(), "wb");

    std::cout << "WRITING FILE " << filepath << std::endl;




    //TODO Should just write whole file directly from memory
    for (tNi col = b; col < pp.total_width-b; col++){

        for (tNi row = b; row < pp.total_height-b; row++){



            fwrite(&data[ twoD_colrow(col, row, pp.total_height) ], sizeof(tQvec), 1, fp_output);

        }}



    fclose(fp_output);
}



void write_file_with_border_in_TEXT(tNi b, std::string dir, std::string filename, tQvec *data, const PP_Dims &pp) {


    std::string filepath = dir + "/" + filename;

    std::cout << "WRITING TEXT  FILE " << filepath << std::endl;


    std::ofstream myfile;
    myfile.open (filepath);



    //TODO Should just write whole file directly from memory
    for (tNi col = b; col < pp.total_width-b; col++){

        for (tNi row = b; row < pp.total_height-b; row++){

            myfile << data[ twoD_colrow(col, row, pp.total_height) ] << ", ";

        }
        myfile << std::endl;
    }



    myfile.close();
}



inline void calc_XY_vorticity(tNi c, tNi r, tNi h, tQvec **ux, tQvec **uy, tQvec **uz, tQvec *uxyz_log_vort,
    tQvec &uxx, tQvec &uxy, tQvec &uxz, tQvec &uyx, tQvec &uyy, tQvec &uyz, tQvec &uzx, tQvec &uzy, tQvec &uzz) {


            uxx = 0.5*(ux[0][twoD_colrow(c+1, r  , h)] - ux[0][twoD_colrow(c-1, r  , h)]);
            uxy = 0.5*(ux[0][twoD_colrow(c  , r+1, h)] - ux[0][twoD_colrow(c  , r-1, h)]);
            uxz = 0.5*(ux[2][twoD_colrow(c  , r  , h)] - ux[1][twoD_colrow(c  , r  , h)]);

            uyx = 0.5*(uy[0][twoD_colrow(c+1, r  , h)] - uy[0][twoD_colrow(c-1, r  , h)]);
            uyy = 0.5*(uy[0][twoD_colrow(c  , r+1, h)] - uy[0][twoD_colrow(c  , r-1, h)]);
            uyz = 0.5*(uy[2][twoD_colrow(c  , r  , h)] - uy[1][twoD_colrow(c  , r  , h)]);

            uzx = 0.5*(uz[0][twoD_colrow(c+1, r  , h)] - uz[0][twoD_colrow(c-1, r  , h)]);
            uzy = 0.5*(uz[0][twoD_colrow(c  , r+1, h)] - uz[0][twoD_colrow(c  , r-1, h)]);
            uzz = 0.5*(uz[2][twoD_colrow(c  , r  , h)] - uz[1][twoD_colrow(c  , r  , h)]);
}



inline void calc_XZ_vorticity(tNi c, tNi r, tNi h, tQvec **ux, tQvec **uy, tQvec **uz, tQvec *uxyz_log_vort,
    tQvec &uxx, tQvec &uxy, tQvec &uxz, tQvec &uyx, tQvec &uyy, tQvec &uyz, tQvec &uzx, tQvec &uzy, tQvec &uzz) {

            uxx = 0.5*(ux[0][twoD_colrow(c+1, r  , h)] - ux[0][twoD_colrow(c-1, r  , h)]);
            uxy = 0.5*(ux[2][twoD_colrow(c  , r  , h)] - ux[1][twoD_colrow(c  , r  , h)]);
            uxz = 0.5*(ux[0][twoD_colrow(c  , r+1, h)] - ux[0][twoD_colrow(c  , r-1, h)]);

            uyx = 0.5*(uy[0][twoD_colrow(c+1, r  , h)] - uy[0][twoD_colrow(c-1, r  , h)]);
            uyy = 0.5*(uy[2][twoD_colrow(c  , r  , h)] - uy[1][twoD_colrow(c  , r  , h)]);
            uyz = 0.5*(uy[0][twoD_colrow(c  , r+1, h)] - uy[0][twoD_colrow(c  , r-1, h)]);

            uzx = 0.5*(uz[0][twoD_colrow(c+1, r  , h)] - uz[0][twoD_colrow(c-1, r  , h)]);
            uzy = 0.5*(uz[2][twoD_colrow(c  , r  , h)] - uz[1][twoD_colrow(c  , r  , h)]);
            uzz = 0.5*(uz[0][twoD_colrow(c  , r+1, h)] - uz[0][twoD_colrow(c  , r-1, h)]);
}



inline void calc_YZ_vorticity(tNi c, tNi r, tNi h, tQvec **ux, tQvec **uy, tQvec **uz, tQvec *uxyz_log_vort,
      tQvec &uxx, tQvec &uxy, tQvec &uxz, tQvec &uyx, tQvec &uyy, tQvec &uyz, tQvec &uzx, tQvec &uzy, tQvec &uzz) {

            uxx = 0.5*(ux[2][twoD_colrow(c  , r  , h)] - ux[1][twoD_colrow(c  , r  , h)]);
            uxy = 0.5*(ux[0][twoD_colrow(c, r+1  , h)] - ux[0][twoD_colrow(c,   r-1, h)]);
            uxz = 0.5*(ux[0][twoD_colrow(c+1  , r, h)] - ux[0][twoD_colrow(c-1, r,   h)]);

            uyx = 0.5*(uy[2][twoD_colrow(c  , r  , h)] - uy[1][twoD_colrow(c  , r  , h)]);
            uyy = 0.5*(uy[0][twoD_colrow(c  , r+1, h)] - uy[0][twoD_colrow(c  , r-1, h)]);
            uyz = 0.5*(uy[0][twoD_colrow(c+1, r  , h)] - uy[0][twoD_colrow(c-1, r  , h)]);

            uzx = 0.5*(uz[2][twoD_colrow(c  , r  , h)] - uz[1][twoD_colrow(c  , r  , h)]);
            uzy = 0.5*(uz[0][twoD_colrow(c  , r+1, h)] - uz[0][twoD_colrow(c  , r-1, h)]);
            uzz = 0.5*(uz[0][twoD_colrow(c+1, r  , h)] - uz[0][twoD_colrow(c-1, r  , h)]);

}





inline void calc_ROTATIONAL_vorticity(tNi c, tNi r, tNi h, tQvec **ux, tQvec **uy, tQvec **uz, tQvec *uxyz_log_vort, tQvec &uxx, tQvec &uxy, tQvec &uxz, tQvec &uyx, tQvec &uyy, tQvec &uyz, tQvec &uzx, tQvec &uzy, tQvec &uzz) {


//col is i
//    row is z or y depending


//    dir[0] = load_dir; root[0] = "Qvec";
//
//    dir[1] = load_dir; root[1] = "Qvec.im1";
//    dir[2] = load_dir; root[2] = "Qvec.ip1";
//
//    dir[3] = load_dir; root[3] = "Qvec.km1";
//    dir[4] = load_dir; root[4] = "Qvec.kp1";



    uxx = 0.5*(ux[2][twoD_colrow(c,   r  , h)] - ux[1][twoD_colrow(c,   r  , h)]);
    uxy = 0.5*(ux[0][twoD_colrow(c,   r+1, h)] - ux[0][twoD_colrow(c,   r-1, h)]);
    uxz = 0.5*(ux[4][twoD_colrow(c,   r  , h)] - ux[3][twoD_colrow(c  , r  , h)]);

    uyx = 0.5*(uy[2][twoD_colrow(c,   r  , h)] - uy[1][twoD_colrow(c,   r  , h)]);
    uyy = 0.5*(uy[0][twoD_colrow(c,   r+1, h)] - uy[0][twoD_colrow(c,   r-1, h)]);
    uyz = 0.5*(uy[4][twoD_colrow(c  , r  , h)] - uy[3][twoD_colrow(c  , r  , h)]);


    uzx = 0.5*(uz[2][twoD_colrow(c,   r  , h)] - uz[1][twoD_colrow(c,   r  , h)]);
    uzy = 0.5*(uz[0][twoD_colrow(c,   r+1, h)] - uz[0][twoD_colrow(c,   r-1, h)]);
    uzz = 0.5*(uz[4][twoD_colrow(c  , r  , h)] - uz[3][twoD_colrow(c  , r  , h)]);


}





void calc_vorticity(Input_FILES_V4 &input, const std::basic_string<char> &load_dir, const PP_Dims &pp, tQvec **ux, tQvec *uxyz_log_vort, tQvec **uy, tQvec **uz) {


    tNi h = pp.total_height;

    std::string plotname = input.get_plot_type_from_directory(load_dir);


    for (tNi c = 1; c < pp.total_width; c++){

        for (tNi r = 1; r < pp.total_height; r++){

            tQvec uxx, uxy, uxz = 0.0;

            tQvec uyx, uyy, uyz = 0.0;

            tQvec uzx, uzy, uzz = 0.0;




            if (plotname == "XYplane")      calc_XY_vorticity(c, r, h, ux, uy, uz, uxyz_log_vort,
                                                              uxx, uxy, uxz, uyx, uyy, uyz, uzx, uzy, uzz);


            else if (plotname == "XZplane") calc_XZ_vorticity(c, r, h, ux, uy, uz, uxyz_log_vort,
                                                              uxx, uxy, uxz, uyx, uyy, uyz, uzx, uzy, uzz);


            else if (plotname == "YZplane") calc_YZ_vorticity(c, r, h, ux, uy, uz, uxyz_log_vort,
                                                              uxx, uxy, uxz, uyx, uyy, uyz, uzx, uzy, uzz);




            else if (plotname == "rotational_capture") calc_ROTATIONAL_vorticity(c, r, h, ux, uy, uz, uxyz_log_vort, uxx, uxy, uxz, uyx, uyy, uyz, uzx, uzy, uzz);


            
            else {
                std::cout << "Cant deal with: " << plotname << std::endl;
                return;
            }

            tQvec uyz_uzy = uyz - uzy;
            tQvec uzx_uxz = uzx - uxz;
            tQvec uxy_uyx = uxy - uyx;

            uxyz_log_vort[ twoD_colrow(c, r, h)] = logf(uyz_uzy * uyz_uzy + uzx_uxz * uzx_uxz + uxy_uyx * uxy_uyx);

        }}


}





void calc_rho_ux_uy_uz(int num_layers, tQvec **Q_plane, tForce **F_plane, tQvec **rho, tQvec **ux, tQvec **uy, tQvec **uz, const PP_Dims &pp) {


    for (int layer = 0; layer < num_layers; layer++){


        for (tNi col = 0; col <= pp.total_width; col++){
            for (tNi row = 0; row <= pp.total_height; row++){


                tNi posPQ = twoD_colrow_len(col, row, pp.total_height, pp.Q_output_length);
                tNi posPF = twoD_colrow_len(col, row, pp.total_height, 3);


                tNi pos = twoD_colrow(col, row, pp.total_height);



                rho[layer][pos] = Q_plane[layer][posPQ + 0];

                
                ux[layer][pos] = (Q_plane[layer][posPQ + 1] + 0.5 * F_plane[layer][posPF + 0]) / rho[layer][pos];
                uy[layer][pos] = (Q_plane[layer][posPQ + 2] + 0.5 * F_plane[layer][posPF + 1]) / rho[layer][pos];
                uz[layer][pos] = (Q_plane[layer][posPQ + 3] + 0.5 * F_plane[layer][posPF + 2]) / rho[layer][pos];

//                    std::cout << "calc_rho_ux_uy_uz  " << plane[layer][posPl + 0] << "  rho[]  " << rho[layer][pos] << std::endl;

            }}
    }
}








