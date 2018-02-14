
#include <tests.h>

TEST(TestTools, NormalizeIsOK)
{
    ASSERT_EQQ( Tools::normalize( "" ), "" );
    ASSERT_EQQ( Tools::normalize( "parler" ), "parler" );
    ASSERT_EQQ( Tools::normalize( "parle/" ), "parlé" );
    ASSERT_EQQ( Tools::normalize( "pre/-e/tude" ), "pré-étude" );
    ASSERT_EQQ( Tools::normalize( "pre'-e'tude" ), "pré-étude" );

    ASSERT_EQQ( Tools::normalize( "e^tre" ), "être" );
    ASSERT_EQQ( Tools::normalize( "a\\" ), "à" );
    ASSERT_EQQ( Tools::normalize( "a`" ), "à" );

    ASSERT_EQQ( Tools::normalize( "Noe:l" ), "Noël" );
}
