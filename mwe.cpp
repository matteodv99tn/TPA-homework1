#include <iostream>
#include "libreries/guida.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;

    cout << endl << "Creo una guida posta al centro del piano da disegno, ossia le coordiante (x,y) = (400,300). " << endl;
    cout << "Il sistema ha una lunghezza di 500 unita' dal centro di una cerniera al centro dell'altra." << endl;
    cout << "La guida è posta, compatibilemente con la geometria del problema, ad una distanza di 100 unita' dalla cerniera a sinsitra." << endl;
    cout << "Le dimensioni sia delle cerniere che della guida è pari a 50x50 unita'" << endl;

    myguida = guida_init(400, 300, 500, 100, 50,50);

    cout << endl << "E' possibile osservare infatti che i dati inseriti sono correttamente ottenuti nella struttura dati:" << endl;
    guida_visualizza_info( myguida );

    cout << endl << "Salvo nel file \"mwe_result1.SVG\" la rappresentazione grafica della guida prismatica." << endl;
    guida_to_SVG ( myguida, "../output/mwe_result1"); 
    cout << endl << "Nel file \"mwe_result1b.SVG\" eseguo la rappresentazione della stessa guida con le dimensioni indicate." << endl;
    guida_to_SVG ( myguida, "../output/mwe_result1b", true); 

    cout << endl << "Modifico le dimensioni della cerniera a valore 40x70 con coordinate RGB (0,200,0), ossia colore verde." << endl;
    guida_set_cerniera( myguida, 40, 70, 0, 200, 0);

    cout << "Incremento lo spessore della guida prismatica al valore di 35" << endl;
    guida_set_spessore( myguida , 35 );

    cout << "Modifico la corsa ad un valore molto alto pari a 800; questo valore sarebbe incompatibile con la lunghezza dell'intero corpo, ma il programma se ne accorge e modifica di conseguenza la lunghezza." << endl; 
    guida_set_corsa( myguida, 800);

    cout << endl << "Le proprietà della guida attuali sono dunque:" << endl;
    guida_visualizza_info( myguida );
    
    cout << endl << "Salvo la versione modificata nel file \"mwe_result2.svg\"." << endl;
    guida_to_SVG ( myguida, "../output/mwe_result2");

    cout << endl << "Terminato il programma è necessario distruggere correttamente la struttura istanziata tramite l'apposita funzione." << endl << endl;
    guida_distruggi( myguida );
}
