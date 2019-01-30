//
//  Header.h
//  stirred-tank-3d-xcode-cpp
//
//  Created by Niall P. O'Byrnes on 16/22/11.
//  Copyright © 2016 Niall P. O'Byrnes. All rights reserved.
//

#ifndef define_typealias_h
#define define_typealias_h




//Indexing for the N matrix
typedef long int tNi;
typedef const long int let_tNi;



typedef float tNvec;
#define tNvec_MPI_TYPE MPI_FLOAT
typedef float tForce;
#define tForce_MPI_TYPE MPI_FLOAT




//The flow parameters
typedef float tFlow;
typedef const float let_tFlow;


//The 3d parameters
typedef int t3d;
typedef const int let_t3d;

#define t3d_pTYPE %lu


//Type for the Geometry Properties
typedef float tGeomShape;
typedef const float let_tGeomShape;


//type for Geom indexing
typedef long int tGeomIndex;


//The stepping vars
typedef  int tStep;



//#define M_PI       3.14159265358979323846  /* pi */
//#define M_PIl      3.141592653589793238462643383279502884L /* pi */
//#define ULONG_MAX    18446744073709551615UL



#endif /* define_typealias_h */

