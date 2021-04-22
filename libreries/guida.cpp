
#include "guida.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>

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

// Funzione ausiliaria per disegnare un rettangolo
string rect_draw( float posx, float posy, GRect * rect){

    string str = "";

    str += "<rext x = \"";
    str += to_string(posx);
    str += "\" y = \"";
    str += to_string(posy);
    str += "\" ";

    str += "width=\"40\" height=\"20\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" />";

    str += "\n";
    return str;

}

string guida_to_SVGstring( GuidaPrismatica * guida ){

    // Inizializzazione della stringa da resistuire per la conversione in SVG
    string str = "";
    str += "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\"> \n";

    str += rect_draw( guida->pos_x - (guida->corsa / 2 ), guida->pos_y, guida->incastri);

    str += "</svg>";
    
    cout << "+++" << endl << str << endl << "+++" << endl;

    return str;

}

void guida_to_SVG (GuidaPrismatica * guida , string nome_file ){

    string str = guida_to_SVGstring( guida );

    ofstream mySVG( "ciao.svg");
    
    cout << "Stringa da salvare:" << endl;

    mySVG << str;

    cout << endl << "--------" << endl;
    mySVG.close();

}