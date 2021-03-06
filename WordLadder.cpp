/*
* File: WordLadder.cpp
* --------------------------
* Name: Daviti Gochitashvili
* Section: 9
* This file is the starter project for the Word Ladder problem.
* [TODO: rewrite the documentation]
*/

#include <iostream>
#include "queue.h"
#include "console.h"
#include "set.h"
#include "simpio.h"
#include <string>
#include "lexicon.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
void searchLadder(string startingWord, string endingWord, Lexicon words);
void printLadder(Vector <string> ladder);

/* Main program */
/*
Makes word ladders untill empty string is not entered as a starting word.
*/
int main() {
	Lexicon words("EnglishWords.dat");
	while(true){
		string startingWord = getLine("Enter the starting word (or nothing to quit): ");
		if(startingWord.length()>0){
			string endingWord = getLine( "Enter the ending word: " );
			searchLadder(startingWord,endingWord, words);
		} else {
			cout<< "Goodbye" <<endl;
			break;
		}
	}
	return 0;
}

/*
This method searchs for ladder of words using given algorithm.
*/
void searchLadder(string startingWord, string endingWord, Lexicon words){
	//Create an empty queue.
	Queue <Vector <string> > queue;
	Vector <string> ladder;
	Set<string> usedWords;
	//Add the start word to the end of the queue.
	ladder.add(startingWord);
	queue.enqueue(ladder);
	bool foundLadder = false;
	cout << "Searching..." << endl;
	//while the queue is not empty.
	while(!queue.isEmpty()){
		if(startingWord.length()!=endingWord.length()) break;
		//Dequeue the first ladder from the queue.
		Vector <string> currentLadder = queue.dequeue();
		string str = currentLadder.get(currentLadder.size()-1);
		//If the final word in this ladder is the destination word.
		if(str==endingWord){
			//Return this ladder as the solution.
			foundLadder = true;
			printLadder(currentLadder);
			break;
		}
		//for each word in the lexicon of English words that differs by one letter.
		for(int i=0; i < str.length(); i++){
			for (char ch = 'a'; ch <= 'z'; ch++) {
				string substituted = str.substr(0,i)+ch+str.substr(i+1,str.length()-i);
				//if that word has not already been used in a ladder.
				if(words.contains(substituted) && !usedWords.contains(substituted)){
					usedWords.add(substituted);
					//Create a copy of the current ladder.
					Vector <string> copy = currentLadder;
					//Add the new word to the end of the copy.
					copy.add(substituted);
					//Add the new ladder to the end of the queue.
					queue.enqueue(copy);
				}
			}
		}		
	}
	//Report that no word ladder exists.
	if(!foundLadder){
		cout << "No word ladder could be found." << endl;
	}
}

/* 
This method just iterates over Vector of words sequence and prints it.
*/
void printLadder(Vector <string> ladder){
	string res = "Ladder found: ";
	foreach (string word in ladder){
		res = res + word + " -> ";
	}
	cout << res.substr(0,res.length()-4) << endl;
}