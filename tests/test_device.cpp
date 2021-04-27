
#define CATCH_CONFIG_MAIN

#include "catch2.hpp"
#include "../libreries/guida.h"

TEST_CASE("Inizializzazione corretta di un puntatore a guida prismatica", "[GuidaPrismatica:inizializzazione]"){

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

TEST_CASE("Un'inizializzazione sbagliata di una guida prismatica dovrebbe comportare un puntatore nullo", "[GuidaPrismatica:inizializzazione]"){

    GuidaPrismatica * guida = guida_init (100, 100, 200, -10, -10, -10);

    REQUIRE( guida == NULL );

    guida_distruggi( guida );

}