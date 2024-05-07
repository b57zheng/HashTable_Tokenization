#include "Linkedlist_Node.hpp"

//Constructor
//
Linkedlist_Node::Linkedlist_Node( string word , int dictionary_index , int total_ascii ) {
    //Initialize all member variables to avoid naming collision. 
    this->word = word;
    this->dictionary_index = dictionary_index;
    this->next_ptr = nullptr;
    this->total_ascii = total_ascii;
}

//Destructor:
//
Linkedlist_Node::~Linkedlist_Node() {

}

//Member functiorns:
//
string Linkedlist_Node::get_word() {
    return this->word;
}

int Linkedlist_Node::get_index() {
    return this->dictionary_index;
}

Linkedlist_Node* Linkedlist_Node::get_next_ptr() {
    return this->next_ptr;
}

void Linkedlist_Node::update_next_ptr( Linkedlist_Node *ptr ) {
    this->next_ptr = ptr;
}

int Linkedlist_Node::get_total_ascii() {
    return this->total_ascii;
}