
#include <tests.h>
#include <model/PrefixModel.h>

QString pr(const PrefixModel& pm, const QString& prefix)
{
    QStringList st = pm.Starts(prefix);
    QStringList qst;
    foreach( QString s, st )
        qst += QString( "'%0'" ).arg( s );

    return QString("[%0]").arg(qst.join(", "));
}

TEST(TestPrefixModel, AdditionIsOK)
{
    PrefixModel pm;
    pm.Add("trans");
    ASSERT_EQ(pm.Size(), 1);
    ASSERT_EQQ(pr(pm, "trans"), "['']");

    pm.Add("r + h, r + <a>, ré + h, ré + <a>, re + <c>");
    ASSERT_EQ(pm.Size(), 4);
    ASSERT_EQQ(pr(pm, "r"), "['h', '<a>']");

    pm.Add("im + m + b + p" );
    ASSERT_EQ(pm.Size(), 5);
    ASSERT_EQQ(pr(pm, "im"), "['m', 'b', 'p']");
}

TEST(TestPrefixModel, MatchIsOK)
{
    PrefixModel pm;

    pm.Add("r+h+<a>, ré+h+<a>, res+s, re+<c>-sh");

    ASSERT_TRUE ( pm.Match("repartir", "re") );
    ASSERT_FALSE( pm.Match("répartir", "ré") );

    ASSERT_FALSE( pm.Match("resortir",  "re" ) );
    ASSERT_TRUE ( pm.Match("ressortir", "res") );

    ASSERT_FALSE( pm.Match("assortir",   "as") );
    ASSERT_TRUE ( pm.Match("réagir",     "ré") );
    ASSERT_TRUE ( pm.Match("réécrire",   "ré") );
    ASSERT_TRUE ( pm.Match("réassortir", "ré") );

    ASSERT_TRUE ( pm.Match("réhabiliter", "ré") );
    ASSERT_TRUE ( pm.Match("rhabiller", "r") );
}
