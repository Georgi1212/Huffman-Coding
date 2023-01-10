#ifndef __NODE_CPP__
#define __NODE_CPP__


#include "Node.h"

Maybe::Maybe() : isDefined(false){}

Maybe::Maybe(const char& _data) : data(_data), isDefined(true){}

Node::Node(const int& _frequency, const Maybe& _symbol, Node* _left, Node* _right){
    
    friquency = _frequency;
    left = _left;
    right = _right;

    if(_symbol.isDefined == false){
        symbol.isDefined = false;
    }
    else if(_symbol.isDefined == true){
        symbol.data = _symbol.data;
        symbol.isDefined = true;
    }
}

#endif