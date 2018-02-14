
#include <tests.h>
#include <model/grammar.h>
#include <model/grammarset.h>
#include <model/LangFile.h>
#include <model/eg_forms.h>
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

    ASSERT_EQQ( ( gs1 + gs2 ).toString(), "ac, bd" );
    ASSERT_EQQ( ( gs1 * gs2 ).toString(), "ac, ad, bc, bd" );
    ASSERT_EQQ( ( gs1 + " test" ).toString(), "a test, b test" );
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

    ASSERT_EQQ( ( gs1 + gs2 ).toString(), "atest1, test2, test3, test4, test5, test6" );
    ASSERT_EQQ( ( gs1 * gs2 ).toString(), "atest1, atest2, atest3, atest4, atest5, atest6" );
}

TEST(TestGrammar, RemovingOK)
{
    GrammarSet gs1;
    gs1.append( "##test1" );

    GrammarSet gs2;
    gs2.append( "##test2" );

    ASSERT_EQQ( ( gs1 + gs2 ).toString(), "testest2" );
    ASSERT_EQQ( ( gs1 * gs2 ).toString(), "testest2" );

    GrammarSet gs3;
    gs3.append( "parlent" );

    GrammarSet gs4;
    gs4.append( "###ions" );
    gs4.append( "###iez" );
    gs4.append( "###ient" );

    ASSERT_EQQ( ( gs3 + gs4 ).toString(), "parlions, iez, ient" );
    ASSERT_EQQ( ( gs3 * gs4 ).toString(), "parlions, parliez, parlient" );
}

TEST(TestGrammar, RuleIsOK)
{
    GrammarRule r( "[PrInd] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );

    ASSERT_EQQ( r.Group(), "PrInd" );
    ASSERT_EQQ( r.Start(), "~er" );
    ASSERT_EQQ( r.Result().toString(), "~e, ~es, ~e, ~ons, ~ez, ~ent" );

    ASSERT_TRUE( r.Match( "parler" ) );
    ASSERT_FALSE( r.Match( "venir" ) );
}

TEST(TestGrammar, FormsAreOK)
{
    GrammarSet pr = GrammarSet() << "je" << "tu" << "il" << "nous" << "vous" << "ils";

    GrammarRule r( "[PrInd] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );
    GrammarSet f = pr + " " + r.Forms("parler");
    ASSERT_EQQ( f.toString(), "je parle, tu parles, il parle, nous parlons, vous parlez, ils parlent" );
}

TEST(TestGrammar, CompleteFormIsOK)
{
    GrammarRule r1( "[Plur] ~ >> ~s" );
    ASSERT_EQQ( r1.Forms("homme").toString(), "hommes" );

    GrammarRule r2( "[Plur] ~mettre >> ~met" );
    ASSERT_EQQ( r2.Forms("mettre").toString(), "met" );
}

TEST(TestGrammar, SingleFormIsOK)
{
    GrammarRule r1( "[Pl] leur >> leurs" );
    ASSERT_EQQ( r1.Forms("leur").toString(), "leurs" );
}

TEST(TestGrammar, PresentIsOK)
{
    Grammar gr( true );

    StdTense* pr = new StdTense( "PrInd", &gr );
    pr->Add( "~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );
    pr->Add( "~ir >> ~is, ~is, ~it, ~issons, ~issez, ~issent" );

    new DepTense( "PrSubj", &gr, "PrInd", 5, GrammarSet( "###e, ###es, ###e, ###ions, ###iez, ###ient", ", " ) );

    ASSERT_EQQ( gr.Forms("PrInd", "parler").toString(), "parle, parles, parle, parlons, parlez, parlent" );
    ASSERT_EQQ( gr.Forms("PrInd", "finir").toString(), "finis, finis, finit, finissons, finissez, finissent" );
    ASSERT_EQQ( gr.Forms("PrSubj", "parler").toString(), "parle, parles, parle, parlions, parliez, parlient" );
    ASSERT_EQQ( gr.Forms("PrSubj", "finir").toString(), "finisse, finisses, finisse, finissions, finissiez, finissient" );
}

TEST(TestGrammar, FormsLoadingIsOK)
{
    LangFile aLangFile;
    ASSERT_TRUE( aLangFile.Load( QString(TEST_DATA) + "/test3.lang" ) );

    Grammar gr;

    QList<IGenerator*> gen;
    gen.append( new EG_Forms(&gr) );
    aLangFile.Build( gen );

    ASSERT_EQQ( gr.Tenses().join( ", " ), "PrInd" );

    ASSERT_EQQ( gr.Forms( "PrInd", "aller" ).toString(), "vais, vas, va, allons, allez, vont" );
    ASSERT_EQQ( gr.Forms( "PrInd", "marcher" ).toString(), "marche, marches, marche, marchons, marchez, marchent" );

    ASSERT_EQQ( gr.CachedForms().join( ", " ), "aller, parler" );
    ASSERT_EQQ( gr.CachedForms("aller").join( ", " ), "vais, vas, va, allons, allez, vont" );
    ASSERT_EQQ( gr.CachedForms("parler").join( ", " ), "parle, parles, parle, parlons, parlez, parlent" );
    ASSERT_EQQ( gr.CachedForms("marcher").join( ", " ), "" );
    ASSERT_EQQ( gr.CachedForms().join( ", " ), "aller, parler" );

    ASSERT_EQQ( gr.Init("parle").join( ", "), "parler" );
    ASSERT_EQQ( gr.Init("parlons").join( ", "), "parler" );
}


TEST(TestGrammar, SecondFileDeactivatesTenses)
{
    LangFile aLangFile;

    aLangFile.AddFile("1");
    ASSERT_TRUE( aLangFile.Add( 0, "[PrInd] ~er >> ~ons" ) );
    ASSERT_TRUE( aLangFile.Add( 0, "parler = говорить" ) );

    aLangFile.AddFile("2");
    ASSERT_TRUE( aLangFile.Add( 1, "[Plur] ~ >> ~s" ) );
    ASSERT_TRUE( aLangFile.Add( 1, "homme = человек" ) );

    Grammar gr;
    QList<IGenerator*> gen;
    gen.append( new EG_Forms(&gr) );
    aLangFile.Build( gen );

    ASSERT_EQQ( gr.CachedForms().join( ", " ), "homme, parler" );
    ASSERT_EQQ( gr.CachedForms("homme").join( ", " ), "hommes" );
    ASSERT_EQQ( gr.CachedForms("parler").join( ", " ), "parlons" );
}
