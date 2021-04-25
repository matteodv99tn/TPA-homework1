# Tecniche di Programmazione Avanzata - Homework1: realizzazione di una guida prismatica

Lo scopo del progetto è quello di creare una guida prismatica che può scorrere su una rotaia fissata ai suoi estremi da due cerniere.

L'idea è di rendere facile la codifica con un'inizializzazione che prevede un numero minimo di parametri, tuttavia la libreria permette una modifica più avanzata sia tramite funzioni apposite, sia tramite menù interattivi da linea di comando.

Un esempio di prima guida prismatica ottenuta da un'inizializzazione semplice può essere osservata come segue (il rendering è ottenuto e commentato nel [_minimal working example_](mwe.cpp))
![](mwe_result1.svg)

## Feature della libreria

La libreria è pensata per facilitare l'implementazione della guida prismatica nei rendering cercando di aggiustare automaticamente parametri in ingresso potenzialmente scorretti sia dal punto di vista logico (dimensioni negative), sia dal punto di vista geometrico (per esempio la guida non potrà mai sovrapporsi alle cerniere, e dunque valori del parametro di corsa che porterebbero a queste situazioni verrebbe opportunamente corretto).

## Roadmap del progetto

v0.0.0 prime sperimentazioni e studio delle strutture \[in corso\]


v1.0.0 struttura definita; implementazione delle funzioni di inizializzazione del software \
v1.1.0 integrazione di un sistema di verifica degli input \
v1.2.0 integrazione di una prima modalità di rendering del dispositivo \
v1.3.0 implementazione delle funzioni di salvataggio e caricamento

La roadmap deve essere intesa come un cronoprogramma da seguire per la fase di sviluppo e il versionamento del programma, ma può subire variazioni; per dettagli più specifici osservare le note di rilascio.


## Note di rilascio
### V1.0.0
- Creata la struttura `GuidaPrismatica` che contiene i dati per il rendering della figura
- Aggiunta la funzione `guida_init` per l'inizializzazione dell'oggetto contenente le informazioni per il rendering
- Aggiunta la funzione `guida_distruggi` per la rimozione dell'oggetto istanziato
