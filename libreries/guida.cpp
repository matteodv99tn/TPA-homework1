
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

    guida->spessore = dimy / 3;
    guida->alpha = 0;

    // Ritorno l'oggetto della guida inizializzata
    return guida;

}

void guida_distruggi ( GuidaPrismatica * guida ){

    delete guida->incastri;
    delete guida->guida;

    delete guida;

}

void guida_visualizza_info ( GuidaPrismatica * guida ){

    cout << "> lunghezza \t\t" << guida->lunghezza << endl;
    cout << "> corsa \t\t" << guida->corsa << endl;
    cout << "> coordinate centro \t(" << guida->pos_x << " , " << guida->pos_y << ")" << endl;
    cout << "> dimensione cerniera \t" << guida->incastri->dim_x << "x" << guida->incastri->dim_y << endl;
    cout << "> dimensione guida \t" << guida->guida->dim_x << "x" << guida->guida->dim_y << endl;
    cout << "> spessore \t\t" << guida->spessore << endl;

}

// Funzione che genera la corretta matrice di roto-traslazione della guida pristmatica
string guida_matricetrasformazione ( GuidaPrismatica * guida ){

    // Basato su:
    // https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/transform

    // Inizializzo la stringa contenente le informazioni sulla trasformazione
    string str = "";

    str += "transform=\"matrix(";

    // Popolo la matrice con le informazioni presenti nella struttura della guida prismatica
    str += to_string( cos( guida->alpha )  ) + " ";
    str += to_string( sin( guida->alpha )  ) + " ";
    str += to_string( -sin( guida->alpha ) ) + " ";
    str += to_string( cos( guida->alpha )  ) + " ";
    str += to_string( guida->pos_x ) + " ";
    str += to_string( guida->pos_y ) + ")\" ";

    // Restituisco le informazioni sulla matrice di trasformazione
    return str;
}

string guida_to_SVGstring( GuidaPrismatica * guida ){

    // Inizializzazione della stringa da resistuire per la conversione in SVG
    string str = "";
    string str_trasf = guida_matricetrasformazione( guida );

    // Cilindro sul quale scorrerà la guida
    str += "\t";
    str += "<rect  x = \"" + to_string(-guida->lunghezza/2) + "\" ";
    str += "y=\"" + to_string( - guida->spessore / 2 ) + "\" ";
    str += "width=\"" + to_string(guida->lunghezza) + "\" ";
    str += "height=\"" + to_string(guida->spessore) + "\" ";
    str += "style=\"fill:rgb(210,210,210);stroke-width:1;stroke:rgb(0,0,0)\" ";
    str += str_trasf;
    str += " /> \n";

    // Prima cerniera
    str += "\t";
    str += "<rect  x = \"" + to_string(-guida->lunghezza/2 - guida->incastri->dim_x/2) + "\" ";
    str += "y=\"" + to_string( - guida->incastri->dim_y / 2  ) + "\" ";
    str += "width=\"" + to_string(guida->incastri->dim_x) + "\" ";
    str += "height=\"" + to_string(guida->incastri->dim_y) + "\" ";
    str += "style=\"fill:rgb(140,140,140);stroke-width:3;stroke:rgb(0,0,0)\" ";
    str += str_trasf;
    str += " /> \n";

    // Seconda cerniera
    str += "\t";
    str += "<rect  x = \"" + to_string( guida->lunghezza/2 - guida->incastri->dim_x/2) + "\" ";
    str += "y=\"" + to_string( - guida->incastri->dim_y / 2  ) + "\" ";
    str += "width=\"" + to_string(guida->incastri->dim_x) + "\" ";
    str += "height=\"" + to_string(guida->incastri->dim_y) + "\" ";
    str += "style=\"fill:rgb(140,140,140);stroke-width:3;stroke:rgb(0,0,0)\" ";
    str += str_trasf;
    str += " /> \n";

    return str;

}

void guida_to_SVG (GuidaPrismatica * guida , string nome_file ){

    string str = guida_to_SVGstring( guida );

    ofstream mySVG( nome_file + ".svg");
    
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl << endl;

    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;

    mySVG << guida_to_SVGstring( guida );

    mySVG << "</svg>";

    mySVG.close();

}