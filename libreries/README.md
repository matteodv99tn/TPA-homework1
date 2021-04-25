# Documentazione

Verranno qui riportate tutte le funzioni implementate nella libreria e fruibili dall'utente con una descrizione sia dei parametri in ingresso che dei valori restituiti.

## Struttura dati

La struttura dati denominata `GuidaPrismatica` contiene le informazioni riguardanti:
- la `lunghezza` della guida prismatica; essa rappresenta la distanza tra i due centri delle cerniere che compongono il sistema;
- la `corsa` della guida, ossia la distanza rispetto alla cerniera a sinista del centro della guida prismatica che di fatto può scorrere sul cilindro di scorrimento;
- la posizione orizzontale `pos_x` e verticale `pos_y` dell centro della guida prismatica rispetto al piando di rappresentazione vettoriale;
- lo `spessore` del cilindro di scorrimento collegante le due cerniere sul quale scorre la guida;
- l'inclinazione `alpha` della guida rispetto all'orizzontale.

Le informazioni sulle cerniere (nella struttura denominate `incastri`) e sulla `guida` del sistema sono contenute in un'altra strtutura dati che contiene:
- le dimensioni orizzontale `dim_x` e verticale `dim_y` del rettangolo associato;
- un vettore di 3 dimensioni `colore` che contiene le informazioni sulla terna di valori RGB che caratterizzano la colorazione delle cerniere o della guida.

## Inizializzazione, salvataggio, caricamento e distruzione
### `guida_init`
Funzione che permette di inizializzare una struttura dati di tipo `GuidaPrismatica` ritornando un puntatore alla stessa; come parametri in ingresso è necessario inserire i parametri:
- `lunghezza` : lunghezza del sistema da generare
- `corsa` : posizione della guida rispetto alla cerniera a sinsitra
- `dimx` : dimensione orizzontale delle cerniere e del telaio del sistema
- `dimy` : dimensione verticale delle cerniere e del telaio del sistema

Lo spessore del cilindro scorrimento è posto ad 1/3 del valore `dimy`; l'inclinazione `alpha` della guida è nulla e il colore sia per la guida che per le cerniere è associata alla terna (130,130,130).

### `guida_crea`
Funzione che restituisce un puntatore ad una struttura `GuidaPrismatica` che viene generata tramite un'interazione via linea di comando con l'utente

### `guida_salva_file`
Funzione che permette di salvare le informazioni 

### `guida_distruggi`
Funzione che permette di _distuggere_ correttamente un puntatore ad una struct `GuidaPrismatica`; non restituisce alcun output.
