#include "Livella.h"
#include <iostream>
#include <string.h> 
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;


Param *parameters_init(int nPar) {

    Param * paramC = new Param;

    string stringArr[nPar] = {"Inserire posizione x del primo pistone: ",
                            "Inserire posizione y dei due pistoni: ",
                            "Inserire larghezza cilindro esterno: ",
                            "Inserire lunghezza cilindro esterno: ",
                            "Inserire posizione x del secondo pistone: ",
                            "Inserire larghezza cilindro interno: ",
                            "Inserire estensione primo pistone: ",
                            "Inserire estensione secondo pistone: ",
                            "Inserire spessore della piastra: ",
                            "Inserire lunghezza della piastra: "};
    int arr[nPar];

    for(int i = 0; i < nPar; i++) {  // Vincolo sui parametri negativi
        cout << stringArr[i];
        cin >> paramC->arr[i];

        if (paramC->arr[i] <= 0) {
            while (paramC->arr[i] <= 0){
                cout << "Inserire un parametro positivo." << endl;
                cout << stringArr[i];
                cin >> paramC->arr[i];
            }
        }
    }

        if (paramC->arr[4] <= paramC->arr[0] + paramC->arr[2]){
            while (paramC->arr[4] <= paramC->arr[0] + paramC->arr[2]){
                cout << "La distanza tra i pistoni non è sufficientemente grande." << endl;
                cout << stringArr[4];
                cin >> paramC->arr[4];
            }
        }

        if (paramC->arr[5] >= paramC->arr[2]){
            while (paramC->arr[5] >= paramC->arr[2]){
                cout << "La larghezza del cilindro interno deve essere minore di quella del cilindro esterno." << endl;
                cout << stringArr[5];
                cin >> paramC->arr[5];
            }
        }

        if (paramC->arr[6] > paramC->arr[3]){
            while (paramC->arr[6] > paramC->arr[3]){
                cout << "L'estensione del cilindro interno non può essere maggiore della lunghezza del cilindro esterno." << endl;
                cout << stringArr[6];
                cin >> paramC->arr[6];
            }
        }

        if (paramC->arr[7] > paramC->arr[3]){
            while (paramC->arr[7] > paramC->arr[3]){
                cout << "L'estensione del cilindro interno non può essere maggiore della lunghezza del cilindro esterno." << endl;
                cout << stringArr[7];
                cin >> paramC->arr[7];
            }
        }

        if (paramC->arr[8] >= paramC->arr[3]){
            while (paramC->arr[7] > paramC->arr[3]){
                cout << "Lo spessore della piastra non deve eccedere l'altezza del cilindro esterno." << endl;
                cout << stringArr[8];
                cin >> paramC->arr[8];
            }
        }

        if (paramC->arr[9] <= (paramC->arr[4] - paramC->arr[0] + paramC->arr[2])){
            while (paramC->arr[7] > paramC->arr[3]){
                cout << "La lunghezza della piastra non può essere inferiore alla distanza delgi estremi dei due cilindri." << endl;
                cout << stringArr[8];
                cin >> paramC->arr[8];
            }
        }

    return paramC;
}


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
    pistonC->pos_cx = pistonC->pos_x2 + (pistonC->larg_2)/2;
    pistonC->pos_cy = pistonC->pos_y2;

    // Ritorno l'oggetto del pistone inizializzato
    return pistonC;

}

Plate* plate_init (float spess, float lungh, Piston * mypiston1, Piston * mypiston2) {


    Plate * plateC = new Plate;

    // Posizione x e y della piastra prima della rotazione
    plateC->pos_x = mypiston1->pos_cx - 50;
    plateC->pos_y = mypiston1->pos_cy - 15;

    // Spessore e lunghezza della piastra
    plateC->spessore = spess;
    plateC->lunghezza = lungh;

    // Angolo di rotazione
    plateC->angle = atan((mypiston2->pos_cy - mypiston1->pos_cy)/(mypiston2->pos_cx - mypiston1->pos_cx))*180/M_PI;

    // Ritorno l'oggetto della piastra inizializzato
    return plateC;

}



