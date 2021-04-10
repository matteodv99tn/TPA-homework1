#ifndef _GUIDA_PRISMATICA_H_

    #define _GUIDA_PRISMATICA_H_

    /*
     *  Definzione della struttura per la guida prismatica
     * 
     *  @param lunghezza: lunghezza complessiva della barra della guida prismatica
     *  @param corsa: posizione relativa del glifo rispetto alla posizione iniziale
     * 
     *  @param dim_perno_x: dimensione orizzontale del perno mobile
     *  @param dim_perno_y: dimensione verticale del perno mobile
     * 
     *  @param dim_base_x: dimensione orizzontale dei supporti di montaggio
     *  @param dim_base_y: dimensione verticale dei supporti di montaggio
     * 
     *  @param spessore: spessore della guida prismatica
     *  @param alpha: inclinazione della guida rispetto all'orizzontale
     */
    struct GuidaPrismatica {
        
        double lunghezza;
        double corsa;
        
        double dim_perno_x;
        double dim_perno_y;
        
        double dim_base_x;
        double dim_base_y;

        double spessore;
        double alpha;
        
    };

#endif