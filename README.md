# Tecniche di Programmazione Avanzata - Homework1
## Device: guida prismatica

Lo scopo del progetto è quello di creare una guida prismatica che può scorrere su una rotaia fissata ai suoi estremi da due cerniere.

L'idea è di rendere facile la codifica con un'inizializzazione che prevede un numero minimo di parametri, tuttavia la libreria permette una modifica più avanzata sia tramite funzioni apposite, sia tramite menù interattivi da linea di comando.

Un esempio di prima guida prismatica ottenuta da un'inizializzazione semplice può essere osservata come segue (il rendering è ottenuto e commentato nel [_minimal working example_](mwe.cpp))
![](output/mwe_result1b.svg)

### Feature della libreria

La libreria è pensata per facilitare l'implementazione della guida prismatica nei rendering cercando di aggiustare automaticamente parametri in ingresso potenzialmente scorretti sia dal punto di vista logico (dimensioni negative), sia dal punto di vista geometrico (per esempio la guida non potrà mai sovrapporsi alle cerniere, e dunque valori del parametro di corsa che porterebbero a queste situazioni verrebbe opportunamente corretto).

E' possibile trovare una descrizione di tutte le funzioni accessibili e il loro funzionamento (con parametri in ingresso e valori in uscita) nella [**documentazione**](libreries/README_guida_prismatica.md) rilasciata.

### _Minimal Working Example_
Ai fini di capire velocemente il funzionamento della libreria e apprendere ad eseguire le operazioni base in maniera corretta è fornito un [_minimal working example_](mwe.cpp) (in segui mwe).

Nel documento viene mostrato come realizzare la guida prismatica mostrata in testa al documento e come, tramite la modifica delle proprietà  dello stesso cilindro, ottenere il seguente risultato:

![](output/mwe_result2.svg)

## Machine: livella a pistone mobile
La machine implementata è una livella scorrevole, realizzata da @davidechiaghi, posta su due supporti costituiti dalla guida prismatica da me realizzata. 

![](output/mwe_machine1.svg)

### Feauture della libreria
La libreria è principalmente pensata per essere istanziata da linea di comando; sfruttando tutte le funzioni implementate per la guida prismatica e la livella è possibile effettuare delle modifiche particolari alla livella mobile costruita.

La libreria si occupa di effettuare dei controlli generici sulla compatibilità geometrica dei vari elementi, integrando nel modo migliore possibile le due librerie di partenza.