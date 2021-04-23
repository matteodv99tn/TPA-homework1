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

    myguida = guida_init(200,200,250, 100, 30, 60);

    guida_modifica( myguida );

    guida_to_SVG( myguida , "test");

    cout << "Informazioni sulla guida salvata:" << endl;
    guida_visualizza_info( myguida );

    cout << "Distruggo la struttura e termino il programma" << endl;
    guida_distruggi( myguida );
    
    return EXIT_SUCCESS;
}
