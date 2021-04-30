
#include "guida.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

#define SPESSORE_ANNOTAZIONI 2
#define SBALZO_ANNOTAZIONI 5

// Funzione ausiliaria per implementare i menu di scelta:
char scelta(char scelta_1, char scelta_2){

    char in;

    cout << " [" << scelta_1 << "/" << scelta_2 << "] ";

    do{
        cin >> in;
    } while (in != scelta_1 && in != scelta_2);

    return in;

}

GRect * grect_init( float dimx, float dimy ){

    // Creo l'istanza del rettangolo
    GRect * rect = new GRect;

    // Imposto le dimensioni in accordo ai parametri in ingresso
    rect->dim_x = dimx;
    rect->dim_y = dimy;

    rect->colore[0] = DEF_RGB_R;
    rect->colore[1] = DEF_RGB_G;
    rect->colore[2] = DEF_RGB_B;

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

    if ( guida_controlla_integrita( guida ) > 0) {

        guida_distruggi(guida);
        return NULL;

    };

    // Ritorno l'oggetto della guida inizializzata
    return guida;

}

GuidaPrismatica * guida_crea(){

    GuidaPrismatica * guida_creata;

    float posx, posy, l, c, dimx, dimy;

    cout << "Specificare le 2 coordinate (x,y) della posizione centrale della guida prismatica: ";
    cin >> posx >> posy;

    cout << "Specificare la lunghezza della guida prismatica: ";
    cin >> l;
    cout << "Spceficiare il valore della corsa della guida prismatica: ";
    cin >> c;

    cout << "Specificare la dimensione orizzontale e verticale delle cerniere e della guida: ";
    cin >> dimx >> dimy;
    
    guida_creata = guida_init(posx, posy, l, c, dimx, dimy);

    if( guida_creata == NULL ) {
        cout << "Errore nei parametri! Non sono riuscito a creare una struttura consistente, riprovare." << endl << endl;
    } else {
        cout << "Continuare con la modifica per cambiare ulteriori proprietà?";
        
        if( scelta('s','n') == 's') guida_modifica( guida_creata );
    }

    return guida_creata;
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

int guida_set_lunghezza( GuidaPrismatica * guida , float l ){

    if ( l > 0 ){
        guida->lunghezza = l;
        return 0;
    } else  return 1;

}

void guida_set_spessore( GuidaPrismatica * guida, float spess){

    if(spess>0){

        guida->spessore = spess;
        guida_controlla_integrita(guida);

    }

    return;
}

int guida_set_corsa( GuidaPrismatica * guida , float c ){

    guida->corsa = c;

    if( guida_controlla_integrita(guida) == 0) return 0;
    else return 1;

}


void guida_set_angolo( GuidaPrismatica * guida, float deg){

    guida->alpha = - deg * 0.0174533;

}


int guida_set_cerniera( GuidaPrismatica * guida , float dimx, float dimy, unsigned int col_R, unsigned int col_G, unsigned int col_B){

    int exit_value = 0;

    if(dimx < 0){
        exit_value = 1;
    } else {
        guida->incastri->dim_x = dimx;
    }

    if(dimy < 0){
        exit_value = 1;
    } else {
        guida->incastri->dim_y = dimy;
    }

    if( col_R > 255) col_R = 255;
    if( col_G > 255) col_G = 255;
    if( col_B > 255) col_B = 255;

    guida->incastri->colore[0] = col_R;
    guida->incastri->colore[1] = col_G;
    guida->incastri->colore[2] = col_B;

    return exit_value;
}

int guida_set_guida( GuidaPrismatica * guida , float dimx, float dimy, unsigned int col_R, unsigned int col_G, unsigned int col_B){

    int exit_value = 0;

    if(dimx < 0){
        exit_value = 1;
    } else {
        guida->guida->dim_x = dimx;
    }

    if(dimy < 0){
        exit_value = 1;
    } else {
        guida->guida->dim_y = dimy;
    }

    if( col_R > 255) col_R = 255;
    if( col_G > 255) col_G = 255;
    if( col_B > 255) col_B = 255;

    guida->guida->colore[0] = col_R;
    guida->guida->colore[1] = col_G;
    guida->guida->colore[2] = col_B;

    return exit_value;
}

// Funzione ausiliaria per la modifica della lunghezza
void guida_modifica_lunghezza (GuidaPrismatica * guida ){
    float temp;

    cout << "Inserire un nuovo valore di lunghezza (attuale: " << guida->lunghezza << "): ";
    temp=input();
    
    
    if ( guida_set_lunghezza(guida, temp) == 1 ){
        cout << "Valore in ingresso negativo o nullo; lunghezza non modificata!";
    }

    cout << "Inserire un nuovo valore di corsa (attuale: " << guida->corsa << "): ";
    temp=input();
    guida_set_corsa(guida, temp);
}

// Funzione ausiliaria per la modifica delle proprietà della cerniera
void guida_modifica_cerniere ( GuidaPrismatica * guida ){

    float x, y;
    char scelta;

    cout << "Dimensione orizzontale della cerniera (attuale: " << guida->incastri->dim_x << "): ";
    x=input();
    cout << "Dimensione verticale della cerniera (attuale: " << guida->incastri->dim_y << "): ";
    y=input();

    cout << "Modificare i colori? [s/n]";
    do{
        cin >> scelta;
    } while (scelta != 's' && scelta != 'n');

    if (scelta == 's'){
        unsigned int col[3];

        cout << "Colore espresso in formato RGB con valori compresi tra 0 e 255:" << endl;
        cout << " > Componente rossa (attuale " << guida->incastri->colore[0] << "): ";
        cin >> col[0];
        cout << " > Componente verde (attuale " << guida->incastri->colore[1] << "): ";
        cin >> col[1];
        cout << " > Componente blu (attuale " << guida->incastri->colore[2] << "): ";
        cin >> col[2];
        
        guida_set_cerniera(guida, x, y, col[1], col[2], col[3]);
    } else {
        guida_set_cerniera(guida, x, y);
    }

}

// Funzione ausiliaria per la modifica delle proprietà della guida
void guida_modifica_guida ( GuidaPrismatica * guida ){

    float x, y;
    char scelta;

    cout << "Dimensione orizzontale della guida (attuale: " << guida->guida->dim_x << "): ";
    x = input();
    cout << "Dimensione verticale della guida (attuale: " << guida->guida->dim_y << "): ";
    y = input();

    cout << "Modificare i colori? [s/n]";
    do{
        cin >> scelta;
    } while (scelta != 's' && scelta != 'n');

    if (scelta == 's'){
        unsigned int col[3];

        cout << "Colore espresso in formato RGB con valori compresi tra 0 e 255:" << endl;
        cout << " > Componente rossa (attuale " << guida->guida->colore[0] << "): ";
        cin >> col[0];
        cout << " > Componente verde (attuale " << guida->guida->colore[1] << "): ";
        cin >> col[1];
        cout << " > Componente blu (attuale " << guida->guida->colore[2] << "): ";
        cin >> col[2];
        
        guida_set_guida(guida, x, y, col[1], col[2], col[3]);
    } else {
        guida_set_guida(guida, x, y);
    }

}

// Funzione ausiliaria per modificare le proprietà delle cerniere
void guida_modifica_cerniera (GuidaPrismatica * guida){

    float temp;

    cout << "Inserire 0 per mantenere invariato il valore" << endl;
    
    cout << "Inserire la dimensione orizzontale della cerniera (attuale: " << guida->incastri->dim_x << "): ";
    do {
        temp = input();
    } while (temp < 0);
    
    if(temp != 0) guida->incastri->dim_x = temp;
    
    cout << "Inserire la dimensione verticale della cerniera (attuale: " << guida->incastri->dim_y << "): ";
    do {
       temp = input();
    } while (temp < 0);
    
    if(temp != 0) guida->incastri->dim_y = temp;
}

void guida_modifica( GuidaPrismatica * guida){\

    char scelta = '0';

    do{

        cout << endl << endl << "Operazioni che è possibile effettuare:" << endl;
        cout << " 1. modificare la lunghezza e la corsa del sistema" << endl;
        cout << " 2. modificare le proprietà delle cerniere" << endl;
        cout << " 3. modificare le proprietà della guida" << endl;
        cout << " 4. modificare l'angolo di inclinazione della guida" << endl;
        cout << " 0. per uscire dal menu di modifica" << endl;
        cout << "Scelta effettuata: ";
        cin >> scelta;
        cout << endl;

        switch( scelta ){

            case '1':
                guida_modifica_lunghezza( guida );
                guida_controlla_integrita( guida );
                break;

            case '2':
                guida_modifica_cerniera( guida );
                guida_controlla_integrita( guida );
                break;

            case '3': 
                guida_modifica_guida( guida );
                guida_controlla_integrita;
                break;
            
            case '4':
                cout << "Valore dell'angolo (in gradi) di inclinazione della struttura: ";
                float temp;
                temp = input();
                guida_set_angolo( guida, temp );
                break;

            default:
                if( scelta != '0' )
                    cout << "Ingresso non valido!" << endl;
                break;
        }


    } while( scelta  != '0' );

    guida_controlla_integrita( guida );

    return;
}

int guida_controlla_integrita (GuidaPrismatica * guida ){

    bool guida_modificata = false;

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

    // Controllo che le dimensioni delle cerniere e della guida non superi la lunghezza complessiva della struttura; in caso riaggiusto
    if( guida->incastri->dim_x + guida->guida->dim_x > guida->lunghezza){

        guida->incastri->dim_x = guida->lunghezza / 2;
        guida->guida->dim_x = guida->lunghezza / 2;
        guida_modificata = true;

    }   

    // Aggiusto lo spessore del cilindro di scorrimento
    // Se lo spessore è maggiore della lunghezza delle cerniere allora la riduco al valore minimo trovato
    // Se la corsa è negativa o nulla la pongo ad un terzo della lunghezza verticale minima delle cerniere
    int spess_min = min( guida->incastri->dim_y, guida->guida->dim_y );
    
    if(guida->spessore > spess_min){

        guida->spessore = spess_min;
        guida_modificata = true;

    }
    
    if(guida->spessore <= 0){

        guida->spessore = spess_min / 3;
        guida_modificata = true;

    }

    // Controllo la posizione della corsa che deve essere entro un range prefissato
    float min_corsa = guida->incastri->dim_x / 2 + guida->guida->dim_x/2;
    float max_corsa = guida->lunghezza - guida->incastri->dim_x / 2 - guida->guida->dim_x/2;
    
    if(guida->corsa > max_corsa) {

        guida->corsa = max_corsa;
        guida_modificata = true;

    }

    if(guida->corsa < min_corsa) {

        guida->corsa = min_corsa;
        guida_modificata = true;

    }

    if ( guida_modificata ) return -1;
    else return 0;
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

string guida_stilerettangolo ( GRect * rett ){
    
    string str = "";

    str += "style=\"fill:rgb(";
    str += to_string(rett->colore[0]) + ",";
    str += to_string(rett->colore[1]) + ",";
    str += to_string(rett->colore[2]);
    str += ");stroke-width:3;stroke:rgb(0,0,0)\" ";

    return str;
}

// Funzione ausiliaria per disegnare una linea per rappresentare le dimensioni
string guida_linee_annotazione( float x1, float y1, float x2, float y2, string str_trasformazione, string str_annotazione){
    
    string str;

    if(x1 == x2){

        str += "\t<text x=\"" + to_string( x1 + 3 ) + "\" y=\"" + to_string( (y1 + y2) / 2 ) + "\" ";
        str += "dominant-baseline=\"middle\" class=\"stileannotazioni\" ";
        str += str_trasformazione;
        str += " >" + str_annotazione + "</text>\n";

    } else {

        str += "\t<text x=\"" + to_string( (x1 + x2) / 2 ) + "\" y=\"" + to_string(y1 - 6) + "\" ";
        str += "dominant-baseline=\"middle\" text-anchor=\"middle\" class=\"stileannotazioni\" ";
        str += str_trasformazione;
        str += " >" + str_annotazione + "</text>\n";
    }

    str += "\t\t <line x1=\"" + to_string(x1) + "\" y1=\"" + to_string(y1) + "\" x2=\"" + to_string(x2) + "\" y2=\"" + to_string(y2) + "\" ";
    str += "style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(SPESSORE_ANNOTAZIONI) + "\" ";
    str += str_trasformazione;
    str += "/>\n";
    
    if (x1 != x2){

        str += "\t\t <line x1=\"" + to_string(x1) + "\" y1=\"" + to_string(y1 - SBALZO_ANNOTAZIONI) + "\" x2=\"" + to_string(x1) + "\" y2=\"" + to_string(y1 + SBALZO_ANNOTAZIONI) + "\" ";
        str += "style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(SPESSORE_ANNOTAZIONI) + "\" ";
        str += str_trasformazione;
        str += "/>\n";

        str += "\t\t <line x1=\"" + to_string(x2) + "\" y1=\"" + to_string(y2 - SBALZO_ANNOTAZIONI) + "\" x2=\"" + to_string(x2) + "\" y2=\"" + to_string(y2 + SBALZO_ANNOTAZIONI) + "\" ";
        str += "style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(SPESSORE_ANNOTAZIONI) + "\" ";
        str += str_trasformazione;
        str += "/>\n";

    } else {

        str += "\t\t <line x1=\"" + to_string(x1 - SBALZO_ANNOTAZIONI) + "\" y1=\"" + to_string(y1) + "\" x2=\"" + to_string(x1 + SBALZO_ANNOTAZIONI) + "\" y2=\"" + to_string(y1) + "\" ";
        str += "style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(SPESSORE_ANNOTAZIONI) + "\" ";
        str += str_trasformazione;
        str += "/>\n";

        str += "\t\t <line x1=\"" + to_string(x2 - SBALZO_ANNOTAZIONI) + "\" y1=\"" + to_string(y2) + "\" x2=\"" + to_string(x2 + SBALZO_ANNOTAZIONI) + "\" y2=\"" + to_string(y2) + "\" ";
        str += "style=\"stroke:rgb(0,0,0);stroke-width:" + to_string(SPESSORE_ANNOTAZIONI) + "\" ";
        str += str_trasformazione;
        str += "/>\n";

    }

    return str;
}

string to_string_2dp( const float number ){

    std::ostringstream out;
    out.precision(2);
    out << std::fixed << number;

    return out.str();
}

string guida_to_SVGstring( GuidaPrismatica * guida, bool visualizza_dimensioni ){

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
    str += guida_stilerettangolo( guida->incastri);
    str += str_trasf;
    str += " /> \n";

    // Seconda cerniera
    str += "\t";
    str += "<rect  x = \"" + to_string( guida->lunghezza/2 - guida->incastri->dim_x/2) + "\" ";
    str += "y=\"" + to_string( - guida->incastri->dim_y / 2  ) + "\" ";
    str += "width=\"" + to_string(guida->incastri->dim_x) + "\" ";
    str += "height=\"" + to_string(guida->incastri->dim_y) + "\" ";
    str += guida_stilerettangolo( guida->incastri);
    str += str_trasf;
    str += " /> \n";

    // Perno 
    str += "\t";
    str += "<rect  x = \"" + to_string( -guida->lunghezza/2 + guida->corsa - guida->guida->dim_x/2) + "\" ";
    str += "y=\"" + to_string( - guida->guida->dim_y / 2  ) + "\" ";
    str += "width=\"" + to_string(guida->guida->dim_x) + "\" ";
    str += "height=\"" + to_string(guida->guida->dim_y) + "\" ";
    str += guida_stilerettangolo( guida->guida );
    str += str_trasf;
    str += " /> \n";

    if( visualizza_dimensioni ){
        
        // Imposto lo stile del testo
        str += "\n\t<style> .stileannotazioni { font: italic 13px sans-serif; } </style>\n\n";

        // Dimensione orizzontale della cerniera// Dimensione orizzontale della cerniera
        str += guida_linee_annotazione( 
                -guida->lunghezza / 2 - guida->incastri->dim_x / 2,
                -guida->incastri->dim_y / 2 - 10,
                -guida->lunghezza / 2 + guida->incastri->dim_x / 2, 
                -guida->incastri->dim_y / 2 - 10,
                str_trasf,
                to_string_2dp( guida->incastri->dim_x )
            );
        str += guida_linee_annotazione( 
                guida->lunghezza / 2 - guida->incastri->dim_x / 2,
                -guida->incastri->dim_y / 2 - 10,
                guida->lunghezza / 2 + guida->incastri->dim_x / 2, 
                -guida->incastri->dim_y / 2 - 10,
                str_trasf,
                to_string_2dp( guida->guida->dim_x )
            );

        // Dimensione orizzontale della guida
        str += guida_linee_annotazione( 
                -guida->lunghezza / 2 + guida->corsa - guida->guida->dim_x / 2,
                -guida->guida->dim_y / 2 - 10,
                -guida->lunghezza / 2 + guida->corsa + guida->guida->dim_x / 2, 
                -guida->guida->dim_y / 2 - 10,
                str_trasf,
                to_string_2dp( guida->incastri->dim_x )
            );

        // Lunghezze e corsa del disegno
        str += guida_linee_annotazione( 
                -guida->lunghezza / 2,
                guida->guida->dim_y / 2 + 35,
                guida->lunghezza / 2, 
                guida->guida->dim_y / 2 + 35,
                str_trasf,
                to_string_2dp( guida->lunghezza )
            );
        str += guida_linee_annotazione( 
                -guida->lunghezza / 2,
                guida->guida->dim_y / 2 + 15,
                -guida->lunghezza / 2 + guida->corsa, 
                guida->guida->dim_y / 2 + 15,
                str_trasf,
                to_string_2dp( guida->corsa ) 
            );

        // Altezza del cilindro di scorrimento
        str += guida_linee_annotazione(
                guida->lunghezza / 2 + guida->incastri->dim_x / 2 + 10,
                -guida->spessore / 2,
                guida->lunghezza / 2 + guida->incastri->dim_x / 2 + 10,
                guida->spessore / 2,
                str_trasf,
                to_string_2dp( guida->spessore )
        );
        // Altezza della cerniera
        str += guida_linee_annotazione(
                guida->lunghezza / 2 + guida->incastri->dim_x / 2 + 60,
                -guida->incastri->dim_y / 2,
                guida->lunghezza / 2 + guida->incastri->dim_x / 2 + 60,
                guida->incastri->dim_y / 2,
                str_trasf,
                to_string_2dp( guida->incastri->dim_y )
        );

        if(guida->lunghezza - guida->corsa > 80){

            str += guida_linee_annotazione(
                - guida->lunghezza / 2 + guida->corsa + guida->guida->dim_x / 2 + SBALZO_ANNOTAZIONI + 5 ,
                - guida->guida->dim_y / 2,
                - guida->lunghezza / 2 + guida->corsa + guida->guida->dim_x / 2 + SBALZO_ANNOTAZIONI + 5 ,
                guida->guida->dim_y / 2,
                str_trasf,
                to_string_2dp(guida->guida->dim_y)
            );
        } else {

            str += guida_linee_annotazione(
                - guida->lunghezza / 2 + guida->corsa - guida->guida->dim_x / 2 - SBALZO_ANNOTAZIONI - 40 ,
                - guida->guida->dim_y / 2,
                - guida->lunghezza / 2 + guida->corsa - guida->guida->dim_x / 2 - SBALZO_ANNOTAZIONI - 40 ,
                guida->guida->dim_y / 2,
                str_trasf,
                to_string_2dp(guida->guida->dim_y)
            );
        }
    }

    return str;

}

void guida_to_SVG (GuidaPrismatica * guida , string nome_file, bool visualizza_dimensioni ){

    string str = guida_to_SVGstring( guida );
    
    ofstream mySVG( nome_file + ".svg");
    
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl << endl;

    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;

    mySVG << guida_to_SVGstring( guida , visualizza_dimensioni);

    mySVG << "</svg>";

    mySVG.close();

}

float guida_val_dopo_str(string str, string da_cercare){

    string str_res = "";

    // cout << endl << "Cerco: " << da_cercare << " in " << endl << str << endl;

    int pos = str.find(da_cercare);
    pos += (int)da_cercare.size();
    
    while(str[pos] != '.'){
        
        str_res += str[pos];
        pos++;
    }
    for(int j = 0; j < 7; j++) str_res += str[pos + j];

    return stof(str_res);

}

vector <int> guida_colori( string str ){

    vector <int> res;

    int pos = str.find("fill:rgb(");
    pos += 9;

    string temp = "";
    
    while(str[pos] != ','){
        temp += str[pos];
        pos++;
    }
    res.push_back( stoi(temp) );
    temp = "";
    pos++;
    
    while(str[pos] != ','){
        temp += str[pos];
        pos++;
    }
    res.push_back( stoi(temp) );
    temp = "";
    pos++;
    
    while(str[pos] != ')'){
        temp += str[pos];
        pos++;
    }
    res.push_back( stoi(temp) );

    return res;
}

vector <float> guida_parse_pos( string str){

    vector <float> res;
    string temp = "";
    float t;

    int pos = str.find("matrix(");
    pos += 7;

    istringstream istr(temp);
    
    istr >> t >> t;
    res.push_back( asin(t) );
    istr >> t >> t;

    istr >> t;
    res.push_back( t );
    istr >> t;
    res.push_back( t );


    return res;
}

GuidaPrismatica * guida_parse_svg(string file_name, bool with_header){

    int tobesummed = 0;
    GuidaPrismatica * guida = new GuidaPrismatica;
    string str;

    vector<string> svglines;

    ifstream svgfile( file_name + ".svg" );

    while( svgfile.good() ){
        getline(svgfile, str);
        svglines.push_back(str);
    }
    svgfile.close();

    if(with_header) tobesummed = 3;

    guida->lunghezza = guida_val_dopo_str( svglines[0 + tobesummed], "width=\"" );
    guida->spessore = guida_val_dopo_str( svglines[0 + tobesummed], "height=\"" );

    vector<int> colcerniera = guida_colori( svglines[1+ tobesummed] );
    guida->incastri = grect_init(
            guida_val_dopo_str( svglines[1 + tobesummed], "width=\"" ),
            guida_val_dopo_str( svglines[1 + tobesummed], "height=\"" )
        );
    guida->incastri->colore[0] = colcerniera[0];
    guida->incastri->colore[1] = colcerniera[1];
    guida->incastri->colore[2] = colcerniera[2];

    vector<int> colguida = guida_colori( svglines[3+ tobesummed] );
    guida->guida = grect_init(
            guida_val_dopo_str( svglines[3+ tobesummed], "width=\"" ),
            guida_val_dopo_str( svglines[3 + tobesummed], "height=\"" )
        );
    guida->guida->colore[0] = colguida[0];
    guida->guida->colore[1] = colguida[1];
    guida->guida->colore[2] = colguida[2];


    float temp = guida_val_dopo_str(svglines[3 + tobesummed], "x = \"" );
    guida->corsa = guida->lunghezza / 2 - guida->guida->dim_x / 2 - temp;

    vector <float> coord = guida_parse_pos(svglines[3 + tobesummed]);
    guida->alpha = coord[0];
    guida->pos_x = coord[1];
    guida->pos_y = coord[2];


    return guida;
}

void guida_salva_file ( GuidaPrismatica * guida, string nome_file ){

    ofstream outfile( nome_file + ".txt");

    outfile << guida->lunghezza << " " << guida->corsa << " " << guida->spessore << endl;

    outfile << guida->pos_x << " " << guida->pos_y << " " << guida->alpha << endl;

    outfile << guida->incastri->dim_x << " " << guida->incastri->dim_y << " " << guida->incastri->colore[0] << " " << guida->incastri->colore[1] << " " << guida->incastri->colore[2] << endl;
    outfile << guida->guida->dim_x << " " << guida->guida->dim_y << " " << guida->guida->colore[0] << " " << guida->guida->colore[1] << " " << guida->guida->colore[2];

}

GuidaPrismatica * guida_carica_file( string nome_file ){

    ifstream infile( nome_file + ".txt");

    GuidaPrismatica * guida = new GuidaPrismatica;
    guida->incastri = new GRect;
    guida->guida = new GRect;

    infile >> guida->lunghezza >> guida->corsa >> guida->spessore;

    infile >> guida->pos_x >> guida->pos_y >> guida->alpha;

    infile >> guida->incastri->dim_x >> guida->incastri->dim_y >> guida->incastri->colore[0] >> guida->incastri->colore[1] >> guida->incastri->colore[2];
    infile >> guida->guida->dim_x >> guida->guida->dim_y >> guida->guida->colore[0] >> guida->guida->colore[1] >> guida->guida->colore[2];

    infile.close();

    return guida;

}
/**
/*  Funzione per input di float,
/*  ritorna il valore inserito da tastiera 
*/
float input(){
    float tmp;
    cin>>tmp;
    while(!(std::cin.good())){
		std::cout<<"\nErrore: Parametro non valido, reinserire\n ";
		std::cin.clear();
      	while (std::cin.get() != '\n');
	    std::cin>>tmp;
	}
    return tmp;
}
