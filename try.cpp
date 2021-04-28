#include <iostream>
#include <fstream>
#include "libreries/guida.h"
#include "libreries/livellaMobile.h"
#include "libreries/external/Livella.h"
#include "libreries/external/sistemaAstePerno.h"

int main(){

    GuidaPrismatica* tmp = guida_init(400,500,30,15,200,20);
    guida_modifica(tmp);
    guida_distruggi(tmp);
}