#ifndef _LIVELLA_MOBILE_H_

#define _LIVELLA_MOBILE_H_

    #include "guida.h"
    #include "external/Livella.h"
    #include "external/sistemaAstePerno.h"

    struct LivellaMobile{
        
        GuidaPrismatica * supporto[2];
        Piston * pistone[2];
        Plate * pedana;

        float pos_x;
        float pos_y;
        float distanza;
        float perc_corsa;

    };

    LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc);

#endif