
#include <gtest/gtest.h>
#include <model/statistics.h>

TEST(TestStatistics, AddIsOK)
{
    Statistics s;
    s.Add("une pomme", true);

    ASSERT_EQ( s.NbCorrect("une pomme"), 1 );
    ASSERT_EQ( s.NbCorrect("une ville"), 0 );
}
