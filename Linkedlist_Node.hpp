#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//class declaration
//
class Linkedlist_Node {
    private:
        string word;
        int dictionary_index;
        Linkedlist_Node* next_ptr;
        int total_ascii;

    public:
        //constructor:
        //
        Linkedlist_Node( string word , int index , int total_ascii );

        //Destructor:
        //
        ~Linkedlist_Node();

        //Member functiorns:
        //
        string get_word();
        int get_index();
        Linkedlist_Node* get_next_ptr();
        void update_next_ptr( Linkedlist_Node *ptr );
        int get_total_ascii();
};