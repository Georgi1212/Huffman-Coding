#ifndef __NODE_H__
#define __NODE_H__

//struct, which is a part of the representation of a node in a Huffman tree and is something like the std::optional
//(node may have a symbol (any symbol of the content, which we want to compress/decompress, etc) or not 
//(if a node is a leaf, then it has a defined symbol, else not))
struct Maybe{
    char data;
    bool isDefined;

    Maybe();
    Maybe(const char& _data);
};

//struct, which represents a node in a Huffman tree:
//frequency - the frequency of any symbol in the content, which we want to compress/decompress
//symbol    - a symbol, which is part of the content
struct Node{
    int friquency;
    Maybe symbol;

    Node* left;
    Node* right;

    Node(const int& _frequency, const Maybe& _symbol, Node* _left, Node* _right);
};

#endif