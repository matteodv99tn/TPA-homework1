
#include <iostream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using matteodv99tn::PrismaticJoint;
using std::cout;
using std::endl;

int main(){
    
    PrismaticJoint prism(400,300,500,10);

    prism.to_svg("example");
    
    PrismaticJoint fromsvg("example");

    fromsvg.to_svg("example-derived");

    return EXIT_SUCCESS;

}