
#include <iostream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using matteodv99tn::PrismaticJoint;
using std::cout;
using std::endl;

int main(){
    
    PrismaticJoint prism(400,300,500,10);

    LOG("DRAWING");
    prism.to_svg("example");

    return EXIT_SUCCESS;

}