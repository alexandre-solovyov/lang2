
#include <gtest/gtest.h>
#include <model/grammar.h>

TEST(TestGrammar, SetOperationsAreOK)
{
    GrammarSet gs1;
    gs1.append( "a" );
    gs1.append( "b" );
    ASSERT_EQ( gs1.size(), 2 );

    GrammarSet gs2;
    gs2.append( "c" );
    gs2.append( "d" );
    ASSERT_EQ( gs2.size(), 2 );

    GrammarSet gs3( "test" );
    ASSERT_EQ( gs3.size(), 1 );

    ASSERT_EQ( ( gs1 + gs2 ).toString().toStdString(), "ac, bd" );
    ASSERT_EQ( ( gs1 * gs2 ).toString().toStdString(), "ac, ad, bc, bd" );
    ASSERT_EQ( ( gs1 + " test" ).toString().toStdString(), "a test, b test" );
}

TEST(TestGrammar, RuleIsOK)
{
    GrammarRule r( "[PrInd] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );

    ASSERT_EQ( r.Group().toStdString(), "PrInd" );
    ASSERT_EQ( r.Start().toStdString(), "~er" );
    ASSERT_EQ( r.Result().toString().toStdString(), "~e, ~es, ~e, ~ons, ~ez, ~ent" );

    ASSERT_TRUE( r.Match( "parler" ) );
    ASSERT_FALSE( r.Match( "venir" ) );
}

TEST(TestGrammar, FormsAreOK)
{
    GrammarRule r( "[PrInd] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );
    ASSERT_EQ( r.Forms("parler").toString().toStdString(), "parle, parles, parle, parlons, parlez, parlent" );
    ASSERT_EQ( r.Forms("venir").toString().toStdString(), "" );
}
