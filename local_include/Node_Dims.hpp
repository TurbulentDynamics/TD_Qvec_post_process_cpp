//
//  Header.h
//  TD_GeomInput_Rushton_Turbine
//
//  Created by Nile Ó Broin on 13/02/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef Node_Dims_hpp
#define Node_Dims_hpp


#include "define_typealias.h"





struct Node_Dims
{

    t3d idi = 0;
    t3d idj = 0;
    t3d idk = 0;

    int node000 = 0;
    int ncpu = 0;
    int rank = 0;

    int nthreads = 0;
    int numprocs = 0;

    tNi x = 0;
    tNi y = 0;
    tNi z = 0;

};


#endif /* Header_h */
