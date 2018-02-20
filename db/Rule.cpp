
#include <Rule.h>
#include <model/Tools.h>
#include <model/GrammarSet.h>

/*
int common( const QString& s1, const QString& s2 )
{
    int c = 0;
    for( int i=0, n=qMin(s1.length(), s2.length()); i<n; i++ )
        if( s1[i]==s2[i] )
            c++;
        else
            break;

    return c;
}

Rule::Rule( const QString& theWord, const QString& theForms )
{
    QStringList forms = theForms.split( ", " );

    int c = theWord.length();
    for( int i=0, n=forms.size(); i<n; i++ )
    {
        forms[i] = forms[i].trimmed();
        c = qMin( c, common( theWord, forms[i]) );
    }

    myN = c - theWord.length();

    for( int i=0, n=forms.size(); i<n; i++ )
    {
        forms[i] = forms[i].mid( c );
    }

    myForms = forms;
}

Rule::~Rule()
{
}

QString Rule::toString() const
{
    return QString( "%0 %1").arg( myN ).arg( myForms.join( ", ") );
}

QString Rule::forms( const QString& theWord ) const
{
    QString base;
    if( myN<0 )
        base = theWord.left( theWord.length() + myN );

    QStringList forms;
    foreach( QString f, myForms )
        forms.append( base + f );
    return forms.join( ", " );
}
*/

Rules::Rules()
{
}

Rules::~Rules()
{
}

void Rules::Add( const QString& theGroup, const QString& thePattern )
{
    myRules.insert( theGroup, GrammarRule( thePattern ) );
}

/*Rule Rules::Get( const QString& theGroup ) const
{
    if( myRules.contains(theGroup) )
        return myRules[theGroup];
    else
        return Rule();
}*/

QString Rules::Forms( const QString& theWord, const QString& theGroup, QString& theError ) const
{
    theError = "";
    if( myRules.contains(theGroup) )
    {
        GrammarSet res = myRules[theGroup].Forms(theWord);
        if( res.isEmpty() )
        {
            theError = QString( "EMPTY GRAMMAR SET: %0; %1" ).arg( theWord ).arg( theGroup);
            return "";
        }
        else
        {
            return res.toString();
        }
    }
    else
    {
        theError = QString( "NOT FOUND GROUP: %0; %1" ).arg( theGroup ).arg( theWord );
        return "";
    }
}
