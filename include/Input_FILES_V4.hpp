
//
//  Output_Qvec.hpp
//  stirred-tank-3d-xcode-cpp
//
//  Created by Niall OByrnes on 23/07/2018.
//  Copyright © 2018 Niall P. O'Byrnes. All rights reserved.
//

#ifndef Input_FILES_V4_hpp
#define Input_FILES_V4_hpp

#include <sys/stat.h> // mkdir
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstdint>



#include "define_typealias.h"
#include "define_datastructures.hpp"


#include "Inline.hpp"
#include "Qvec_Dims.hpp"
#include "PostProcessing_Dims.hpp"



//#if IS_INTEL_CXX == 1
//#include "half.hpp"
//#endif



//https://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g-mingw
#include <sstream>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}




struct tDisk_grid_Q3_V4 {
    uint16_t i_grid, j_grid, k_grid;
    float s[3];
};
struct tDisk_colrow_Q3_V4 {
    uint16_t col, row;
    float s[3];
};
struct tDisk_grid_colrow_Q3_V4 {
    uint16_t i_grid, j_grid, k_grid;
    uint16_t col, row;
    float s[3];
};




struct tDisk_grid_Q4_V4 {
    uint16_t i_grid, j_grid, k_grid;
    float s[4];
};
struct tDisk_colrow_Q4_V4 {
    uint16_t col, row;
    float s[4];
};
struct tDisk_grid_colrow_Q4_V4 {
    uint16_t i_grid, j_grid, k_grid;
    uint16_t col, row;
    float s[4];
};



struct tDisk_grid_Q19_V4 {
    uint16_t i_grid, j_grid, k_grid;
    float s[19];
};
struct tDisk_colrow_Q19_V4 {
    uint16_t col, row;
    float s[19];
};
struct tDisk_grid_colrow_Q19_V4 {
    uint16_t i_grid, j_grid, k_grid;
    uint16_t col, row;
    float s[19];
};



//struct tDisk_grid_Q27_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    float s[27];
//};
//
//struct tDisk_colrow_Q27_V4 {
//    uint16_t col, row;
//    float s[27];
//};
//
//struct tDisk_grid_colrow_Q27_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    uint16_t col, row;
//    float s[27];
//};

//----------------------------------------


//struct tDisk_grid_double_Q4_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    double q[4];
//};
//
//struct tDisk_colrow_double_Q4_V4 {
//    uint16_t col, row;
//    double q[4];
//};
//
//struct tDisk_grid_colrow_double_Q4_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    uint16_t col, row;
//    double q[4];
//};
//
//
//
//struct tDisk_grid_double_Q19_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    double q[19];
//};
//
//struct tDisk_colrow_double_Q19_V4 {
//    uint16_t col, row;
//    double q[19];
//};
//
//struct tDisk_grid_colrow_double_Q19_V4 {
//    uint16_t i_grid, j_grid, k_grid;
//    uint16_t col, row;
//    double q[19];
//};





//----------------------------------



class Input_FILES_V4 {

private:


    std::string get_Qvec_fileroot(const std::string dir, const std::string name, t3d idi, t3d idj, t3d idk) {
        return dir + "/" + name + ".node." + std::to_string(idi) + "." + std::to_string(idj) + "." + std::to_string(idk) + ".V4";
    }



    tDisk_grid_Q3_V4 *Disk_grid_Q3;
    tDisk_colrow_Q3_V4 *Disk_colrow_Q3;
    tDisk_grid_colrow_Q3_V4 *Disk_grid_colrow_Q3;

    tDisk_grid_Q4_V4 *Disk_grid_Q4;
    tDisk_colrow_Q4_V4 *Disk_colrow_Q4;
    tDisk_grid_colrow_Q4_V4 *Disk_grid_colrow_Q4;

    tDisk_grid_Q19_V4 *Disk_grid_Q19;
    tDisk_colrow_Q19_V4 *Disk_colrow_Q19;
    tDisk_grid_colrow_Q19_V4 *Disk_grid_colrow_Q19;

//    tDisk_grid_Q27_V4 *Disk_grid_Q27;
//    tDisk_colrow_Q27_V4 *Disk_colrow_Q27;
//    tDisk_grid_colrow_Q27_V4 *Disk_grid_colrow_Q27;


    //----------------------------------------

//    tDisk_grid_double_Q3_V4 *Disk_grid_double_Q3;
//    tDisk_colrow_double_Q3_V4 *Disk_colrow_double_Q3;
//    tDisk_grid_colrow_double_Q3_V4 *Disk_grid_colrow_double_Q3;

//    tDisk_grid_double_Q4_V4 *Disk_grid_double_Q4;
//    tDisk_colrow_double_Q4_V4 *Disk_colrow_double_Q4;
//    tDisk_grid_colrow_double_Q4_V4 *Disk_grid_colrow_double_Q4;
//
//    tDisk_grid_double_Q19_V4 *Disk_grid_double_Q19;
//    tDisk_colrow_double_Q19_V4 *Disk_colrow_double_Q19;
//    tDisk_grid_colrow_double_Q19_V4 *Disk_grid_colrow_double_Q19;

//    tDisk_grid_double_Q27_V4 *Disk_grid_double_Q27;
//    tDisk_colrow_double_Q27_V4 *Disk_colrow_double_Q27;
//    tDisk_grid_colrow_double_Q27_V4 *Disk_grid_colrow_double_Q27;



public:

