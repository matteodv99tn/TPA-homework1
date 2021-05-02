# Documentazione per la libreria della Livella Mobile - v1.4.0

## Struttura dati
Tutte le informazioni della livella mobile sono contenute nella struttura dati `LivellaMobile`; in particolare sono salvate:
- un vettore `supporto` di dimensione binaria di tipo puntatore alla struttura `GuidaPrismatica`; questa variabile permette di immagazzinare le informazioni sui supporti della livella mobile che si vuole realizzare;
- una variabile `livella` (di tipo `struct Livella`) che contiene tutte le informazioni riguardanti la livella che dovrà scorrere sulle guide prismatica;
- le coordinate `pos_x` e `pos_y` rappresentanti il punto medio tra le cerniere interne delle due guide prismatiche;
- la `distanza` a cui sono posti i due cilindri della livella e la percentuale di corsa `perc_corsa` a cui sono poste le guide rispetto all'incastro a sinistra delle due guide prismatiche.

Per poter modificare più agilmente le proprietà della livella è stata creata una struttura dati `dati_livella` aggiuntiva, presente all'interno di `LivellaMobile`, contenente le informazioni salienti della livella presenti nella libreria di origine, in particolare
- `posx1` e `posx2` sono le coordinate orizzontali dell'estremo sinistro dei rettangoli rappresentante le basi dei cilindri rispettivamente sinistro e destro;
- `posy` è la coordinata dell'estremo superiore del rettangolo rappresentante la base dei cilindi;
- la larghezza della camera del cilindro `largbase` e della testa del cilindo `largtesta`;
- l'altezza della camera del cilindro `alt_cilindro` e l'elongazione del pistone a sinistro `alt_sx` e destro `alt_dx`;
- lo `spessore` e la `lunghezza` della piattaforma della livella congiungente i due pistoni.

## Funzioni implementate
### `livellaMobile_init`
Questa funzione permette di inizializzare un puntatore ad una livella mobile realizzata tramite i parametri:
- `posx` e `posy`, le due coordinate della livella mobile (descritte nelle sezione della struttura dati);
- la distanza orizzontale `dist` tra le camere dei cilindri e la percentuale di corsa utile `perc` delle guide prismatiche;
- l'altezza `alt_cil` della camera dei pistoni e le elongazioni `alt_sx` e `alt_dx` dei pistoni sinistro e destro rispettivamente

Di default le guide prismatiche vengono realizzate per avere incastri e guida scorrevole di dimensione 40x40, e la distanza tra gli incastri interni è fissata al valore di 20 unità.

La larghezza della base dei cilindri è pari a 4/5 della dimensione orizzontale della guida cui i pistoni poggiano, mentre il diametro della testa è 2/3 del diametro della camera del cilindro.

### `livellaMobile_destroy`
Funzione che prende in input un puntatore a struttura `LivellaMobile` e la dealloca correttamente, in modo da evitare di tenere occupata memoria inutilmente.

### `livellaMobile_controlla`
Questa funzione prende un puntatore ad una struttura `LivellaMobile` e verifica l'integrità della struttura dati, effettuando delle correzioni sui parametri laddove possibile.

Essa esegue un controllo di integrità sulle guide prismatiche di supporto tramite la funzione `guida_controlla_integrita`, mentre per quanto riguarda la livella vengono fatti i controlli sulle informazioni contenute in `dati_livella`; in particolare si individuano e corregono le seguenti situazioni:
- quando la base del cilindro supera le dimensioni delle guide cui si appoggiano; se la dimensione è negativa essa è posta a 4/5 della guida cui si poggiano;
- quando la testa del cilindro ha dimensione maggiore della rispettiva base (o ha valore negativo); in questo caso la dimensione è posta a 2/3 il diametro della camera del cilindro;
- quando l'elongazione dei cilindri è negativa, essa viene posta uguale a 10, mentre se è superiore all'altezza della camera meno 10 unità, viene ridotta al valore di elongazione massima.

### `livellaMobile_to_svg`
Funzione che permette di renderizzare una livella mobile tramite un file svg; parametri di ingresso della funzione sono:

- un puntatore ad una struttura `LivellaMobile` che si vuole renderizzare;
- una stringa `nome_file` contenente il nome, senza estensione, del file rispetto al quale si vuole effettuare il salvataggio.

### `livellaMobile_da_console()`
Funzione che permette di creare un menù interattivo da interfaccia console per creare un puntatore a struttura `LivellaMobile`; le regole di inizializzazione seguono quelle descritte nella funzione `livellaMobile_init`.

### `livellaMobile_salva_file`
Funzione che permette di salvare su un file di testo le proprietà fondamentali della livella mobile che, tramite un'opportuna funzione, potranno poi essere caricati per ricostruire la livella. Parametri della funzione sono
- `livella`: puntatore alla struttura di tipo `LivellaMobile` che si vuole salvare;
- `nome_file`: stringa contenente il nome del file, senza estensione, nel quale si vogliono salvare le informazioni.

### `livellaMobile_da_file` 
Funzione che permette di generare una livella mobile leggendo le informazioni della stessa da file; in particolare il parametro della funzione è una stringa `nome_file` che contiene il nome del file di testo, senza estensione, dal quale reperire le informazioni. La funzione restituisce un puntatore alla struttura `LivellaMobile` caricata.

### `livellaMobile_verifica_uguaglianza`
Funzione che permette di controllare su due puntatori a `LivellaMobile` contengono le stesse informazioni, rappresentando dunque la stessa livella mobile; come parametri in ingresso è necessario specificare le due livelle mobili `l1` ed `l2` che si vogliono confrontare.

La funzione restituisce un valore booleano vero se verifica che le due strutture presentano le stesse informazioni, un valore falso altrimenti.