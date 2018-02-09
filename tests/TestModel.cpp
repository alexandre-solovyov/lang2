
#include <gtest/gtest.h>
#include <model/model.h>
#include <QString>

TEST(TestModel, LoadingIsOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test1.lang" ) );
}

TEST(TestModel, NoDuplicates)
{
    Model aModel;

    ASSERT_TRUE( aModel.Add( "test" ) );
    ASSERT_EQ( aModel.Size(), 1 );

    ASSERT_FALSE( aModel.Add( "test" ) );
    ASSERT_EQ( aModel.Size(), 1 );

    ASSERT_FALSE( aModel.Add( "  test " ) );
    ASSERT_EQ( aModel.Size(), 1 );

    ASSERT_TRUE( aModel.Add( "test 2" ) );
    ASSERT_EQ( aModel.Size(), 2 );
}