    Grid_Dims grid;
    Node_Dims node;
    PP_Dims pp_data;
    

    Input_FILES_V4() {};


    Input_FILES_V4(Grid_Dims _grid, Node_Dims _node){
        grid = _grid;
        node = _node;
    };


    std::string format_step(tStep step){

        std::stringstream sstream;

        sstream << std::setw(8) << std::setfill('0') << patch::to_string(step);

        return sstream.str();
    }





    std::string get_Qvec_filename(const std::string dir, const std::string name, t3d idi, t3d idj, t3d idk) {
        return get_Qvec_fileroot(dir, name, idi, idj, idk) + ".bin";
    }

    std::string get_my_Qvec_filename(const std::string dir, const std::string name) {
        return get_Qvec_filename(dir, name, node.idi, node.idj, node.idk);
    }

    std::string get_node000_Qvec_filename(const std::string dir, const std::string name) {
        return get_Qvec_filename(dir, name, 0, 0, 0);
    }



    std::string get_start(std::string dir_root, std::string name, std::string plot_type, int Q_length, tStep step) {
        return dir_root + "/" + name + "." + plot_type + ".V_4.Q_" + patch::to_string(Q_length) + ".step_" + format_step(step);
    }




    std::string get_XY_plane_dir(tStep step, tNi at_k, int Q_length, const std::string name="plot", const std::string dir_root="."){

        return get_start(dir_root, name, "XYplane", Q_length, step) + ".cut_" + patch::to_string(at_k);
    }

    //Formally Axis
    std::string get_XZ_plane_dir(tStep step, tNi at_j, int Q_length, const std::string name="plot", const std::string dir_root="."){

        return get_start(dir_root, name, "XZplane", Q_length, step) + ".cut_" + patch::to_string(at_j);
    }

    //Formally Slice
    std::string get_YZ_plane_dir(tStep step, tNi at_i, int Q_length, const std::string name="plot", const std::string dir_root="."){

        return get_start(dir_root, name, "YZplane", Q_length, step) + ".cut_" + patch::to_string(at_i);
    }



    std::string get_volume_dir(tStep step, int Q_length, const std::string name="plot", const std::string dir_root="."){
        return get_start(dir_root, name, "volume", Q_length, step);
    }


    



    std::string get_capture_at_blade_angle_dir(tStep step, int angle, int blade_id, int Q_length, const std::string name="plot_", const std::string dir_root="."){

        return get_start(dir_root, name, "rotational_capture", Q_length, step) + ".angle_" + patch::to_string(angle) + ".blade_id_" + patch::to_string(blade_id);
    }


    std::string get_axis_when_blade_angle_dir(tStep step, int angle, int Q_length, const std::string name="plot", const std::string dir_root="."){

        return get_start(dir_root, name, "YZplane", Q_length, step) + ".angle_" + patch::to_string(angle);
    }



    std::string get_rotating_sector_dir(tStep step, int angle, int Q_length, const std::string name="plot", const std::string dir_root="."){

        std::string ret = "";
        return ret;
    }



    std::string get_dir_delta(int delta, const std::basic_string<char> &load_dir) {
        using namespace std;


        if (!plot_type_in_dir("cut", load_dir)) return "not_found";


        string delta_load_dir = load_dir;

        size_t index = load_dir.find("cut_");

        int cut = stoi(load_dir.substr (index + 4));

        string delta_cut = "cut_" + patch::to_string(cut + delta);

        delta_load_dir.replace(index, string::npos, delta_cut);

        //    std::cout << "String" << load_dir << " Delta String   " << delta_load_dir << std::endl;

        return delta_load_dir;
    }




    bool plot_type_in_dir(const std::basic_string<char> &type, const std::basic_string<char> &load_dir) {
        using namespace std;

        size_t found = load_dir.find(type);
        if (found != string::npos) {
            //        cout << "found  " << type << " in " << load_dir << endl;
            return true;
        }
        return false;
    }


    std::string get_plot_type_from_directory(const std::basic_string<char> &load_dir) {

        if (plot_type_in_dir("XYplane", load_dir)) return "XYplane";
        else if (plot_type_in_dir("XZplane", load_dir)) return "XZplane";
        else if (plot_type_in_dir("YZplane", load_dir)) return "YZplane";

        else if (plot_type_in_dir("volume", load_dir)) return "volume";

        else if (plot_type_in_dir("rotational_capture", load_dir)) return "rotational_capture";



        return "";
    }




    
    //----------------------------



    void load_plane(int num_layers, const std::basic_string<char> &load_dir, tQvec **Q_plane, tForce **F_plane, const PP_Dims &pp);


    void allocate_and_orient_plane_from_filepath(const std::string plotname, PP_Dims pp, const std::string Qvec_filepath, tQvec *plane, bool is_F=0);


    void load_angle(int layers, const std::basic_string<char> &load_dir, tQvec **plane, const PP_Dims &pp);



};








#endif














