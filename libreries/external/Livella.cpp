#include "Livella.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;



// Funzione per creare una livella da console
Livella * livella_from_console(){

    float posx1, posx2, posy, alt1, larg1, larg2, altS, altD, spess, lung;
    
     cout << "Inserire posizione x del primo pistone:";
     cin >> posx1;
     cout << "Inserire posizione x del secondo pistone:";
     cin >> posx2;
     cout << "Inserire posizione y dei due pistoni:";
     cin >> posy;
     cout << "Inserire altezza del cilindro esterno:";
     cin >> alt1;
     cout << "Inserire larghezza del cilindro esterno:";
     cin >> larg1;
     cout << "Inserire larghezza del cilindo interno:";
     cin >> larg2;
     cout << "Inserire estensione del del primo pistone:";
     cin >> altS;
     cout << "Inserire estensione del secondo pistone:";
     cin >> altD;
     cout << "Inserire spessore della piastra:";
     cin >> spess;
     cout << "Inserire lunghezza della piastra:";
     cin >> lung;

    return livella_init(posx1, posx2, posy, larg1, larg2, alt1, altS, altD, spess, lung);
    
}


// Inizializzazione dei parametri del device
Livella * livella_init(float posx1, float posx2, float posy, float larg1, float larg2, float alt1, float altS, float altD, float spess, float lung){

    Livella * new_livella = new Livella;

    new_livella -> mypiston1 = piston_init(posx1, posy, alt1, larg1, altS, larg2);
    new_livella -> mypiston2 = piston_init(posx2, posy, alt1, larg1, altD, larg2);
    new_livella -> myplate = plate_init(spess, lung, posx1, posx2, posy, alt1, larg1, altS, altD, larg2);

}


// Inizializzazione dei pistoni

Piston* piston_init (float posx, float posy, float alt1, float larg1, float alt2, float larg2){

    Piston * pistonC  = new Piston;

    // Dimensioni del cilindro interno
    pistonC->alt_1 = alt1;
    pistonC->larg_1 = larg1;
    // Dimensioni del cilindro esterno
    pistonC->alt_2 = alt2;
    pistonC->larg_2 = larg2;
    // Posizione del cilindro esterno
    pistonC->pos_x1 = posx;
    pistonC->pos_y1 = posy;
    // Poiszione del cilindro interno
    pistonC->pos_x2 = pistonC->pos_x1 + ((pistonC->larg_1 - pistonC->larg_2)/2);
    pistonC->pos_y2 = pistonC->pos_y1 - pistonC->alt_2;
    // Centri delle coppie rotoidali
    pistonC->pos_cx = pistonC->pos_x1 + ((pistonC->larg_1 - pistonC->larg_2)/2) + (pistonC->larg_2)/2;
    pistonC->pos_cy = pistonC->pos_y1 - pistonC->alt_2;

    return pistonC;

}


// Inizializzazione della piastra

Plate* plate_init (float spess, float lungh, float posx1, float posx2, float posy, float alt1, float larg1, float altS, float altD, float larg2) {

    Plate * plateC = new Plate;

    // Coordinate delle coppie rotoidali di destra e sinistra
    plateC->pos_cxS = posx1 + (larg1 / 2);
    plateC->pos_cyS = posy - altS;
    plateC->pos_cxD = posx2 + (larg1 / 2);
    plateC->pos_cyD = posy - altD;
    // Spessore e lunghezza della piastra
    plateC->spessore = spess;
    plateC->lunghezza = lungh;
    // Posizione x e y della piastra prima della rotazione
    plateC->pos_x = plateC->pos_cxS - 50;
    plateC->pos_y = plateC->pos_cyS - (plateC->spessore / 2);
    // Angolo di rotazione
    plateC->angle = atan((plateC->pos_cyD - plateC->pos_cyS)/(plateC->pos_cxD - plateC->pos_cxS))*180/M_PI;
    
    return plateC;
}


// Funzione che permette di cambiare la posizione del secondo pistone.

