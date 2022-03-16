#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include "Hashtable.h"
#include <sstream>
using namespace std;
//
LLNode * createNode(Movie movie){
    LLNode * newNode = new LLNode;
    newNode->data = movie;
    newNode->next = EMPTY;
    return newNode;
}
//
string removePrefix(string key){
    string s = "";
    for (int i = 2; i < key.length(); i++){
        s += key[i];
    }
    return s;
}
//
int hashLoc (string key, HashTable * ht){
	int i, sum, length, power10, digit;
	string s = removePrefix(key);
	
	char * c = new char[s.length() + 1];
    strcpy(c, s.c_str());
    // taken from COMP1602 notes : function toint
 	length = strlen (c);
 	sum = 0;
 	power10 = 1;

	for (i=length-1; i>=0; i=i-1) {
 		digit = c[i] - '0';
 		sum = sum + (digit * power10);
 		power10 = power10 * 10;
 	}
 	
 return (sum % ht->sizeTable)+1; 
}
//
HashTable * initHashTable (int sizeTable) {
	HashTable * hashTable = new HashTable;
   
    for (int i = 0; i < sizeTable; i++){
        hashTable->elements[i] = EMPTY;
    }
     hashTable->sizeTable = sizeTable;
    return hashTable;
}
//
void insertHT (HashTable * ht, Movie movie) {
  	int found =  containsHT (ht, movie.ID);
  	int loc = hashLoc (movie.ID, ht);
	if (found != -1){
		cout << "Movie is already present in the Database, cannot insert!!";
		return;
	} 	else{
		LLNode * newNode =  createNode(movie);
		
		if(ht->elements[loc]== EMPTY){
			ht->elements[loc] = newNode;
		}	else{
			newNode->next = ht->elements[loc];
			ht->elements[loc]=newNode;
		}
	}
	return;		
}
//
void deleteHT (HashTable * ht, string key) {
	int index = hashLoc(key, ht);
    LLNode * curr = ht->elements[index];
    LLNode * prev = EMPTY;
    while (curr != EMPTY){
        if (curr->data.ID == key){
            if (prev == EMPTY){
                ht->elements[index] = curr->next;
            }
            else{
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
	return;
}
//
int containsHT (HashTable * ht, string key) {	
	int index = hashLoc(key, ht);
	if(ht->elements[index]== EMPTY)
		return -1;
	else{
    	LLNode * curr = ht->elements[index];
    	while (curr != EMPTY){
       		if (curr->data.ID == key){
            	return index;
        	}
        curr = curr->next;
    	}
	}
    return -1;
}
//
int lengthChain (HashTable * ht, int location) {
	LLNode * curr = ht->elements[location];
    int count = 0;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}
//
void displayMovie (HashTable * ht, int location, string key) {
	 LLNode * curr = ht->elements[location];
    while (curr != NULL){
        if (curr->data.ID == key){
            cout << "ID: " << curr->data.ID << endl;
            if (curr->data.title == "999"){
            	cout << "Title: Data not available " << endl;
			}else {
				cout << "Title: " << curr->data.title << endl;
			}
            if (curr->data.yearReleased == 999){
            	cout << "Year: Data not available " << endl;
			}else {
				cout << "Year: " << curr->data.yearReleased << endl;
			}
            if (curr->data.duration == 999){
            	cout << "Duration: Data not available " << endl;
			}else {
				cout << "Duration: " << curr->data.duration << endl;
			}
            if (curr->data.genre == "999"){
            	cout << "Genre: Data not available " << endl;
			}else {
				cout << "Genre: " << curr->data.genre << endl;
			}
            return;
        }
        curr = curr->next;
    }
    return;
}
//
void statistics (HashTable * ht) {
	int count = 0;
    int countEmpty = 0;
    int longestChain = 0;
    for (int i = 0; i < ht->sizeTable; i++){
        if (ht->elements[i] != EMPTY){
            count++;
            int length = lengthChain(ht, i);
            if (length > longestChain){
                longestChain = length;
            }
        }
        else{
            countEmpty++;
        }
    }
    cout << "Number of locations in the hash table that are filled: " << count << endl;
    cout << "Number of locations that are empty: " << countEmpty << endl;
    cout << "Length of the longest chain: " << longestChain << endl;
	return;
}		
