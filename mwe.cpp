#include <iostream>
#include "libreries/guida.h"
#include "libreries/livellaMobile.h"

using namespace std;

int main() {

    GuidaPrismatica * myguida;
    cout << "+-+-+ Device: guida prismatica +-+-+" << endl;
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

    cout << endl << "Quando si finisce di lavorare con la guida prismatica è necessario eliminarla utilizzando l'apposita funzione \"distruggi\"." << endl << endl;
    guida_distruggi( myguida );


    
    cout << "+-+-+ Machine: livella mobile +-+-+" << endl;
    
    LivellaMobile * mylivella = livellaMobile_init(400, 500, 300, 25, 200, 30, 100);
    cout << "Inizializzo una livella mobile il cui centro dei supporti è posto nel punto (400,500);" << endl;
    cout << "la distanza tra i centri delle guide prismatiche (e dei pistoni) è pari a 300;" << endl;
    cout << "le guide prismatiche sono poste al 25% della loro corsa utile;" << endl;
    cout << "l'altezza del corpo dei cilindri è pari a 200, il cilindro a sinistra si estende di 30 mentre quello di destra di 100." << endl << endl;

    cout << "Salvo la versione modificata nel file \"mwe_machine1.svg\"" << endl << endl;
    livellaMobile_to_svg( mylivella , "../output/mwe_machine1");

    cout << "E' necessario ora distruggere opportunamente l'istanza tramite l'opportuna funzione." << endl;
    livellaMobile_destroy( mylivella );

}
