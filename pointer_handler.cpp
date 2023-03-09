#include "pointer_handler2.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
using namespace std;
const int MAX = 1024;

void showRecords(FILE *file) {
    char str[MAX];
    fseek(file, 0, 0);
    char dot = '.';
    int iter=1;

    if (fgets(str, MAX, file) != nullptr) {
        fseek(file, 0, 0);
        cout<<"------------- Records ------------- \n";
        while (fgets(str, MAX, file)) {
            cout<<iter<<dot<<str;
            iter++;
        }
        cout<<"\n-----------------------------------\n";
    } else {
        cout<<"File is empty.\n\n";
    }

}

void sort(char **mass, size_t num){
    int i,j;
    for(i=0;i<num-1;i++)
        for(j=i+1;j<num;j++)
            if (strcmp(mass[i],mass[j]) >0 ){
                char *tmp;
                tmp=mass[i];
                mass[i]=mass[j];
                mass[j]=tmp;
            }
}

void delete_char(char *arr, int index){
    int len = strlen(arr);
//    if (index < 0 || index > len) {
//        printf("Invalid index\n");
//        return;
//    }
    for (int i = index; i < len - 1; i++) {
        arr[i] = arr[i+1];
    }
    arr[len-1] = '\0';
}

void convertLine(char line[], int &i){
    while(line[i]!='\n'){
        if(isupper(line[i])){
            char temp = tolower(line[i]);
            line[i]=temp;
        }
        i++;
        if(ispunct(line[i])){
            delete_char(line, i);
            i--;
        }
    }
}

void arrange(FILE* nfile, char *line, size_t n, int size){
    char* rest = line;
    char** table = (char**) malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        table[i] = (char*) malloc(sizeof(char) * MAX);
    }

    int a = 0;
    char* token;
    while ((token = strtok_r(rest, " ", &rest))) {
        strcpy(table[a], token);
        a++;
    }

    char result[MAX] = "";
    char *temp = nullptr;

    sort(table, a);

    int t=0;
    while (t<a) {
        temp = table[t];
        int len = strlen(temp);
        if (len > 0 && temp[len - 1] == '\n'){
            temp[len - 1] = '\0';
        }
        char space[] = " ";
        strcat(temp, space);
        strcat(result, temp);
        t++;
    }
    //printf("Result: %s\n", result);
    fprintf(nfile, "%s\n", result);
    for (int i = 0; i < n; i++) {
        free(table[i]);
    }
    free(table);
    char myArray[MAX];
    strcpy(myArray, result);
}

void checkLine(FILE* nfile, char *line, int fileLen){
    size_t len = strlen(line);
    if(line[len-2]=='.'){
        int lenC=0;
        convertLine(line, lenC);
        arrange(nfile, line, lenC, fileLen);//len-2
    }
}

void workWithRec(FILE* file, char name[]){
    char *line = (char*)malloc(sizeof(char)*MAX);
    int size=0;
    char ch;
    file = fopen(name, "r");
    if (file != nullptr) {
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                size++;
            }
        }
    }else{
        printf("Error opening file");
    }

    char nameN[MAX] = "new_";
    strcat(nameN, name);

    FILE *filePtr;
    filePtr = fopen(nameN, "w+");
    if (filePtr != nullptr) {
        int count = 1;
        fseek(file, 0, 0);
        while (fgets(line, MAX, file) != nullptr) {
            if((count%2)!=0){
                checkLine(filePtr, line, size);
            }
            count++;
        }
    } else {
        cout<<"Error. Try again...\n\n";
    }

    showRecords(filePtr);
    free(line);
    fclose(filePtr);
    fclose(file);
}

void editFilePrt(FILE* file, char name[]){
    fopen(name, "a+");
    fseek(file, 0, SEEK_END);
    char *line = (char*)(malloc(sizeof(char)*MAX));
    if (line == nullptr) {
        cout<<"Failed to allocate memory\n";
    }

    cout<<"Enter a line:";
    fgets(line, MAX, stdin);
    if (fgets(line, MAX, stdin) != nullptr) {
        fprintf(file, "%s", line);
    } else {
        cout<<"Failed to read input\n";
    }
    cout<<"Changed file:"<<endl;
    showRecords(file);
    free(line);
    fclose(file);

}

void fillFile(FILE* file, char name[]){
    file = fopen(name, "w+");
    char *line = (char*)(malloc(sizeof(char)*MAX)); // allocate memory for the line
    if (line == nullptr) {
        cout<<"Failed to allocate memory\n";
    }
    char ch;
    cout<<"Enter a lines(hit 'Enter' and press '*' to stop entering text):";
    do{
        if (fgets(line, MAX, stdin) != nullptr) { // read input from stdin
            ch = line[0];
            if(ch == '*') break;
            fprintf(file, line, "%s");
        } else {
            std::cout<<"Failed to read input\n";
        }
    }while(true);

    cout<<"Created file:"<<endl;
    showRecords(file);
    free(line);

    char answ;
    do{
        cout<<"\nDo you want to add text to the file?[Y/N]";
        cin>>answ;
        if(answ!= 'Y' && answ!= 'y') break;
        editFilePrt(file, name);
    }while(true);
    workWithRec(file, name);
    fclose(file);
}

void enterName(char name[]){
    cout<<"\nEnter a name of the file:";
    scanf("%s", name);
    strcat(name, ".txt");
    fflush(stdin);
}

void createFilePtr(FILE *file, char name[]){
    file = fopen(name, "r+");
    if(file == nullptr){
        FILE* cr;
        cr = fopen(name, "r");
        if (cr == nullptr) {
            file = fopen(name, "w");
            if (file != nullptr) {
                cout<<"Created successfully!!!\n\n";
                fillFile(file, name);
            } else {
                cout<<"Error. Try again...\n\n";
            }
            fclose(file);
        }
    }else{
        cout<<"\nThe file with that name already exists.\n";
        cout<<"Content from the file:";
        showRecords(file);
        char answ;
        do{
            cout<<"\nDo you want to add text to the file?[Y/N]";
            cin>>answ;
            if(answ!= 'Y' && answ!= 'y') break;
            editFilePrt(file, name);
        }while(true);
        workWithRec(file, name);
    }
}

void startPointerHandling(){
    char fileName[MAX];
    FILE *file = nullptr;
    enterName(fileName);
    createFilePtr(file, fileName);
}
