
#ifndef _MY_LOG_H_
#define _MY_LOG_H_

    // To see the log massages set to 1
    // otherwise set to 0
    #define LOG_MODE 1
    

    #if LOG_MODE == 1
        #include <iostream>        
        #define LOG( value ) std::cout << "LOG info: " /* <<  __FILE__ << "::"  */ << __FUNCTION__ << "(line " << __LINE__ <<"): " << value << endl;
    #else
        #define LOG( value )
    #endif

#endif