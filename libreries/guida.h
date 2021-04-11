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

    /*
     * Funzione che inizializza una guida prismatica
     * 
     * @param lungh: lunghezza della guida prismatica che si vuole generare
     * @param corsa: corsa dell'elemento prismatico
     * @param dimx: dimensione orizzontale delle cerniere e dell'elemento prismatico
     * @param dimy: dimensione verticale delle cerniere dell'elemento prismatico
     * 
     */
    GuidaPrismatica * guida_inizializzazione ( double lungh, double corsa, double dimx, double dimy);

#endif