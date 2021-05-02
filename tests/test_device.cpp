
#define CATCH_CONFIG_MAIN

#include "catch2.hpp"
#include "../libreries/guida.h"

TEST_CASE("Inizializzazione corretta di un puntatore a guida prismatica", "[GuidaPrismatica][inizializzazione]"){

    GuidaPrismatica * guida = guida_init (100, 100, 200, 100, 50, 60);

    REQUIRE( guida != NULL );
    REQUIRE( guida->alpha == 0);
    REQUIRE( guida->corsa == 100);
    REQUIRE( guida->lunghezza == 200);
    REQUIRE( guida->incastri->dim_x == 50);
    REQUIRE( guida->incastri->dim_y == 60);
    REQUIRE( guida->guida->dim_x == 50);
    REQUIRE( guida->guida->dim_y == 60);
    REQUIRE( guida->spessore == 20);

    guida_distruggi( guida );
}

TEST_CASE("Un'inizializzazione sbagliata di una guida prismatica dovrebbe comportare un puntatore nullo", "[GuidaPrismatica][inizializzazione]"){

    GuidaPrismatica * guida = guida_init (100, 100, 200, -10, -10, -10);

    REQUIRE( guida == NULL );

    guida_distruggi( guida );

}

TEST_CASE("Controllo sulla correzione in guida_set_corsa", "[GuidaPrismatica][controllo]"){

    GuidaPrismatica * guida = guida_init (100, 100, 500, 250, 100, 100);

    REQUIRE( guida->corsa == 250 );

    REQUIRE( guida_set_corsa( guida, 0) == 1 );
    REQUIRE( guida->corsa == 100);

    REQUIRE( guida_set_corsa( guida, 1000) == 1 );
    REQUIRE( guida->corsa == 400);

    guida_distruggi( guida );

}

TEST_CASE("Controllo sulle funzioni di controllo", "[GuidaPrismatica][controllo]"){

    GuidaPrismatica * guida = guida_init (100, 100, 500, 250, 100, 100);

    guida->incastri->dim_x = -10;
    REQUIRE( guida_controlla_integrita( guida ) != 0 );

    guida->incastri->dim_y = -10;
    REQUIRE( guida_controlla_integrita( guida ) != 0 );

    guida->guida->dim_x = -10;
    REQUIRE( guida_controlla_integrita( guida ) != 0 );

    guida->guida->dim_y = -10;
    REQUIRE( guida_controlla_integrita( guida ) != 0 );

    guida->spessore = -10;
    REQUIRE( guida_controlla_integrita( guida ) != 0 );

    guida_distruggi( guida );
    
    }

TEST_CASE("La funzione di verifica di uguaglianza deve essere consistente", "[GuidaPrismatica][uguaglianza]"){

    GuidaPrismatica * g1 = guida_init (100, 100, 500, 250, 100, 100);
    GuidaPrismatica * g2 = guida_init (100, 100, 500, 250, 100, 100);
    GuidaPrismatica * g3 = guida_init (100, 100, 500, 250, 100, 60);

    g2->incastri->colore[0] = 255;

    REQUIRE( guida_verifica_uguaglianza(g1, g2) == true );
    REQUIRE( guida_verifica_uguaglianza(g1, g3) == false );
    REQUIRE( guida_verifica_uguaglianza(g1, g2, true) == false );

    guida_distruggi( g1 );
    guida_distruggi( g2 );
    guida_distruggi( g3 );
    
}

TEST_CASE("Controllo che l'operazione di salvataggio/caricamento non perda informazioni", "[GuidaPrismatica][salvataggio/caricamento]"){

    GuidaPrismatica * guida = guida_init (100, 100, 500, 250, 90, 90);

    guida_salva_file( guida, "test_guida");
    
    GuidaPrismatica * copia = guida_carica_file("test_guida");

    REQUIRE( guida_verifica_uguaglianza(guida, copia) == true );

    guida_distruggi( guida );
    guida_distruggi( copia );

}
