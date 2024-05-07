#include "Hash_Table.hpp"

int main();

int main() {
    Hash_Table* hash_table;
    string cmd;

    while( cin >> cmd ) {
        if( cmd == "M" ) {
            int size = 0;
            cin >> size;
            
            hash_table = new Hash_Table( size );
            cout << "success" << endl;
        } 
        
        else if( cmd == "INSERT" ) {
            string word;
            cin >> word;
            
            if( hash_table->insert( word ) ) {
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }
        }

        else if( cmd == "READ" ) {
            string filename;
            cin >> filename;
            fstream fin( filename.c_str() );

            if( hash_table->read_file( fin ) ){
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }

            fin.close();    
        }

        else if( cmd == "TOKENIZE" ) {
            string word;
            cin >> word;
            
            int token_of_word = hash_table->tokenize( word );
            cout << token_of_word << endl;
        }

        else if( cmd == "RETRIEVE" ) {
            int token;
            cin >> token;

            string word_with_token = hash_table->retrieve( token );
            cout << word_with_token << endl;
        }

        else if( cmd == "STOK" ) {
            string sentence;

            cin.ignore();
            getline( cin , sentence );

            hash_table->tokenize_string( sentence );
        }

        else if( cmd == "TOKS" ) {
            string tokens;

            cin.ignore();
            getline( cin , tokens );

            hash_table->retrieve_string( tokens );
        }

        else if( cmd == "PRINT" ) {
            int position;
            cin >> position;

            hash_table->print_keys_at( position );
        }

        else if( cmd == "EXIT" ) {
            delete hash_table;
            return 0;
        }   
    }
}