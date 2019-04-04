//
//  define_datastructures.hpp
//  stirred-tank-3d-xcode-cpp
//
//  Created by Nile Ó Broin on 08/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef QvecBinFile_Dims_hpp
#define QvecBinFile_Dims_hpp

#include <stdlib.h>



#include "define_typealias.h"
#include "Base_Dims.hpp"





struct Qvec_Dims {

    tNi grid_x = 0;
    tNi grid_y = 0;
    tNi grid_z = 0;


    t3d ngx = 0;
    t3d ngy = 0;
    t3d ngz = 0;

    t3d idi = 0;
    t3d idj = 0;
    t3d idk = 0;


    std::string struct_name;
    unsigned long int bin_file_size_in_structs = 0;



    std::string coords_type = "";
    bool has_grid_coords;
    bool has_col_row_coords;



    std::string Q_data_type = "";
    int Q_output_length = 0;

};



class Handle_Qvec_Dims: public Base_Dims<Qvec_Dims>{
private:
    std::string get_name(){return "Qvec_Dims";}

public:
    Handle_Qvec_Dims(){}

    Handle_Qvec_Dims(Qvec_Dims _dim)
    {
        dim = _dim;
    }




    void set_dims(t3d ngx, t3d ngy, t3d ngz, tNi snx, tNi sny, tNi snz){

        dim.ngx = ngx;
        dim.ngy = ngy;
        dim.ngz = ngz;

        dim.grid_x = snx;
        dim.grid_y = sny;
        dim.grid_z = snz;
    }

    void set_ids(t3d idi, t3d idj, t3d idk){

        dim.idi = idi;
        dim.idj = idj;
        dim.idk = idk;

    }

    void set_file_content(std::string struct_name, unsigned long int bin_file_size_in_structs,
                          std::string coords_type, bool has_grid_coords, bool has_col_row_coords,
                          std::string Q_data_type, int Q_output_length)
    {

        dim.struct_name = struct_name;
        dim.bin_file_size_in_structs = bin_file_size_in_structs;

        dim.coords_type = coords_type;
        dim.has_grid_coords = has_grid_coords;
        dim.has_col_row_coords = has_col_row_coords;

        dim.Q_data_type = Q_data_type;
        dim.Q_output_length = Q_output_length;


    }



    








    std::string get_json_filepath_from_Qvec_filepath(const std::string Qvec_filepath){
        return Qvec_filepath + ".json";
    }

    bool Qvec_json_file_exists(const std::string Qvec_filepath){
        std::string json_filepath = get_json_filepath_from_Qvec_filepath(Qvec_filepath);
        return file_exists(json_filepath);
    }




    Qvec_Dims get_from_json_filepath(const std::string filepath);


    Qvec_Dims get_from_Qvec_filepath(const std::string Qvec_filepath){

        std::string json_filepath = get_json_filepath_from_Qvec_filepath(Qvec_filepath);

        return get_from_json_filepath(json_filepath);
    }




    int save_json_to_Qvec_filepath(const std::string qvec_filepath);






    void print();
};







#endif   /*  Dims_hpp  */
