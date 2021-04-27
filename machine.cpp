#include <iostream>
#include <fstream>
#include "libreries/guida.h"
#include "libreries/livellaMobile.h"
#include "libreries/external/Livella.h"
#include "libreries/external/sistemaAstePerno.h"

int main(){

    LivellaMobile * mylivella;

    mylivella = livellaMobile_init(400, 300, 300, 50);

    /*string str = livella_to_ParamSVG(mylivella->pistone[0], mylivella->pistone[1], mylivella->pedana);
    ofstream out ("ciaghi");
    out << str;
    out.close();*/

    return EXIT_SUCCESS;
}