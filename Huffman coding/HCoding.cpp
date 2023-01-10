#ifndef __HCODING_CPP__
#define __HCODING_CPP__

#include "HCoding.h"

void HCoding::readCompressedContentFromBinaryFile(const std::string& fileName, std::string& content) const{
    std::ifstream readContent(fileName, std::ios::binary);
    unsigned int contentLength;

    if(!readContent.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    readContent.read((char*)(&contentLength), sizeof(contentLength));
    content.resize(contentLength);

    readContent.read((char*)content.c_str(), contentLength);

    readContent.close();
}

Node* HCoding::readHuffmanTree (std::istream& in) const{
    assert(in.get()=='(');

    if(in.peek()==')'){
        in.get();
        return nullptr;
    }

    int frequencyNode;
    in >> frequencyNode;

    if(in.peek() == '|'){
        in.get();

        char symbol = in.get();

        assert(in.get() == ')');

        return new Node(frequencyNode, Maybe(symbol), nullptr, nullptr);
    }

    assert(in.get() == 32);

    Node* left = readHuffmanTree(in);

    assert(in.get() == 32);

    Node* right = readHuffmanTree(in);

    assert(in.get() == ')');

    return new Node(frequencyNode, Maybe(), left, right);
}

Node* HCoding::readHuffmanTreeFromFile(const std::string& fileName) const{
    std::ifstream readTree(fileName);

    if(!readTree.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    Node* nodeFromFile = readHuffmanTree(readTree);

    readTree.close();

    return nodeFromFile;
}

std::string HCoding::compress(const std::string& fileName){
    std::string content;

    std::ifstream readContent(fileName);

    if(!readContent.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    getline(readContent, content, '\n');
    
    std::string compressed = huffmanTree.compress(content);

    readContent.close();

    return compressed;
}

void HCoding::outputCompressedContentIntoBinaryFile(const std::string& content, const std::string& fileName){
    std::ofstream outputContent(fileName, std::ios::trunc | std::ios::binary);
    unsigned int contentLength = content.length();

    if(!outputContent.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    outputContent.write((char*)(&contentLength), sizeof(contentLength));
    outputContent.write(content.c_str(), contentLength);

    outputContent.close();
}

void HCoding::outputHuffmanTreeIntoFile(const std::string& fileName){
    std::ofstream outTree(fileName, std::ios::trunc);

    if(!outTree.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    huffmanTree.printHuffmanTree(outTree);

    outTree.close();
}


void HCoding::debugCompress(const std::string& content) const{
    std::vector<int> debugCompressed = huffmanTree.debugCompress(content);

    std::cout << "The result after execution of debug compress: ";

    for(int i = 0; i < debugCompressed.size(); ++i){
        std::cout << debugCompressed[i] << " ";
    }
    std::cout << std::endl;
}

void HCoding::computeDegreeOfCompression(const std::string& inputContent, const std::string& compressedContent){
    double result = huffmanTree.degreeOfCompression(inputContent, compressedContent);

    std::cout << "The result after computing the degree of compression is " << result * 100 << " and it says that we have represented a \"" << inputContent
              << "\" with about " << ceil((double)100/(result*100)) << " times less memory!" << std:: endl;
}

std::string HCoding::decompress(const std::string& fileName, const std::string& treeFileName) const{
    std::string content;

    readCompressedContentFromBinaryFile(fileName, content);

    Node* nodeFromFile = readHuffmanTreeFromFile(treeFileName);

    std::string decompressed = huffmanTree.decompress(nodeFromFile, content);

    return decompressed;
}

void HCoding::outputDecompressedContentIntoFile(const std::string& content, const std::string& fileName){
    std::ofstream outputContent(fileName, std::ios::trunc);

    if(!outputContent.good()){
        throw std::invalid_argument("Invalid content file!");
    }

    outputContent << content;

    outputContent.close();
}

#endif
