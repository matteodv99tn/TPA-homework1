
#include "guida.h"
#include "catch2.hpp"

#define CATCH_CONFIG_MAIN

using matteodv99tn::Rectangle;

TEST_CASE("Correct Rectangle first constructor", "[Rectangle][constructor]"){

    Rectangle r(-10,10, 20, 30);

    REQUIRE(r.get_x() == -10);
    REQUIRE(r.get_y() == -10);
    REQUIRE(r.get_width() == 20);
    REQUIRE(r.get_height() == 30);
    
}

TEST_CASE("Incorrect Rectangle first constructorm should throw exception", "[Rectangle][constructor]"){

    CHECK_THROWS_AS( Rectangle(-10,10, 20, 30), std::out_of_range );
    
}

TEST_CASE("Correct Rectangle second constructor", "[Rectangle][constructor]"){

    Rectangle r(-10,10, 20, 30);

    REQUIRE(r.get_x() == -10);
    REQUIRE(r.get_y() == -10);
    REQUIRE(r.get_width() == 20);
    REQUIRE(r.get_height() == 30);
    
}
