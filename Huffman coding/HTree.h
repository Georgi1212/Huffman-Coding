#ifndef __HTREE_H__
#define __HTREE_H__

#include<iostream>

#include<cmath>
#include<fstream>
#include<exception>
#include<cassert>

#include<string>
#include<vector>
#include<queue>
#include<map>

#include "Node.cpp"

//class, which is directly related with the Huffman algorithm - the class contains methods for creating frquency table,
//creating the Huffman tree, creating code table, compression and decompression, etc.
class HTree{
    private:
        //pointer to the root of the Huffman tree
        Node* root;
        
        //struct compare, which helps us to create the priorityQueue (min heap)
        struct compare{
            //compares if first->frequency > second->frequency
            bool operator()(Node* first, Node* second) const;
        };

        //helper method, which is contained in the destuctor of the class HTree and it destroys the tree 
        //parameters: current - pointer to the root of the Huffman tree
        void clear(Node* current);

        //helper method, which creates the code table
        //parameters: current   - pointer to the root of the Huffman tree
        //            trace     - string, in which we will write the path from root to any leaf (when "current" become a leaf node,
        //                        we insert in the codeTable the path (trace) from root of the tree to the leaf node)
        //            codeTable - a map with key   - any symbol, which is contained in the text, which we want to compress and
        //                                   value - the path from the root of the Huffman tree to the key, which is a leaf node
        void createCodeTableHelper(Node* current, const std::string& trace, std::map<char, std::string>& codeTable) const;

        //helper method, which helps us to print the tree in file or in the standard output
        //parameters: current - pointer to the root of the tree
        //            out     - output stream
        void printTreeHelper (Node* current, std::ostream& out) const;

        //helper method, which decompress a symbol
        //parameters: current      - pointer to the root of the tree
        //            compressed   - string, which contains the compressed content and from which we get the "information" for decompression
        //            decompressed - string, in which we will push already decompressed symbol and it will help us 
        //                           to return the result of decompression
        //            index        - index, which is related to "compressed" and it is used in "decompress" method
        void decompressSymbol(Node* current, const std::string& compressed, std::string& decompressed, int& index) const;

    public:
        //Big four; we delete the copy constructor and operator=, because we don't want to copy trees
        HTree();
        HTree(const HTree& other) = delete;
        HTree& operator=(const HTree& other) = delete;
        ~HTree();

        //method, which returns pointer to the root of the tree
        Node* getRoot() const;

        //method, which creates a frequency table from given "inputText" and returns a map, which 
        //key - symbol, which is contained in the "inputText"
        //and value - the frequency of the symbol in the "inputText"
        //parameters: inputText - string, which contaains the content we want to compress/decompress, etc.
        std::map<char, int> createFriquencyTable(const std::string& inputText) const;

        using priority_queue = std::priority_queue<Node*, std::vector<Node*>, compare>;

        //method, which creates a priority queue from given frequency table (the priority is the frequency of the symbol in the input text)
        //parameters: frequencyTable - a map, which key - symbol, which is any symbol in the input text and value - 
        //the frequency of the symbol in the input text
        priority_queue createPriorityqueueFromFrequencyTable(const std::map<char, int>& frequencyTable) const;

        //method which creates the Huffman tree from given priorityQueue
        //parameters: priorityQueue - priority queue (the priority is the frequency of the symbol in the input text)
        void createHTree(priority_queue priorityQueue);

        //method, which creates a code table (for every symbol there will be a binary code) and returns a map, which key - symbol, which is any 
        //symbol in the input text and value - string, which contains a binary code, which is taken from the Huffman tree
        std::map<char, std::string> createCodeTable() const;

        //method, which compress the "input" and returns the compressed string
        //parameters: input - the content, which we have input and want to compress, decompress, etc. 
        std::string compress(const std::string& input);

        //method, which decompress the "compressed" with the help of the "current", which is pointer to the root of the tree, 
        //and returns the decompressed string
        std::string decompress(Node* current, const std::string& compressed) const;

        //method, which makes a debug compress of the compressed information and returns a vector, which contains the values, which are
        //result of the debug compress
        //parameters: input - string, which contains compressed information
        std::vector<int> debugCompress(const std::string& input) const;

        //method, which computes the degree of compression and returns a value, which is result of dividing the size (bits) of the 
        //"compressed" by the "inputText"
        //parameters: inputText  - the content, which we have input and want to compress, decompress, etc.
        //            compressed - the string, which contains the compressed content
        double degreeOfCompression(const std::string& inputText, const std::string& compressed) const;

        //method, which prints a tree in a file or in the standard output
        //and the Huffman tree is saved in preorder (root, left, righ) (Scheme format) 
        //parameters: out - output stream
        void printHuffmanTree (std::ostream& out) const;

};

#endif