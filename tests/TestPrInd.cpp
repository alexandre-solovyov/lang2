
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
    ASSERT_EQQ( GR.Forms("PrInd", "céder").toString(), "cède, cèdes, cède, cédons, cédez, cèdent");
    ASSERT_EQQ( GR.Forms("PrInd", "acheter").toString(), "achète, achètes, achète, achetons, achetez, achètent");
    ASSERT_EQQ( GR.Forms("PrInd", "jeter").toString(), "jette, jettes, jette, jetons, jetez, jettent");
    ASSERT_EQQ( GR.Forms("PrInd", "projeter").toString(), "projette, projettes, projette, projetons, projetez, projettent");
    ASSERT_EQQ( GR.Forms("PrInd", "ensorceler").toString(), "ensorcèle, ensorcèles, ensorcèle, ensorcelons, ensorcelez, ensorcèlent");
    ASSERT_EQQ( GR.Forms("PrInd", "appeler").toString(), "appelle, appelles, appelle, appelons, appelez, appellent");
    ASSERT_EQQ( GR.Forms("PrInd", "rappeler").toString(), "rappelle, rappelles, rappelle, rappelons, rappelez, rappellent");
    ASSERT_EQQ( GR.Forms("PrInd", "interpeler").toString(), "interpelle, interpelles, interpelle, interpelons, interpelez, interpellent");
    ASSERT_EQQ( GR.Forms("PrInd", "peler").toString(), "pèle, pèles, pèle, pelons, pelez, pèlent");
    ASSERT_EQQ( GR.Forms("PrInd", "maugréer").toString(), "maugrée, maugrées, maugrée, maugréons, maugréez, maugréent");
    ASSERT_EQQ( GR.Forms("PrInd", "apprécier").toString(), "apprécie, apprécies, apprécie, apprécions, appréciez, apprécient");
    ASSERT_EQQ( GR.Forms("PrInd", "payer").toString(), "paye|paie, payes|paies, paye|paie, payons, payez, payent|paient");
    ASSERT_EQQ( GR.Forms("PrInd", "rayer").toString(), "raye, rayes, raye, rayons, rayez, rayent");
    ASSERT_EQQ( GR.Forms("PrInd", "ennuyer").toString(), "ennuie, ennuies, ennuie, ennuyons, ennuyez, ennuient");
    ASSERT_EQQ( GR.Forms("PrInd", "envoyer").toString(), "envoie, envoies, envoie, envoyons, envoyez, envoient");
}

TEST(TestPrInd, Group2IsOK)
{
    load();

    ASSERT_EQQ( GR.Forms("PrInd", "finir").toString(), "finis, finis, finit, finissons, finissez, finissent");
    ASSERT_EQQ( GR.Forms("PrInd", "haïr").toString(), "hais, hais, hait, haïssons, haïssez, haïssent" );
    ASSERT_EQQ( GR.Forms("PrInd", "amuïr").toString(), "amuis, amuis, amuit, amuïssons, amuïssez, amuïssent" );
    ASSERT_EQQ( GR.Forms("PrInd", "assortir").toString(), "assortis, assortis, assortit, assortissons, assortissez, assortissent" );
    ASSERT_EQQ( GR.Forms("PrInd", "réassortir").toString(), "réassortis, réassortis, réassortit, réassortissons, réassortissez, réassortissent" );
    ASSERT_EQQ( GR.Forms("PrInd", "sertir").toString(), "sertis, sertis, sertit, sertissons, sertissez, sertissent" );
    ASSERT_EQQ( GR.Forms("PrInd", "répartir").toString(), "répartis, répartis, répartit, répartissons, répartissez, répartissent" );
    ASSERT_EQQ( GR.Forms("PrInd", "maudire").toString(), "maudis, maudis, maudit, maudissons, maudissez, maudissent" );
}

TEST(TestPrInd, Group3IsOK)
{
    load();

    ASSERT_EQQ( GR.Forms("PrInd", "aller").toString(), "vais, vas, va, allons, allez, vont");
    ASSERT_EQQ( GR.Forms("PrInd", "être").toString(), "suis, es, est, sommes, êtes, sont" );
    ASSERT_EQQ( GR.Forms("PrInd", "tenir").toString(), "tiens, tiens, tient, tenons, tenez, tiennen" );
    ASSERT_EQQ( GR.Forms("PrInd", "venir").toString(), "viens, viens, vient, venons, venez, viennen" );
    ASSERT_EQQ( GR.Forms("PrInd", "souvenir").toString(), "souviens, souviens, souvient, souvenons, souvenez, souviennen" );
    ASSERT_EQQ( GR.Forms("PrInd", "sentir").toString(), "sens, sens, sent, sentons, sentez, sentent" );
    ASSERT_EQQ( GR.Forms("PrInd", "mentir").toString(), "mens, mens, ment, mentons, mentez, mentent" );
    ASSERT_EQQ( GR.Forms("PrInd", "partir").toString(), "pars, pars, part, partons, partez, partent" );
    ASSERT_EQQ( GR.Forms("PrInd", "repartir").toString(), "repars, repars, repart, repartons, repartez, repartent" );
    ASSERT_EQQ( GR.Forms("PrInd", "sortir").toString(), "sors, sors, sort, sortons, sortez, sortent" );
    ASSERT_EQQ( GR.Forms("PrInd", "ressortir").toString(), "ressors, ressors, ressort, ressortons, ressortez, ressortent" );
}

