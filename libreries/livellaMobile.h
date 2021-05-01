#ifndef _LIVELLA_MOBILE_H_

#define _LIVELLA_MOBILE_H_

    #include "guida.h"
    #include "external/Livella.h"
    #include "external/sistemaAstePerno.h"

    /*
     * Struttura ausiliaria contenente le informazioni della livella
     * 
     * Per comodità di scrittura mi salvo le informazioni necessarie all'inizializzazione
     * e all'occorrenza cancello e reinizializzo la livella utilizzando questi dati salvati
     * 
     */
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

    /*
     * Struttura contenente le informazioni della livella mobile
     * 
     * La struttura contiene:
     *  - Un vettore di 2 guide prismatiche usate come supporto di scorrimento per la livella
     *  - Una livella (device di @DavideCiaghi)
     * 
     *  - Una struttura contenente i dati della livella
     *  - Le posizioni della livella (riferite al punto medio delle guide prismatiche di supporto)
     *  - La distanza tra i due cilindri della livella (e dunque dei centri delle guide prismatiche) 
     *  - La percentuale di corsa alla quale sono ognuna delle guide prismatiche
     * 
     */
    struct LivellaMobile{
        
        GuidaPrismatica * supporto[2];
        Livella * livella;

        DatiLivella dati_livella;

        float pos_x;
        float pos_y;
        float distanza;
        float perc_corsa;

    };

    /*
     * Funzione che permette di inizializzare una struttura LivellaMobile
     * 
     * Internamente la funzione esegue anche dei controlli di correttezza dei dati inseriti, correggendo opportunamente;
     * ingressi negativi vengono automaticamente posti a valori di default
     * 
     * @param posx: ascissa del centro del punto medio dei due supporti della livella mobile
     * @param posy: ordinata del centro del punto medio dei due supporti della livella mobile
     * @param dist: distanza tra i centri dei due cilindri della livella (e dunque delle guide prismatiche)
     * @param perc: percentuale di corsa utile delle guide prismatiche
     * @param alt_cil: altezza fissa delle camere dei cilindri della livella
     * @param alt_sx: altezza del cilindro a sinistra della livella
     * @param alt_dx: altezza del cilindro a destra della livella
     * 
     * @return un puntatore alla struttura LivellaMobile appena creata
     * 
     */
    LivellaMobile * livellaMobile_init(float posx, float posy, float dist, float perc, float alt_cil, float alt_sx, float alt_dx);

    /*
     * Funzione che permette di controllare la correttezza dei dati inseriti nella struttura LivellaMobile;
     * la funzione effettua internamente delle correzioni, impostando a valori default quando non riesce a determinare alcuni parametri
     *  
     * Controlli effettuati:
     *  - la larghezza della base dei pistoni che non debba superare la grandezza della guida cui è vincolato
     *  - la larghezza della testa dei pistoni non debba superare la larghezza della testa dei pistoni
     *  - la corsa dei cilindri deve essere positiva e non superiore all'altezza della camera dei pistoni da cui partono
     * 
     * @param livella: puntatore alla struttura LivellaMobile che si vuole controllare e/o correggere
     * 
     * @return un intero contenente il codice di uscita della funzione di controllo:
     *   0 : nessuna correzione effettuata
     *   1 : effettuate delle correzioni
     * 
     */
    int livellaMobile_controlla( LivellaMobile * livella );

    /* 
     * Funzione che permette di creare un file .svg della livella mobile creata
     * 
     * @param livella: puntatore alla struttura LivellaMobile che si vuole renderizzare;
     * @param nome_file: stringa contenente il nome del file, senza estensione, nel quale si vuole salvare l'immagine
     * 
     */
    void livellaMobile_to_svg(LivellaMobile * livella, string nome_file);

    /*
     * Funzione che, tramite menu interattivo da console, permette di creare una struttura LivellaMobile
     * 
     * @return un puntatore alla livella mobile ottenuta da terminale
     * 
     * La livella mobile restituita è già stata controllate e presenta valori coerenti alla geometria del problema
     * 
     */
    LivellaMobile * livellaMobile_da_console();

    /*
     * Funzione che permette di "distruggere" correttamente tutte le informazioni di una struttura GuidaPrismatica
     * 
     * @param livella: puntatore a struttura LivelalMobile che si vuole distruggere
     * 
     */
    void livellaMobile_destroy(LivellaMobile * livella);

    /*
     * Funzione che permette di salvare le informazioni importanti di una livella mobile su file
     *  
     * @param livella: puntatore alla livella mobile della quale si vogliono salvare le informazioni
     * @param nome_file: stringa del nome, senza estensione, del file di testo nel quale si vogliono salvare le informazioni
     * 
     */
    void livellaMobile_salva_file(LivellaMobile * livella, std::string nome_file );

    /*
     * Funzione che permette di caricare le informazioni di una livella mobile da un file correttamente redatto
     * 
     * @param nome_file: stringa contenente il nome, senza estensione, del file dal quale caricare le informazioni
     * 
     * @return un puntatore alla livella mobile creata; il puntatore è nullo se non riesce a caricare il file;
     */
    LivellaMobile * livellaMobile_da_file(std::string nome_file);

#endif