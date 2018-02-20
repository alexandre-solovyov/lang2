
#include <DbReader.h>
#include <Rule.h>
#include <model/Tools.h>
#include <model/LangFile.h>
#include <model/Grammar.h>
#include <model/EG_Forms.h>
#include <QDir>

int main( int argc, char** argv )
{
    // Forms according to https://leconjugueur.lefigaro.fr/conjugaison/verbe/<SOME VERB>.html
    Rules r;

    r.Add( "00", "[a] ~ >> -, -, -, -, -, -" ); // verbes non conjugués

    r.Add( "1a", "[a] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );                             // chanter
    r.Add( "1A", "[a] ester >> -, -, -, -, -, -" );                                       // ester
    r.Add( "1b", "[a] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );                             // baisser, pleurer, etc.
    r.Add( "1c", "[a] ~yer >> ~yie, ~ies, ~ie, ~yons, ~yez, ~ient" );                     // ployer, essuyer
    r.Add( "1d", "[a] ~yer >> ~ie|~ye, ~ies|~yes, ~ie|~ye, ~yons, ~yez, ~ient, ~yent" );  // payer"
    r.Add( "1e", "[a] ~cer >> ~ce, ~ces, ~ce, ~çons, ~cez, ~cent" );                      // avancer, acquiescer
    r.Add( "1f", "[a] ~ger >> ~ge, ~ges, ~ge, ~geons, ~gez, ~gent" );                     // manger, déneiger
    r.Add( "1g", "[a] ~é~er >> ~è.e, ~è.es, ~è.e, ~é.ons, ~é.ez, ~è.ent" );               // céder
    r.Add( "1G", "[a] ~e~er >> ~è.e, ~è.es, ~è.e, ~e.ons, ~e.ez, ~è.ent" );               // halener
    r.Add( "1h", "[a] ~écer >> ~èce, ~èces, ~èce, ~éçons, ~écez, ~ècent" );               // rapiécer
    r.Add( "1i", "[a] ~éger >> ~ège, ~èges, ~ège, ~égeons, ~égez, ~ègent" );              // siéger
    r.Add( "1j", "[a] ~e~er >> ~è.e, ~è.es, ~è.e, ~e.ons, ~e.ez, ~è.ent" );               // semer, peler, acheter
    r.Add( "1k", "[a] dépecer >> dépèce, dépèces, dépèce, dépeçons, dépecez, dépècent" ); // dépecer
    r.Add( "1l", "[a] ~e.er >> ~e.&e, ~e.&es, ~e.&e, ~e.ons, ~e.ez, ~e.&ent" );           // appeler, jeter
    r.Add( "1m", "[a] ~e.er >> ~è.e|~e.&e, ~è.es|~e.&es, ~è.e|~e.&e, ~e.ons, ~e.ez, ~è.ent|~e.&ent" ); // harceler, haleter
    r.Add( "1w", "[a] arguer >> argue, argues, argue, arguons, arguez, arguent" );        // arguer
    r.Add( "1W", "[a] stérer >> stère, stères, stère, stérons, stérez, stèrent" );        // stérer
    r.Add( "1x", "[a] ~ficher >> ~fiche, ~fiches, ~fiche, ~fichons, ~fichez, ~fichent" ); // fiche(r)
    r.Add( "1X", "[a] ~fiche >> ~fiche, ~fiches, ~fiche, ~fichons, ~fichez, ~fichent" );  // fiche(r)
    r.Add( "1y", "[a] ~yer >> ~ie, ~ies, ~ie, ~yons, ~yez, ~ient" ); // envoyer
    r.Add( "1z", "[a] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" ); // *aller
    r.Add( "1Z", "[a] aller >> vais, vas, va, allons, allez, vont" ); // aller

    r.Add( "2a", "[a] ~(i|ï)r >> ~.s, ~.s, ~.t, ~.ssons, ~.ssez, ~.ssent" ); // finir
    r.Add( "2b", "[a] ~ïr >> ~is, ~is, ~it, ~ïssons, ~ïssez, ~ïssent" ); // haïr

    r.Add( "3a", "[a] ~rir >> ~re, ~res, ~re, ~rons, ~rez, ~rent" ); // ouvrir
    r.Add( "3b", "[a] ~illir >> ~ille, ~illes, ~ille, ~illons, ~illez, ~illent" ); // cueillir, saillir
    r.Add( "3c", "[a] ~illir >> ~ille, ~illes, ~ille, ~illons, ~illez, ~illent" ); // défaillir
    r.Add( "3d", "[a] ~(m|t|v)ir >> ~s, ~s, ~t, ~.ons, ~.ez, ~.ent" ); // dormir, mentir, partir
    r.Add( "3D", "[a] chauvir >> chauvis, chauvis, chauvit, chauvons, chauvez, chauvent" ); // chauvir
    r.Add( "3e", "[a] ~ir >> ~s, ~s, ~t, ~ons, ~ez, ~ent" ); // courir
    r.Add( "3f", "[a] ~mourir >> ~meurs, ~meurs, ~meurt, ~mourons, ~mourez, ~meurent" ); // mourir
    r.Add( "3g", "[a] ~enir >> ~iens, ~iens, ~ient, ~enons, ~enez, ~iennent" ); // venir, tenir
    r.Add( "3h", "[a] ~fuir >> ~fuis, ~fuis, ~fuit, ~fuyons, ~fuyez, ~fuient" ); // fuir
    r.Add( "3i", "[a] ~vêtir >> ~vêts, ~vêts, ~vêt, ~vêtons, ~vêtez, ~vêtent" ); // revêtir
    r.Add( "3j", "[a] ~érir >> ~iers, ~iers, ~iert, ~érons, ~érez, ~ièrent" ); // acquérir
    r.Add( "3k", "[a] ~bouillir >> ~bous, ~bous, ~bout, ~bouillons, ~bouillez, ~bouillent" ); // bouillir
    r.Add( "3l", "[a] gésir >> gis, gis, gît|git, gisons, gisez, gisent" ); // gésir
    r.Add( "3m", "[a] ouïr >> ois, ois, oit, oyons, oyez, oient" ); // ouïr

    r.Add( "4a", "[a] ~cevoir >> ~çois, ~çois, ~çoit, ~cevons, ~cevez, ~çoivent" ); // recevoir
    r.Add( "4b", "[a] ~devoir >> ~dois, ~dois, ~doit, ~devons, ~devez, ~doivent" ); // devoir
    r.Add( "4c", "[a] ~mouvoir >> ~meus, ~meus, ~meut, ~mouvons, ~mouvez, ~meuvent" ); // émouvoir, promouvoir, mouvoir
    r.Add( "4d", "[a] ~vouloir >> ~veux, ~veux, ~veut, ~voulons, ~voulez, ~veulent" ); // vouloir
    r.Add( "4e", "[a] pouvoir >> peux|puis, peux, peut, pouvons, pouvez, peuvent" ); // pouvoir
    r.Add( "4f", "[a] savoir >> sais, sais, sait, savons, savez, savent" ); // savoir
    r.Add( "4g", "[a] ~valoir >> vaux, vaux, vaut, valons, valez, valent" ); // valoir
    r.Add( "4G", "[a] ~falloir >> -, -, ~faut, -, -, -" ); // falloir
    r.Add( "4h", "[a] prévaloir >> prévaux, prévaux, prévaut, prévalons, prévalez, prévalent" ); // prévaloir
    r.Add( "4i", "[a] ~voir >> ~vois, ~vois, ~voit, ~voyons, ~voyez, ~voient" ); // voir
    r.Add( "4j", "[a] ~voir >> ~vois, ~vois, ~voit, ~voyons, ~voyez, ~voient" ); // prévoir
    r.Add( "4k", "[a] ~oir >> ~ois, ~ois, ~oit, ~oyons, ~oyez, ~oient" ); // pourvoir, déchoir
    r.Add( "4l", "[a] ~seoir >> ~sois|~sieds, ~sois|~sieds, ~soit|~sied, ~soyons|~seyons, ~soyez|~seyez, ~soient|~seyent" ); // asseoir
    r.Add( "4m", "[a] surseoir >> sursois, sursois, sursoit, sursoyons, sursoyez, sursoient" ); // surseoir
    r.Add( "4n", "[a] seoir >> -, -, sied, -, -, siéent" ); // seoir
    r.Add( "4N", "[a] messeoir >> -, -, messied, -, -, messiéent" ); // messeoir
    r.Add( "4o", "[a] ~pleuvoir >> -, -, ~pleut, -, -, ~pleuvent"); // pleuvoir
    r.Add( "4p", "[a] échoir >> -, -, échoit|échet, -, -, échoient|échéent"); // échoir
    r.Add( "4q", "[a] choir >> chois, chois, choit, choyons, choyez, choient"); // choir

    r.Add( "5a", "[a] ~re >> ~s, ~s, ~, ~ons, ~ez, ~ent" ); // vendre, mordre, perdre
    r.Add( "5b", "[a] ~rompre >> ~romps, ~romps, ~rompt, ~rompons, ~rompez, ~rompent" ); // rompre
    r.Add( "5c", "[a] ~dre >> ~ds, ~ds, ~d, ~ons, ~ez, ~nent" ); // prendre
    r.Add( "5d", "[a] ~indre >> ~ins, ~ins, ~int, ~ignons, ~ignez, ~ignent" ); // craindre, peindre
    r.Add( "5D", "[a] poindre >> -, -, point, -, -, poignent" ); // poindre
    r.Add( "5e", "[a] ~battre >> ~bats, ~bats, ~bat, ~battons, ~battez, ~battent" ); // battre
    r.Add( "5f", "[a] ~mettre >> ~mets, ~mets, ~met, ~mettons, ~mettez, ~mettent" ); // mettre
    r.Add( "5g", "[a] ~moudre >> ~mouds, ~mouds, ~moud, ~moulons, ~moulez, ~moulent" ); // moudre
    r.Add( "5h", "[a] ~coudre >> ~couds, ~couds, ~coud, ~cousons, ~cousez, ~cousent" ); // coudre
    r.Add( "5i", "[a] ~soudre >> ~sous, ~sous, ~sout, ~solvons, ~solvez, ~solvent" ); // absoudre
    r.Add( "5I", "[a] soudre >> sous, sous, sout, solvons, solvez, solvent" ); // soudre

    r.Add( "5k", "[a] ~suivre >> ~suis, ~suis, ~suit, ~suivons, ~suivez, ~suivent" ); // suivre
    r.Add( "5l", "[a] ~vivre >> ~vis, ~vis, ~vit, ~vivons, ~vivez, ~vivent" ); // vivre
    r.Add( "5m", "[a] ~ître >> ~is, ~is, ~ît, ~issons, ~issez, ~issent" ); // paraître, accroître
    r.Add( "5n", "[a] ~naître >> nais, nais, naît, naissons, naissez, naissent" ); // naître
    r.Add( "5o", "[a] ~croître >> ~croîs, ~croîs, ~croît, ~croissons, ~croissez, ~croissent" ); // croître
    r.Add( "5p", "[a] ~vaincre >> ~vaincs, ~vaincs, ~vainc, ~vainquons, ~vainquez, ~vainquent" ); // vaincre
    r.Add( "5q", "[a] ~foutre >> ~fous, ~fous, ~fout, ~foutons, ~foutez, ~foutent" ); // foutre
    r.Add( "5j", "[a] résoudre >> résous, résous, résout, résolvons, résolvez, résolvent" ); // résoudre
    r.Add( "6a", "[a] ~re >> ~s, ~s, ~t, ~ons, ~ez, ~ent" ); // rire, conclure
    r.Add( "6A", "[a] (re|per)clure >> -, -, -, -, -, -" ); // reclure
    r.Add( "6b", "[a] ~uire >> ~uis, ~uis, ~uit, ~uisons, ~uisez, ~nuisent" ); // nuire
    r.Add( "6c", "[a] ~ire >> ~is, ~is, ~it, ~isons, ~isez, ~isent" ); // conduire, confire
    r.Add( "6C", "[a] ~ire >> ~is, ~is, ~it, ~isons, ~isez, ~isent" ); // circoncire
    r.Add( "6d", "[a] ~rire >> ~ris, ~ris, ~rit, ~rivons, ~rivez, ~rivent" ); // écrire
    r.Add( "6e", "[a] ~suffire >> ~suffis, ~suffis, ~suffit, ~suffisons, ~suffisez, ~suffisent" ); // suffire
    r.Add( "6f", "[a] ~dire >> ~dis, ~dis, ~dit, ~disons, ~dites, ~disent" ); // dire
    r.Add( "6g", "[a] ~maudire >> ~maudis, ~maudis, ~maudit, ~maudissons, ~maudissez, ~maudissent" ); // maudire
    r.Add( "6h", "[a] ~lire >> ~lis, ~lis, ~lit, ~lisons, ~lisez, ~lisent" ); // lire
    r.Add( "6i", "[a] ~croire >> ~crois, ~crois, ~croit, ~croyons, ~croyez, ~croient" ); // croire
    r.Add( "6j", "[a] ~boire >> ~bois, ~bois, ~boit, ~buvons, ~buvez, ~boivent" ); // boire
    r.Add( "6J", "[a] emboire >> embois, embois, emboit, embuvons, embuvez, emboivent" ); // emboire
    r.Add( "6k", "[a] ~faire >> ~fais, ~fais, ~fait, ~faisons, ~faites, ~font" ); // faire
    r.Add( "6K", "[a] ~faire >> ~fais, ~fais, ~fait, ~faisons, ~faites, ~font" ); // surfaire
    r.Add( "6l", "[a] ~plaire >> ~plais, ~plais, ~plaît|~plait, ~plaisons, ~plaisez, ~plaisent" ); // plaire
    r.Add( "6m", "[a] taire >> tais, tais, tait, taisons, taisez, taisent"); // taire
    r.Add( "6n", "[a] ~ire >> ~is, ~is, ~it, ~yons, ~yez, ~ient" ); // extraire, bruire
    r.Add( "6N", "[a] ~ire >> ~is, ~is, ~it, ~yons, ~yez, ~ient" ); // attraire
    r.Add( "6o", "[a] ~clore >> ~clos, ~clos, ~clot, -, -, ~closent" ); // clore
    r.Add( "6O", "[a] ~clore >> ~clos, ~clos, ~clôt, -, -, ~closent" ); // clore
    r.Add( "7K", "[a] forfaire >> -, -, -, -, -, -" ); // forfaire
    r.Add( "7K", "[a] stupéfaire >> -, -, stupéfait, -, -, -" ); // stupéfaire

    r.Add( "9a", "[a] avoir >> ai, as, a, avons, avez, ont" ); // avoir
    r.Add( "9b", "[a] être >> suis, es, est, sommes, êtes, sont" ); // être

    bool isOK;
    //Tools::print( r.Forms("parler", "1b"), isOK );
    //Tools::print( r.Forms("appeler", "1l", isOK) );
    //Tools::print( r.Forms("jeter", "1l", isOK) );
    //Tools::print( r.Forms("harceler", "1m", isOK) );
    //Tools::print( r.Forms("haleter", "1m", isOK) );


#ifdef WIN32
    QString DB_FILE = "d:/asl/lang3/lang/db/dubois.xml";
    QString T_FILE = "d:/asl/lang3/lang/testdata/pr_ind.lang";"
#else
    QString DB_FILE = QDir::home().absoluteFilePath( "lang2/db/dubois.xml" );
    QString T_FILE = QDir::home().absoluteFilePath( "lang2/testdata/pr_ind.lang" );
#endif

    Grammar aGrammar;
    LangFile aLangFile;
    aLangFile.Load( T_FILE );

    QList<IGenerator*> gen;
    gen.append( new EG_Forms(&aGrammar, true) );
    aLangFile.Build(gen, false);

    DbReader aReader( DB_FILE, 20000, 200, 1 );
    aReader.Perform(&r, &aGrammar);


    Tools::print( "\n\nRESULTS:" );
    Tools::print( QString( "  %0 verbs" ).arg( aReader.Count() ) );

    QStringList err = aReader.Errors();
    Tools::print( QString( "  %0 errors:\n    %1" ).arg( err.count() ).arg( err.join("\n    ")) );
    // 12308

    return 0;
}
