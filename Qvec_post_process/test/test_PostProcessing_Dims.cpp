
#include "PostProcessing_Dims.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>

using ::testing::Eq;
using ::testing::Ne;

/*-------------------------------------*/
/* --          TEST CASES           -- */
/*-------------------------------------*/

TEST(Dims, CanPrint)
{
    Handle_PP_Dims pp;
    ASSERT_NO_THROW(pp.print());
}

TEST(Dims, CanSetDimsToJSONAndLoadIt)
{
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"testDims.json"};

    ppHandle.set_dims(1, 2, 3, 4, 5, 6);
    ASSERT_NO_THROW(ppHandle.save_json_to_filepath(testFile));

    ASSERT_THAT(ppDim.ngx, Ne(ppHandle.dim.ngx));

    ASSERT_NO_THROW(ppDim = ppHandle.get_from_json_filepath(testFile));

    ASSERT_THAT(ppDim.ngx, Eq(ppHandle.dim.ngx));
    ASSERT_THAT(ppDim.ngy, Eq(ppHandle.dim.ngy));
    ASSERT_THAT(ppDim.ngz, Eq(ppHandle.dim.ngz));

    ASSERT_THAT(ppDim.grid_x, Eq(ppHandle.dim.grid_x));
    ASSERT_THAT(ppDim.grid_y, Eq(ppHandle.dim.grid_y));
    ASSERT_THAT(ppDim.grid_z, Eq(ppHandle.dim.grid_z));
}

TEST(Dims, CanSetHeightWidhtToJSONAndLoadIt)
{
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"testHeightWidth.json"};

    ppHandle.set_height_width(1, 2, 3, 4);
    ASSERT_NO_THROW(ppHandle.save_json_to_filepath(testFile));

    ASSERT_THAT(ppDim.file_height, Ne(ppHandle.dim.file_height));

    ASSERT_NO_THROW(ppDim = ppHandle.get_from_json_filepath(testFile));

    ASSERT_THAT(ppDim.file_height, Eq(ppHandle.dim.file_height));
    ASSERT_THAT(ppDim.file_width, Eq(ppHandle.dim.file_width));

    ASSERT_THAT(ppDim.total_height, Eq(ppHandle.dim.total_height));
    ASSERT_THAT(ppDim.total_width, Eq(ppHandle.dim.total_width));
}

TEST(Dims, CanSetRunningToJSONAndLoadIt) {
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"testRunning.json"};

    ppHandle.set_running(1, 2.5);
    ASSERT_NO_THROW(ppHandle.save_json_to_filepath(testFile));

    ASSERT_THAT(ppDim.step, Ne(ppHandle.dim.step));

    ASSERT_NO_THROW(ppDim = ppHandle.get_from_json_filepath(testFile));

    ASSERT_THAT(ppDim.step, Eq(ppHandle.dim.step));
    ASSERT_THAT(ppDim.teta, Eq(ppHandle.dim.teta));
}

TEST(Dims, CanSetFlowToJSONAndLoadIt) {
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"testFlow.json"};

    ppHandle.set_flow(1.4, 2.5, 3.6);
    ASSERT_NO_THROW(ppHandle.save_json_to_filepath(testFile));

    ASSERT_THAT(ppDim.initial_rho, Ne(ppHandle.dim.initial_rho));

    ASSERT_NO_THROW(ppDim = ppHandle.get_from_json_filepath(testFile));

    ASSERT_THAT(ppDim.initial_rho, Eq(ppHandle.dim.initial_rho));
    ASSERT_THAT(ppDim.Re_m_nondimensional, Eq(ppHandle.dim.Re_m_nondimensional));
    ASSERT_THAT(ppDim.uav, Eq(ppHandle.dim.uav));
}

TEST(Dims, CanSetPlotToJSONAndLoadIt) {
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"testPlot.json"};

    ppHandle.set_plot("testFnc", "testDir", 5, 10);
    ASSERT_NO_THROW(ppHandle.save_json_to_filepath(testFile));

    ASSERT_THAT(ppDim.func, Ne(ppHandle.dim.func));

    ASSERT_NO_THROW(ppDim = ppHandle.get_from_json_filepath(testFile));

    ASSERT_THAT(ppDim.func, Eq(ppHandle.dim.func));
    ASSERT_THAT(ppDim.dirname, Eq(ppHandle.dim.dirname));
    ASSERT_THAT(ppDim.cut_at, Eq(ppHandle.dim.cut_at));
    ASSERT_THAT(ppDim.Q_output_length, Eq(ppHandle.dim.Q_output_length));
}