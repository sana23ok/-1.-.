#include <cstdio>

#include "pointer_handler2.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAX = 1024;

void showRecords(FILE*);

void sort(char **, size_t);

void delete_char(char*, int);

void convertLine(char[], int&);

void arrange(FILE*, char*, size_t, int);

void checkLine(FILE*, char*, int);

void workWithRec(FILE*, char[]);

void editFilePrt(FILE*, char[]);

void fillFile(FILE*, char[]);

void enterName(char[]);

void createFilePtr(FILE *, char[]);

void startPointerHandling();

