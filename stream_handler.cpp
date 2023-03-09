#include"stream_handler.h"
#include"pointer_handler.h"
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<filesystem>
const int MAX = 255;
using namespace std;

string start(){
    cout<<"Enter the name of the file:";
    string name;
    cin>>name;
    return name;
}

int checkFile(const string& filename){
    if (filesystem::exists(filename)) {
        cout << "The file exists!" <<endl;
        return 1;
    } else {
        return 0;
    }
}

void writeInFile(ofstream &file){
    cout<<"\nEnter records in file:(press 'Enter' and '*' if you want to stop):"<<endl;
    string line;
    int iter=0;
    if(file.is_open()){
        cin.ignore(256, '\n');
        do{
            cout<<"\nLine["<<iter+1<<"]:"<<endl;
            getline(cin, line);
            if(line == "*") break;
            file<<line<<endl;
            iter++;
        }while(1);
    }else{
        cout<<"Unable to write in file..."<<endl;
    }
}

void readFromFile(ifstream &file){
    string line;
    int iter=1;
    char dot = '.';
    if(file.is_open()){
        while (getline(file, line)){
            cout << iter << dot << line << endl;
            iter++;
        }
    }else{
        cout<<"An error of opening the file"<<endl;
    }
    file.close();
}

string strClear(char arr[], string s,  int size){
    int j=0;
    while (s[j]) {
        s[j] = tolower(arr[j]);
        j++;
    }

    for (int i = 0, len = s.size(); i < len; i++)
    {
        if (ispunct(s[i]))
        {
            s.erase(i--, 1);
            len = s.size();
        }
    }
    return s;
}

void compare(string arr[], int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(arr[i]<arr[j]){
                string temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

string rearange(const string& str){
    string splited[MAX];
    istringstream ss(str);
    string del;
    int i=0;
    while(getline(ss, del, ' ')) {
        splited[i] = del;
        i++;
    }

    compare(splited, i);
    cout<<endl;
    string ordered;
    for(int k=0; k<i; k++){
        ordered += splited[k];
        if(k!= i-1){
            ordered += " ";
        }
    }
    return ordered;
}

int checkPunct(char arr[], int size){
    if(/*(f!=0) && */ arr[size-1] == '.') return 1;
    else return 0;
}

void convertToCharArr(string line, char ch_arr[], int &len){
    len = line.length();
    ch_arr[len+1];
    strcpy(ch_arr, line.c_str());
    //convertLine(ch_arr, len);
}

void get_sent(istream &file, string rec[], int &j){
    string line;
    int i=1;

    while(getline(file, line)){
        if(i%2!=0){
            rec[j]=line;
            j++;
        }
        i++;
    }
}

void writeInFile(ofstream &file, string arr[], int size ){
    int i = 0;
    while(i<size){
        file<<arr[i]<<endl;
        i++;
    }
}

void addLine(string path){
    ofstream file;
    file.open(path, ios::app);
    cout<<"Enter the line that you want to append:\n";
    string line;
    if(file.is_open()){
        cin.ignore(256, '\n');
        getline(cin, line);
        file<<line<<endl;
    }else{
        cout<<"Unable to write in file..."<<endl;
    }
}

void startEditing(string path){
     addLine(path);
}

void edit(string path){
    char ch = 'y';
    do{
        cout<<"Do you want to add text to the file?[y/n]";
        cin>>ch;
        if((ch!='y')&&(ch!='Y')) break;
        startEditing(path);
    }while(true);
}

void task(string path){
    if(checkFile(path)==0){
        ofstream output;
        output.open(path);
        writeInFile(output);
        output.close();
    }

    ifstream file;
    file.open(path);
    if(file.is_open()) readFromFile(file);
    else cout<<"Error of reading the file";
    file.close();
}

void createNewFile(ifstream &infile, const string& name){
    string rec[MAX];
    string path= name + ".txt";
    string path_new = name + "_new.txt";
    infile.open(path);
    if(infile.is_open()) {
        int j = 0;
        get_sent(infile, rec, j);
        char arr[MAX];
        string updated[MAX];
        int len = 0;
        int k = 0;
        for (int i = 0; i < j; i++) {
            convertToCharArr(rec[i], arr, len);
            int res = checkPunct(arr, len);
//            cout<<rec[i];
            if (res) {
                string tmp = strClear(arr, rec[i], len);
                updated[k] = rearange(tmp);
                k++;
            }
        }

        ofstream nFile(path_new);
        if (nFile.is_open()) {
            writeInFile(nFile, updated, k);
            cout << "------------Records from new file:-------------" << endl;
            nFile.close();
            ifstream rNew(path_new);
            if (rNew.is_open()) readFromFile(rNew);
            else cout << "Error of reading from new file";
            rNew.close();
        } else {
            cout << "Error of reading from input file" << endl;
        }
        nFile.close();
    }
    infile.close();
}

void startStreamHandling(){
    string name = start();
    string path = name + ".txt";
    //open for writing in file
    task(path);
    edit(path);
    //open for reading
    ifstream input;
    input.open(path);
    cout<<endl<<"----------------Records----------------"<<endl;
    readFromFile(input);
    createNewFile(input, name);
    input.close();
}

