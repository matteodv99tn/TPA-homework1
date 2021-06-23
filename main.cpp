
#include <iostream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using matteodv99tn::PrismaticJoint;
using std::cout;
using std::endl;

int main(){

    START_LOGGING_SESSION

    // Creating a prismatic guid with center in coordinates (400, 300)
    // and length = 500; the stroke is 10% of the aviable space
    PrismaticJoint prism(400,300,500,10);

    // Changing the dimension and color of the moving prismatic guide to 100x70
    prism.set_prism_dimension(100, 70);
    int colors[3] = {70, 70, 70};
    prism.set_prism_color(colors);

    // Displaying the property of the current object:
    cout << "On \"example.svg\" and \"example-measures.svg\": " << endl << prism;

    // Saving the prism to a svg file without measurements
    prism.to_svg(std::string("../output/example")); // equivalent to
                                                    // prism.to_svg(std::string("../output/example"). false);

    // Saving the prism to a svg file with measurements
    prism.to_svg(std::string("../output/example-measures.svg"), true); 


    // Creating a new prismatic joint by parsing example.svg
    PrismaticJoint parsed("../output/example");

    cout << endl << "Datas from the imported svg:" << endl;
    cout << parsed;

    return EXIT_SUCCESS;

}