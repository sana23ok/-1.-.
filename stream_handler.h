#include<iostream>
#include<string>
using namespace std;

string start();

void writeInFile(ofstream&);

void readFromFile(ifstream&);

string strClear(char[], string, int);

void compare(string[], int);

string rearange(const string&);

int checkPunct(char[], int);

void convertToCharArr(string, char[], int&);

void get_sent(istream&, string[], int&);

void writeInFile(ofstream&, string[], int);

void startEditing(string);

void edit(string);

void task(string);

void createNewFile(ifstream&, const string&);

void startStreamHandling();

