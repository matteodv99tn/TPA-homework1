
#include <string>
#include <sstream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using matteodv99tn::PrismaticJoint;
using std::endl;

// DEFAULT VALUES
#define DEF_RECT_COLOR 150
#define DEF_STROKE_LINE_WIDTH 2

#define DEF_PRISM_WIDTH 50
#define DEF_PRISM_HEIGHT 40


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

    this->set_colors(col);

}

Rectangle::Rectangle(const Rectangle &other){

    this->x_rel = other.x_rel;
    this->y_rel = other.y_rel;

    this->width = other.width;
    this->height = other.height;

    for(int i = 0; i < 3; i++) this->colors[i] = other.colors[i];

}

Rectangle::Rectangle(Rectangle &other){

    this->x_rel = other.x_rel;
    this->y_rel = other.y_rel;

    this->width = other.width;
    this->height = other.height;

    for(int i = 0; i < 3; i++) this->colors[i] = other.colors[i];

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

void Rectangle::set_colors(const int new_colors[3]){

    for(int i = 0; i < 3; i++) {
        if( new_colors[i] < 0 || new_colors[i] > 255) {
            throw std::out_of_range("RGB codes should be between value 0 and 255 (trying to insert " + std::to_string(new_colors[i]) +")");
        }
    }

    this->colors[0] = new_colors[0];
    this->colors[1] = new_colors[1];
    this->colors[2] = new_colors[2];

}

int* Rectangle::get_colors() const{

    int * tbr = new int[3];
    tbr[0] = this->colors[0];
    tbr[1] = this->colors[1];
    tbr[2] = this->colors[2];

    return tbr;
}

string Rectangle::svg_code(string transform_string) const{

    std::stringstream out;

    out << "<rect x=\"" << this->x_rel - this->width / 2 << "\" ";
    out << "y=\"" << this->y_rel - this->height / 2 <<"\" ";

    out << "width=\"" << this->width <<"\" ";
    out << "height=\"" << this->height <<"\" ";

    out << "style=\"fill:rgb(" << this->colors[0] << ",";
    out << this->colors[1] << ",";
    out << this->colors[2] << "); stroke-width:" << DEF_STROKE_LINE_WIDTH << ";";
    out << "stroke:rgb(0,0,0)\" ";

    out << transform_string;
    out << " />";

    return out.str();
}

void PrismaticJoint::define_positions(){

    this->support[0]->set_relative_position(-this->length / 2, 0);
    this->support[1]->set_relative_position(this->length / 2, 0);

    float maximum_stroke = this->length - this->support[0]->get_width() - this->support[1]->get_width();
    float relative_stroke = - this->length / 2 + this->support[0]->get_width() + maximum_stroke * this->stroke / 100 ;
    this->prism->set_relative_position(relative_stroke, 0);

}

PrismaticJoint::PrismaticJoint(float x, float y, float len, float str) {

    LOG("PrismaticJoint constructor called")

    // TO BE IMPLEMENTED: check on input and relative throws

    this->pos_x = x;
    this->pos_y = y;

    this->prism = new Rectangle( 0, 0, DEF_PRISM_WIDTH < 2 * len ? DEF_PRISM_WIDTH : len / 2, DEF_PRISM_HEIGHT );
    this->support[0] = new Rectangle(*this->prism);
    this->support[1] = new Rectangle(*this->prism);
    this->cylinder = new Rectangle(0, 0, len, DEF_PRISM_HEIGHT / 2);

    this->define_positions();

}

PrismaticJoint::~PrismaticJoint(){

    LOG("PrismaticJoint desctructor called");
    
    delete this->prism;
    delete this->cylinder;
    delete this->support[0];
    delete this->support[1];

}
