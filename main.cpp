#include <iostream>
#include "libreries/guida.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;

    myguida = guida_carica_file("myguida");

    guida_to_SVG(myguida, "test", true);

    guida_distruggi( myguida );
    return EXIT_SUCCESS;
}
