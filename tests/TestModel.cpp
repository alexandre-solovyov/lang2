
#include <tests.h>
#include <model/model.h>
#include <model/eg_one.h>
#include <model/eg_trans.h>

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

TEST(TestModel, LoadingIsOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test1.lang" ) );
    ASSERT_EQ( aModel.Size(), 7 );
}

TEST(TestModel, BuildWithOneIsOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test2.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_One() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 8 );

    ASSERT_EQQ( ex[0].Question, "couper <?> pomme en deux parties" );
    ASSERT_EQQ( ex[0].Answer, "une" );
    ASSERT_EQQ( ex[0].Lang1, "fr" );
    ASSERT_EQQ( ex[0].Lang2, "ru" );
    ASSERT_EQQ( ex[0].Category, "basic" );

    ASSERT_EQQ( ex[1].Question, "couper une pomme <?> deux parties" );
    ASSERT_EQQ( ex[1].Answer, "en" );
    ASSERT_EQQ( ex[1].Lang1, "fr" );
    ASSERT_EQQ( ex[1].Lang2, "ru" );
    ASSERT_EQQ( ex[1].Category, "basic" );

    ASSERT_EQQ( ex[2].Question, "aller <?> Italie" );
    ASSERT_EQQ( ex[2].Answer, "en" );
    ASSERT_EQQ( ex[2].Lang1, "fr" );
    ASSERT_EQQ( ex[2].Lang2, "ru" );
    ASSERT_EQQ( ex[2].Category, "basic" );

    ASSERT_EQQ( ex[3].Question, "<?> scène = сцена" );
    ASSERT_EQQ( ex[3].Answer, "une" );
    ASSERT_EQQ( ex[3].Lang1, "fr" );
    ASSERT_EQQ( ex[3].Lang2, "ru" );
    ASSERT_EQQ( ex[3].Category, "basic" );

    ASSERT_EQQ( ex[4].Question, "<?> modèle = модель" );
    ASSERT_EQQ( ex[4].Answer, "un" );
    ASSERT_EQQ( ex[4].Lang1, "fr" );
    ASSERT_EQQ( ex[4].Lang2, "ru" );
    ASSERT_EQQ( ex[4].Category, "basic" );

    ASSERT_EQQ( ex[5].Question, "<?>, marcher" );
    ASSERT_EQQ( ex[5].Answer, "aller" );
    ASSERT_EQQ( ex[5].Lang1, "fr" );
    ASSERT_EQQ( ex[5].Lang2, "ru" );
    ASSERT_EQQ( ex[5].Category, "basic" );

    ASSERT_EQQ( ex[6].Question, "aller, <?>" );
    ASSERT_EQQ( ex[6].Answer, "marcher" );
    ASSERT_EQQ( ex[6].Lang1, "fr" );
    ASSERT_EQQ( ex[6].Lang2, "ru" );
    ASSERT_EQQ( ex[6].Category, "basic" );

    ASSERT_EQQ( ex[7].Question, "<?>" );
    ASSERT_EQQ( ex[7].Answer, "abat-jour" );
    ASSERT_EQQ( ex[7].Lang1, "fr" );
    ASSERT_EQQ( ex[7].Lang2, "ru" );
    ASSERT_EQQ( ex[7].Category, "basic" );
}

TEST(TestModel, BuildWithTransIsOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test2.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Trans() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 6 );

    ASSERT_EQQ( ex[0].Question, "une scène = <?>" );
    ASSERT_EQQ( ex[0].Answer, "сцена" );
    ASSERT_EQQ( ex[0].Lang1, "fr" );
    ASSERT_EQQ( ex[0].Lang2, "ru" );
    ASSERT_EQQ( ex[0].Category, "basic" );

    ASSERT_EQQ( ex[1].Question, "сцена = <?>" );
    ASSERT_EQQ( ex[1].Answer, "une scène" );
    ASSERT_EQQ( ex[1].Lang1, "ru" );
    ASSERT_EQQ( ex[1].Lang2, "fr" );
    ASSERT_EQQ( ex[1].Category, "basic" );

    ASSERT_EQQ( ex[2].Question, "un modèle = <?>" );
    ASSERT_EQQ( ex[2].Answer, "модель" );
    ASSERT_EQQ( ex[2].Lang1, "fr" );
    ASSERT_EQQ( ex[2].Lang2, "ru" );
    ASSERT_EQQ( ex[2].Category, "basic" );

    ASSERT_EQQ( ex[3].Question, "модель = <?>" );
    ASSERT_EQQ( ex[3].Answer, "un modèle" );
    ASSERT_EQQ( ex[3].Lang1, "ru" );
    ASSERT_EQQ( ex[3].Lang2, "fr" );
    ASSERT_EQQ( ex[3].Category, "basic" );

    ASSERT_EQQ( ex[4].Question, "prévenir = <?>" );
    ASSERT_EQQ( ex[4].Answer, "предупредить" );
    ASSERT_EQQ( ex[4].Lang1, "fr" );
    ASSERT_EQQ( ex[4].Lang2, "ru" );
    ASSERT_EQQ( ex[4].Category, "basic" );

    ASSERT_EQQ( ex[5].Question, "предупредить = <?>" );
    ASSERT_EQQ( ex[5].Answer, "prévenir" );
    ASSERT_EQQ( ex[5].Lang1, "ru" );
    ASSERT_EQQ( ex[5].Lang2, "fr" );
    ASSERT_EQQ( ex[5].Category, "basic" );
}

TEST(TestModel, TranslationVariantsAreOK)
{
    qsrand(1234);

    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test4.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Trans() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 40 );

    ListOfExercises fex1 = ex.Filter( gen[0]->Type(), "fr", "ru" );
    ASSERT_EQ( fex1.size(), 20 );

    ListOfExercises rex1 = fex1.Random( 10 );
    ASSERT_EQ( rex1.size(), 8 );

    QStringList vars = ex.Shuffle( ex[4], rex1 );
    ASSERT_EQ( vars.size(), 9 );

    QString svars = vars.join( ", ");
    ASSERT_EQQ( ex[4].Question, "un problème = <?>" );
    ASSERT_EQQ( ex[4].Answer, "проблема" );
    ASSERT_EQQ( svars, "сцена, отель, почта, центр, музей, проблема, река, год, принцип" );


    qsrand(1234);
    ListOfExercises fex2 = ex.Filter( gen[0]->Type(), "ru", "fr" );
    ASSERT_EQ( fex2.size(), 20 );

    ListOfExercises rex2 = fex2.Random( 10 );
    ASSERT_EQ( rex2.size(), 8 );

    QStringList vars2 = ex.Shuffle( ex[5], rex2 );
    ASSERT_EQ( vars2.size(), 9 );

    QString svars2 = vars2.join( ", ");
    ASSERT_EQQ( ex[5].Question, "проблема = <?>" );
    ASSERT_EQQ( ex[5].Answer, "un problème" );
    ASSERT_EQQ( svars2, "une scène, un hôtel, une poste, un centre, un musée, un problème, un fleuve, une année, un principe" );
}

TEST(TestModel, TagsAreOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test5.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Trans() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 4 );

    ASSERT_EQQ( ex[0].Tag, "просьба" );
    ASSERT_EQQ( ex[1].Tag, "просьба" );
    ASSERT_EQQ( ex[2].Tag, "благодарность" );
    ASSERT_EQQ( ex[3].Tag, "благодарность" );
}
