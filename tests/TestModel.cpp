
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
    QList<Exercise> ex = aModel.Build( gen );
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
    QList<Exercise> ex = aModel.Build( gen );
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
