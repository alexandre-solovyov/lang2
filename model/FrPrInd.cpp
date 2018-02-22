
#include <model/FrPrInd.h>
#include <model/GrammarSet.h>
#include <model/Tools.h>

static GrammarSet ALLER( "vais, vas, va, allons, allez, vont", ", " );
static GrammarSet STD_1( "e, es, e, ons, ez, ent", ", " );
static GrammarSet STD_2( "is, is, it, issons, issez, issent", ", " );
static QString E = "éè";
static QString C = "ç";

FrPrInd::FrPrInd( Grammar* theGrammar )
    : ITense( "PrInd", theGrammar )
{
}

FrPrInd::~FrPrInd()
{
}

QString sum_verb_let( const QString& s1, const QString& s2 )
{
    int l = s1.length()-1;
    QString res = s1;
    if( s1[l] == 'g' && s2[0] == 'o')
    {
        res += 'e';
    }
    if( s1[l] == 'c' && s2[0] == 'o')
    {
        res[l] = C[0];
    }
    res += s2;
    return res;
}

GrammarSet sum_verb( const GrammarSet& s1, const GrammarSet& s2 )
{
    GrammarSet aSet;
    for( int i=0, n=qMin(s1.size(), s2.size()); i<n; i++ )
    {
         aSet.append( sum_verb_let( s1[i], s2[i] ) );
    }
    return aSet;
}

GrammarSet sum_verb( const QString& s1, const GrammarSet& s2 )
{
    GrammarSet aSet;
    for( int i=0, n=s2.size(); i<n; i++ )
    {
         aSet.append( sum_verb_let( s1, s2[i] ) );
    }
    return aSet;
}

GrammarSet group_1( const QString& base )
{
    GrammarSet aBase( base, STD_1.size() );

    int i = base.length()-1;
    while(i>=1 && ( !Tools::isVowel(base[i]) || base.mid(i-1,2)=="qu") )
        i--;
    if( i>=0 )
    {
        QChar v = base[i];
        //Tools::print( base + " " + QString(v));
        if( v==E[0] )
        {
            aBase[0][i] = E[1];
            aBase[1][i] = E[1];
            aBase[2][i] = E[1];
            aBase[5][i] = E[1];
        }
    }
    return sum_verb( aBase, STD_1 );
}

GrammarSet group_2( const QString& base )
{
    GrammarSet aBase( base, STD_2.size() );
    return sum_verb( aBase, STD_2 );
}

GrammarSet group_3( const QString& base, const QString& end )
{
    static GrammarSet SS( "s, s, , tons, tez, tent", ", " );
    if( base.endsWith("batt") || base.endsWith("mett") )
    {
        QString base1 = base.left(base.length()-1);
        return sum_verb( base1, SS );
    }

    GrammarSet res;
    return res;
}

GrammarSet FrPrInd::Forms( const QString& theWord ) const
{
    GrammarSet gs;
    if( theWord.size() <= 2 )
        return gs;

    QString base = theWord.left(theWord.length()-2);
    QString e = theWord.right(2);

    if( e=="er" )
    {
        if( theWord=="aller" )
            return ALLER;
        else
            return group_1( base );
    }

    gs = group_3( base, e );
    if( gs.isEmpty() && e=="ir" )
        gs = group_2( base );

    return gs;
}
