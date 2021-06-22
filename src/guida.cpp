
#include <string>
#include <sstream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using std::endl;

// DEFAULT VALUES
#define DEF_RECT_COLOR 150
#define DEF_STROKE_WIDTH 2

Rectangle::Rectangle(float x, float y, float w, float h){

    this->x_rel = x;
    this->y_rel = y;
    
    this->set_dimensions(w, h);

    this->colors[0] = DEF_RECT_COLOR;
    this->colors[1] = DEF_RECT_COLOR;
    this->colors[2] = DEF_RECT_COLOR;

}

Rectangle::Rectangle(float x, float y, float w, float h, int * col){

    this->x_rel = x;
    this->y_rel = y;
    this->width = w;
    this->height = h;

    this->colors[0] = col[0];
    this->colors[1] = col[1];
    this->colors[2] = col[2];

}

Rectangle::~Rectangle(){
    
    LOG("deconstructor called");

}

void Rectangle::set_relative_position(const float x, const float y){

    this->x_rel = x;
    this->y_rel = y;
}

void Rectangle::set_dimensions(const float w, const float h){

    if( w <= 0 ) throw std::out_of_range("Cannot set negative width value for a rectangle!"); 
    if( h <= 0 ) throw std::out_of_range("Cannot set negative height value for a rectangle!"); 

    this->width = w;
    this->height = h;
    
}

string Rectangle::svg_code(string transform_string) const{

    std::stringstream out;

    out << "<rect x=\"" << this->x_rel << "\" ";
    out << "y=\"" << this->y_rel <<"\" ";

    out << "width=\"" << this->width <<"\" ";
    out << "height=\"" << this->height <<"\" ";

    out << "style=\"fill:rgb(" << this->colors[0] << ",";
    out << this->colors[1] << ",";
    out << this->colors[2] << "); stroke-width:" << DEF_STROKE_WIDTH << ";";
    out << "stroke:rgb(0,0,0)\" ";

    out << transform_string;
    out << " />";

    return out.str();
}
