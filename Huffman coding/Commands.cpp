#ifndef __COMMANDS_CPP__
#define __COMMANDS_CPP__

#include "Commands.h"

void Command::intro(){
    std::cout << "POSSIBLE COMMANDS YOU CAN INPUT:" << std::endl;
    std::cout << "  c                       - to work in compress mode" << std::endl;
    std::cout << "  d                       - to work in decompress mode" << std::endl;
    std::cout << "  b                       - to output the result of debug compress" << std::endl;
    std::cout << "  g                       - to compute the degree of compression" << std::endl;
    std::cout << "  i <filename>            - to say which is the input file which will be compressed" << std::endl;
    std::cout << "  i <filename> <filename> - to say which is the input file which will be decompressed and the file of the tree" << std::endl;
    std::cout << "  o <filename>            - to say which is the output file for the compression or decompression" << std::endl;
    std::cout << "  e                       - exit" << std::endl;
    std::cout << std::endl;
}

void Command::outputContent(const std::string& content, const std::string& contentFile){

    std::ofstream outputContent(contentFile, std::ios::trunc);

    // the "good()" method returns true if the stream is good, it means that this function
    // will check if this stream has raised any error or not.
    if(!outputContent.good()){
        throw std::invalid_argument("Invalid content file!");
    }
    
    outputContent << content;

    outputContent.close();
}

