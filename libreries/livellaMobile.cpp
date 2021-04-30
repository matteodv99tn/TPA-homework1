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

vector <float> liv_posisizionilivella(LivellaMobile * livella, float hc, float bc){

    vector <float> res;

    float posy = livella->pos_y - hc;
    res.push_back( posy );

    float posx1 = liv_livposfromsup(livella, 0) - bc / 2;
    res.push_back( posx1 );

    float posx2 = liv_livposfromsup(livella, 1) - bc / 2;
    res.push_back( posx2 );


    return res;

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

    vector <float> pos = liv_posisizionilivella(livella, hc, bc);
    livella->livella = livella_init( pos[1], pos[2], pos[0], bc, bc * 2 /3 , hc, 30, 20, 10, 700  );

    #pragma endregion

    return livella;

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












