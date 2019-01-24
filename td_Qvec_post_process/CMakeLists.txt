cmake_minimum_required(VERSION 3.5.1)
project (td-qvec-post-process)



cmake_host_system_information(RESULT host_name QUERY HOSTNAME)
if (${host_name} MATCHES "login*")
    message("Building on Cluster detected")
    set(CLUSTER True)
else()
    message("Assuming NOT building on Cluster")
endif()

find_package(Git 1.6.5 REQUIRED)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")


# Download and unpack googletest at configure time
#configure_file(CMakeLists.txt.in 3rd_party/googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#    RESULT_VARIABLE result
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/3rd_party/googletest-download )
#if(result)
#    message(STATUS "CMake step for googletest failed: ${result}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#    RESULT_VARIABLE result
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/3rd_party/googletest-download )
#if(result)
#    message(STATUS "Build step for googletest failed: ${result}")
#endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
#add_subdirectory(${CMAKE_BINARY_DIR}/3rd_party/googletest-src
#    ${CMAKE_BINARY_DIR}/googletest-build
#    EXCLUDE_FROM_ALL)








include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_NO_SYSTEM_FROM_IMPORTED OFF)

#find_package(MPI REQUIRED)
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})

#Must follow MPI...
find_package(OpenMP)
if (OPENMP_FOUND AND APPLE)
    message("OpenMP found but supressing on Apple Device")
elseif(OPENMP_FOUND)
    message("Building with OpenMP")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


if (CLUSTER)
#    set(BOOST_ROOT /boost-root)
endif()
find_package(Boost 1.68 REQUIRED COMPONENTS program_options)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()




set(DEPRECATED ../deprecated/)


add_executable(td_Qvec_post_process PostProcessing_Dims.cpp main_Qvec_pp.cpp)

target_link_libraries(td_Qvec_post_process ${MPI_LIBRARIES} ${Boost_LIBRARIES} Boost::program_options)
target_compile_definitions(td_Qvec_post_process PRIVATE -DWITH_MPI=0)

