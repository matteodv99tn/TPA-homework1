
#include "guida.h"

GuidaPrismatica* guida_inizializzazione ( double lungh, double corsa, double dimx, double dimy){

    // Creo l'istanza della guida prismatica
    GuidaPrismatica* guida = new GuidaPrismatica;

    // Associo le grandezze in input alle relative grandezze della struct
    guida->lunghezza = lungh;
    guida->corsa = corsa;

    guida->dim_base_x = dimx;
    guida->dim_base_y = dimy;

    guida->dim_perno_x = dimx;
    guida->dim_perno_y = dimy;

    guida->corsa = dimy / 3;
    guida->alpha = 0;

    // Ritorno l'oggetto della guida inizializzata
    return guida;

}

void guida_distruggi ( GuidaPrismatica * guida ){

    delete guida;

}