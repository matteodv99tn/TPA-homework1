#ifndef _LIVELLA_MOBILE_H_

#define _LIVELLA_MOBILE_H_

    #include "guida.h"
    #include "external/Livella.h"
    #include "external/sistemaAstePerno.h"

    struct DatiLivella{

        float posx1;
        float posx2;
        float posy;

        float largbase;
        float largtesta;

        float alt_cilindro;
        float alt_sx;
        float alt_dx;

        float spessore;
        float lunghezza;

    };

    struct LivellaMobile{
        
        GuidaPrismatica * supporto[2];
        Livella * livella;

        DatiLivella dati_livella;

        float pos_x;
        float pos_y;
        float distanza;
        float perc_corsa;

    };

    LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc);

    void livellaMobile_to_svg(LivellaMobile * livella, string nome_file);

#endif