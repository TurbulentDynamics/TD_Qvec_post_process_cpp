//
//  main_Qvec_pp.cpp
//  TD-Qvec-post-process
//
//  Created by Nile Ó Broin on 02/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef Turb_Spec_hpp
#define Turb_Spec_hpp


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


struct turbSpec_point {
    std::string name = "";
    int i = 0;
    int j = 0;
    int k = 0;
};


void search_and_output_turbSpec_points(const std::vector<std::string> &dirs, bool print_to_screen, const std::vector<turbSpec_point> &turbSpec_points);


void load_temporal_spectrum(const std::string &temporal_data_points_path, std::vector<turbSpec_point> &turbSpec_points);



#endif
