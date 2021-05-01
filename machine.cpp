#include <iostream>
#include <fstream>
#include "libreries/guida.h"
#include "libreries/livellaMobile.h"
#include "libreries/external/Livella.h"
#include "libreries/external/sistemaAstePerno.h"

int main(){

    LivellaMobile * mylivella = livellaMobile_da_console();

    livellaMobile_to_svg(mylivella, "livtest");

    livellaMobile_destroy(mylivella);
    
    return EXIT_SUCCESS;
}