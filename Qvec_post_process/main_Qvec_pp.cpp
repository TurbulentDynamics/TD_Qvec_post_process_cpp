//
//  main.cpp
//  TD-Qvec-post-process
//
//  Created by Nile Ó Broin on 02/01/2019.
//  Copyright © 2019 Nile Ó Broin. All rights reserved.
//

#include <iostream>
#include <vector>


#ifdef _OPENMP
#include <omp.h>
#endif


#include <boost/program_options.hpp>


namespace
{
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}
using namespace std;





int main(int argc, const char * argv[]) {

    int avail_nthreads = 1;
#ifdef _OPENMP
    avail_nthreads = omp_get_max_threads();
#endif


    std::vector<std::string> dirs;

    int req_threads = 0;

    bool print_log = 0;
    bool overwrite = 0;


    try
    {
        namespace po = boost::program_options;

        po::options_description desc{"Options"};
        desc.add_options()
        ("help,h", "Lots of Arguments")
        ("nthreads,n", po::value<int>(&req_threads), "Request number of OpenMP threads ")

        ("overwrite,o", po::bool_switch(&overwrite), "Overwrite files if they exist ")


        //        ("dirs,d", po::value<std::vector<std::string>>(&dirs)->multitoken()->required(), "Directories")
        ("dirs,d", po::value<std::vector<std::string>>(&dirs)->multitoken(), "Directories")


        ("printlog,p", po::bool_switch(&print_log), "Print Log")
        ;



        po::variables_map vm;
        try
        {

            po::store(po::parse_command_line(argc, argv, desc), vm);

            if ( vm.count("help")  )
            {
                std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl;
                return SUCCESS;
            }

            // throws on error, so do after help in case there are any problems
            po::notify(vm);

        }
        catch(po::error& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }


        int nthreads = 1;
#if _OPENMP
        if (req_threads == 0) nthreads = avail_nthreads;
        else if (req_threads > avail_nthreads) nthreads = avail_nthreads;
        else nthreads = req_threads;

        //Too many threads usually crash because of disk access
        omp_set_num_threads(nthreads);
#endif
        std::cout << "nthreads " << nthreads << std::endl;



    }
    catch(std::exception& e)
    {
        std::cerr << "Unhandled Exception reached parsing arguments: "
        << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }














    for (auto load_dir : dirs) {

        std::cout << "load_dir " << load_dir << std::endl;

    }



}//end of main
