
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

TEST(Dims, CanSaveJSONToFileAndLoadIt)
{
    Handle_PP_Dims ppHandle;
    PP_Dims ppDim;
    std::string testFile{"test.json"};

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
