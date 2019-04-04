//
//  Grid_Dims.hpp
//  lb-halo-3dmpi
//
//  Created by Nile Ó Broin on 07/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "json.h"



#include "PostProcessing_Dims.hpp"









PP_Dims Handle_PP_Dims::get_from_json_filepath(const std::string filepath){

    PP_Dims d;

    try
    {
        std::ifstream in(filepath.c_str());
        Json::Value dim_json;
        in >> dim_json;


        d.func = dim_json["function"].asString();
        d.dirname = dim_json["dirname"].asString();
        d.cut_at = (tNi)dim_json["cut_at"].asInt();
        d.Q_output_length = (int)dim_json["Q_output_length"].asInt();
        d.note = dim_json["note"].asString();


        d.ngx = (t3d)dim_json["ngx"].asInt();
        d.ngy = (t3d)dim_json["ngy"].asInt();
        d.ngz = (t3d)dim_json["ngz"].asInt();


        d.grid_x = (tNi)dim_json["grid_x"].asInt();
        d.grid_y = (tNi)dim_json["grid_y"].asInt();
        d.grid_z = (tNi)dim_json["grid_z"].asInt();


        d.file_height = (tNi)dim_json["file_height"].asInt();
        d.file_width = (tNi)dim_json["file_width"].asInt();
        d.total_height = (tNi)dim_json["total_height"].asInt();
        d.total_width = (tNi)dim_json["total_width"].asInt();


        d.step = (tStep)dim_json["step"].asInt();
        d.teta = (tGeomShape)dim_json["teta"].asDouble();


        d.initial_rho = (tQvec)dim_json["initial_rho"].asDouble();
        d.re_m_nondimensional = (tQvec)dim_json["re_m_nondimensional"].asDouble();
        d.uav = (tGeomShape)dim_json["uav"].asDouble();

        in.close();

        return d;
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
        return d;
    }
}



int Handle_PP_Dims::save_json_to_filepath(const std::string filepath){
    try
    {
        Json::Value dim_json;

        dim_json["name"] = get_name();

        dim_json["function"] = dim.func;
        dim_json["dirname"] = dim.dirname;
        dim_json["cut_at"] = (int)dim.cut_at;
        dim_json["Q_output_length"] = (int)dim.Q_output_length;


        dim_json["note"] = dim.note;


        dim_json["ngx"] = (int)dim.ngx;
        dim_json["ngy"] = (int)dim.ngy;
        dim_json["ngz"] = (int)dim.ngz;

        dim_json["grid_x"] = (int)dim.grid_x;
        dim_json["grid_y"] = (int)dim.grid_y;
        dim_json["grid_z"] = (int)dim.grid_z;


        dim_json["file_height"] = (int)dim.file_height;
        dim_json["file_width"] = (int)dim.file_width;
        dim_json["total_height"] = (int)dim.total_height;
        dim_json["total_width"] = (int)dim.total_width;


        dim_json["step"] = (int)dim.step;
        dim_json["teta"] = (double)dim.teta;


        dim_json["initial_rho"] = (double)dim.initial_rho;
        dim_json["re_m_nondimensional"] = (double)dim.re_m_nondimensional;
        dim_json["uav"] = (double)dim.uav;


        std::ofstream out(filepath.c_str(), std::ofstream::out);
        out << dim_json;
        out.close();

        return 0;
    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
        return 1;
    }
    return 0;
}




void Handle_PP_Dims::print(){
    std:: cout
    << " name:" << get_name()
    << " func:" << dim.func
    << " dirname:" << dim.dirname
    << " cut_at:" << dim.cut_at
    << " note:" << dim.note
    << " Q_output_length:" << dim.Q_output_length


    << " ngx:" << dim.ngx
    << " ngx:" << dim.ngy
    << " ngx:" << dim.ngz

    << " grid_x:" << dim.grid_x
    << " grid_y:" << dim.grid_y
    << " grid_z:" << dim.grid_z

    << " file_height:" << dim.file_height
    << " file_width:" << dim.file_width
    << " total_height:" << dim.total_height
    << " total_width:" << dim.total_width

    << " step:" << dim.step
    << " teta:" << dim.teta


    << " initial_rho:" << dim.initial_rho
    << " re_m_nondimensional:" << dim.re_m_nondimensional
    << " uav:" << dim.uav

    << std::endl;
}






PostProcess_Data_V3 Handle_PP_Dims::read_Qvec_pp_dim_V3(const std::string dir, tGeomShape *teta) {

    //Deprecated, however many files exist in tape archive of this type

    PostProcess_Data_V3 q;


    //TODO Change to std::string
    char filename_PP[200];
    sprintf(filename_PP, "%s/pp_dim.0.0.0.V3.bin", dir.c_str());
    FILE *fp_Qvec_PP = fopen(filename_PP, "r");



    float unused_float = 0.0f;
    int unused_int = 0;

    //Size of file
    fread(&q.file_height, sizeof(long int), 1, fp_Qvec_PP);
    fread(&q.file_width, sizeof(long int), 1, fp_Qvec_PP);

    //The size of the full slice/axis
    fread(&q.total_height, sizeof(long int), 1, fp_Qvec_PP);
    fread(&q.total_width, sizeof(long int), 1, fp_Qvec_PP);



    fread(teta, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);
    fread(&unused_float, sizeof(float), 1, fp_Qvec_PP);



    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&q.half_float, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);
    fread(&unused_int, sizeof(int), 1, fp_Qvec_PP);


    fclose(fp_Qvec_PP);

    q.matrix_size = (q.total_height) * (q.total_width);

    return q;
}










