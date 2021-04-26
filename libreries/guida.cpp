
#include "guida.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>

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

    if ( guida_controlla_integrita( guida ) != 0) {

        guida_distruggi(guida);
        return NULL;

    };

    // Ritorno l'oggetto della guida inizializzata
    return guida;

}

void guida_distruggi ( GuidaPrismatica * guida ){

    if( guida == NULL ) return;

    delete guida->incastri;
    delete guida->guida;

    delete guida;

}

void guida_visualizza_info ( GuidaPrismatica * guida ){

    if(guida == NULL){
        cout << "Oggetto non valido" << endl;
        return;
    }

    cout << "> lunghezza \t\t" << guida->lunghezza << endl;
    cout << "> corsa \t\t" << guida->corsa << endl;
    cout << "> coordinate centro \t(" << guida->pos_x << " , " << guida->pos_y << ")" << endl;
    cout << "> dimensione cerniera \t" << guida->incastri->dim_x << "x" << guida->incastri->dim_y << endl;
    cout << "> dimensione guida \t" << guida->guida->dim_x << "x" << guida->guida->dim_y << endl;
    cout << "> spessore \t\t" << guida->spessore << endl;

}

// Funzione ausiliaria per la modifica della lunghezza
void guida_modifica_lunghezza (GuidaPrismatica * guida ){
    float temp;

    cout << "Inserire 0 per mantenere invariato il valore" << endl;
    cout << "Inserire un nuovo valore di lunghezza (attuale: " << guida->lunghezza << "): ";
    cin >> temp;
    
    if(temp > 0 ){
        guida->lunghezza = temp;
    }

    cout << "Inserire un nuovo valore di corsa (attuale: " << guida->corsa << "): ";
    cin >> temp;
    guida->corsa = temp;
}

// Funzione ausiliaria per modificare le proprietà delle cerniere
void guida_modifica_cerniera (GuidaPrismatica * guida){

    float temp;

    cout << "Inserire 0 per mantenere invariato il valore" << endl;
    
    cout << "Inserire la dimensione orizzontale della cerniera (attuale: " << guida->incastri->dim_x << "): ";
    do {
        cin >> temp;
    } while (temp < 0);
    
    if(temp != 0) guida->incastri->dim_x = temp;
    
    cout << "Inserire la dimensione verticale della cerniera (attuale: " << guida->incastri->dim_y << "): ";
    do {
        cin >> temp;
    } while (temp < 0);
    
    if(temp != 0) guida->incastri->dim_y = temp;
}

// Funzione ausiliaria per modificare le proprietà della guida
void guida_modifica_guida (GuidaPrismatica * guida){

    float temp;

    cout << "Inserire 0 per mantenere invariato il valore" << endl;
    
    cout << "Inserire la dimensione orizzontale della guida (attuale: " << guida->guida->dim_x << "): ";
    do {
        cin >> temp;
    } while (temp < 0);
    
    if(temp != 0) guida->guida->dim_x = temp;
    
    cout << "Inserire la dimensione verticale della guida (attuale: " << guida->incastri->dim_y << "): ";
    do {
        cin >> temp;
    } while (temp < 0);
    
    if(temp != 0) guida->incastri->dim_y = temp;
}

void guida_modifica( GuidaPrismatica * guida){\

    int scelta = 0;

    do{

        cout << endl << endl << "Operazioni che è possibile effettuare:" << endl;
        cout << " 1. modificare la lunghezza e la corsa del sistema" << endl;
        cout << " 2. modificare le proprietà delle cerniere del componente" << endl;
        cout << " 3. modificare le proprietà della guida del componente" << endl;
        cout << " 0. per uscire dal menu di modifica" << endl;
        cout << "Scelta effettuata: ";
        cin >> scelta;
        cout << endl;

        switch( scelta ){

            case 1:
                guida_modifica_lunghezza( guida );
                guida_controlla_integrita( guida );
                break;

            case 2:
                guida_modifica_cerniera( guida );
                guida_controlla_integrita( guida );
                break;

            case 3: 
                guida_modifica_guida( guida );
                guida_controlla_integrita;
                break;

            default:
                if( scelta != 0 )
                    cout << "Ingresso non valido!" << endl;
                break;
        }


    } while( scelta  != 0 );

    return;
}

int guida_controlla_integrita (GuidaPrismatica * guida ){

    // Controllo che la lunghezza della guida prismatica sia un valore positivo
    if(guida->lunghezza <= 0) {

        guida->lunghezza = 0;
        return 1;

    }

    // Controllo sulla dimensione delle cerniere
    if( guida->incastri->dim_x <= 0 || guida->incastri->dim_y <= 0 ){

        guida->incastri->dim_x = 0;
        guida->incastri->dim_y = 0;
        return 2;

    }

    // Controllo sulla dimensione della guida prismatica del sistema
    if( guida->guida->dim_x <= 0 || guida->guida->dim_y <= 0 ){

        guida->guida->dim_x = 0;
        guida->guida->dim_y = 0;
        return 3;

    }

    // Aggiusto lo spessore del cilindro di scorrimento
    // Se lo spessore è maggiore della lunghezza delle cerniere allora la riduco al valore minimo trovato
    // Se la corsa è negativa o nulla la pongo ad un terzo della lunghezza verticale minima delle cerniere
    int spess_min = min( guida->incastri->dim_y, guida->guida->dim_y );
    
    if(guida->spessore > spess_min)
        guida->spessore = spess_min;
    
    if(guida->spessore <= 0)
        guida->spessore = spess_min / 3;

    // Controllo la posizione della corsa che deve essere entro un range prefissato
    float min_corsa = guida->incastri->dim_x / 2 + guida->guida->dim_x/2;
    float max_corsa = guida->lunghezza - guida->incastri->dim_x / 2 - guida->guida->dim_x/2;
    
    if(guida->corsa > max_corsa) 
        guida->corsa = max_corsa;

    if(guida->corsa < min_corsa) 
        guida->corsa = min_corsa;

    // Controllo che le dimensioni delle cerniere e della guida non superi la lunghezza complessiva della struttura; in caso riaggiusto
    if( guida->incastri->dim_x + guida->guida->dim_x > guida->lunghezza){

        guida->incastri->dim_x = guida->lunghezza / 2;
        guida->guida->dim_x = guida->lunghezza / 2;

    }

    return 0;
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

    if(guida == NULL) return "";

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

    // Perno 
    str += "\t";
    str += "<rect  x = \"" + to_string( -guida->lunghezza/2 + guida->corsa - guida->guida->dim_x/2) + "\" ";
    str += "y=\"" + to_string( - guida->guida->dim_y / 2  ) + "\" ";
    str += "width=\"" + to_string(guida->guida->dim_x) + "\" ";
    str += "height=\"" + to_string(guida->guida->dim_y) + "\" ";
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