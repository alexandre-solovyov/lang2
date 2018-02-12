
#include <gtest/gtest.h>
#include <model/grammar.h>
#include <model/grammarset.h>
#include <model/stdtense.h>
#include <model/deptense.h>

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

TEST(TestGrammar, OperationsWithOneItemAreOK)
{
    GrammarSet gs1;
    gs1.append( "a" );

    GrammarSet gs2;
    gs2.append( "test1" );
    gs2.append( "test2" );
    gs2.append( "test3" );
    gs2.append( "test4" );
    gs2.append( "test5" );
    gs2.append( "test6" );

    ASSERT_EQ( ( gs1 + gs2 ).toString().toStdString(), "atest1, test2, test3, test4, test5, test6" );
    ASSERT_EQ( ( gs1 * gs2 ).toString().toStdString(), "atest1, atest2, atest3, atest4, atest5, atest6" );
}

TEST(TestGrammar, RemovingOK)
{
    GrammarSet gs1;
    gs1.append( "##test1" );

    GrammarSet gs2;
    gs2.append( "##test2" );

    ASSERT_EQ( ( gs1 + gs2 ).toString().toStdString(), "testest2" );
    ASSERT_EQ( ( gs1 * gs2 ).toString().toStdString(), "testest2" );

    GrammarSet gs3;
    gs3.append( "parlent" );

    GrammarSet gs4;
    gs4.append( "###ions" );
    gs4.append( "###iez" );
    gs4.append( "###ient" );

    ASSERT_EQ( ( gs3 + gs4 ).toString().toStdString(), "parlions, iez, ient" );
    ASSERT_EQ( ( gs3 * gs4 ).toString().toStdString(), "parlions, parliez, parlient" );
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
    GrammarSet pr = GrammarSet() << "je" << "tu" << "il" << "nous" << "vous" << "ils";

    GrammarRule r( "[PrInd] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );
    GrammarSet f = pr + " " + r.Forms("parler");
    ASSERT_EQ( f.toString().toStdString(), "je parle, tu parles, il parle, nous parlons, vous parlez, ils parlent" );
}

TEST(TestGrammar, PresentIsOK)
{
    Grammar gr( true );

    StdTense* pr = new StdTense( "PrInd", &gr );
    pr->Add( "~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );
    pr->Add( "~ir >> ~is, ~is, ~it, ~issons, ~issez, ~issent" );

    new DepTense( "PrSubj", &gr, "PrInd", 5, GrammarSet( "###e, ###es, ###e, ###ions, ###iez, ###ient", ", " ) );

    ASSERT_EQ( gr.Forms("PrInd", "parler").toString().toStdString(), "parle, parles, parle, parlons, parlez, parlent" );
    ASSERT_EQ( gr.Forms("PrInd", "finir").toString().toStdString(), "finis, finis, finit, finissons, finissez, finissent" );
    ASSERT_EQ( gr.Forms("PrSubj", "parler").toString().toStdString(), "parle, parles, parle, parlions, parliez, parlient" );
    ASSERT_EQ( gr.Forms("PrSubj", "finir").toString().toStdString(), "finisse, finisses, finisse, finissions, finissiez, finissient" );
}