void info_parti ( Piston * mypiston1, Piston * mypiston2, Plate * myplate ){
    
    cout << "Pistone di Sinistra: \t\t " << endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mypiston1->pos_x1 <<  ", y: " << mypiston1->pos_y1 <<  endl;
    cout << "Cilindro esterno: \t\t" << "diametro: " << mypiston1->larg_1 << ", altezza: " << mypiston1->alt_1 << endl;
    cout << "Cilindro Interno: \t\t" << "diametro: " << mypiston1->larg_2 << ", altezza: " << mypiston1->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t\t" << "x: " << mypiston1->pos_cx <<  ", y: " << mypiston1->pos_cy <<  endl;

    cout << "Pistone di Destra: \t\t " << endl;
    cout << "Posizione pistone:  \t\t" << "x: " << mypiston2->pos_x1 <<  ", y: " << mypiston2->pos_y1 <<  endl;
    cout << "Cilindro esterno: \t\t" << "diametro: " << mypiston2->larg_1 << ", altezza: " << mypiston2->alt_1 << endl;
    cout << "Cilindro Interno: \t\t" << "diametro: " << mypiston2->larg_2 << ", altezza: " << mypiston2->alt_2 << endl;
    cout << "Coordinate coppia rotoidale: \t" << "x: " << mypiston2->pos_cx <<  ", y: " << mypiston2->pos_cy <<  endl;

    cout << "Piastra: \t\t " << endl;
    cout << "Spessore piastra: \t 30" <<  endl;
    cout << "Lunghezza piastra: \t\t 500" << endl;
    cout << "Angolo di inclinazione: \t\t" << myplate->angle << endl;

}



void livella_to_svg (Piston * mypiston1, Piston * mypiston2, Plate * myplate, string fileName, bool measures ){

    ofstream mySVG( fileName + ".svg");
    
    mySVG << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
    mySVG << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;

    mySVG << livella_to_ParamSVG( mypiston1, mypiston2, myplate );
    
    if (measures == 1) {

        mySVG << livella_to_MeasureSVG( mypiston1, mypiston2, myplate );
    }

    mySVG << "</svg>";
    mySVG.close();

}


string livella_to_ParamSVG ( Piston * mypiston1, Piston * mypiston2, Plate * myplate ){

    string str = "";

    // Pistone di Sinistra
    str += "<rect  x=\"" + to_string(mypiston1->pos_x2) + "\" y=\"" + to_string(mypiston1->pos_y2) + "\" width=\"" + to_string(mypiston1->larg_2) + "\" height=\"" + to_string(mypiston1->alt_2) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    str += "<rect  x=\"" + to_string(mypiston1->pos_x1) + "\" y=\"" + to_string(mypiston1->pos_y1) + "\" width=\"" + to_string(mypiston1->larg_1) + "\" height=\"" + to_string(mypiston1->alt_1) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    // Pistone di Destra
    str += "<rect  x=\"" + to_string(mypiston2->pos_x2) + "\" y=\"" + to_string(mypiston2->pos_y2) + "\" width=\"" + to_string(mypiston2->larg_2) + "\" height=\"" + to_string(mypiston2->alt_2) +  "\" style=\"fill:rgb(200,200,200);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    str += "<rect  x=\"" + to_string(mypiston2->pos_x1) + "\" y=\"" + to_string(mypiston2->pos_y1) + "\" width=\"" + to_string(mypiston2->larg_1) + "\" height=\"" + to_string(mypiston2->alt_1) +  "\" style=\"fill:rgb(0,200,0);stroke-width:3;stroke:rgb(0,0,0)\" /> \n";
    // Lastra:
    str += "<g transform=\"rotate(" + to_string(myplate->angle) + "," + to_string(mypiston1->pos_cx) + "," + to_string(mypiston1->pos_cy) + ")\"> \n";
    str += "<rect  x=\"" + to_string(myplate->pos_x) + "\" y=\"" + to_string(myplate->pos_y) + "\" width=\"" + to_string(myplate->lunghezza) + "\" height=\"" + to_string(myplate->spessore) + "\" style=\"fill:rgb(0,120,0);stroke-width:3;stroke:rgb(200,200,200)\" /> \n";
    str += "</g> \n";
    // Coppie rotoidali
    str += "<circle cx=\"" + to_string(mypiston1->pos_cx) + "\" cy=\"" + to_string(mypiston1->pos_cy) + "\" r=\"20\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";
    str += "<circle cx=\"" + to_string(mypiston2->pos_cx) + "\" cy=\"" + to_string(mypiston2->pos_cy) + "\" r=\"20\" stroke=\"black\" stroke-width=\"3\" fill=\"lightgrey\" /> \n";


    return str;
}


