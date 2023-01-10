#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "HCoding.cpp"
#include "Modes.h"

//struct, which helps us to run the program 
struct Command{
    private:
        //method that output the valid commands with their arguments
        void intro();

        //method that outputs the content, which we are going to compress/decompress and do other commands, in a text file
        //parameters: content     - the string which we have input and that is the content which we want to manipulate
        //            contentFile - the name of the file we want to save the content 
        void outputContent(const std::string& content, const std::string& contnentFile);

    public:
        //method, that runs the program with the given command parameters
        void run();
};

#endif