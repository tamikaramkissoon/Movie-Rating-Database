#include <iostream>
#include <fstream>
#include <windows.h>
#include "Hashtable.h"

using namespace std;

#define QUIT 7

void showVideo (string URL);
int readFile (HashTable * MovieDatabase);
void menu ();
void option1 (HashTable * ht);
void option2 (HashTable * ht);
void option3 (HashTable * ht);
void option4 (HashTable * ht);
void option5 (HashTable * ht);
void option6 (HashTable * ht);
void option7 ();

void showVideo (string URL) {
	char cURL [150];
	int i;

	for (i = 0; i < URL.length(); i=i+1){
    	cURL[i] = URL[i];
	}

	cURL[URL.length()] = '\0';
    
    ShellExecute(NULL, "open", cURL, NULL, NULL, SW_SHOWNORMAL);
}


int readFile (HashTable * MovieDatabase){
	
	string ID = "";
	int numMovies =0;
	ifstream input;
	input.open("Movies.txt");
	Movie movie;
	movie.duration=0;
	movie.genre="";
	movie.ID="";
	movie.title="";
	movie.yearReleased=0;
	string temp_str = "";
		// if statement to check whether the input file was successfully opened.
	if (!input.is_open())
	{
		cout << "There was an error opening the data file!  Operation aborting!!..." << endl;
		exit(1);
	}		
	
	input >> temp_str;
	while (temp_str != "END" ){
		movie.ID = temp_str;
		input >> movie.yearReleased; 
		input >> movie.duration;
		input >> movie.genre;
		getline (input, movie.title);
		insertHT (MovieDatabase, movie);
		input >> temp_str;
		numMovies++;
	}
	input.close();
	return numMovies;
}
void option1 (HashTable * ht){
	Movie movie;
	movie.duration=0, movie.genre="", movie.ID="", movie.title="", movie.yearReleased=0;
	
	cout << "	Please provide the details of the movie you wish to enter into the database" <<endl;
	cout << "Movie Id: ";
	cin >> movie.ID;
	int found = containsHT (ht, movie.ID);
	if (found != -1){
		cout << " The movie is already in the database, movie cannt be inserted!!" <<endl;
		system("pause");
		return;
	}else if (found == -1){
		cout << "Movie Year Release: ";
		cin >> movie.yearReleased;
		cin.ignore();
		cout << "Movie Duration: ";
		cin >> movie.duration;
		cin.ignore();
		cout << "Movie genre: ";
		cin >> movie.genre;
		cin.ignore();
		cout << "Movie Title: ";
		getline(cin, movie.title);
		insertHT (ht, movie);
	}
	system("pause");
}

void option2 (HashTable * ht){
	string ID = "";
	cout << "Please enter the ID of the movie you wish to find ";
	cin >> ID;
	int found = containsHT (ht, ID);
	if (found != -1){
		displayMovie (ht, found, ID);
	}else {
		cout << "This movie is not found in the movie database " <<endl;
	}
	system("pause");
}
// assuming the value of the chain means the location of the chain containing the ID or the value of the chain means the length of the chain containing the 
// ID. The option 3 function displays both assumptions.
void option3 (HashTable * ht){
	string ID = "";
	cout << "Please enter the ID of the movie ";
	cin >> ID;
	int found = containsHT (ht, ID);
	if (found != -1){
		cout << "The movie is found at location/value " << found << " in the movie database " << endl;
		int length = lengthChain (ht, found);
		cout << "The length/value of the chain containing the movie is " << length << endl;
	}else {
		cout << "The movie was not found in the movie database value of chain is " << found <<endl;
	}
	system("pause");	
}
void option4 (HashTable * ht){
	string ID = "";
	cout << "Please enter the ID of the movie you wish to delete ";
	cin >> ID;
	int found = containsHT (ht, ID);
	if (found != -1){
		deleteHT (ht, ID);
		cout << "Movie deleted!! " <<endl;
	}else{
		cout << "The movie was not found in the movie database, delete operation aborted!!" << endl;
	}
	system("pause");
}
void option5 (HashTable * ht){
	statistics (ht);
	system("pause");
}
void option6 (HashTable * ht){
	string ID = "";
	cout << "Please enter the ID of the movie you wish to view ";
	cin >> ID;
	int found = containsHT (ht, ID);
	if (found != -1){
		string view = "https://imdb.com/title/"+ ID;
		showVideo (view);
	}else{
		cout << "The movie was not found in the movie database, cannot view!!" << endl;
	}
	system("pause");	
}
void option7 (){	
	system("cls");
	cout << "MENU QUIT\n";
	cout << "\n\n\n\t\tEND OF COMP2611 ASSIGNMENT 3";
}

void menu () {

	system("cls");
	cout << "\n\n	Please select you menu option!!" << endl;
	cout << "1. Insert a movie in the hash table." << endl;
	cout << "2. Check if the hash table contains a movie." << endl;
	cout << "3. Check the length of the list containing a movie." << endl;
	cout << "4. Delete a movie from the database." << endl;
	cout << "5. Display statistics of hash table." << endl;
	cout << "6. Load IMDB web page for a movie." << endl;
	cout << "7. Quit" << endl;
	
}

int main () {
	HashTable * MovieDatabase = initHashTable (29501);
	int numMovies = readFile (MovieDatabase);

	int choice = 1;
	
	while (choice != QUIT){
		menu();
		cin	>> choice;
		// OPTION 1
		if(choice == 1){
		//function call
			option1 (MovieDatabase);
		//OPTION 2
		} else if (choice == 2){
		//function call
			option2(MovieDatabase);
		//OPTION 3	
		}else if(choice == 3){
		//function call
		option3(MovieDatabase);
		//OPTION 4		
		}else if (choice == 4){
		//function call
			option4(MovieDatabase);
		//OPTION 5	
		}else if (choice == 5){
		//function call
			option5(MovieDatabase);
		//OPTION 6	
		}else if (choice == 6){
			//function call
			option6(MovieDatabase); 
		}
	}
	if (choice == 7){
		option7();
	}		
	return 0;
}
