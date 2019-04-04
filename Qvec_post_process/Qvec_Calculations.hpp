//
//  main_Qvec_pp.cpp
//  TD-Qvec-post-process
//
//  Created by Nile Ó Broin on 02/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef Qvec_Calculations_hpp
#define Qvec_Calculations_hpp


#include <fstream>
#include <sstream>
#include <iostream>


#include <vector>
#include <string>



#include "define_typealias.h"
#include "define_datastructures.hpp"



#include "Input_FILES_V4.hpp"
#include "PostProcessing_Dims.hpp"
#include "Inline.hpp"





void calc_vorticity(Input_FILES_V4 &input, const std::basic_string<char> &load_dir, const PP_Dims &pp, tQvec **ux, tQvec *uxyz_log_vort, tQvec **uy, tQvec **uz);




void calc_rho_ux_uy_uz(int num_layers, tQvec **Q_plane, tForce **F_plane, tQvec **rho, tQvec **ux, tQvec **uy, tQvec **uz, const PP_Dims &pp);



void write_file_with_border(tNi b, std::string dir, std::string filename, tQvec *data, const PP_Dims &pp);


void write_file_with_border_in_TEXT(tNi b, std::string dir, std::string filename, tQvec *data, const PP_Dims &pp);






#endif
