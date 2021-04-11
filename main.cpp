#include <iostream>
#include "libreries/guida.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;

    cout << "Inizializzo una guida prismatica di " << endl;
    cout << "> lunghezza: 50" << endl;
    cout << "> corsa: 20" << endl;
    cout << "> dimesione orizzontale di cerniere e guida: 10" << endl;
    cout << "> dimesione verticale di cerniere e guida: 10" << endl << endl;

    myguida = guida_init(50,20, 10,10);


    cout << "Distruggo la struttura e termino il programma" << endl;
    guida_distruggi( myguida );
    
    return EXIT_SUCCESS;
}
