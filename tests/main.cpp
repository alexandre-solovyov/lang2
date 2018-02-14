
#include <gtest/gtest.h>
#include <model/tools.h>
#include <QString>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    Tools::print( "Test Unicode: une scène, сцена\n\n" );
    return RUN_ALL_TESTS();
}
