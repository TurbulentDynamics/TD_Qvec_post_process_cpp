//
//  Inline.hpp
//  stirred-tank-3d-xcode-cpp
//
//  Created by Niall P. O'Byrnes on 17/17/4.
//  Copyright © 2017 Niall P. O'Byrnes. All rights reserved.
//

#ifndef Inline_hpp
#define Inline_hpp

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>


#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "Grid_Dims.hpp"
#include "Node_Dims.hpp"







inline bool cmpf(float A, float B, float epsilon = 0.05f)
{
    return (fabs(A - B) < epsilon);
}






inline tNi twoD_colrow(tNi col, tNi row, tNi height)
{
    return col * height + row;

}

inline tNi twoD_colrow_len(tNi col, tNi row, tNi height, tNi len){

    return col * height * len + row * len;
}











inline bool grid_ijk_on_node(tNi gi, tNi gj, tNi gk, Node_Bounds f){

    if (gi >= f.i0 && gi <= f.i1 && gj >= f.j0 && gj <= f.j1 && gk >= f.k0 && gk <= f.k1) return 1;

    return 0;

}




inline Node_Bounds get_node_bounds(const Node_Dims node, const Grid_Dims grid){

    Node_Bounds ret;

    ret.i0 = (node.x * (tNi)node.idi);
    if (node.idi>0) ret.i0 += 1;

    ret.i1 = (node.x * (tNi)node.idi + node.x);
    if (node.idi == grid.ngx-1) ret.i1 += 1;


    ret.j0 = (node.y * (tNi)node.idj);
    if (node.idj>0) ret.j0 += 1;

    ret.j1 = (node.y * (tNi)node.idj + node.y);
    if (node.idj == grid.ngy-1) ret.j1 += 1;


    ret.k0 = (node.z * (tNi)node.idk);
    if (node.idk > 0) ret.k0 += 1;

    ret.k1 = (node.z * (tNi)node.idk + node.z);
    if (node.idk == grid.ngz - 1) ret.k1 += 1;

    return ret;
}


#endif /* Inline_External_h */

