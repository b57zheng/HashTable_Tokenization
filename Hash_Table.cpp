#include "Hash_Table.hpp"

//Constructor:
//
Hash_Table::Hash_Table( int size_hash_table ) {
    //Initialize dictionary count to count 
    this->dictionary_count = 0;

    //Initialize word hash table to nullptr
    //
    this->word_table = new Linkedlist_Node*[size_hash_table];
    for( int i{0}; i < size_hash_table; i++ ) { 
        this->word_table[i] = nullptr;
    }

    //Initialize index hash table to nullptr
    //
    this->index_table = new Linkedlist_Node*[size_hash_table];
    for( int i{0}; i < size_hash_table; i++ ) { 
        this->index_table[i] = nullptr;
    }

    //Initialize size_hash_table
    this->size_hash_table = size_hash_table;
}

//Destructor:
//
Hash_Table::~Hash_Table() {
    //Release memory allocated to word hash table
    //
    //Iterate through each position in the hash table
    for( int i{0}; i < size_hash_table; i++ ) {
        Linkedlist_Node* p_current_node = word_table[i];
        //Iterate through the linkedlist if it is not empty, and delete the nodes one-by-one.
        while( p_current_node != nullptr ) {
            Linkedlist_Node* p_previous_node = p_current_node;
            p_current_node = p_current_node->get_next_ptr();
            delete p_previous_node;
        }
    }
    //Delete word hash table
    delete[] word_table;

    //Release memory allocated to index hash table
    //
    //Iterate through each position in the hash table
    for( int i{0}; i < size_hash_table; i++ ) {
        Linkedlist_Node* p_current_node = index_table[i];
        //Iterate through the linkedlist if it is not empty, and delete the nodes one-by-one.
        while( p_current_node != nullptr ) {
            Linkedlist_Node* p_previous_node = p_current_node;
            p_current_node = p_current_node->get_next_ptr();
            delete p_previous_node;
        }
    }
    //Delete index hash table
    delete[] index_table;
}

//Private Member Functions:
//
/*
This is a helper function that returns an integer value after calculating the hash function.
Output: hash value; if the word does not contain non-alphabetic character
        -1; if the word contain non-alphabetic character
*/      
int Hash_Table::hash_function( string& text ) {
    //calculate hash function:
    int sum = 0;
    for( int i{0}; i < text.length(); i++ ) {
        //Include the ASCII value of the character if it is an alphabetic character.
        if( text.at(i) >= 'a' && text.at(i) <= 'z' || text.at(i) >= 'A' && text.at(i) <= 'Z' ) {
            sum = sum + int( text.at(i) );
        } else {
            return -1;
        }
    }

    //Primary hash function h(k) = k mod m, where k is the sum of ASCII values of the word.
    int hash_value = sum % this->size_hash_table;  
    return hash_value; 
}

/*
This is a helper function that returns a boolean value after checking if a word is already exsited.
Output: true; if the word was found in the dictionary
        false; if the word was not found in the dictionary
*/      
bool Hash_Table::in_node( string& text , Linkedlist_Node* node ) {
     Linkedlist_Node* p_current = node;
     //Travers through the linkedlist, return true if the word in the node matches the input
     while( p_current != nullptr ) {
        if( p_current->get_word() == text ) {
            return true;
        }
        p_current = p_current->get_next_ptr();
     }
     return false;
}

//Public Member Functions:
//
/*
This is a function for command "INSERT", it returns an boolean value and insert word into the dictionary.
Output: true; if the word does not contain non-alphabetic character and does not exist in the dictionary, the word will be inserted into the dictionary.
        false; if the word contain non-alphabetic character or existed in the dictionary.
*/     
bool Hash_Table::insert( string& text ) {
    //Insert the word to word_table:
    //
    //calculate hash value:
    int index = this->hash_function( text );

    //Return false if current word contains nonalphabetic characters
    if( index < 0 ) {
        return false;
    }

    Linkedlist_Node* p_current_node = this->word_table[index];

    //Return false if word already existed or contains nonalphabetic characters
    if( this->in_node( text , p_current_node ) == 1 ) {
        return false;
    }

    //calculate total ascii for the word that is going to be inserted
    int total_ascii = 0;
    for ( int i{0}; i < text.length(); i++ ) {
        total_ascii = total_ascii + int( text.at(i) );
    }

    //Update dictionary counter if the above condition were met.
    this->dictionary_count++;
    //Create new node 
    Linkedlist_Node* p_word_node = new Linkedlist_Node( text , this->dictionary_count , total_ascii );
    //update p_current_node to be the next node of word node
    p_word_node->update_next_ptr( p_current_node );
    //update head node (table index) to new word node, chaining new node to the front of the list
    this->word_table[index] = p_word_node;
    
    //Insert the word to index_table: 
    //
    //calculate hash value with secondary hash function: h(t) = t mod m, where t is the token of the word
    int dictionary_index = (this->dictionary_count) % this->size_hash_table;
    //Create new node 
    Linkedlist_Node* p_index_node = new Linkedlist_Node( text , this->dictionary_count , total_ascii );
    //update the index node to be the next node of index node.
    p_index_node->update_next_ptr( this->index_table[dictionary_index] );
    //update head node (dictionary index) to index node, chaining new node to the front of the list
    this->index_table[dictionary_index] = p_index_node;        

    return true;
}