void piston_set_pos(Livella * mylivella, float new_param) {  
    mylivella->mypiston2->pos_x1 = new_param;
    mylivella->mypiston2->pos_x2 = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2);
    mylivella->mypiston2->pos_cx = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2) + (mylivella->mypiston2->larg_2 /2);
    mylivella->myplate->pos_cxD = mylivella->mypiston2->pos_x1 + (mylivella->mypiston2->larg_1 /2);
    mylivella->myplate->angle = atan((mylivella->myplate->pos_cyD - mylivella->myplate->pos_cyS)/(mylivella->myplate->pos_cxD - mylivella->myplate->pos_cxS))*180/M_PI; 
}

// Funzione che permette di cambiare l'altezza dei cilindri esterni.

void piston_set_alt(Livella * mylivella, float new_param) { 
    mylivella->mypiston1->alt_1 = new_param;
    mylivella->mypiston2->alt_1 = new_param;
}

// Funzione che permette di cambiare la larghezza dei cilindri esterni.

void piston_set_larg1(Livella * mylivella, float new_param) { 
    mylivella->mypiston1->larg_1 = new_param;
    mylivella->mypiston2->larg_1 = new_param;
    mylivella->mypiston1->pos_x2 = mylivella->mypiston1->pos_x1 + ((mylivella->mypiston1->larg_1 - mylivella->mypiston1->larg_2)/2);
    mylivella->mypiston2->pos_x2 = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2);
    mylivella->mypiston1->pos_cx = mylivella->mypiston1->pos_x1 + ((mylivella->mypiston1->larg_1 - mylivella->mypiston1->larg_2)/2) + (mylivella->mypiston1->larg_2)/2;
    mylivella->mypiston2->pos_cx = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2) + (mylivella->mypiston2->larg_2)/2;
    mylivella->myplate->pos_cxS = mylivella->mypiston1->pos_x1 + (mylivella->mypiston1->larg_1 / 2);
    mylivella->myplate->pos_cxD = mylivella->mypiston2->pos_x1 + (mylivella->mypiston2->larg_1 / 2);
    mylivella->myplate->pos_x = mylivella->myplate->pos_cxS - 50;
    mylivella->myplate->angle = atan((mylivella->myplate->pos_cyD - mylivella->myplate->pos_cyS)/(mylivella->myplate->pos_cxD - mylivella->myplate->pos_cxS))*180/M_PI;  
}

// Funzione che permette di cambiare l'estensione del primo pistone.

void piston_set_alt1(Livella * mylivella, float new_param) { 
    mylivella->mypiston1->alt_2 = new_param;
    mylivella->mypiston1->pos_y2 = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->mypiston1->pos_cy = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->myplate->pos_cyS = mylivella->mypiston1->pos_y1 - mylivella->mypiston1->alt_2;
    mylivella->myplate->pos_y = mylivella->myplate->pos_cyS - (mylivella->myplate->spessore / 2);
    mylivella->myplate->angle = atan((mylivella->myplate->pos_cyD - mylivella->myplate->pos_cyS)/(mylivella->myplate->pos_cxD - mylivella->myplate->pos_cxS))*180/M_PI;  
}

// Funzione che permette di cambiare l'estensione del secondo pistone.

void piston_set_alt2(Livella * mylivella, float new_param) { 
    mylivella->mypiston2->alt_2 = new_param;
    mylivella->mypiston2->pos_y2 = mylivella->mypiston2->pos_y1 - mylivella->mypiston2->alt_2;
    mylivella->mypiston2->pos_cy = mylivella->mypiston2->pos_y1 - mylivella->mypiston2->alt_2;
    mylivella->myplate->pos_cyD = mylivella->mypiston2->pos_y1 - mylivella->mypiston2->alt_2;
    mylivella->myplate->angle = atan((mylivella->myplate->pos_cyD - mylivella->myplate->pos_cyS)/(mylivella->myplate->pos_cxD - mylivella->myplate->pos_cxS))*180/M_PI;  
}

// Funzione che permette di cambiare la larghezza dei due cilindri interni.

void piston_set_larg2(Livella * mylivella, float new_param) { 
    mylivella->mypiston1->larg_2 = new_param;
    mylivella->mypiston2->larg_2 = new_param;
    mylivella->mypiston1->pos_x2 = mylivella->mypiston1->pos_x1 + ((mylivella->mypiston1->larg_1 - mylivella->mypiston1->larg_2)/2);
    mylivella->mypiston2->pos_x2 = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2);
    mylivella->mypiston1->pos_cx = mylivella->mypiston1->pos_x1 + ((mylivella->mypiston1->larg_1 - mylivella->mypiston1->larg_2)/2) + (mylivella->mypiston1->larg_2)/2;
    mylivella->mypiston2->pos_cx = mylivella->mypiston2->pos_x1 + ((mylivella->mypiston2->larg_1 - mylivella->mypiston2->larg_2)/2) + (mylivella->mypiston2->larg_2)/2;
}

