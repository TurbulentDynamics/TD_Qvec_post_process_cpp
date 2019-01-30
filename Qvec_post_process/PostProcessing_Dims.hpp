//
//  define_datastructures.h
//  stirred-tank-3d-xcode-cpp
//
//  Created by Nile Ó Broin on 08/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef PP_Dims_hpp
#define PP_Dims_hpp

#include <stdlib.h>



#include "define_typealias.h"

#include "Base_Dims.hpp"




struct PP_Dims {


    std::string func = "";
    std::string dirname = "";
    tNi cut_at = 0;
    int Q_output_length = 0;


    std::string note = "";


    t3d ngx = 0;
    t3d ngy = 0;
    t3d ngz = 0;

    tNi grid_x = 0;
    tNi grid_y = 0;
    tNi grid_z = 0;


    tNi file_height = 0;
    tNi file_width = 0;
    tNi total_height = 0;
    tNi total_width = 0;


    tStep step = 0;
    tGeomShape teta = 0;


    tFlow initial_rho = 0;
    tFlow Re_m_nondimensional = 0;
    tGeomShape uav = 0;



};







struct PostProcess_Data_V3 {
    tNi total_height, total_width;
    tNi file_height, file_width;

    tNi matrix_size;

    int save_ijk_grid, save_row_cols;
    int half_float;

    tFlow nu;
    tGeomShape uav;
};








class Handle_PP_Dims: public Base_Dims<PP_Dims>{
private:
    std::string get_name(){return "Post_Processing_Dims";}

public:
    Handle_PP_Dims(){}

    Handle_PP_Dims(PP_Dims _dim)
    {
        dim = _dim;
    }


    void set_dims(t3d ngx, t3d ngy, t3d ngz, tNi x, tNi y, tNi z){

        dim.ngx = ngx;
        dim.ngy = ngy;
        dim.ngz = ngz;

        dim.grid_x = x;
        dim.grid_y = y;
        dim.grid_z = z;
    }


    void set_height_width(tNi file_height, tNi file_width, tNi total_height, tNi total_width){
        dim.file_height = file_height;
        dim.file_width = file_width;
        dim.total_height = total_height;
        dim.total_width = total_width;
    }


    void set_running(tStep step, tGeomShape teta){
        dim.teta = teta;
        dim.step = step;
    }

    
    void set_flow(tFlow initial_rho, tFlow Re_m_nondimensional, tGeomShape uav){
        dim.initial_rho = initial_rho;
        dim.Re_m_nondimensional = Re_m_nondimensional;
        dim.uav = uav;
    }


    void set_note(const std::string note){
        dim.note = note;
    }



    void set_plot(const std::string func, const std::string dirname, int Q_output_length = 4, tNi cut_at = 0){
        dim.func = func;
        dim.dirname = dirname;
        dim.cut_at = cut_at;
        dim.Q_output_length = Q_output_length;
    }





    PP_Dims get_from_json_filepath(const std::string filepath);
    int save_json_to_filepath(const std::string filepath);
    void print();



    PostProcess_Data_V3 read_Qvec_pp_dim_V3(const std::string dir, tGeomShape *teta);



//    PostProcess_Data_V3 read_Qvec_header_V3(bool print, const std::string dir,
//                                          const std::string filename, FILE *fp_Qvec, Grid_Dims *grid);



};




#endif   /*  PP_Dims_hpp  */