/*
This is a function for command "READ", it returns an boolean value and insert words in a text file into the dictionary.
Output: true; if there is at least one word being inserted into the library by insert()
        false; if there is no word being inserted into the library by insert()
*/    
bool Hash_Table::read_file( fstream& fin ) {
    string to_read;
    bool inserted = false;

    while( fin >> to_read ) {
        if ( this->insert( to_read ) ) {
            inserted = true;
        } 
    }
    return inserted;
}

/*
This is a function for command "TOKENIZE", it returns the token of the inputed word
Output: token; if the word exsit in the dictionary
        0; if the word does not exsit in the dictionary
*/ 
int Hash_Table::tokenize( string& text ) {
    //Calculate hash value with primary hash function h(k):
    int hash_value = this->hash_function( text );

    //Return 0 if current word contains nonalphabetic characters
    if( hash_value < 0 ) {
        return 0;
    }

    //Travers through the linked list at computed hash value
    Linkedlist_Node* p_current_node = this->word_table[hash_value];
    while( p_current_node != nullptr ) {
        //return the dictionary_index if the word is found in the linkedlist of hash_value
        if( p_current_node->get_word() == text ) { 
            return p_current_node->get_index();
        }
        p_current_node = p_current_node->get_next_ptr();
    }
    
    //return 0 if the word is not found in the linkedlist of hash_value
    return 0;
}

/*
This is a function for command "RETRIEVE", it returns the word of the inputed token
Output: word; if the word esxsit in the dictionary
        UNKNOWN; if the word does not exsit in the dictionary
*/ 
string Hash_Table::retrieve( int token ) {
    //return UNKNOWN if token is not valid.
    if( token <= 0 || token > this->dictionary_count ) {
        return "UNKNOWN";
    }

    //calculate hash value with secondary hash function h(t): 
    int hash_value = token % this->size_hash_table;

    //Travers through the linked list at computed hash value
    Linkedlist_Node* p_current_node = this->index_table[hash_value];
    while( p_current_node != nullptr ) {
        //return the word if the token is found in the linkedlist of hash_value
        if( p_current_node->get_index() == token ) {
            return p_current_node->get_word();
        }
        p_current_node = p_current_node->get_next_ptr();
    }

    //For TESTING: return ERROR if above failed ( bug ). 
    return "UNKNOWN";
}

/*
This is a function for command "STOK", it returns the string of token of the inputed string of words
Output: token; if the word exsit in the dictionary
        0; if the word does not exsit in the dictionary
*/ 
void Hash_Table::tokenize_string( string& sentence ) {
    //Initialize starting position of the current word
    int start_word = 0;
    //Initialize end position of the current word
    int end_word;

    //loop through each character in the sentence.
    while( start_word < sentence.length() ) {
        //Assign end position to the space after starting position of the current word
        end_word = sentence.find( " " , start_word );

        //if the next postion of end_word is not a space, end_word is at the end of sentence
        if( end_word == string::npos ) {
            end_word = sentence.length();
        }

        //Get current word by getting a sub string from starting position to the ending positoin of the current word.
        string current_word = sentence.substr( start_word , end_word - start_word );

        //stop tokenize current word if the current word is: "_DONE_" as the string is ended
        if (current_word.find("_DONE_") != string::npos) {
            break;
        }

        //Tokenize current word:
        cout << tokenize( current_word ) << " ";
        //Update starting position of the current word to tokenize next word:
        start_word = end_word + 1;
    }
    cout << endl;
}

/*
This is a function for command "TOKS", it returns the string of words of the inputed string of tokens
Output: word; if the token exsit in the dictionary
        UNKNOWN; if the token does not exsit in the dictionary
*/ 
void Hash_Table::retrieve_string( string& tokens ) {
    //Initialize starting position of the current token
    int start_token = 0;
    //Initialize end position of the current token
    int end_token;

    //loop through each number in the tokens.
    while( start_token < tokens.length() ) {
        //Assign end position to the space after starting position of the current token
        end_token = tokens.find( " " , start_token );

        //if the next postion of end_token is not a space, end_token is at the end of the tokens
        if( end_token == string::npos ) {
            end_token = tokens.length();
        }

        //Get currcent token by getting a sub string from starting position to the ending positoin of the current token.
        string current_token = tokens.substr( start_token , end_token - start_token );

        //stop tokenize retrieve current token if the current token is: "-1" as the string is ended
        if (current_token.find("-1") != string::npos) {
            break;
        }

        //Retrieve current token:
        cout << retrieve( stoi( current_token ) ) << " ";
        //Update starting position of the current token to retrieve next token:
        start_token = end_token + 1;
    }
    cout << endl;    
}


/*
This is a function for command "PRINT", it returns the key of words stored in the inputed position
Output: key; if the position is not empty 
        chain is empty; if the position is empty
*/ 
void Hash_Table::print_keys_at( int position ) {
    //Create a pointer pointing to the current position in word table
    Linkedlist_Node* p_current_node = this->word_table[position];

    //print "chain is empty" when the position is nullptr in the hash table
    if( p_current_node == nullptr ) {
        cout << "chain is empty" << endl;
    } else {
        //Iterate through the linkedlist if the position is not nullptr
        //print the index stored in each node. 
        while( p_current_node != nullptr ) {
            cout << p_current_node->get_total_ascii() << " ";
            p_current_node = p_current_node->get_next_ptr();
        }
        cout << endl;        
    }
}