#ifndef LIVELLA

    #define LIVELLA

    #include <iostream>


    /*
     *  Introduzione ai membri della struct Piston:
     * 
     *  @param pos_x1: posizione x del cilindro esterno
     *  @param pos_y1: posizione y del cilindro esterno
     *  @param pos_x2: posizione x del cilindro interno
     *  @param pos_y2: posizione x del cilindro interno
     *  @param pos_cx: posizione x della coppia rotoidale
     *  @param pos_cy: posizione y della coppia rotoidale
     *  @param alt_1: altezza del cilindro esterno
     *  @param larg_1: larghezza del cilindro esterno
     *  @param alt_2: altezza del cilindro interno
     *  @param larg_2: larghezza del cilindro interno
     * 
     */
    struct Piston {
    
        float pos_x1;
        float pos_y1;
        float pos_x2;
        float pos_y2;
        float pos_cx;
        float pos_cy;
        float alt_1;
        float larg_1;
        float alt_2;
        float larg_2;        
    };

    /*
     *  Introduzione ai membri della struct Plate:
     *  
     *  @param pos_cxS: coordinata x del centro della coppia rotoidale del pistone di sinistra
     *  @param pos_cyS: coordinata y del centro della coppia rotoidale del pistone di sinistra
     *  @param pos_cxD: coordinata x del centro della coppia rotoidale del pistone di destra
     *  @param pos_cyD: coordinata y del centro della coppia rotoidale del pistone di destra
     *  @param pos_x: posizione x della piastra
     *  @param pos_y: posizione y della piastra
     *  @param spessore: spessore della piastra
     *  @param lunghezza: lunghezza della piastra
     *  @param angle: angolo di inclinazione della piastra
     * 
     */
    struct Plate {
        
        float pos_cxS;
        float pos_cyS;
        float pos_cxD;
        float pos_cyD;
        float pos_x;
        float pos_y;
        float spessore;
        float lunghezza;
        float angle;    
    };


 
    struct Livella {

        Piston * mypiston1;
        Piston * mypiston2;
        Plate * myplate;

    };

    /*
     * Funzione che permette di creare una livella da console iniziando internamente i valori
     * 
     * @return puntatore alla livella creata
     * 
     */ 
    Livella * livella_from_console();


    /*
     * Funzione di inserimento dei parametri
     * 
     *  @param posx1: posizione x del cilindro esterno
     *  @param posy: posizione y dei cilindri esterni
     *  @param alt1: altezza del cilindro esterno
     *  @param larg1: larghezza del cilindro esterno
     *  @param altS: estensione del pistone di sinistra
     *  @param altD: estensione del pistone di destra
     *  @param larg2: larghezza del cilindro interno
     *  @param spess: spessore della piastra
     *  @param lung: lunghezza della piastra
     * 
     */
     Livella * livella_init(float posx1, float posx2, float posy, float larg1, float larg2, float alt1, float altS, float altD, float spess, float lung);


  
    /*
     * Funzione che inizializza entrambi i pistoni
     * 
     *  @param posx1: posizione x del cilindro esterno
     *  @param posy: posizione y del cilindri esterni
     *  @param alt1: altezza del cilindro esterno
     *  @param larg1: larghezza del cilindro esterno
     *  @param alt2: altezza del cilindro interno
     *  @param larg2: larghezza del cilindro interno
     * 
     */
    Piston * piston_init (float posx, float posy, float alt1, float larg1, float alt2, float larg2);


    /*
     * Funzione che inizializza la piastra
     * 
     * @param spess: spessore della piastra
     * @param lung: lunghezza della piastra
     * @param posx1: posizione x del cilindro di destra
     * @param posx2: posizione x del cilindro di sinistra
     * @param posy: posizione y dei cilindri
     * @param alt1: altezza dei cilindri estrni
     * @param larg1: larghezza dei cilindri esterni
     * @param altS: estensione del pistone di sinistra
     * @param altD: estensione del pistone di destra
     * @param larg2: larghezza dei cilindri interni
     * 
     */
    Plate * plate_init (float spess, float lung, float posx1, float posx2, float posy, float alt1, float larg1, float altS, float altD, float larg2);

    
    

    /*
     * Funzione che controlla che i parametri inseriti siano valori
     * positivi e non nulli. Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ chepermette di modificare il parametro.
     * 
     */
    int param_control(Livella * mylivella);

    /*
     * Funzione che controlla che i parametri inseriti siano coerenti con
     * il device che si vuole creare.
     * Qualora fosse necessario viene chiamata una delle
     * funzioni _set_ chepermette di modificare il parametro.
     * 
     */
    int device_control(Livella * mylivella);


    /*
     * piston_set_pos: funzione che permette di cambiare la posizione del secondo pistone.
     * piston_set_alt: funzione che permette di cambiare l'altezza dei cilindri esterni.
     * piston_set_larg1: funzione che permette di cambiare la larghezza dei cilindri esterni.
     * piston_set_alt1: funzione che permette di cambiare l'estensione del primo pistone.
     * piston_set_alt2: funzione che permette di cambiare l'estensione del secondo pistone
     * piston_set_larg2: funzione che permette di cambiare la larghezza dei due cilindri interni.
     * plate_set_spessore: funzione che permette di cambiare lo spessore della piastra.
     * plate_set_lunghezza: funzione che permette di cambiare la lunghezza della piastra.
     * 
     */
    void piston_set_pos(Livella * mylivella);
    void piston_set_alt(Livella * mylivella);
    void piston_set_larg1(Livella * mylivella);
    void piston_set_alt1(Livella * mylivella);
    void piston_set_alt2(Livella * mylivella);
    void piston_set_larg2(Livella * mylivella);
    void plate_set_spessore(Livella * mylivella);
    void plate_set_lunghezza(Livella * mylivella);

    


    /*
     * Funzione che stampa i parametri dei due pistoni e della piastra
     * 
     */
    void info_parti ( Livella * mylivella );


    /*
     * Dato il nome del file dall'utente, la funzione realizza il file .svg
     * 
     */
    void livella_to_svg (Livella * mylivella, std::string fileName, char measures);


    /*
     * Funzione che restituisce la stringa di codice svg per la realizzazione del file
     * 
     */
    std::string livella_to_ParamSVG ( Livella * mylivella);


    /*
     * Funzione che permette di implementare le misure all'interno del file svg
     * 
     */
    std::string livella_to_MeasureSVG ( Livella * mylivella);


    /*
     * Funzione cancellazione struct e istanze
     * 
     */
    void livella_destroy(Livella * mylivella);


    

#endif