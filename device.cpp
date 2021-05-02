#include <iostream>
#include "libreries/guida.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;

    myguida = guida_crea();

    guida_visualizza_info( myguida );

    cout << endl << "Salvo il risultato della guida prismatica in \"guidaprismatica.svg\"." << endl << endl;
    guida_to_SVG(myguida, "guidaprismatica", false);

    cout << "Faccio il parsing della guida prismatica e ne visualizzo i dati: " << endl;
    GuidaPrismatica * g = guida_parse_svg("guidaprismatica", true);
    guida_visualizza_info( g );
    if( guida_verifica_uguaglianza(myguida, g, true) ) cout << "Le due guide sono uguali!" << endl;
    else cout << "Le due guide sono diverse" << endl;

    guida_distruggi( g );
    guida_distruggi( myguida );
    return EXIT_SUCCESS;
}
