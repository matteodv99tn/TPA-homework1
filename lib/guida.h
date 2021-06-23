#ifndef _PRISMATIC_JOINT_H_
#define _PRISMATIC_JOINT_H_

#include <string>
#include <vector>
#include <ostream>
#include <istream>

using std::string;
using std::vector;

namespace matteodv99tn{

    class Rectangle{

        private:

            // Class attributes

            float x_rel;    // Using a relative position sistem in respect to the main prismatic join
            float y_rel;  

            float width;    // Width and height of the rectangle
            float height;

            int colors[3];  // Colors to be rendered
            
        public:
            // Constructors:
            Rectangle(float x, float y, float w, float h);
            Rectangle(float x, float y, float w, float h, int * col);
            Rectangle(const Rectangle &other);
            Rectangle(Rectangle &other);

            // Destructor:
            ~Rectangle();

            // Getter and setter funcions
            void set_relative_position(const float x, const float y);
            void set_dimensions(const float w, const float h);
            void set_colors(const int new_colors[3]);

            float get_x() const {return this->x_rel; };
            float get_y() const {return this->y_rel; };
            float get_width() const {return this->width; };
            float get_height() const {return this->height; };
            int* get_colors() const;

            // Other function
            string svg_code(string transform_string) const;
            vector<string> svg_draw_width(const string transformation_string, const float offset) const;


            // Operator overload
            friend std::ostream& operator<<(std::ostream& stream, const Rectangle &rect);
            friend std::istream& operator>>(std::istream& stream, Rectangle &rect);


    };

    class PrismaticJoint{

        private: 

            // Private class attributes
            float pos_x;
            float pos_y;

            float stroke;
            float length;
            float thickness;

            Rectangle * support[2];
            Rectangle * prism;
            Rectangle * cylinder;

            // Private functions
            void define_positions();
            string svg_header() const;

        public:

            // Constructors 
            PrismaticJoint(float x, float y, float len, float str);
            PrismaticJoint(const string file_name, const int index = 0);

            // Destructor
            ~PrismaticJoint();

            // Getter and setter function
            void set_support_dimension(const float w, const float h);
            void set_support_color(const int newcol[3]);
            void set_prism_dimension(const float w, const float h);
            void set_prism_color(const int newcol[3]);
            void set_stroke(const float str);
            void set_cylinder_diameter(const float newdiameter);
            void set_cylinder_color(const int newcol[3]);
            void set_length(const float l);

            // Other functions
            vector<string> to_svg(bool draw_annotation = false) const;
            void to_svg(const string file_name) const;


            // Operator overloads
            friend std::ostream& operator<<(std::ostream &stream, const PrismaticJoint &joint);
    };

}

#endif