void Command::run(){
    std::string content;

    //we can't work with a content, which has 1 symbol, we can't construct the Huffman tree
    do{
        std::cout << "Input the content you want to work with: ";
        getline(std::cin, content, '\n');

        if(content.size() == 1){
            std::cout << "You can't use Huffman algorithm to compress/decompress one element!" << std::endl;
        }

    }while(content.size() == 1);


    std::string contentFile;
    std::cout << "Input the content file where the content will be saved: ";
    getline(std::cin, contentFile, '\n');

    std::cout << std::endl;

    outputContent(content, contentFile);
    intro();

    Modes mode;
    std::string inputFileName, outputFileName, treeFileName;
    std::string compressed, decompressed;
    HCoding coding;

    std::map<std::string, Modes> containerFilesWithMode;

    containerFilesWithMode.insert({contentFile, Modes::DECOMPRESS});

    std::string command;
    
    do{
        std::cout << "> ";
        getline(std::cin, command, '\n');

        if(command == "e"){
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else{
            char commandSymbol = command[0];
            command.erase(0, 1);
            
            if(commandSymbol == 'c' || commandSymbol == 'd' || commandSymbol == 'b' || commandSymbol == 'g'){
                try{
                    if(!command.empty()){
                        throw std::invalid_argument("Invalid input command - when you want to input this type of commands there is no other information like name of a file!");
                    }

                    if(commandSymbol == 'c'){
                        mode = Modes::COMPRESS;
                        std::cout << "You are now in COMPRESS mode!" << std::endl;
                    }

                    else if(commandSymbol == 'd'){
                        mode = Modes::DECOMPRESS;
                        std::cout << "You are now in DECOMPRESS mode!" << std::endl;
                    }

                    else if(commandSymbol == 'b'){
                        try{
                            if(compressed.empty()){
                                throw std::invalid_argument("The string you want to do a debug compress is empty and you can't do that command!");
                            }
                            
                            coding.debugCompress(compressed);
                            
                        }
                        catch(std::invalid_argument& e){
                            std::cout << e.what() << std::endl;
                            std::cout << "First, compress the content you want and after that try to do debug compress command!" << std::endl;
                            continue;
                        }
                    }

                    else if(commandSymbol == 'g'){
                        try{
                            if(compressed.empty() || content.empty()){
                                throw std::invalid_argument("One of the strings or both of them from which you want to compute the degree of compression is/are empty and you can't do that command!");
                            }

                            coding.computeDegreeOfCompression(content, compressed);

                        }
                        catch(std::invalid_argument& e){
                            std::cout << e.what() << std::endl;
                            std::cout << "First, compress the content you want and after that try to compute the degree of compression!" << std::endl;
                            continue;
                        }
                    }
                }
                catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    std::cout << "Please, try again!"<< std::endl;
                    std::cout << std::endl;
                    continue;
                }
            }

            else if(commandSymbol == 'i' || commandSymbol == 'o'){
                try{
                    if(command.empty()){
                        throw std::invalid_argument("Invalid input command - when you want to input \"i\" or \"o\" command there is other information like name of a file!");
                    }
                    
                    while(command[0] == ' '){
                        command.erase(0,1);
                    }
                        
                    std::string fileName;

                    for(char symbol : command){
                        if(symbol == ' '){
                            break;
                        }
                        fileName += symbol;
                    }

                    command.erase(0, fileName.length());

                    if(commandSymbol == 'i'){
                        inputFileName = fileName;
                        fileName = "";

                        try{
                            if(containerFilesWithMode.count(inputFileName) == 0){
                                throw std::invalid_argument("You can't compress or decompress a file which doesn't exist and file, which contains Huffman tree!");
                            }
                        }
                        catch(std::invalid_argument& e){
                            std::cout << e.what() << std::endl;
                            std::cout << "First, type right the name of the file, which you want to compress or decompress, and after that try to do a \"i\" command!" << std::endl;
                            continue;
                        }

                        try{
                            if(containerFilesWithMode[inputFileName] != mode){
                                switch(mode){
                                    case Modes::COMPRESS:
                                        compressed = coding.compress(inputFileName); 
                                        std::cout << "File " << inputFileName << " is successfully compressed! You can output that compessed content with using \"o\" command!" << std::endl;
                                        break;

                                    case Modes::DECOMPRESS:
                                        try{
                                            if(command.empty()){
                                                throw std::invalid_argument("Invalid input command - when you want to input \"i\" command in DECOMPRESS mode there is also other information like name of a file, which contains the Huffman tree!");
                                            }
                                            
                                            while(command[0] == ' '){
                                                command.erase(0,1);
                                            }

                                            for(char symbol : command){
                                                if(symbol == ' '){
                                                    break;
                                                }
                                                fileName += symbol;
                                            }

                                            command.erase(0, fileName.length());

                                            if(fileName != treeFileName){
                                                throw std::invalid_argument("The name of the file, where the Huffman tree is saved, is not the name that you have input!");
                                            }

                                            decompressed = coding.decompress(inputFileName, treeFileName);
                                            std::cout << "File " << inputFileName << " is successfully decompressed! You can output that decompessed content with using \"o\" command!" << std::endl;
                                        }
                                        catch(std::invalid_argument& e){
                                            std::cout << e.what() << std::endl;
                                            continue;
                                        }
                                        break;
                                }
                            }
                            else{
                                throw std::invalid_argument("You can't compress a file which is already compressed (the content of this file contains binary code) and you can't decompress a file which is already decompressed!");
                            }
                        }
                        catch(std::invalid_argument& e){
                            std::cout << e.what() << std::endl;
                            continue;
                        }
                    }

                    else if(commandSymbol == 'o'){
                        outputFileName = fileName; 

                        if(containerFilesWithMode.count(outputFileName) == 0){
                            containerFilesWithMode.insert({outputFileName, mode});
                        }

                        switch(mode){
                            case Modes::COMPRESS:
                                coding.outputCompressedContentIntoBinaryFile(compressed, outputFileName);
                                std::cout << "Input the name of the file, where the Huffman tree will be saved: ";
                                getline(std::cin, treeFileName, '\n');
                                coding.outputHuffmanTreeIntoFile(treeFileName);
                                std::cout << "The result of the compression is saved on " << outputFileName << " file!" << std::endl;
                                break;
                                
                            case Modes::DECOMPRESS:
                                coding.outputDecompressedContentIntoFile(decompressed, outputFileName); 
                                std::cout << "The result of the decompression is saved on " << outputFileName << " file!" << std::endl;
                                break;
                        }
                    }
                }
                catch(std::invalid_argument& e){
                    std::cout << e.what() << std::endl;
                    std::cout << "Please, try again!"<< std::endl;
                    std::cout << std::endl;
                    continue;
                }
            }

            else{
                std::cout << "Invalid input command - this command is not supported!" << std::endl; 
            }
        }  

    }while(true);
}

#endif