
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

TEST(TestTools, isVowelIsOK)
{
    ASSERT_TRUE( Tools::isVowel( QString("a")[0] ) );
    ASSERT_TRUE( Tools::isVowel( QString("e")[0] ) );
    ASSERT_TRUE( Tools::isVowel( QString("à")[0] ) );
    ASSERT_TRUE( Tools::isVowel( QString("é")[0] ) );

    ASSERT_FALSE( Tools::isVowel( QString("b")[0] ) );
    ASSERT_FALSE( Tools::isVowel( QString("c")[0] ) );
    ASSERT_FALSE( Tools::isVowel( QString("ç")[0] ) );
}

TEST(TestTools, isConsonantIsOK)
{
    ASSERT_FALSE( Tools::isConsonant( QString("a")[0] ) );
    ASSERT_FALSE( Tools::isConsonant( QString("e")[0] ) );
    ASSERT_FALSE( Tools::isConsonant( QString("à")[0] ) );
    ASSERT_FALSE( Tools::isConsonant( QString("é")[0] ) );

    ASSERT_TRUE( Tools::isConsonant( QString("b")[0] ) );
    ASSERT_TRUE( Tools::isConsonant( QString("c")[0] ) );
    ASSERT_TRUE( Tools::isConsonant( QString("ç")[0] ) );
}

/*TEST(TestTools, GoogleFindPictureIsOK)
{

}*/
//https://www.google.ru/search?q=une+carotte+png&tbm=isch
