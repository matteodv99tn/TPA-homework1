#include "catch2.hpp"
#include "../libreries/livellaMobile.h"

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