// Funzione che permette di cambiare lo spessore della piastra.

void plate_set_spessore(Livella * mylivella, float new_param) { 
    mylivella->myplate->spessore = new_param;
    mylivella->myplate->pos_y = mylivella->myplate->pos_cyS - (mylivella->myplate->spessore / 2);
}

// Funzione che permette di cambiare la lunghezza della piastra.

void plate_set_lunghezza(Livella * mylivella, float new_param) { 
    mylivella->myplate->lunghezza = new_param;
}


// Funzione controllo dei segni dei parametri inseriti

int param_control(Livella * mylivella) {
    
    int n = 0;

    float new_param;

    if (mylivella->mypiston1->alt_1 <= 0) {
        cout << "Altezza del cilindro esterno non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        piston_set_alt(mylivella, new_param);  
    }
    if (mylivella->mypiston1->larg_1 <= 0) {
        cout << "Larghezza del cilindro esterno non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1; 
        piston_set_larg1(mylivella, new_param);
    }
    if (mylivella->mypiston1->alt_2 <= 0) {
        cout << "Estensione del primo cilindro non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        piston_set_alt1(mylivella, new_param);  
    }
    if (mylivella->mypiston2->alt_2 <= 0) {
        cout << "Estensione del secondo cilindro non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        piston_set_alt2(mylivella, new_param);  
    }
    if (mylivella->mypiston1->larg_2 <= 0) {
        cout << "Larghezza del cilindro interno non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        piston_set_larg2(mylivella, new_param);
    }
    if (mylivella->myplate->spessore <= 0) {
        cout << "Spessore della piastra non valido, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        plate_set_spessore(mylivella, new_param);
    }
    if (mylivella->myplate->lunghezza <= 0) {
        cout << "Lunghezza della piastra non valida, inserire un valore positivo: ";
        cin >> new_param;
        n = 1;
        plate_set_lunghezza(mylivella, new_param);
    }

    return n;

}


// Controllo della coerenza dei parametri inseriti

int device_control(Livella * mylivella) {

    int n = 0;

    float new_param;

    if (mylivella->mypiston2->pos_x1 <= (mylivella->mypiston1->pos_x1 + mylivella->mypiston1->larg_1)) {
        cout << "Distanza tra i pistoni non sufficientemente grande, reinserire la coordinata x del secondo pistone: ";
        cin >> new_param;
        n = 1;
        piston_set_pos(mylivella, new_param);
    }
    if (mylivella->mypiston1->larg_1 <= mylivella->mypiston1->larg_2) {
        cout << "La larghezza del cilindro interno deve essere minore di quella del cilindro esterno, reinserire la larghezza del cilindro interno: ";
        cin >> new_param;
        n = 1;
        piston_set_larg2(mylivella, new_param);
    }
    if (mylivella->mypiston1->alt_2 > mylivella->mypiston1->alt_1) {
        cout << "L'estensione del pistone non può essere maggiore della lunghezza del cilindro esterno, reinserire l'estensione del pistone di sinistra: ";
        cin >> new_param;
        n = 1;
        piston_set_alt1(mylivella, new_param);
    }
    if (mylivella->mypiston2->alt_2 > mylivella->mypiston2->alt_1) {
        cout << "L'estensione del pistone non può essere maggiore della lunghezza del cilindro esterno, reinserire l'estensione del pistone di destra: ";
        cin >> new_param;
        n = 1;
        piston_set_alt2(mylivella, new_param);
    }
    if (mylivella->myplate->spessore >= mylivella->mypiston1->alt_1) {
        cout << "Lo spessore della piastra non deve eccedere l'altezza del cilindro esterno: ";
        cin >> new_param;
        n = 1;
        plate_set_spessore(mylivella, new_param);
    }
    if (mylivella->myplate->lunghezza < (mylivella->mypiston2->pos_x1 - mylivella->mypiston1->pos_x1 - mylivella->mypiston1->larg_1)) {
        cout << "La lunghezza della piastra non può essere inferiore alla distanza degli estremi dei due cilindri: ";
        cin >> new_param;
        n = 1;
        plate_set_lunghezza(mylivella, new_param);
    }

    return n;
}



