//
//  Grid_Dims.hpp
//  lb-halo-3dmpi
//
//  Created by Nile Ó Broin on 08/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include "json.h"


#include "define_typealias.h"

#include "Base_Dims.hpp"
#include "Qvec_Dims.hpp"








Qvec_Dims Handle_Qvec_Dims::get_from_json_filepath(const std::string filepath){


    Qvec_Dims d;

    try
    {
        std::ifstream in(filepath.c_str());
        Json::Value dim_json;
        in >> dim_json;


        d.grid_x = (tNi)dim_json["grid_x"].asInt();
        d.grid_y = (tNi)dim_json["grid_y"].asInt();
        d.grid_z = (tNi)dim_json["grid_z"].asInt();

        d.ngx = (t3d)dim_json["ngx"].asInt();
        d.ngy = (t3d)dim_json["ngy"].asInt();
        d.ngz = (t3d)dim_json["ngz"].asInt();

        d.idi = (t3d)dim_json["idi"].asInt();
        d.idj = (t3d)dim_json["idj"].asInt();
        d.idk = (t3d)dim_json["idk"].asInt();


        d.struct_name = dim_json["struct_name"].asString();
        d.bin_file_size_in_structs = dim_json["bin_file_size_in_structs"].asUInt64();


        d.coords_type = dim_json["coords_type"].asString();
        d.has_grid_coords = dim_json["has_grid_coords"].asBool();
        d.has_col_row_coords = dim_json["has_col_row_coords"].asBool();


        d.Q_data_type = dim_json["Q_data_type"].asString();
        d.Q_output_length = (t3d)dim_json["Q_output_length"].asInt();


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





//template <class Tpos, class Tdata>
int Handle_Qvec_Dims::save_json_to_Qvec_filepath(const std::string qvec_filepath){

    std::string json_filepath = get_json_filepath_from_Qvec_filepath(qvec_filepath);

    try
    {
        Json::Value dim_json;

        dim_json["name"] = get_name();

        dim_json["grid_x"] = (int)dim.grid_x;
        dim_json["grid_y"] = (int)dim.grid_y;
        dim_json["grid_z"] = (int)dim.grid_z;


        dim_json["ngx"] = (int)dim.ngx;
        dim_json["ngy"] = (int)dim.ngy;
        dim_json["ngz"] = (int)dim.ngz;

        dim_json["idi"] = (int)dim.idi;
        dim_json["idj"] = (int)dim.idj;
        dim_json["idk"] = (int)dim.idk;


        dim_json["struct_name"] = dim.struct_name;
        dim_json["bin_file_size_in_structs"] = (uint64_t)dim.bin_file_size_in_structs;


        dim_json["coords_type"] = dim.coords_type;
        dim_json["has_grid_coords"] = dim.has_grid_coords;
        dim_json["has_col_row_coords"] = dim.has_col_row_coords;


        dim_json["Q_data_type"] = dim.Q_data_type;
        dim_json["Q_output_length"] = (int)dim.Q_output_length;



        std::ofstream out(json_filepath.c_str(), std::ofstream::out);
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




void Handle_Qvec_Dims::print(){
    std::cout << std::endl << "QvecBinFile_Dims "
    << " bin_file_size_in_structs:" << dim.bin_file_size_in_structs

    << " grid_x:" << dim.grid_x
    << " grid_y:" << dim.grid_y
    << " grid_z:" << dim.grid_z


    << " ngx:" << dim.ngx
    << " ngx:" << dim.ngy
    << " ngx:" << dim.ngz


    << " idi:" << dim.idi
    << " idj:" << dim.idj
    << " idk:" << dim.idk

    << " struct_name:" << dim.struct_name
    << " bin_file_size_in_structs:" << dim.bin_file_size_in_structs


    << " coords_type:" << dim.coords_type
    << " has_grid_coords:" << dim.has_grid_coords
    << " has_col_row_coords:" << dim.has_col_row_coords


    << " Q_data_type:" << dim.Q_data_type
    << " Q_output_length:" << dim.Q_output_length


    << std::endl
    << std::endl;
}




