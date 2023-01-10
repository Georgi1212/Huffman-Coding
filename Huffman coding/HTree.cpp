#ifndef __HTREE_CPP__
#define __HTREE_CPP__

#include "HTree.h"

void HTree::clear(Node* current){
    if(current == nullptr){
        return;
    }

    clear(current->left);
    clear(current->right);
    delete current;
}

bool HTree::compare::operator () (Node* first, Node* second) const{
    return first->friquency > second->friquency;
}

HTree::HTree(){
    root == nullptr;
}

HTree::~HTree(){
    clear(root);
}

Node* HTree::getRoot() const{
    return this->root;
}

std::map<char, int> HTree::createFriquencyTable(const std::string& inputText) const{
    std::map<char, int> frequencyTable;

    for(char symbol : inputText){
        if(frequencyTable.find(symbol) == frequencyTable.end()){ 
            frequencyTable[symbol] = 1;
        }
        else{
            frequencyTable[symbol]++;
        }
    }

    return frequencyTable;
}

HTree::priority_queue HTree::createPriorityqueueFromFrequencyTable(const std::map<char, int>& frequencyTable) const{
    priority_queue priorityQueueFromFrequencyTable;

    for(std::pair<char, int> it : frequencyTable){
        Node* element = new Node(it.second, Maybe(it.first), nullptr, nullptr);

        priorityQueueFromFrequencyTable.push(element);
    }

    return priorityQueueFromFrequencyTable;
}

void HTree::createHTree(priority_queue priorityQueue){
    
    while(!priorityQueue.empty()){
        Node* _left = priorityQueue.top();
        priorityQueue.pop();

        Node* _right = priorityQueue.top();
        priorityQueue.pop();

        Node* current = new Node(_left->friquency + _right->friquency, Maybe(), _left, _right);

        if(priorityQueue.empty()){
            this->root = current;
            return;
        }

        priorityQueue.push(current);
    }
}

void HTree::createCodeTableHelper(Node* current, const std::string& trace, std::map<char, std::string>& codeTable) const{
    if(current->symbol.isDefined){
        codeTable[current->symbol.data] = trace;
        return;
    }

    createCodeTableHelper(current->left, trace + "0", codeTable);
    createCodeTableHelper(current->right, trace + "1", codeTable);
}

std::map<char, std::string> HTree::createCodeTable() const{
    std::map<char, std::string> codeTable;
    createCodeTableHelper(root, "", codeTable);
    return codeTable;
}

std::string HTree::compress(const std::string& input){
    std::map<char, int> frequencyTable = createFriquencyTable(input);

    priority_queue priorityQueue = createPriorityqueueFromFrequencyTable(frequencyTable);

    createHTree(priorityQueue);

    std::map<char, std::string> codeTable = createCodeTable();

    std::string compressedInfo;
    for(char symbol : input){
        compressedInfo += codeTable[symbol];
    }

    return compressedInfo;
}

std::vector<int> HTree::debugCompress(const std::string& input) const{
    std::string inputToConvert = input;
    int sizeInputToConvert = inputToConvert.size();
    int parts = std::ceil((double)sizeInputToConvert / 8);
    
    if(sizeInputToConvert % 8 != 0){
        while(inputToConvert.size() % 8 != 0){
            inputToConvert = inputToConvert.insert((8 * (parts - 1)), "0");
        }
    }

    std::vector<int> decimalCompress;

    std::string compressedPart;
    int indexCompressPart = 0;

    while(!inputToConvert.empty()){
        while(indexCompressPart != 8){
            compressedPart.push_back(inputToConvert[indexCompressPart]);
            ++indexCompressPart;
        }

        int copressedPartDecimal = std::stoi(compressedPart, 0, 2);

        decimalCompress.push_back(copressedPartDecimal);

        inputToConvert.erase(0, compressedPart.size());
        
        indexCompressPart = 0;
        compressedPart = "";
    }

    return decimalCompress;
}

void HTree::decompressSymbol(Node* current, const std::string& compressed, std::string& decompressed, int& index) const{
    if(index == compressed.size() && !current->symbol.isDefined){
        throw std::invalid_argument("The last element is not found, the tree might be wrong constructed");
    }

    if(current->symbol.isDefined){
        decompressed.push_back(current->symbol.data);
        return;
    }

    if(compressed[index] == '0'){
        decompressSymbol(current->left, compressed, decompressed, ++index);
    }
    else{
        decompressSymbol(current->right, compressed, decompressed, ++index);
    }
}

std::string HTree::decompress(Node* current, const std::string& compressed) const{
    
    std::string decompressed;

	int index = 0;
	while (index != compressed.size()){
		decompressSymbol(root, compressed, decompressed, index);
    }

    return decompressed;
}

double HTree::degreeOfCompression(const std::string& inputText, const std::string& compressed) const{
    return ((double)compressed.size() / (inputText.size() * 8));
}

void HTree::printTreeHelper (Node* current, std::ostream& out) const{
    if (current->symbol.isDefined)
    {
        out << "(" << std::to_string(current->friquency) << "|" << current->symbol.data << ")";
        return;
    }

    out << "(" << std::to_string(current->friquency) << " ";
    printTreeHelper(current->left, out);
    out << " ";
    printTreeHelper(current->right, out);
    out << ")";
}

void HTree::printHuffmanTree (std::ostream& out) const{
    printTreeHelper(root, out);
}

#endif
