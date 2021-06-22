
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <ostream>
#include <istream>

#include "guida.h"
#include "log.h"

using matteodv99tn::Rectangle;
using matteodv99tn::PrismaticJoint;
using std::vector;
using std::string;
using std::ostream;
using std::istream;
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

ostream& matteodv99tn::operator<<(ostream &stream, const Rectangle &rect){

    stream << rect.get_width() << " ";
    stream << rect.get_height() << " ";
    stream << rect.colors[0] << " ";
    stream << rect.colors[1] << " ";
    stream << rect.colors[2];

    return stream;

}

istream& matteodv99tn::operator>>(istream &stream, Rectangle &rect){

    stream >> rect.width >> rect.height;
    stream >> rect.colors[0] >> rect.colors[1] >> rect.colors[2];

    return stream;
}

void PrismaticJoint::define_positions(){

    this->support[0]->set_relative_position(-this->length / 2, 0);
    this->support[1]->set_relative_position(this->length / 2, 0);

    float maximum_stroke = this->length - this->support[0]->get_width() - this->support[1]->get_width();
    float relative_stroke = - this->length / 2 + this->support[0]->get_width() + maximum_stroke * this->stroke / 100 ;
    this->prism->set_relative_position(relative_stroke, 0);

}

string PrismaticJoint::svg_header()const {

    std::stringstream out;

    out << "<!-- matteodv99tn::PrismaticJoint code, info: ";

    out << this->length << " ";
    out << this->stroke << " ";
    out << this->pos_x << " ";
    out << this->pos_y << " ";

    out << *(this->cylinder) << " ";
    out << *(this->prism) << " ";
    out << *(this->support[0]) << " ";
    
    out << " -->";

    return out.str();
}

PrismaticJoint::PrismaticJoint(float x, float y, float len, float str) {

    LOG("PrismaticJoint constructor called")

    this->set_length(len);
    this->set_stroke(str);

    this->pos_x = x;
    this->pos_y = y;

    this->prism = new Rectangle( 0, 0, DEF_PRISM_WIDTH < 2 * len ? DEF_PRISM_WIDTH : len / 2, DEF_PRISM_HEIGHT );
    this->support[0] = new Rectangle(*this->prism);
    this->support[1] = new Rectangle(*this->prism);
    this->cylinder = new Rectangle(0, 0, len, DEF_PRISM_HEIGHT / 2);

    int color_to_set[3] {210,210,210};
    this->cylinder->set_colors(color_to_set);

    this->define_positions();

}

PrismaticJoint::PrismaticJoint(const string file_name, const int index){
    
    LOG( "PrismaticJoint parser called" )

    std::ifstream svgfile(file_name + ".svg");

    if( !svgfile.is_open() ) throw std::runtime_error("Couldn't open" + file_name + ".svg thus cannot create a PrismaticJoint object.");

    LOG( "File opened correctly! ");

    vector<string> svg_lines;
    string str;

    while( svgfile.good() ){
        std::getline(svgfile, str);
        svg_lines.push_back(str);
    }

    int joint_found = 0;
    int joint_position;
    for(int i = 0; i < svg_lines.size(); i++){
        
        if( svg_lines[i].find("matteodv99tn") != string::npos ){
            
            joint_position = i;

            if(joint_found == index) i = svg_lines.size();

            joint_found++;
        }
        
    }

    LOG("comparing " << joint_found << " " << index)
    if(joint_found < index+1 ) throw std::out_of_range("In " + file_name + ".svg there are less prismatic joint (" + std::to_string(joint_found) + ") than the required index (" + std::to_string(index) + ") thus cannot create a PrismaticJoint object.");
    
    LOG("Correct prismatic Joint found on row " << joint_position);
 
    LOG( svg_lines[joint_position].erase( 0, svg_lines[joint_position].find("info:")+6 )  );

    std::istringstream in (svg_lines[joint_position]);
    float w, h;

    in >> this->length >> this->stroke >> this->pos_x >> this->pos_y;

    this->cylinder = new Rectangle(0,0, 1,1);
    this->prism = new Rectangle(0,0, 1,1);
    this->support[0] = new Rectangle(0,0, 1,1);

    in >> *(this->cylinder);
    in >> *(this->prism);
    in >> *(this->support[0]);

    this->support[1] = new Rectangle( *(this->support[0]) );

    this->define_positions();
}

PrismaticJoint::~PrismaticJoint(){

    LOG("PrismaticJoint desctructor called");
    
    delete this->prism;
    delete this->cylinder;
    delete this->support[0];
    delete this->support[1];

}

void PrismaticJoint::set_support_dimension(float w, float h){

    float max_width = ( this->length - this->prism->get_width() ) / 2;
    if( w > max_width ) throw std::out_of_range("Collision detected on setting the support width to " + std::to_string(w) + "; maximum value allowed: " + std::to_string(max_width));

    this->support[0]->set_dimensions(w,h);

}

void PrismaticJoint::set_support_dimension(float w, float h){

    float max_width = this->length - this->support[0]->get_width() - this->support[1]->get_width();
    if( w > max_width ) throw std::out_of_range("Collision detected on setting the prism width to " + std::to_string(w) + "; maximum value allowed: " + std::to_string(max_width));

    this->prism->set_dimensions(w,h);

}

void PrismaticJoint::set_stroke(const float str){
    
    if( str < 0 || str > 100) throw std::out_of_range("Cannot create a prismatic joint with stroke percentage out of the range [0,100] (inserted " + std::to_string(str) + ")");

    this->stroke = str;
}

void PrismaticJoint::set_length(const float l){

    if( l < 0 ) throw std::out_of_range("Cannot create a prismatic joint with a negative length!");

    this->length = l;
    
}

vector<string> PrismaticJoint::to_svg() const {

    vector<string> tbr;

    std::stringstream trasf;
    trasf << "transform=\"matrix(1 0 0 1 ";
    trasf << this->pos_x << " ";
    trasf << this->pos_y << ")\"";

    tbr.push_back( this->svg_header() );
    tbr.push_back( this->cylinder->svg_code( trasf.str() ) );
    tbr.push_back( this->support[0]->svg_code( trasf.str() ) );
    tbr.push_back( this->support[1]->svg_code( trasf.str() ) );
    tbr.push_back( this->prism->svg_code( trasf.str() ) );

    return tbr;
}

void PrismaticJoint::to_svg(const string file_name) const{

    std::ofstream to_file(file_name + ".svg");

    to_file << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl << endl;
    to_file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">" << endl;

    vector<string> svg_codes = this->to_svg();
    for(string str : svg_codes){

        to_file << "\t" << str << endl;

    }

    to_file << "</svg>";

    to_file.close();

}

