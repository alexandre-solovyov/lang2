
#include <DbReader.h>
#include <Rule.h>
#include <model/Tools.h>
#include <QFile>
#include <QXmlStreamReader>

DbReader::DbReader( const QString& theFileName, int theLimit, int theErrLimit, bool isVerbose )
    : myFileName( theFileName ), myLimit( theLimit ), myErrLimit( theErrLimit ), myCount( 0 ), myErrorCount( 0 ), myRules( 0 ), myIsVerbose( isVerbose )
{
}

DbReader::~DbReader()
{
}

int DbReader::Count() const
{
    return myCount;
}

bool DbReader::Perform( Rules* theRules )
{
    myRules = theRules;

    QFile aFile( myFileName );
    if( !aFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        Tools::print( "Cannot read file: " + aFile.errorString() );
        return false;
    }

    myCount = 0;
    myErrorCount = 0;

    QXmlStreamReader aReader( &aFile );
    while( aReader.readNextStartElement() )
    {
        //Tools::print( ">> " + aReader.name().toString() );
        if( aReader.name()=="verbes" )
        {
            PerformVerbs( aReader );
            if( myCount>=myLimit )
                break;
        }
        else
            aReader.skipCurrentElement();
    }

    aFile.close();
    return true;
}

void DbReader::PerformVerbs( QXmlStreamReader& theReader )
{
    while( theReader.readNextStartElement() )
    {
        //Tools::print( "  >> " + theReader.name().toString() );
        if( theReader.name() == "verbe" )
        {
            PerformVerb( theReader );
            if( myCount>=myLimit || myErrorCount>=myErrLimit )
                break;
        }
        else
            theReader.skipCurrentElement();
    }
}

void DbReader::PerformVerb( QXmlStreamReader& theReader )
{
    QString word = theReader.attributes().value( "mot" ).toString();

    bool isFound = false;
    while( theReader.readNextStartElement() )
    {
        if( theReader.name()=="entree" )
        {
            if( !isFound )
            {
                //Tools::print( "    >> " + theReader.name().toString() );
                while( theReader.readNextStartElement() )
                {
                    if( theReader.name()=="conjugaison" )
                    {
                        QString group = theReader.readElementText();
                        group = group.left( 2 );
                        PerformData( word, group );
                    }
                    else
                        theReader.skipCurrentElement();
                }
                isFound = true;
            }
            else
                theReader.skipCurrentElement();
        }
    }

    //Tools::print( "    >> " + theReader.name().toString() );
    myCount++;
}

void DbReader::PerformData( const QString& theWord, const QString& theGroup )
{
    if( myIsVerbose )
        Tools::print( theWord + ": " + theGroup );

    QString forms;
    bool isOK;
    if( myRules )
    {
        forms = myRules->Forms( theWord, theGroup, isOK );
        if( !isOK )
            myErrorCount++;
    }

    if( myIsVerbose )
        Tools::print( forms+"\n" );
}
