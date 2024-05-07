#include "Linkedlist_Node.hpp"

using namespace std;

class Hash_Table {
    private:
        Linkedlist_Node** word_table;
        Linkedlist_Node** index_table;
        int size_hash_table;
        int dictionary_count;
        int hash_function( string& text );
        bool in_node( string& text , Linkedlist_Node* node );

    public:
        //Constructor:
        //
        Hash_Table( int size_hash_table );
        
        //Destructor:
        //
        ~Hash_Table();

        //Member functions:
        //
        //insert word:
        bool insert( string& text );
        //read file:
        bool read_file( fstream& fin );
        //Tokenize word:
        int tokenize( string& text );
        //Retrieve word with token:
        string retrieve( int token );
        //Tokenize string:
        void tokenize_string( string& sentence );
        //Retrieve string with tokens:
        void retrieve_string( string& tokens );
        //Print the chain of stored tokens in position k of the hash table.
        void print_keys_at( int position );
};