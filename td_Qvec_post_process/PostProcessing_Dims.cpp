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

#include <boost/property_tree/json_parser.hpp>



#include "PostProcessing_Dims.hpp"












PP_Dims Handle_PP_Dims::get_from_json_filepath(const std::string filepath){

    PP_Dims d;

    try
    {
        boost::property_tree::ptree jsontree;
        boost::property_tree::read_json(filepath.c_str(), jsontree);

        d.func = jsontree.get<std::string>("func", "");
        d.dirname = jsontree.get<std::string>("dirname", "");
        d.cut_at = jsontree.get<tNi>("cut_at", 0);
        d.Q_output_length = jsontree.get<int>("Q_output_length", 0);
        d.note = jsontree.get<std::string>("note", "");


        d.ngx = jsontree.get<t3d>("ngx", 0);
        d.ngy = jsontree.get<t3d>("ngy", 0);
        d.ngz = jsontree.get<t3d>("ngz", 0);

        d.grid_x = jsontree.get<tNi>("grid_x", 0);
        d.grid_y = jsontree.get<tNi>("grid_y", 0);
        d.grid_z = jsontree.get<tNi>("grid_z", 0);


        d.file_height = jsontree.get<tNi>("file_height", 0);
        d.file_width = jsontree.get<tNi>("file_width", 0);
        d.total_height = jsontree.get<tNi>("total_height", 0);
        d.total_width = jsontree.get<tNi>("total_width", 0);

        d.step = jsontree.get<tStep>("step", 0);
        d.teta = jsontree.get<tGeomShape>("teta", 0);


        d.initial_rho = jsontree.get<tFlow>("initial_rho", 0);
        d.Re_m_nondimensional = jsontree.get<tFlow>("Re_m_nondimensional", 0);
        d.uav = jsontree.get<tGeomShape>("uav", 0);


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

        boost::property_tree::ptree jsontree;
        jsontree.put<std::string>("name", get_name());
        jsontree.put<std::string>("func", dim.func);
        jsontree.put<std::string>("dirname", dim.dirname);
        jsontree.put<tNi>("cut_at", dim.cut_at);
        jsontree.put<tNi>("Q_output_length", dim.Q_output_length);


        jsontree.put<std::string>("note", dim.note);


        jsontree.put<t3d>("ngx", dim.ngx);
        jsontree.put<t3d>("ngy", dim.ngy);
        jsontree.put<t3d>("ngz", dim.ngz);

        jsontree.put<tNi>("grid_x", dim.grid_x);
        jsontree.put<tNi>("grid_y", dim.grid_y);
        jsontree.put<tNi>("grid_z", dim.grid_z);



        
        jsontree.put<tNi>("file_height", dim.file_height);
        jsontree.put<tNi>("file_width", dim.file_width);
        jsontree.put<tNi>("total_height", dim.total_height);
        jsontree.put<tNi>("total_width", dim.total_width);

        jsontree.put<tStep>("step", dim.step);
        jsontree.put<tGeomShape>("teta", dim.teta);


        jsontree.put<tFlow>("initial_rho", dim.initial_rho);
        jsontree.put<tGeomShape>("Re_m_nondimensional", dim.Re_m_nondimensional);
        jsontree.put<tGeomShape>("uav", dim.uav);




        boost::property_tree::write_json(filepath.c_str(), jsontree);
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
    << " Re_m_nondimensional:" << dim.Re_m_nondimensional
    << " uav:" << dim.uav

    << std::endl;
}






PostProcess_Data_V3 Handle_PP_Dims::read_Qvec_pp_dim_V3(const std::string dir, tGeomShape *teta) {

    //Deprecated, however many files exist in archive of this type

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










