#ifndef _PRISMATIC_JOINT_H_
#define _PRISMATIC_JOINT_H_

#include <string>

using std::string;

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

            // Destructor:
            ~Rectangle();

            // Getter and setter funcions
            void set_relative_position(const float x, const float y);
            void set_dimensions(const float w, const float h);


            // Other function
            string svg_code(string transform_string) const;


    };

}

#endif