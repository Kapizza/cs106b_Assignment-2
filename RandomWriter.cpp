/*
* File: RandomWriter.cpp
* ----------------------
* Name: Daviti Gochitashvili
* Section: 9
* This file is the starter project for the Random Writer problem.
* [TODO: rewrite the documentation]
*/

#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include <string>
#include "random.h"
#include <fstream>
using namespace std;

/* Constant */
const int numberOfSymbols = 2000;

/* Function prototypes */
int getMarkovNum();
string mostOftenSeq(Map<string, Vector <char> > map);
string generatedRandomText(Map<string, Vector <char> > map);
string readFromFile();
Map<string, Vector <char> > fillMap(int markovNum, string text);


/* Main program */
int main() {
	string text = readFromFile();
	int markovNum = getMarkovNum();
	cout <<"Processing file..."<< endl;
	Map<string, Vector <char> > map = fillMap(markovNum, text);
	cout << generatedRandomText(map) << endl;
	return 0;
}

/* 
This method asks user to enter number for Markov order;
If invalid number is entered asks to enter againg.
*/
int getMarkovNum(){
	int num = getInteger("Enter Markov order [1-10]: ");
	while(num>10 || num <1){
		cout <<"That value is out of range. " << endl;
		num = getInteger("Enter Markov order [1-10]: ");
	}
	return num;
}

/* 
This method finds and returns most often sequence of symbols in map.
*/
string mostOftenSeq(Map<string, Vector <char> > map){
	int size = 0;
	string res;
	foreach (string str in map){
		if(map[str].size()>size){
			size=map[str].size();
			res=str;
		}
	}
	return res;
}

/* 
This method generates and returns random text using markov algorithm.
*/
string generatedRandomText(Map<string, Vector <char> > map){
	string res = mostOftenSeq(map);
	int markovNum = res.length();
	for(int i=0; i < numberOfSymbols-markovNum; i++){
		string seed = res.substr(i);
		if(!map.containsKey(seed)) break;
		int index = randomInteger(0,map[seed].size()-1);
		res = res + map[seed].get(index);
	}
	return res;
}

/* 
This method asks use to enter file name, than reads it and returns as a string.
*/
string readFromFile(){
	ifstream file;
	promptUserForFile(file, "Please enter file name: ");
	char c;
	string text;
	while(file.get(c)){
		text+=c;
	}
	return text;
}

/* 
This method fills map. Key of map is all symbol sequences of markov number 
lenght in given text. Value is vector of symbols which come after key sequence.
*/
Map<string, Vector <char> > fillMap(int markovNum, string text){
	Map<string, Vector <char> > map;
	for(int i=0; i < text.length()-markovNum; i++){
		string seed = text.substr(i,markovNum);
		char sym = text[i+markovNum];
		if(!map.containsKey(seed)){
			Vector <char> symbols;
			map.put(seed, symbols);
		}
		map[seed].add(sym);		
	}
	return map;
}