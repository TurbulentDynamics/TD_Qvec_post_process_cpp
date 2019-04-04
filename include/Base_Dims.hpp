//
//  Grid_Dims.hpp
//  lb-halo-3dmpi
//
//  Created by Nile Ó Broin on 08/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#ifndef Base_Dims_hpp
#define Base_Dims_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/stat.h> // mkdir


#include "define_typealias.h"



template <class T>
class Base_Dims {
private:
    virtual std::string get_name(){return "Error-should-be-overwritten";}

public:
    virtual ~Base_Dims(){};
    T dim;


    Base_Dims(){}

    Base_Dims(T _dim)
    {
        dim = _dim;
    }


    void set_dim(T _dim){
        dim = _dim;
    }

    T get_dim(){
        return dim;
    }




    std::string get_base_filepath(t3d idi, t3d idj, t3d idk, const std::string dir="."){
        return dir + "/" + get_name() + "_dims." + std::to_string(idi) + "." + std::to_string(idj) + "." + std::to_string(idk);
    }


    std::string get_filepath(t3d idi, t3d idj, t3d idk, const std::string dir="."){
        return get_base_filepath(idi, idj, idk, dir) + ".V4.json";
    }


    std::string get_bin_filepath_v3(t3d idi, t3d idj, t3d idk, const std::string dir="."){
        return get_base_filepath(idi, idj, idk, dir) + ".V3.bin";
    }




    bool path_exists(std::string path) {

        if (FILE *file = fopen(path.c_str(), "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }


    bool file_exists(std::string path) {
        return path_exists(path);
    }






    //Loading
    T get_from_file(t3d idi, t3d idj, t3d idk, const std::string dir="."){

        std::string filepath = get_filepath(idi, idj, idk, dir);
        if (file_exists(filepath)) return get_from_json_filepath(filepath);

        //Try V3
        filepath = get_bin_filepath_v3(idi, idj, idk, dir);
        if (file_exists(filepath)) return get_from_bin_filepath(filepath);


        //ERROR
        T empty;
        return empty;
    }

    //Will be overloaded
    virtual T get_from_json_filepath(std::string filepath) = 0;


    T get_from_bin_filepath(std::string filepath) {
        T result;
        FILE * fp = fopen(filepath.c_str(), "r");
        fread(&result, sizeof(T), 1, fp);
        fclose(fp);

        return result;
    }

    T get_from_node000_from_filepath(const std::string dir = "."){
        return get_from_file(0, 0, 0, dir);
    }




    //Set from file
    void set_from_filepath(std::string filepath){
        dim = get_from_file(filepath);
    }

    void set_from_dir(t3d idi, t3d idj, t3d idk, const std::string dir = ".") {
        dim = get_from_file(idi, idj, idk, dir);
    }

    void set_from_node000_from_filepath(const std::string dir="."){
        dim = get_from_file(0, 0, 0, dir);
    }





    //Will be overloaded
    virtual int save_json_to_filepath(const std::string filepath)
    {
        std::cout << "BASE_Dim:  Error: hould have been provided by child" << std::endl;
        return 0;
    };


    //Will be overloaded
    virtual int save_public_json_to_filepath(const std::string filepath)
    {
        std::cout << "BASE_Dim:  Error: hould have been provided by child" << std::endl;
        return 0;
    };



    int save_json_to_dir(t3d idi, t3d idj, t3d idk, const std::string dir = "."){

        if (!path_exists(dir)) mkdir(dir.c_str(), 0775);


        std::string filepath = get_filepath(idi, idj, idk, dir);
        //        std::cout << "BASE_Dim:  Saving json to " << filepath << std::endl;

        return save_json_to_filepath(filepath);

    }

    void save_json_as_node000_to_dir(const std::string dir="."){
        save_json_to_dir(0, 0, 0, dir);
    }






    int save_public_json_to_dir(t3d idi, t3d idj, t3d idk, const std::string dir = "."){

        if (!path_exists(dir)) mkdir(dir.c_str(), 0775);


        std::string filepath = get_filepath(idi, idj, idk, dir);
        //        std::cout << "BASE_Dim:  Saving json to " << filepath << std::endl;

        return save_public_json_to_filepath(filepath);

    }

    void save_public_json_as_node000_to_dir(const std::string dir="."){
        save_public_json_to_dir(0, 0, 0, dir);
    }



};




#endif

