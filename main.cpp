#include <iostream>
#include "libreries/guida.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;

    myguida = guida_init(400,400,500, 150, 50, 70);

    guida_to_SVG(myguida, "../test");

    guida_distruggi( myguida );
    return EXIT_SUCCESS;
}
