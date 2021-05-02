# Documentazione per la libreria GuidaPrismatica - v1.5.0

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
Funzione che permette di salvare le informazioni di un oggetto `GuidaPrismatica` su un file di testo; come parametri in ingresso è necessario specificare:
- un puntatore alla struttura `GuidaPrismatica` da voler salvare su file
- una stringa contenente il nome del file sul quale salvare le informazioni (senza estensione .txt che verrà automaticamente introdotta dal programma)

### `guida_carica_file`
Funzione che resistituisce un puntatore ad una struttura `GuidaPrismatica` caricata da un file di testo correttamente redatto. Come parametri in ingresso alla funzione è necessario specificare:

- una stringa contenente il nome (senza estensione) del file del quale caricare le informazioni

### `guida_distruggi`
Funzione che permette di _distuggere_ correttamente un puntatore ad una struct `GuidaPrismatica`; non restituisce alcun output.

## Conversione in file SVG
### `guida_to_SVGstring`
Funzione che permette di ottenere il codice in formato _SVG_ di una guida prismatica che può essere integrato in generico file; l'unico parametro in ingresso alla funzione è
- un puntatore alla struttura `GuidaPrismatica` che si vuole integrare nel proprio file
- opzionalmente è possibile introdurre un valore booleano affermativo (che di default è negativo) che permette di renderizzare sulla figura le dimensioni degli elementi strutturali

Il programma restituisce dunque una stringa contenente il codice correlato alla struttura.

### `guida_to_SVG`
Funzione che permette di creare un file in estensione .svg contenente la rappresentazione di una guida prismatica; i parametri in ingresso da fornire sono:
- un puntatore alla struttura `GuidaPrismatica` che si vuole renderizzare;
- una stringa contenente il nome del file (senza estensione) nel quale si vuole salvare il rendering

## Modifica e controllo sulla struttura dati
### `guida_controlla_integrita`
Questa funzione è utilizzata per controllare che la guida prismatica che si vuole renderizzare sia consistente, ossia che non vada incontro a problemi di rendering per via di dimensioni potenzialmente incompatibili.
La funzione restituisce dei codici di errore specifici per problemi legati a parametri della struttura scorretti e che non possono essere risolti automaticamente, mentre altre informazioni che portano a incongruenze geometriche sono automaticamente corrette dalla funzione.

Come ingresso richiede
- un puntatore ad una struttura `GuidaPrismatica` che si vuole controllare ed eventualmente correggere

I codici di uscita associati alla funzione sono:
- `0` se la guida prismatica era corretta e non è stata modificata;
- `-1` se la guida prismatica non presentava criticità nei parametri che non possono essere corretti, tuttavia alcuni membri sono stati modificati
- `1` se la lunghezza della guida prismatica presentava valore negativo o nullo
- `2` se le dimensioni associate alle cerniere della struttura sono negative o nulle
- `3` se le dimensioni associate al rettangolo della guida prismatica sono negative o nulle

Le correzioni automaticamente apportate dalla funzione sono:
- se le dimensioni orizzontali di guida e cerniere portano ad una sovrapposizione dei componenti rispetto alla lunghezza della guida prismatica, allora esse vengono riscalate in modo da avere cerniere e guida con stessa dimensione orizzontale in modo da poter giacere affiancate correttamente una lungo l'altra
- se lo spessore del cilindro di scorrimento è superiore all'altezza minima dei rettangoli associati alla guida o alle cerniere, allora esso viene riscalato a tale valore minimo; se lo spessore era negativo viene posto automaticamente ad un valore pari ad 1/3 dello spessore minimo
- se la corsa impostata porta ad una collisione tra cerniere e guida (o la corsa è superiore alla lunghezza del sistema), allora essa viene riportata al valore minimo tollerato dal disegno per non avere compenetrazioni.

### `guida_modifica`
Funzione che permette di modificare le proprietà di una guida prismatica tramite un menu interattivo da linea di comando; il parametro in ingresso da fornire alla funzione è
- un puntatore ad una struttura `GuidaPrismatica` della quale si vuole modificare le proprietà

Dal menù interattivo è possibile

1. modificare la lunghezza e la corsa del sistema
2. modificare le dimensioni (e opzionalmente il colore) delle cerniere dalla guida prismatica
3. modificare le dimensioni (e opzionalmente il colore) della guida della struttura

### Funzioni `guida_set`
Esistono una serie di funzioni del tipo `guida_set`__attributo_ che permettono di modificare le proprietà dell'attributo specificato effettuando contestualmente dei controlli durante l'operazione.

Ogni funzione implementata richiede come primo parametro un puntatore ad una struttura `GuidaPrismatica` della quale si vuole modificare; gli altri parametri della funzione da inserire sono descritti nelle varie funzioni implementate come segue:

- `guida_set_lunghezza` modifica la lunghezza del sistema tramite un nuovo valore decimale; se la lunghezza inserita è negativa o nulla allora il valore non viene alterato
- `guida_set_spessore` modifica lo spessore del cilindro di scorrimento per la guida; ad ogni esecuzione di questo comando segue un controllo dell'integrità strutturale tramite apposita funzione
- `guida_set_corsa` modifica la corsa della guida lungo il cilindo; ad ogni esecuzione di questo comando segue un controllo dell'integrità strutturale tramite apposita funzione
- `guida_set_angolo` permette di impostare l'angolo di inclinazione alpha della struttura rispetto all'orizzontale; l'angolo deve essere espresso in gradi
- `guida_set_cerniera` e `guida_set_guida` permettono di modificare gli attributi associati ai rettangoli rispettivamente della cerniera o della guida che scorre sul cilindro; come parametri in ingresso è necessario introdurre le nuove dimensioni orizzontali e verticali e opzionalmente le coordinate RGB (tra 0 e 255) dei tre canali rosso, verde e blu 

### Funzione `guida_parse_svg`
Questa funzione permette di effettuare il _parsing_ di un codice SVG di una guida prismatica; in particolare la funzione presenta come parametri in ingresso:
- una stringa `file_name` contenente il nome, senza estensione, del file svg del quale si vuole effettuare il parsing;
- un booleano `with_header` che permette di specificare se il file che si vuole scansionare presenta (o meno) l'header svg;
- opzionalmente è possibile inserire un valore intero `pos` associato al numero della riga alla quale dovrebbe partire il codice di una guida prismatica all'interno di un svg qualsiasi. Se specificato tale valore, esso sovrascrive l'opzione booleana `with_header`.

La funzione restituisce un puntatore alla guida prismatica del quale è stato effettuato il parse.

### Funzione `guida_verifica_uguaglianza`
Funzione che permette di stabilire sue due punatori a strutture `GuidaPrismatica` sono coincidenti e dunque rappresentano la stessa entità; i parametri in ingresso sono
- due puntatori `g1` e `g2` ad una struttura di tipo `GuidaPrismatica` delle quale si vuole effettuare il confronto;
- opzionalmente è possibile includere un valore booleano `controlla_colore` che permette di specificare se, nel controllo, confrontare anche i colori di guida e incastri; di default il valore è negativo, e dunque nessun controllo sul colore viene effettuato.

Il risultato della funzione è un valore booleano falso se le due strutture sono diverse, mentre il risultato è vero se le due strutture risultano essere uguali.