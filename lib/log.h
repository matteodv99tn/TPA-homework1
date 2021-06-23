
#ifndef _MY_LOG_H_
#define _MY_LOG_H_

    // To see the log massages set to 1
    // otherwise set to 0
    #define LOG_MODE 1
    

    #if LOG_MODE == 1
        #include <iostream>
        #include <string>
        #include <fstream>        
        // #define LOG( value ) std::cout << "LOG info: " /* <<  __FILE__ << "::"  */ << __FUNCTION__ << "(line " << __LINE__ <<"): " << value << endl;
        #define LOG( value ) { \
            std::string file_name = __FILE__; \
            while(file_name.find("/") != std::string::npos ) file_name.erase(0, file_name.find("/")+ 1); \
            std::fstream file ("log.txt", std::ios_base::app); \
            file << file_name << "::" << __LINE__ << "  \t" << value << endl; \
            file.close();  } ;

        #define START_LOGGING_SESSION std::ofstream file ("log.txt"); file << "LOGGING STARTED AT " << __TIME__ << " on " << __DATE__ << std::endl;

    #else
        #define START_LOGGING_SESSION
        #define LOG( value )
    #endif

#endif