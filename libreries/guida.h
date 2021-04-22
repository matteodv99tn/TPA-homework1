#ifndef _GUIDA_PRISMATICA_H_

    #define _GUIDA_PRISMATICA_H_

    #include <iostream>

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
     * @param posx: posizione orizzontale
     * @param posy: posizione verticale
     * @param lungh: lunghezza della guida prismatica che si vuole generare
     * @param corsa: corsa dell'elemento prismatico
     * @param dimx: dimensione orizzontale delle cerniere e dell'elemento prismatico
     * @param dimy: dimensione verticale delle cerniere dell'elemento prismatico
     * 
     */
    GuidaPrismatica * guida_init ( float posx, float posy, float lungh, float corsa, float dimx, float dimy);

    /*
     * Funzione che permette di deallocare correttamente l'istanza di una guida prismatica creata
     */
    void guida_distruggi ( GuidaPrismatica * guida );

    /*
     * Funzione che permette di visualizzare a schermo le informazioni sulla guida prismatica
     */    
    void guida_visualizza_info ( GuidaPrismatica * guida );

    /*
     * Funzione che permette di controllare l'integrità strutturale di una guida prismatica, correggendo eventuali errori
     * 
     * @param guida: guida prismatica della quale controllare l'integrità
     * 
     * @errorcode 0: la guida prismatica è corretta
     * @errorcode 1: lunghezza della guida negativa o nulla
     * @errorcode 2: dimensioni delle cerniere invalide
     * @errorcode 3; dimensioni della guida prismatica invalide
     * 
     * Correzioni effettuate automaticamente:
     *  > spostare la corsa al valore tollerato più plausibile alla realtà
     */
    int guida_controlla_integrita ( GuidaPrismatica * guida );

    /*
     * Funzione che permette di convertire un oggetto GuidaPrismatica in una stringa SVG
     * 
     * @param guida: guida prismatica che si vuole convertire in sorgente SVG
     * 
     */
    std::string guida_to_SVGstring( GuidaPrismatica * guida );  

    /*
     * Funzione che permette di salvare in un file SVG il disegno della guida prismatica.
     * 
     * @param guida: guida prismatica da renderizzare
     * @param nome_file: nome del file SVG contenente il disegno
     * 
     */
    void guida_to_SVG( GuidaPrismatica * guida , std::string nome_file );
#endif