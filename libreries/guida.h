#ifndef _GUIDA_PRISMATICA_H_

    #define _GUIDA_PRISMATICA_H_

    #include <iostream>

    #define DEF_RGB_R 130
    #define DEF_RGB_G 130
    #define DEF_RGB_B 130

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

        unsigned int colore[3];

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
     * Funzione che inizializza una guida pristring
     * @param lungh: lunghezza della guida prismatica che si vuole generare
     * @param corsa: corsa dell'elemento prismatico
     * @param dimx: dimensione orizzontale delle cerniere e dell'elemento prismatico
     * @param dimy: dimensione verticale delle cerniere dell'elemento prismatico
     * 
     * restituisce un oggetto NULL se l'inizializzazione non è andata a buon fine
     * 
     */
    GuidaPrismatica * guida_init ( float posx, float posy, float lungh, float corsa, float dimx, float dimy);

    /*
     * Funzione che permette di creare da terminale una guida prismatica
     * 
     * @return guida prismatica risultante dall'operazione
     * 
     */
    GuidaPrismatica * guida_crea();

    /*
     * Funzione che permette di deallocare correttamente l'istanza di una guida prismatica creata
     */
    void guida_distruggi ( GuidaPrismatica * guida );

    /*
     * Funzione che permette di visualizzare a schermo le informazioni sulla guida prismatica
     */    
    void guida_visualizza_info ( GuidaPrismatica * guida );
    
    /*
     * Funzione che permette di impostare la lunghezza della guida prismatica
     * 
     * @param guida: struttura GuidaPrismatica da modificare
     * @param l: lunghezza da associare alla struttura
     * 
     * @return 0: operazione effettuata correttamente
     * @return 1: ingresso negativo, grandezza invariata
     * 
     */ 
    int guida_set_lunghezza( GuidaPrismatica * guida , float l );

    /* 
     * Funzione che permette di impostare lo spessore della guida prismatica
     * 
     * @param guida: guida della quale modificare lo spessore
     * @param spess: nuovo spessore da inserire
     * 
     */
    void guida_set_spessore( GuidaPrismatica * guida, float spess);

    /*
     * Funzione che permette di impostare la corsa di una guida prismatica effettuando dei controlli
     * 
     * @param guida: struttura GuidaPrismatica da modificare
     * @param c: corsa da associare alla struttura
     * 
     * @return 0: operazione effettuata con successo
     * @return 1: operazione effettuata con modifiche
     * 
     */ 
    int guida_set_corsa( GuidaPrismatica * guida , float c );

    /* 
     * Funzione che permette di impostare l'angolo (in gradi) nel verso antiorario della struttura
     *
     * @param guida: puntatore alla guida prismatica da modificare
     * @param deg: angolo in gradi da impostare
    */
    void guida_set_angolo( GuidaPrismatica * guida, float deg);

    /*
     * Funzione che permette di impostare la corsa di una guida prismatica effettuando dei controlli
     * 
     * @param guida: struttura GuidaPrismatica da modificare
     * @param dimx: dimensione orizzontale della cerniera
     * @param dimy: dimensione verticale della cerniera
     * @param col_R (opzionale): componente rossa del colore RGB (tra 0 e 255)
     * @param col_G (opzionale): componente verde del colore RGB (tra 0 e 255)
     * @param col_B (opzionale): componente blu del colore RGB (tra 0 e 255)
     * 
     * @return 0: operazione effettuata con successo
     * @return 1: modifica non effettuata per dimensione negativa
     * 
     */ 
    int guida_set_cerniera( GuidaPrismatica * guida , float dimx, float dimy, unsigned int col_R = DEF_RGB_R, unsigned int col_G = DEF_RGB_R , unsigned int col_B = DEF_RGB_B);

    /*
     * Funzione che permette di impostare le proprietà del rettangolo della guida prismatica
     * 
     * @param guida: struttura GuidaPrismatica da modificare
     * @param dimx: dimensione orizzontale della guida
     * @param dimy: dimensione verticale della guida
     * @param col_R (opzionale): componente rossa del colore RGB (tra 0 e 255)
     * @param col_G (opzionale): componente verde del colore RGB (tra 0 e 255)
     * @param col_B (opzionale): componente blu del colore RGB (tra 0 e 255)
     * 
     * @return 0: operazione effettuata con successo
     * @return 1: modifica non effettuata per dimensione negativa
     * 
     */ 
    int guida_set_guida( GuidaPrismatica * guida , float dimx, float dimy, unsigned int col_R = DEF_RGB_R, unsigned int col_G = DEF_RGB_R , unsigned int col_B = DEF_RGB_B);


    /*
     * Funzione interattiva che da linea di comando permette di modificare dei parametri della guida prismatica
     * 
     * @param guida: oggetto guida prismatica da modificare
     * 
     */
    void guida_modifica( GuidaPrismatica * guida);

    /*
     * Funzione che permette di controllare l'integrità strutturale di una guida prismatica, correggendo eventuali errori
     * 
     * @param guida: guida prismatica della quale controllare l'integrità
     * 
     * @return -1: effettuate modifiche ma operazione svolta correttamente
     * @return 0: la guida prismatica è corretta
     * @return 1: lunghezza della guida negativa o nulla
     * @return 2: dimensioni delle cerniere invalide
     * @return 3; dimensioni della guida prismatica invalide
     * 
     * Correzioni effettuate automaticamente:
     *  > spostare la corsa al valore tollerato più plausibile alla realtà
     */
    int guida_controlla_integrita ( GuidaPrismatica * guida );

    /*
     * Funzione che permette di convertire un oggetto GuidaPrismatica in una stringa SVG
     * 
     * @param guida: guida prismatica che si vuole convertire in sorgente SVG
     * @param visualizza_dimensioni (opzionale): permette di scegliere se visualizzare o meno le dimensioni  sul disegno
     * 
     */
    std::string guida_to_SVGstring( GuidaPrismatica * guida, bool visualizza_dimensioni = false);  

    /*
     * Funzione che permette di salvare in un file SVG il disegno della guida prismatica.
     * 
     * @param guida: guida prismatica da renderizzare
     * @param nome_file: nome del file SVG contenente il disegno
     * 
     */
    void guida_to_SVG( GuidaPrismatica * guida , std::string nome_file, bool visualizza_dimensioni = false );

    GuidaPrismatica * guida_parse_svg(std::string file_name, bool with_header);

    /*
     * Funzione che permette il salvataggio di una guida in un file di testo .txt
     * 
     * @param guida: guida prismatica da salvare
     * @param nome_file: nome del file sul quale salvare le informazioni
     */
    void guida_salva_file ( GuidaPrismatica * guida, std::string nome_file );

    /*
     * Funzione che permette di creare una struttura GuidaPrismatica partendo da un file di testo correttamente redatto
     * 
     * @param nome_file: nome del file (senza estensione) da caricare
     * 
     */
    GuidaPrismatica * guida_carica_file( std::string nome_file );

    /**
    /*  Funzione per input di float,
    /*  ritorna il valore inserito da tastiera 
    */
    float input();

#endif