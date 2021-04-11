# Descrizione della libreria

L'idea di funzionamento della libreria per la rappresentazione grafica di una coppia prismatica è quella di rendere il più pratico possibile l'inserzione del disegno in qualsiasi programma; l'inizializzazione infatti prevede l'input di pochi elementi che potranno essere modificati in un secondo momento per avere un disegno più flessibile ma poco complicato da apprendere.

Le funzioni implementate permetteranno di correggere automaticamente ingressi in input non attendibili rispetto alla realizzazione grafica del dispositivo.

# Funzioni implementate e documentazione
### `guida_init`
Funzione che permette di inizializzare la struttura per il rendering della guida prismatica; come output restituisce un puntatore all'oggetto creato del tipo `guida prismatica`. I parametri della funzione sono:
- `lunghezza` : lunghezza complessiva della sbarra rispetto alla quale la guida prismatica si può muovere
- `corsa` : posizione della guida rispetto all'origine (sinistra) dell'asta di supporto
- `dimx` : dimensione orizzontale delle cerniere a telaio e del glifo del meccanismo
- `dimy` : dimensione verticale delle cerniere a telaio e del glifo del meccanismo

### `guida_distruggi`
Funzione che permette di _distuggere_ correttamente un puntatore ad una struct `guida prismatica`; non restituisce alcun output.
