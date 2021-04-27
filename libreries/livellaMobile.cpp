#include <iostream>
#include <string.h> 
#include <fstream>
#include "livellaMobile.h"

#define GUIDA_DIMX 40
#define GUIDA_DIMY 40
#define GUIDA_DIST_REL 20

float liv_determinacorsa(GuidaPrismatica * guida, float perc){

    float res;

    float corsa_utile = guida->lunghezza - guida->incastri->dim_x - guida->incastri->dim_y;

    res = guida->incastri->dim_x / 2 + perc * corsa_utile / 100;

    return res;
}

float liv_posizioneguida(GuidaPrismatica * guida){
 
    float res = guida->pos_x - guida->lunghezza / 2 + guida->corsa;
    cout << res << endl;
    return res;
}

LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc){

    LivellaMobile * livella = new LivellaMobile;

    livella->pos_x = posx;
    livella->pos_y = posy;

    livella->distanza = dist;
    livella->perc_corsa = perc;

    livella->supporto[0] = guida_init(
            livella->pos_x - livella->distanza / 2,
            livella->pos_y,
            livella->distanza - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2,
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );

    livella->supporto[1] = guida_init(
            livella->pos_x + livella->distanza / 2,
            livella->pos_y,
            livella->distanza - GUIDA_DIMX / 2 - GUIDA_DIST_REL / 2,
            0,
            GUIDA_DIMX,
            GUIDA_DIMY 
        );

    guida_set_corsa( livella->supporto[0], liv_determinacorsa(livella->supporto[0], livella->perc_corsa) );
    guida_set_corsa( livella->supporto[1], liv_determinacorsa(livella->supporto[1], livella->perc_corsa) );

    livella->pistone[0] = piston_init(
        liv_posizioneguida(livella->supporto[0]),
        livella->pos_y,
        50, 20,
        20, 30
    );

    livella->pistone[0] = piston_init(
        liv_posizioneguida(livella->supporto[1]),
        livella->pos_y,
        50, 20,
        20, 30
    );

    // livella->pedana = plate_init(10, 800, livella->pistone[0], livella->pistone[1]); 
}

void livellaMobile_to_svg(LivellaMobile * livella, string nome_file){
    
    string str;

    str += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\n";
    str += "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\"> \n";

    str += guida_to_SVGstring( livella->supporto[0] );
    str += guida_to_SVGstring( livella->supporto[1] );

    str += "</svg>";

    ofstream mySVG( nome_file + ".svg" );

    mySVG << str;

    mySVG.close();

}












