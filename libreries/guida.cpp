
#include "guida.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

GRect * grect_init( float dimx, float dimy ){

    // Creo l'istanza del rettangolo
    GRect * rect = new GRect;

    // Imposto le dimensioni in accordo ai parametri in ingresso
    rect->dim_x = dimx;
    rect->dim_y = dimy;

    // Ritorno l'oggetto istanziato
    return rect;

}

GuidaPrismatica* guida_init ( float posx, float posy, float lungh, float corsa, float dimx, float dimy){

    // Creo l'istanza della guida prismatica
    GuidaPrismatica* guida = new GuidaPrismatica;

    // Associo le grandezze in input alle relative grandezze della struct
    guida->pos_x = posx;
    guida->pos_y = posy;

    guida->lunghezza = lungh;
    guida->corsa = corsa;

    guida->incastri = grect_init( dimx, dimy );
    guida->guida = grect_init( dimx, dimy );

    guida->corsa = dimy / 3;
    guida->alpha = 0;

    // Ritorno l'oggetto della guida inizializzata
    return guida;

}

void guida_distruggi ( GuidaPrismatica * guida ){

    delete guida->incastri;
    delete guida->guida;

    delete guida;

}


// Funzione che genera la corretta matrice di roto-traslazione della guida pristmatica
string guida_matricetrasformazione ( GuidaPrismatica * guida ){

    string str = "";

    str += "transform=\"matrix(";

    str += to_string( cos( guida->alpha )  ) + " ";
    str += to_string( sin( guida->alpha )  ) + " ";
    str += to_string( -sin( guida->alpha ) ) + " ";
    str += to_string( cos( guida->alpha )  ) + " ";
    str += to_string( guida->pos_x ) + " ";
    str += to_string( guida->pos_y ) + ")\" ";

    return str;
}

string guida_to_SVGstring( GuidaPrismatica * guida ){

    // Inizializzazione della stringa da resistuire per la conversione in SVG
    string str = "";

    return str;

}

void guida_to_SVG (GuidaPrismatica * guida , string nome_file ){

    string str = guida_to_SVGstring( guida );

    ofstream mySVG( nome_file + ".svg");
    
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;

    mySVG << guida_to_SVGstring( guida );

    mySVG << "<\svg";

    mySVG.close();

}