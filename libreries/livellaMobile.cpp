#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include "livellaMobile.h"

#define GUIDA_DIMX 40
#define GUIDA_DIMY 40
#define GUIDA_DIST_REL 20

#define LIV_REF_H 50

#pragma region // Funzioni ausiliarie per l'inizializzazione della Livella

    // Funzione che permette di determinare il valore della corsa delle guide prismatiche in funzione della percentuale
    float liv_determinacorsa(GuidaPrismatica * guida, float perc){

        float res;

        float corsa_utile = guida->lunghezza - guida->incastri->dim_x - guida->guida->dim_x / 2;

        res = guida->incastri->dim_x / 2 + perc * corsa_utile / 100;

        return res;
    }

    // Funzione che permette di determinare le coordinate del centro dei supporti (guide prismatiche) della machine
    void liv_impostaposizione_supporti(LivellaMobile * livella){

        float pos = livella->pos_x;
        pos -= livella->supporto[0]->lunghezza / 2 + livella->supporto[0]->incastri->dim_x / 2;
        pos -= GUIDA_DIST_REL / 2;
        livella->supporto[0]->pos_x = pos;

        pos += livella->supporto[0]->lunghezza + GUIDA_DIST_REL + livella->supporto[0]->incastri->dim_x;
        livella->supporto[1]->pos_x = pos;

    }

    // funzione che permette di determinare la posizione orizzontale dei pistoni della livella, usate nella funzione successiva
    float liv_livposfromsup(LivellaMobile * liv, unsigned int index){
        return liv->supporto[index]->pos_x - liv->supporto[index]->lunghezza/2 + liv->supporto[index]->corsa;
    }

    // Funzione che permette di calcolare la posizione associata ai pistoni della livella
    void liv_posisizionilivella(LivellaMobile * livella){

        livella->dati_livella.posy = livella->pos_y - livella->dati_livella.alt_cilindro;

        livella->dati_livella.posx1 = liv_livposfromsup(livella, 0) - livella->dati_livella.largbase / 2;
        livella->dati_livella.posx2 = liv_livposfromsup(livella, 1) - livella->dati_livella.largbase / 2;

    }

    // Funzione che permette di inizializzare la livella determinandone la posizione e utilizzando i dati nella struttura dati_livella
    void liv_inizializzalivella(LivellaMobile * livella ){
        
        liv_posisizionilivella(livella);

        livella->livella = livella_init( 
                livella->dati_livella.posx1,
                livella->dati_livella.posx2,
                livella->dati_livella.posy,
                livella->dati_livella.alt_cilindro,
                livella->dati_livella.largbase,
                livella->dati_livella.largtesta,
                livella->dati_livella.alt_sx,
                livella->dati_livella.alt_dx,
                livella->dati_livella.spessore,
                livella->dati_livella.lunghezza
            );
    }

    // Funzione che inizializza i dati della struttura dati_livella
    void liv_inizializza_dati(LivellaMobile * livella ){

        livella->dati_livella.alt_cilindro = LIV_REF_H;
        livella->dati_livella.alt_dx = 50;
        livella->dati_livella.alt_sx = 30;
        livella->dati_livella.largbase = livella->supporto[0]->guida->dim_x * 4 / 5;
        livella->dati_livella.largtesta = livella->dati_livella.largbase * 2/3;
        livella->dati_livella.spessore = 15;
        livella->dati_livella.lunghezza = livella->distanza * 1.7;

    }

#pragma endregion

LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc, float alt_cil, float alt_sx, float alt_dx){

    LivellaMobile * livella = new LivellaMobile;

    livella->pos_x = posx;
    livella->pos_y = posy;

    if(perc < 0 || perc > 100) perc = 20;

    livella->distanza = dist;
    livella->perc_corsa = perc;

    livella->supporto[0] = guida_init(
            0,
            livella->pos_y,
            2 * (livella->distanza / 2 - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2),
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );

    livella->supporto[1] = guida_init(
            0,
            livella->pos_y,
            2 * (livella->distanza / 2 - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2),
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );
    liv_impostaposizione_supporti( livella );

    guida_set_corsa( livella->supporto[0], liv_determinacorsa(livella->supporto[0], livella->perc_corsa) );
    guida_set_corsa( livella->supporto[1], liv_determinacorsa(livella->supporto[1], livella->perc_corsa) );

    liv_inizializza_dati( livella );

    livella->dati_livella.alt_cilindro = alt_cil;
    livella->dati_livella.alt_sx = alt_sx;
    livella->dati_livella.alt_dx = alt_dx;

    liv_inizializzalivella( livella );

    livellaMobile_controlla( livella );

    return livella;

}

