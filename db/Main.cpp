
#include <DbReader.h>
#include <Rule.h>
#include <model/Tools.h>

int main( int argc, char** argv )
{
    // Forms according to https://leconjugueur.lefigaro.fr/conjugaison/verbe/<SOME VERB>.html
    Rules r;

    r.Add( "00", "[a] ~ >> -, -, -, -, -, -" ); // verbes non conjugués

    r.Add( "1a", "[a] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );                            // chanter
    r.Add( "1b", "[a] ~er >> ~e, ~es, ~e, ~ons, ~ez, ~ent" );                            // baisser, pleurer, etc.
    r.Add( "1c", "[a] ~yer >> ~yie, ~ies, ~ie, ~yons, ~yez, ~ient" );                    // ployer, essuyer
    r.Add( "1d", "[a] ~yer >> ~ie|~ye, ~ies|~yes, ~ie|~ye, ~yons, ~yez, ~ient, ~yent" ); // payer"
    r.Add( "1e", "[a] ~cer >> ~ce, ~ces, ~ce, ~çons, ~cez, ~cent" );                     // avancer, acquiescer
    r.Add( "1f", "[a] ~ger >> ~ge, ~ges, ~ge, ~geons, ~gez, ~gent" ); // manger, déneiger
    r.Add( "1g", "[a] ~é~er >> ~è.e, ~è.es, ~è.e, ~é.ons, ~é.ez, ~è.ent" ); // céder
    r.Add( "1h", "[a] ~écer >> ~èce, ~èces, ~èce, ~éçons, ~écez, ~ècent" ); // rapiécer
    r.Add( "1i", "[a] ~éger >> ~ège, ~èges, ~ège, ~égeons, ~égez, ~ègent" ); // siéger
    r.Add( "1j", "[a] ~e~er >> ~è.e, ~è.es, ~è.e, ~e.ons, ~e.ez, ~è.ent" ); // semer, peler, acheter
    r.Add( "1k", "[a] dépecer >> dépèce, dépèces, dépèce, dépeçons, dépecez, dépècent" ); // dépecer
    r.Add( "1l", "[a] ~e.er >> ~e.&e, ~e.&es, ~e.&e, ~e.ons, ~e.ez, ~e.&ent" ); // appeler, jeter
    r.Add( "1m", "[a] ~e.er >> ~è.e|~e.&e, ~è.es|~e.&es, ~è.e|~e.&e, ~e.ons, ~e.ez, ~è.ent|~e.&ent" ); // harceler, haleter
    r.Add( "1w", "[a] arguer >> argue, argues, argue, arguons, arguez, arguent" ); // arguer
    r.Add( "1x", "[a] ~ficher >> ~fiche, ~fiches, ~fiche, ~fichons, ~fichez, ~fichent" ); // fiche(r)
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
    r.Add( "3i", "[a] ~vêtir >> ~vêts, ~vêts, ~vêt, ~vêtons, ~vêtez, ~vêtent" ); // revêtir
    r.Add( "3j", "[a] ~érir >> ~iers, ~iers, ~iert, ~érons, ~érez, ~ièrent" ); // acquérir
    r.Add( "3k", "[a] ~bouillir >> ~bous, ~bous, ~bout, ~bouillons, ~bouillez, ~bouillent" ); // bouillir

    r.Add( "4a", "[a] ~cevoir >> ~çois, ~çois, ~çoit, ~cevons, ~cevez, ~çoivent" ); // recevoir
    r.Add( "4b", "[a] devoir >> dois, dois, doit, devons, devez, doivent" ); // devoir
    r.Add( "4l", "[a] asseoir >> assois|assieds, assois|assieds, assoit|assied, assoyons|asseyons, assoyez|asseyez, assoient|asseyent" ); // asseoir

    r.Add( "5a", "[a] ~re >> ~s, ~s, ~, ~ons, ~ez, ~ent" ); // vendre, mordre, perdre
    r.Add( "5c", "[a] ~dre >> ~ds, ~ds, ~d, ~ons, ~ez, ~nent" ); // prendre
    r.Add( "5d", "[a] ~indre >> ~ins, ~ins, ~int, ~ignons, ~ignez, ~ignent" ); // craindre, peindre
    r.Add( "5e", "[a] ~battre >> ~bats, ~bats, ~bat, ~battons, ~battez, ~battent" ); // battre
    r.Add( "5f", "[a] ~mettre >> ~mets, ~mets, ~met, ~mettons, ~mettez, ~mettent" ); // mettre
    r.Add( "5i", "[a] ~soudre >> ~sous, ~sous, ~sout, ~solvons, ~solvez, ~solvent" ); // absoudre
    r.Add( "5m", "[a] ~ître >> ~is, ~is, ~ît, ~issons, ~issez, ~issent" ); // paraître, accroître

    r.Add( "6a", "[a] ~re >> ~s, ~s, ~t, ~ons, ~ez, ~ent" ); // rire, conclure
    r.Add( "6c", "[a] ~ire >> ~is, ~is, ~it, ~isons, ~isez, ~isent" ); // conduire, confire
    r.Add( "6e", "[a] ~suffire >> ~suffis, ~suffis, ~suffit, ~suffisons, ~suffisez, ~suffisent" ); // suffire
    r.Add( "6i", "[a] ~croire >> ~crois, ~crois, ~croit, ~croyons, ~croyez, ~croient" ); // croire
    r.Add( "6j", "[a] ~boire >> ~bois, ~bois, ~boit, ~buvons, ~buvez, ~boivent" ); // boire
    r.Add( "6k", "[a] ~faire >> ~fais, ~fais, ~fait, ~faisons, ~faites, ~font" ); // faire
    r.Add( "6n", "[a] ~ire >> ~is, ~is, ~it, ~yons, ~yez, ~ient" ); // extraire, bruire
    r.Add( "6N", "[a] ~ire >> ~is, ~is, ~it, ~yons, ~yez, ~ient" ); // attraire

    r.Add( "9a", "[a] avoir >> ai, as, a, avons, avez, ont" ); // avoir
    r.Add( "9b", "[a] être >> suis, es, est, sommes, êtes, sont" ); // être

    bool isOK;
    //Tools::print( r.Forms("parler", "1b"), isOK );
    //Tools::print( r.Forms("appeler", "1l", isOK) );
    //Tools::print( r.Forms("jeter", "1l", isOK) );
    //Tools::print( r.Forms("harceler", "1m", isOK) );
    //Tools::print( r.Forms("haleter", "1m", isOK) );

    DbReader aReader( "d:/asl/lang3/lang/db/dubois.xml", 20000, 20, false );
    aReader.Perform(&r);
    Tools::print( QString( "\n%0 verbs" ).arg( aReader.Count() ) );
    // 12308

    return 0;
}
