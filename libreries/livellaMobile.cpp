#include <iostream>
#include <string.h> 
#include <fstream>
#include <vector>
#include "livellaMobile.h"

#define GUIDA_DIMX 40
#define GUIDA_DIMY 40
#define GUIDA_DIST_REL 20

#pragma region // Funzioni ausiliarie per l'inizializzazione della Livella

float liv_determinacorsa(GuidaPrismatica * guida, float perc){

    float res;

    float corsa_utile = guida->lunghezza - guida->incastri->dim_x - guida->incastri->dim_y;

    res = guida->incastri->dim_x / 2 + perc * corsa_utile / 100;

    return res;
}

void liv_impostaposizione_supporti(LivellaMobile * livella){

    float pos = livella->pos_x;
    pos -= livella->supporto[0]->lunghezza / 2 + livella->supporto[0]->incastri->dim_x / 2;
    pos -= GUIDA_DIST_REL / 2;
    livella->supporto[0]->pos_x = pos;

    pos += livella->supporto[0]->lunghezza + GUIDA_DIST_REL + livella->supporto[0]->incastri->dim_x;
    livella->supporto[1]->pos_x = pos;

}

float liv_livposfromsup(LivellaMobile * liv, unsigned int index){
    return liv->supporto[index]->pos_x - liv->supporto[index]->lunghezza/2 + liv->supporto[index]->corsa;
}

void liv_posisizionilivella(LivellaMobile * livella, float hc, float bc){

    vector <float> res;

    livella->dati_livella.posy = livella->pos_y - hc;

    livella->dati_livella.posx1 = liv_livposfromsup(livella, 0) - bc / 2;
    livella->dati_livella.posx2 = liv_livposfromsup(livella, 1) - bc / 2;

}




#pragma endregion

LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc){

    LivellaMobile * livella = new LivellaMobile;

    livella->pos_x = posx;
    livella->pos_y = posy;

    livella->distanza = dist;
    livella->perc_corsa = perc;

    #pragma region // Inizializzazione delle guide prismatiche di supporto
    
    livella->supporto[0] = guida_init(
            0,
            livella->pos_y,
            livella->distanza - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2,
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );

    livella->supporto[1] = guida_init(
            0,
            livella->pos_y,
            livella->distanza - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2,
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );
    liv_impostaposizione_supporti( livella );

    guida_set_corsa( livella->supporto[0], liv_determinacorsa(livella->supporto[0], livella->perc_corsa) );
    guida_set_corsa( livella->supporto[1], liv_determinacorsa(livella->supporto[1], livella->perc_corsa) );

    #pragma endregion

    #pragma region // Inizializzazione della livella

    float hc = 90;
    float bc = 30;

    livella->livella = livella_init( 
        livella->dati_livella.posx1 , 
        livella->dati_livella.posx2 , 
        livella->dati_livella.posy ,
        livella->dati_livella.largbase, 
        livella->dati_livella.largtesta, 
        livella->dati_livella.alt_cilindro,
        livella->dati_livella.alt_dx,
        livella->dati_livella.alt_sx,
        livella->dati_livella.spessore,
        livella->dati_livella.lunghezza,
        );

    #pragma endregion

    return livella;

}

#pragma region // Funzioni ausiliarie per la correzione della struttura dati

#pragma endregion

int livellaMobile_controlla( LivellaMobile * livella ){

    int returnstatus = 0;


    if( livella->livella->mypiston1->larg_1 > livella->supporto[0]->guida->dim_x){

        livella->livella->mypiston1->larg_1 = livella->supporto[0]->guida->dim_x - 5;

    }


    return returnstatus;
}

void livellaMobile_to_svg(LivellaMobile * livella, string nome_file){
    
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












