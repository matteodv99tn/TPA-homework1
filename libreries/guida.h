#ifndef _GUIDA_PRISMATICA_H_

    #define _GUIDA_PRISMATICA_H_

    /*
     * Definizione della struttura dei rettangoli utilizzati per la guida prismatica
     * Struttura di supporto per la rappresentazione grafica del componente
     * 
     * @param dim_x: dimensione orizzontale del rettangolo
     * @param dim_y: dimensione verticale del rettangolo
     * 
     */
    struct GRect {
        
        float dim_x;
        float dim_y;

    };

    /*
     *  Definzione della struttura per la guida prismatica
     * 
     *  @param lunghezza: lunghezza complessiva della barra della guida prismatica
     *  @param corsa: posizione relativa del glifo rispetto alla posizione iniziale
     *  
     *  @param pos_x: posizione orizzontale del centro della guida prismatica
     *  @param pos_y: posizione verticale del centro della guida prismatica
     *  
     *  @param incastri: oggetto GRect che contiene le informazioni per quanto riguarda le cerniere del sistema
     *  @param guida: oggetto GRect che contiene le informazioni per quanto riguarda la guida del componente
     * 
     *  @param spessore: spessore della guida prismatica
     *  @param alpha: inclinazione della guida rispetto all'orizzontale
     */
    struct GuidaPrismatica {
        
        float lunghezza;
        float corsa;

        float pos_x;
        float pos_y;
        
        GRect * incastri;
        GRect * guida;

        float spessore;
        float alpha;
        
    };

    /*
     * Funzione che istanzia e inizializza il rettangolo
     * 
     * @param dimx: dimensione orizzontale del rettangolo
     * @param dimy: dimensione verticale del rettangolo
     */
    GRect * grect_init( float dimx, float dimy );
    
    /*
     * Funzione che inizializza una guida prismatica
     * 
     * @param lungh: lunghezza della guida prismatica che si vuole generare
     * @param corsa: corsa dell'elemento prismatico
     * @param dimx: dimensione orizzontale delle cerniere e dell'elemento prismatico
     * @param dimy: dimensione verticale delle cerniere dell'elemento prismatico
     * 
     */
    GuidaPrismatica * guida_init ( float lungh, float corsa, float dimx, float dimy);

    /*
     * Funzione che permette di deallocare correttamente l'istanza di una guida prismatica creata
     */
    void guida_distruggi ( GuidaPrismatica * guida );
    
#endif