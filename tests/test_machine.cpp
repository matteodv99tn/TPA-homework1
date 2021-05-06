#include "catch2.hpp"
#include "../libreries/livellaMobile.h"

#define TOL 0.001

TEST_CASE("Controllo di una corretta inizializzazione della struttura", "[LivellaMobile][inizializzazione]"){

    LivellaMobile * liv = livellaMobile_init(400, 400, 400, 50, 100, 20, 50);

    REQUIRE( liv->supporto[0] != NULL );
    REQUIRE( liv->supporto[1] != NULL );

    REQUIRE( liv->supporto[1]->pos_x - liv->supporto[0]->pos_x  == 400 );

    livellaMobile_destroy( liv  );

}

TEST_CASE("Inizializzazione con percentuali fuoori dall'intervallo 0-100", "[LivellaMobile][inizializzazione]"){

    LivellaMobile * liv = livellaMobile_init(400, 400, 400, -20, 100, 20, 50);
    REQUIRE( liv->perc_corsa == 20 );
    livellaMobile_destroy( liv  );

    liv = livellaMobile_init(400, 400, 400, 120, 100, 20, 50);
    REQUIRE( liv->perc_corsa == 20 );
    livellaMobile_destroy( liv  );

}

TEST_CASE("Modifico le elongazioni dei cilindri in modo incompatibili e controllo che la modifica venga correttamente","[LivellaMobile][controllo]"){

    LivellaMobile * liv = livellaMobile_init(400, 400, 400, 40, 100, 20, 50);

    liv->dati_livella.alt_dx = 150;
    REQUIRE( livellaMobile_controlla(liv) == 1 );
    REQUIRE( liv->dati_livella.alt_dx == 90 );

    liv->dati_livella.alt_dx = -10;
    REQUIRE( livellaMobile_controlla(liv) == 1 );
    REQUIRE( liv->dati_livella.alt_dx == 10 );

    liv->dati_livella.alt_sx = 150;
    REQUIRE( livellaMobile_controlla(liv) == 1 );
    REQUIRE( liv->dati_livella.alt_sx == 90 );

    liv->dati_livella.alt_sx = -10;
    REQUIRE( livellaMobile_controlla(liv) == 1 );
    REQUIRE( liv->dati_livella.alt_sx == 10 );

    livellaMobile_destroy( liv  );

}

TEST_CASE("Controllo il corretto funzionamento della funzione di controllo uguaglianza","[LivellaMobile][uguaglianza]"){

    LivellaMobile * liv1 = livellaMobile_init(400, 400, 400, 40, 100, 20, 50);
    LivellaMobile * liv2 = livellaMobile_init(400, 400, 400, 40, 100, 20, 50);
    LivellaMobile * liv3 = livellaMobile_init(400, 400, 400, 40, 100, 20, 60);

    REQUIRE( livellaMobile_verifica_uguaglianza(liv1, liv2) == true );
    REQUIRE( livellaMobile_verifica_uguaglianza(liv1, liv3) == false );
    REQUIRE( livellaMobile_verifica_uguaglianza(liv2, liv3) == false );

    livellaMobile_destroy( liv1 );
    livellaMobile_destroy( liv2 );
    livellaMobile_destroy( liv3 );

}

TEST_CASE("Salvo e carico da file e controllo che le strutture siano uguali","[LivellaMobile][salva/carica]"){

    LivellaMobile * liv1 = livellaMobile_init(400, 400, 400, 40, 100, 20, 50);    
    livellaMobile_salva_file(liv1, "test_livella");

    // Devo fare il controllo manuale e utilizzare un valore di tolleranza 
    // in quanto i numeri decimali danno problemi nel verificare l'uguaglianza
    LivellaMobile * liv2 = livellaMobile_da_file("test_livella");
    REQUIRE( liv1->distanza == liv2->distanza );
    REQUIRE( liv1->perc_corsa == liv2->perc_corsa );
    REQUIRE( guida_verifica_uguaglianza(liv1->supporto[0], liv2->supporto[0]) == true );
    REQUIRE( guida_verifica_uguaglianza(liv1->supporto[1], liv2->supporto[1]) == true );
    REQUIRE( liv1->pos_x == liv2->pos_x);
    REQUIRE( liv1->pos_y == liv2->pos_y);
    REQUIRE( liv1->dati_livella.alt_cilindro == liv2->dati_livella.alt_cilindro);
    REQUIRE( liv1->dati_livella.alt_sx == liv2->dati_livella.alt_sx);
    REQUIRE( liv1->dati_livella.alt_dx == liv2->dati_livella.alt_dx);
    REQUIRE( liv1->dati_livella.spessore == liv2->dati_livella.spessore);
    REQUIRE( liv1->dati_livella.largbase - liv2->dati_livella.largbase < TOL);
    REQUIRE( liv1->dati_livella.largtesta - liv2->dati_livella.largtesta < TOL);
    REQUIRE( liv1->dati_livella.lunghezza - liv2->dati_livella.lunghezza < TOL);
    REQUIRE( liv1->dati_livella.posx1 == liv2->dati_livella.posx1);
    REQUIRE( liv1->dati_livella.posx2 == liv2->dati_livella.posx2);
    REQUIRE( liv1->dati_livella.posy == liv2->dati_livella.posy);



    // Carico un file inesistente
    LivellaMobile * liv3 = livellaMobile_da_file("test_livella2");
    REQUIRE( liv3 == NULL );

    livellaMobile_destroy( liv1 );
    livellaMobile_destroy( liv2 );
    livellaMobile_destroy( liv3 );


}





