// Funzione stampa parametri del device

void info_parti ( Livella * mylivella){
    
    cout << "Pistone di Sinistra: \t\t " << endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mylivella->mypiston1->pos_x1 <<  ", y: " << mylivella->mypiston1->pos_y1 <<  endl;
    cout << "Cilindro esterno: \t\t" << "diametro: " << mylivella->mypiston1->larg_1 << ", altezza: " << mylivella->mypiston1->alt_1 << endl;
    cout << "Cilindro Interno: \t\t" << "diametro: " << mylivella->mypiston1->larg_2 << ", altezza: " << mylivella->mypiston1->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t\t" << "x: " << mylivella->mypiston1->pos_cx <<  ", y: " << mylivella->mypiston1->pos_cy <<  endl;
    cout << "Pistone di Destra: \t\t " << endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mylivella->mypiston2->pos_x1 <<  ", y: " << mylivella->mypiston2->pos_y1 <<  endl;
    cout << "Cilindro esterno: \t\t" << "diametro: " << mylivella->mypiston2->larg_1 << ", altezza: " << mylivella->mypiston2->alt_1 << endl;
    cout << "Cilindro interno: \t\t" << "diametro: " << mylivella->mypiston2->larg_2 << ", altezza: " << mylivella->mypiston2->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t" << "x: " << mylivella->mypiston2->pos_cx <<  ", y: " << mylivella->mypiston2->pos_cy <<  endl;
    cout << "Piastra: \t\t " << endl;
    cout << "Spessore piastra: \t 30" <<  endl;
    cout << "Lunghezza piastra: \t\t 500" << endl;
    cout << "Angolo di inclinazione: \t\t" << mylivella->myplate->angle << endl;

}


// Funzione di inizializzazione e implementazione del file svg

void livella_to_svg (Livella * mylivella, string fileName, char measures ){

    ofstream mySVG( fileName + ".svg");
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;
    mySVG << livella_to_ParamSVG( mylivella );
    if (measures == 'Y') {

        mySVG << livella_to_MeasureSVG( mylivella );
    }
    mySVG << "</svg>";
    mySVG.close();

}


// Funzione implementazione del device nel file svg

string livella_to_ParamSVG ( Livella * mylivella ){

    string str = "";

    // Pistone di Sinistra
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x2) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y2) + "\" width=\"" + to_string(mylivella->mypiston1->larg_2) + "\" height=\"" + to_string(mylivella->mypiston1->alt_2) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x1) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1) + "\" width=\"" + to_string(mylivella->mypiston1->larg_1) + "\" height=\"" + to_string(mylivella->mypiston1->alt_1) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    // Pistone di Destra
    str += "<rect  x=\"" + to_string(mylivella->mypiston2->pos_x2) + "\" y=\"" + to_string(mylivella->mypiston2->pos_y2) + "\" width=\"" + to_string(mylivella->mypiston2->larg_2) + "\" height=\"" + to_string(mylivella->mypiston2->alt_2) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    str += "<rect  x=\"" + to_string(mylivella->mypiston2->pos_x1) + "\" y=\"" + to_string(mylivella->mypiston2->pos_y1) + "\" width=\"" + to_string(mylivella->mypiston2->larg_1) + "\" height=\"" + to_string(mylivella->mypiston2->alt_1) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    // Lastra:
    str += "<g transform=\"rotate(" + to_string(mylivella->myplate->angle) + "," + to_string(mylivella->mypiston1->pos_cx) + "," + to_string(mylivella->mypiston1->pos_cy) + ")\"> \n";
    str += "<rect  x=\"" + to_string(mylivella->myplate->pos_x) + "\" y=\"" + to_string(mylivella->myplate->pos_y) + "\" width=\"" + to_string(mylivella->myplate->lunghezza) + "\" height=\"" + to_string(mylivella->myplate->spessore) + "\" style=\"fill:rgb(0,120,0);stroke-width:3;stroke:rgb(200,200,200)\" /> \n";
    str += "</g> \n";
    // Coppie rotoidali
    str += "<circle cx=\"" + to_string(mylivella->mypiston1->pos_cx) + "\" cy=\"" + to_string(mylivella->mypiston1->pos_cy) + "\" r=\"20\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";
    str += "<circle cx=\"" + to_string(mylivella->mypiston2->pos_cx) + "\" cy=\"" + to_string(mylivella->mypiston2->pos_cy) + "\" r=\"20\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";

    return str;
}


