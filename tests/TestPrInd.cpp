
#include <tests.h>
#include <model/LangFile.h>
#include <model/Grammar.h>
#include <model/GrammarSet.h>
#include <model/EG_Forms.h>

LangFile LF;
Grammar GR;

void load()
{
    static bool isLoaded = false;
    if( isLoaded )
        return;

    ASSERT_TRUE( LF.Load( QString(TEST_DATA) + "/pr_ind.lang" ) );

    QList<IGenerator*> gen;
    gen.append( new EG_Forms(&GR, true) );
    LF.Build(gen, false);

    isLoaded = true;
}

TEST(TestPrInd, Group1IsOK)
{
    load();

    ASSERT_EQQ( GR.Forms("PrInd", "aimer").toString(), "aime, aimes, aime, aimons, aimez, aiment");
    ASSERT_EQQ( GR.Forms("PrInd", "commencer").toString(), "commence, commences, commence, commençons, commencez, commencent");
    ASSERT_EQQ( GR.Forms("PrInd", "agacer").toString(), "agace, agaces, agace, agaçons, agacez, agacent");
    ASSERT_EQQ( GR.Forms("PrInd", "juger").toString(), "juge, juges, juge, jugeons, jugez, jugent");
    ASSERT_EQQ( GR.Forms("PrInd", "conjuguer").toString(), "conjugue, conjugues, conjugue, conjuguons, conjuguez, conjuguent");
    ASSERT_EQQ( GR.Forms("PrInd", "peser").toString(), "pèse, pèses, pèse, pesons, pesez, pèsent");
}