int livellaMobile_controlla( LivellaMobile * livella ){

    if(livella == NULL) return -1;
    
    int returnstatus = 0;

    if( guida_controlla_integrita(livella->supporto[0]) > 0 ) returnstatus = 2;

    if( livella->dati_livella.largbase > livella->supporto[0]->guida->dim_x || livella->dati_livella.largbase <= 0){

        livella->dati_livella.largbase = livella->supporto[0]->guida->dim_x - 10;
        returnstatus = 1;

    }

    if( livella->dati_livella.largtesta > livella->dati_livella.largbase || livella->dati_livella.largtesta <= 0) {
       
        livella->dati_livella.largtesta = livella->dati_livella.largbase * 2 / 3;
        returnstatus = 1;
    }

    if( livella->dati_livella.alt_cilindro <= 0 ){

        livella->dati_livella.alt_cilindro = LIV_REF_H;
        returnstatus = 1;

    }

    if( livella->dati_livella.alt_sx < 0 ){

        livella->dati_livella.alt_sx = 10;
        returnstatus = 1;

    }

    if( livella->dati_livella.alt_dx < 0 ){

        livella->dati_livella.alt_dx = 10;
        returnstatus = 1;

    }

    if( livella->dati_livella.alt_dx > livella->dati_livella.alt_cilindro - 10){

        livella->dati_livella.alt_dx = livella->dati_livella.alt_cilindro - 10;
        returnstatus = 1;
    }

    if( livella->dati_livella.alt_sx > livella->dati_livella.alt_cilindro - 10){

        livella->dati_livella.alt_sx = livella->dati_livella.alt_cilindro - 10;
        returnstatus = 1;
    }

    if(returnstatus == 1) {
        livella_destroy( livella->livella);
        liv_inizializzalivella( livella );
    }
    
    return returnstatus;
}

void livellaMobile_to_svg(LivellaMobile * livella, string nome_file){
    
    if(livella == NULL) return;

    string str;

    str += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n";
    str += "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\"> \n";

    str += guida_to_SVGstring( livella->supporto[0] ); 
    str += guida_to_SVGstring( livella->supporto[1] );
    
    str += livella_to_ParamSVG(livella->livella);

    str += "</svg>";

    ofstream mySVG( nome_file + ".svg" );

    mySVG << str;

    mySVG.close();

}

LivellaMobile * livellaMobile_da_console(){

    float x, y, dist, perc, hc, hs, hd;

    cout << "Coordinate del centro delle due guide prismatiche che supportano la livella: ";
    cin >> x >> y;

    cout << "Distanza tra i cilindri della livella: ";
    cin >> dist;
    cout << "Percentuale di corsa delle guide prismatiche: ";
    cin >> perc;

    cout << "Indicare l'altezza base del cilindro: ";
    cin >> hc;
    cout << "Estensione del cilindro a sinistra: ";
    cin >> hs;
    cout << "Estensione del cilindro a destra: ";
    cin >> hd;

    return livellaMobile_init(x, y, dist, perc, hc, hs, hd);

}

void livellaMobile_destroy(LivellaMobile * livella){

    if(livella == NULL) return;

    livella_destroy(livella->livella);
    guida_distruggi(livella->supporto[0]);
    guida_distruggi(livella->supporto[1]);

    delete livella;

}

void livellaMobile_salva_file(LivellaMobile * livella, std::string nome_file ){

    if(livella == NULL) return;

    ofstream outfile(nome_file+ ".txt");

    outfile << livella->pos_x << " " << livella->pos_y << endl;
    outfile << livella->distanza << " " << livella->perc_corsa << endl;

    outfile << livella->dati_livella.alt_cilindro << " ";
    outfile << livella->dati_livella.alt_sx << " ";
    outfile << livella->dati_livella.alt_dx << " ";
    outfile << livella->dati_livella.largbase << " ";
    outfile << livella->dati_livella.largtesta << " ";
    outfile << livella->dati_livella.lunghezza ;

    outfile.close();

}

LivellaMobile * livellaMobile_da_file(std::string nome_file){

    float x, y, dist, perc, h1, h2, h3;
    ifstream infile( nome_file + ".txt" );

    if ( !infile.is_open() ){

        return NULL;
    }

    infile >> x >> y >> dist >> perc >> h1 >> h2 >> h3;

    LivellaMobile * liv = livellaMobile_init(x, y, dist, perc, h1, h2, h3);

    infile >> liv->dati_livella.largbase;
    infile >> liv->dati_livella.largtesta;
    infile >> liv->dati_livella.lunghezza;

    livella_destroy(liv->livella);
    liv_inizializzalivella( liv );

    return liv;

}

bool livellaMobile_verifica_uguaglianza( LivellaMobile * l1, LivellaMobile * l2 ){

    // Controllo sugli attributi delle livelle mobili:
    if( l1->distanza != l2->distanza ) return false;
    if( l1->perc_corsa != l2->perc_corsa ) return false;
    if( l1->pos_x != l2->pos_x ) return false;
    if( l1->pos_y != l2->pos_y ) return false;

    // Controllo sulle guide prismatiche delle livelle
    if ( !guida_verifica_uguaglianza(l1->supporto[0], l2->supporto[0]) ) return false;
    if ( !guida_verifica_uguaglianza(l1->supporto[1], l2->supporto[1]) ) return false;
    
    // Controllo sulle informazioni della livella
    if( l1->dati_livella.posx1 != l2->dati_livella.posx1 ) return false;
    if( l1->dati_livella.posx2 != l2->dati_livella.posx2 ) return false;
    if( l1->dati_livella.posy != l2->dati_livella.posy ) return false;
    if( l1->dati_livella.alt_cilindro != l2->dati_livella.alt_cilindro ) return false;
    if( l1->dati_livella.alt_dx != l2->dati_livella.alt_dx ) return false;
    if( l1->dati_livella.alt_sx != l2->dati_livella.alt_sx ) return false;
    if( l1->dati_livella.largbase != l2->dati_livella.largbase ) return false;
    if( l1->dati_livella.largtesta != l2->dati_livella.largtesta ) return false;
    if( l1->dati_livella.spessore != l2->dati_livella.spessore ) return false;
    if( l1->dati_livella.lunghezza != l2->dati_livella.lunghezza ) return false;

    return true;
}






