
#include <gtest/gtest.h>
#include <model/model.h>
#include <model/eg_one.h>
#include <model/eg_trans.h>
#include <QString>

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

    ASSERT_EQ( ex[0].Question.toStdString(), "couper <?> pomme en deux parties" );
    ASSERT_EQ( ex[0].Answer.toStdString(), "une" );
    ASSERT_EQ( ex[0].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[0].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[0].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[1].Question.toStdString(), "couper une pomme <?> deux parties" );
    ASSERT_EQ( ex[1].Answer.toStdString(), "en" );
    ASSERT_EQ( ex[1].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[1].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[1].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[2].Question.toStdString(), "aller <?> Italie" );
    ASSERT_EQ( ex[2].Answer.toStdString(), "en" );
    ASSERT_EQ( ex[2].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[2].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[2].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[3].Question.toStdString(), "<?> scène = сцена" );
    ASSERT_EQ( ex[3].Answer.toStdString(), "une" );
    ASSERT_EQ( ex[3].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[3].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[3].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[4].Question.toStdString(), "<?> modèle = модель" );
    ASSERT_EQ( ex[4].Answer.toStdString(), "un" );
    ASSERT_EQ( ex[4].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[4].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[4].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[5].Question.toStdString(), "<?>, marcher" );
    ASSERT_EQ( ex[5].Answer.toStdString(), "aller" );
    ASSERT_EQ( ex[5].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[5].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[5].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[6].Question.toStdString(), "aller, <?>" );
    ASSERT_EQ( ex[6].Answer.toStdString(), "marcher" );
    ASSERT_EQ( ex[6].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[6].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[6].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[7].Question.toStdString(), "<?>" );
    ASSERT_EQ( ex[7].Answer.toStdString(), "abat-jour" );
    ASSERT_EQ( ex[7].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[7].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[7].Category.toStdString(), "basic" );
}

TEST(TestModel, BuildWithTransIsOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test2.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Trans() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 6 );

    ASSERT_EQ( ex[0].Question.toStdString(), "une scène = <?>" );
    ASSERT_EQ( ex[0].Answer.toStdString(), "сцена" );
    ASSERT_EQ( ex[0].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[0].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[0].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[1].Question.toStdString(), "сцена = <?>" );
    ASSERT_EQ( ex[1].Answer.toStdString(), "une scène" );
    ASSERT_EQ( ex[1].Lang1.toStdString(), "ru" );
    ASSERT_EQ( ex[1].Lang2.toStdString(), "fr" );
    ASSERT_EQ( ex[1].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[2].Question.toStdString(), "un modèle = <?>" );
    ASSERT_EQ( ex[2].Answer.toStdString(), "модель" );
    ASSERT_EQ( ex[2].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[2].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[2].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[3].Question.toStdString(), "модель = <?>" );
    ASSERT_EQ( ex[3].Answer.toStdString(), "un modèle" );
    ASSERT_EQ( ex[3].Lang1.toStdString(), "ru" );
    ASSERT_EQ( ex[3].Lang2.toStdString(), "fr" );
    ASSERT_EQ( ex[3].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[4].Question.toStdString(), "prévenir = <?>" );
    ASSERT_EQ( ex[4].Answer.toStdString(), "предупредить" );
    ASSERT_EQ( ex[4].Lang1.toStdString(), "fr" );
    ASSERT_EQ( ex[4].Lang2.toStdString(), "ru" );
    ASSERT_EQ( ex[4].Category.toStdString(), "basic" );

    ASSERT_EQ( ex[5].Question.toStdString(), "предупредить = <?>" );
    ASSERT_EQ( ex[5].Answer.toStdString(), "prévenir" );
    ASSERT_EQ( ex[5].Lang1.toStdString(), "ru" );
    ASSERT_EQ( ex[5].Lang2.toStdString(), "fr" );
    ASSERT_EQ( ex[5].Category.toStdString(), "basic" );
}

TEST(TestModel, TranslationVariants)
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
    ASSERT_EQ( ex[4].Question.toStdString(), "un problème = <?>" );
    ASSERT_EQ( ex[4].Answer.toStdString(), "проблема" );
    ASSERT_EQ( svars.toStdString(), "сцена, отель, почта, центр, музей, проблема, река, год, принцип" );

    //printf( "%s\n", ex[4].Answer.toStdString().c_str() );
    //printf( "%s\n", svars.toStdString().c_str() );


    qsrand(1234);
    ListOfExercises fex2 = ex.Filter( gen[0]->Type(), "ru", "fr" );
    ASSERT_EQ( fex2.size(), 20 );

    ListOfExercises rex2 = fex2.Random( 10 );
    ASSERT_EQ( rex2.size(), 8 );

    QStringList vars2 = ex.Shuffle( ex[5], rex2 );
    ASSERT_EQ( vars2.size(), 9 );

    QString svars2 = vars2.join( ", ");
    ASSERT_EQ( ex[5].Question.toStdString(), "проблема = <?>" );
    ASSERT_EQ( ex[5].Answer.toStdString(), "un problème" );
    ASSERT_EQ( svars2.toStdString(), "une scène, un hôtel, une poste, un centre, un musée, un problème, un fleuve, une année, un principe" );
    //printf( "%s\n", ex[5].Answer.toStdString().c_str() );
    //printf( "%s\n", svars2.toStdString().c_str() );
}

TEST(TestModel, TagsAreOK)
{
    Model aModel;
    ASSERT_TRUE( aModel.Load( QString(TEST_DATA) + "/test5.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Trans() );
    ListOfExercises ex = aModel.Build( gen );
    ASSERT_EQ( ex.size(), 4 );

    ASSERT_EQ( ex[0].Tag.toStdString(), "просьба" );
    ASSERT_EQ( ex[1].Tag.toStdString(), "просьба" );
    ASSERT_EQ( ex[2].Tag.toStdString(), "благодарность" );
    ASSERT_EQ( ex[3].Tag.toStdString(), "благодарность" );
}
