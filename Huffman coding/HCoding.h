#ifndef __HCODING_H__
#define __HCODING_H__

#include <fstream>
#include <string>

#include "HTree.cpp"

//class, which works with files and works with class HTee (writes the compressed content in a file and writes the Huffman tree in a file 
//                                                         and also reads the compressed content and the Huffman tree and creates 
//                                                         the decompressed ouput file) 
class HCoding{
    private:
        HTree huffmanTree;

        //method, which reads the content, which is already compressed, from a binary file
        //parameters: fileName - the name of the file, from which we will read the compressed content,
        //            content  - the content, in which we will write the information that we have read from "fileName"                
        void readCompressedContentFromBinaryFile(const std::string& fileName, std::string& content) const;

        //method, which reads the Huffman tree from a text file and returns pointer to the root of the Huffman tree
        //parameters: fileName - the name of the file, from which we will read the Huffman tree
        Node* readHuffmanTreeFromFile(const std::string& fileName) const;

        //method, which helps to the method "readHuffmanTreeFromFile" to read the Huffman tree and returns pointer to the root of the Huffman tree
        //parameters: in - input stream, which helps us to read from a file
        Node* readHuffmanTree (std::istream& in) const;

    public:

        //method, which compress the content from "fileName" and returns the compressed string
        //parameters: fileName - the name of the file, from which we will read the content and then we will compress it
        std::string compress(const std::string& fileName); 

        //method, which outputs the compressed content into the fileName
        //parameters: content  - the compressed content we will output into fileName
        //            fileName - the fileName, in which the content will be saved
        void outputCompressedContentIntoBinaryFile(const std::string& content, const std::string& fileName);

        //method, which save the result Huffman tree into fileName
        //parameters: fileName - the name of the file, which the Huffman tree will be saved 
        void outputHuffmanTreeIntoFile(const std::string& fileName);

        //method, which outputs the result of debug compress
        //parameters: content - the compressed content, from which we will get the information for debug compress
        void debugCompress(const std::string& content) const;

        //method, which computes the degree of compression
        //parameters: inputContent      - the content, which we have input first
        //            compressedContent - the compress content, which is result of compression of "inputContent"
        void computeDegreeOfCompression(const std::string& inputContent, const std::string& compressedContent);

        //method, which decompress the compressed content from "fileName" and for this process we need also the file,
        //which contains the Huffman tree 
        //parameters: fileName     - the name of the file, from which we will read the compressed content
        //            treeFileName - the name of the file, from which we will read the Huffman tree
        std::string decompress(const std::string& fileName, const std::string& treeFileName) const;

        //method, which outputs the decompressed content in "fileName"
        //parameters: content  - the decompressed content, which we will output in the "fileName"
        //            fileName - the name of the file, in which the decompressed content will be saved
        void outputDecompressedContentIntoFile(const std::string& content, const std::string& fileName);
};

#endif