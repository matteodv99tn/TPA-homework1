#include <iostream>
#include <fstream>
#include "libreries/guida.h"
#include "libreries/livellaMobile.h"
#include "libreries/external/Livella.h"
#include "libreries/external/sistemaAstePerno.h"

int main(){

    LivellaMobile * mylivella;

    mylivella = livellaMobile_init(400, 300, 300, 100);
    cout << "Inizializzazione effettuata!" << endl << endl;

    guida_visualizza_info(mylivella->supporto[0]);


    livellaMobile_to_svg(mylivella, "livtest");

    return EXIT_SUCCESS;
}