string livella_to_MeasureSVG (Piston * mypiston1, Piston * mypiston2, Plate * myplate) {

    string str = "";

    // Misura larghezza cilindro esterno
    str += "<rect  x=\"" + to_string(mypiston1->pos_x1) + "\" y=\"" + to_string(mypiston1->pos_y1 + mypiston1->alt_1 + 40) + "\" width=\"" + to_string(mypiston1->larg_1) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mypiston1->pos_x1 + (mypiston1->larg_1)/2) + "\" y=\"" + to_string(mypiston1->pos_y1 + mypiston1->alt_1 + 30) + "\" fill=\"white\">" + to_string(mypiston1->larg_1) + "</text>";

    // Misura altezza cilindro esterno
    str += "<rect  x=\"" + to_string(mypiston1->pos_x1 - 30) + "\" y=\"" + to_string(mypiston1->pos_y1) + "\" width=\"0.1\" height=\"" + to_string(mypiston1->alt_1) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mypiston1->pos_x1 - 60) + "\" y=\"" + to_string(mypiston1->pos_y1 + (mypiston1->alt_1)/2) + "\" fill=\"white\">" + to_string(mypiston1->alt_1) + "</text>\n";

    // Misura altezza cilindro interno di sinistra
    str += "<rect  x=\"" + to_string(mypiston1->pos_x2 - 95) + "\" y=\"" + to_string(mypiston1->pos_y2) + "\" width=\"0.1\" height=\"" + to_string(mypiston1->alt_2) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mypiston1->pos_x2 - 105) + "\" y=\"" + to_string(mypiston1->pos_y2 + (mypiston1->alt_2)/2) + "\" fill=\"white\">" + to_string(mypiston1->alt_2) + "</text>\n";

    // Misura altezza cilindro interno di destra
    str += "<rect  x=\"" + to_string(mypiston2->pos_x2 + 95) + "\" y=\"" + to_string(mypiston2->pos_y2) + "\" width=\"0.1\" height=\"" + to_string(mypiston2->alt_2) + "\" style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mypiston2->pos_x2 + 105) + "\" y=\"" + to_string(mypiston2->pos_y2 + (mypiston2->alt_2)/2) + "\" fill=\"white\">" + to_string(mypiston2->alt_2) + "</text>\n";

    // Misura fra cilindri
    str += "<rect  x=\"" + to_string(mypiston1->pos_x1 + mypiston1->larg_1) + "\" y=\"" + to_string(mypiston1->pos_y1 + (mypiston1->alt_1)/2) + "\" width=\"" + to_string(mypiston2->pos_x1 - (mypiston1->pos_x1 - mypiston1->larg_1)) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(mypiston1->pos_x1 + mypiston1->larg_1 + (mypiston2->pos_x1 - (mypiston1->pos_x1 - mypiston1->larg_1))/2) + "\" y=\"" + to_string((mypiston1->pos_y1 + (mypiston1->alt_1)/2) - 10) + "\" fill=\"white\">" + to_string(mypiston2->pos_x1 - (mypiston1->pos_x1 - mypiston1->larg_1)) + "</text>\n";

    // Misura piastra
    str += "<g transform=\"rotate(" + to_string(myplate->angle) + "," + to_string(mypiston1->pos_cx) + "," + to_string(mypiston1->pos_cy) + ")\"> \n";
    str += "<rect  x=\"" + to_string(myplate->pos_x) + "\" y=\"" + to_string(myplate->pos_y - 28) + "\" width=\"" + to_string(myplate->lunghezza) + "\" height=\"0.1\"" + " style=\"fill:rgb(0,0,0);stroke-width:1;stroke:rgb(225,225,225)\" /> \n";
    str += "<text x=\"" + to_string(myplate->pos_x + (myplate->lunghezza)/2) + "\" y=\"" + to_string(myplate->pos_y - 40) + "\" fill=\"white\">" + to_string(myplate->lunghezza) + "</text>\n";
    str += "</g> \n";

    return str;
}









void livella_destroy (Piston * mypiston1, Piston * mypiston2, Plate * myplate, Param * myparam) {

    delete mypiston1;
    delete mypiston2;
    delete myplate;
    delete myparam;

}