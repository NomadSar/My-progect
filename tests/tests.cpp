#include "tests.h"

int run_tests()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}