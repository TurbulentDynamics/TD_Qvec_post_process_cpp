#-------------------------------
# DOWNLOAD AND BUILD OF GOOGLETEST
# https://github.com/google/googletest/blob/master/googletest/README.md#incorporating-into-an-existing-cmake-project
#-------------------------------

configure_file(googletest-download/CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

#-------------------------------
# SOURCE FILES CONFIGURATION
#-------------------------------

set(TESTS_SRCS
        td_Qvec_post_process.cpp
        test_PostProcessing_Dims.cpp)

#-------------------------------
# GENERAL COMPILER CONFIGURATION
#-------------------------------

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#----------------------------------
# BUILD INFORMATION
#----------------------------------

# Turn off -isystem gcc option that CMake uses for imported
# targets even when INTERFACE_INCLUDE_DIRECTORIES is used.
set(CMAKE_NO_SYSTEM_FROM_IMPORTED "1")

add_executable(td_pp_tests ${TESTS_SRCS} $<TARGET_OBJECTS:objects>)
target_link_libraries(td_pp_tests gmock gmock_main)