// Funzione implementazione delle misure nel file svg

string livella_to_MeasureSVG (Livella * mylivella) {

    string str = "";

    // Misura larghezza cilindro esterno
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x1) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1 + mylivella->mypiston1->alt_1 + 40) + "\" width=\"" + to_string(mylivella->mypiston1->larg_1) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->mypiston1->pos_x1 + (mylivella->mypiston1->larg_1)/2) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1 + mylivella->mypiston1->alt_1 + 30) + "\" fill=\"white\">" + to_string(mylivella->mypiston1->larg_1) + "</text>";
    // Misura altezza cilindro esterno
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x1 - 30) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1) + "\" width=\"0.1\" height=\"" + to_string(mylivella->mypiston1->alt_1) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->mypiston1->pos_x1 - 60) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1 + (mylivella->mypiston1->alt_1)/2) + "\" fill=\"white\">" + to_string(mylivella->mypiston1->alt_1) + "</text>\n";
    // Misura altezza cilindro interno di sinistra
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x2 - 95) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y2) + "\" width=\"0.1\" height=\"" + to_string(mylivella->mypiston1->alt_2) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->mypiston1->pos_x2 - 110) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y2 + (mylivella->mypiston1->alt_2)/2) + "\" fill=\"white\">" + to_string(mylivella->mypiston1->alt_2) + "</text>\n";
    // Misura altezza cilindro interno di destra
    str += "<rect  x=\"" + to_string(mylivella->mypiston2->pos_x2 + 95) + "\" y=\"" + to_string(mylivella->mypiston2->pos_y2) + "\" width=\"0.1\" height=\"" + to_string(mylivella->mypiston2->alt_2) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->mypiston2->pos_x2 + 105) + "\" y=\"" + to_string(mylivella->mypiston2->pos_y2 + (mylivella->mypiston2->alt_2)/2) + "\" fill=\"white\">" + to_string(mylivella->mypiston2->alt_2) + "</text>\n";
    // Misura fra cilindri
    str += "<rect  x=\"" + to_string(mylivella->mypiston1->pos_x1 + mylivella->mypiston1->larg_1) + "\" y=\"" + to_string(mylivella->mypiston1->pos_y1 + (mylivella->mypiston1->alt_1)/2) + "\" width=\"" + to_string(mylivella->mypiston2->pos_x1 - mylivella->mypiston1->pos_x1 - mylivella->mypiston1->larg_1) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->mypiston1->pos_x1 + mylivella->mypiston1->larg_1 + (mylivella->mypiston2->pos_x1 - mylivella->mypiston1->pos_x1 - mylivella->mypiston1->larg_1)/2) + "\" y=\"" + to_string((mylivella->mypiston1->pos_y1 + (mylivella->mypiston1->alt_1)/2) - 10) + "\" fill=\"white\">" + to_string(mylivella->mypiston2->pos_x1 - (mylivella->mypiston1->pos_x1 - mylivella->mypiston1->larg_1)) + "</text>\n";
    // Misura piastra
    str += "<g transform=\"rotate(" + to_string(mylivella->myplate->angle) + "," + to_string(mylivella->mypiston1->pos_cx) + "," + to_string(mylivella->mypiston1->pos_cy) + ")\"> \n";
    str += "<rect  x=\"" + to_string(mylivella->myplate->pos_x) + "\" y=\"" + to_string(mylivella->myplate->pos_y - 28) + "\" width=\"" + to_string(mylivella->myplate->lunghezza) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mylivella->myplate->pos_x + (mylivella->myplate->lunghezza)/2) + "\" y=\"" + to_string(mylivella->myplate->pos_y - 40) + "\" fill=\"white\">" + to_string(mylivella->myplate->lunghezza) + "</text>\n";
    str += "</g> \n";

    return str;
}


// Funzione cancellazione struct e istanze

void livella_destroy (Livella * mylivella) {

    delete mylivella->mypiston1;
    delete mylivella->mypiston2;
    delete mylivella->myplate;

}