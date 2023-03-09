#include<iostream>
#include<cstring>
#include "stream_handler.h"
#include "pointer_handler.h"

int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i<argc; i++){
        if (strcmp(argv[i], "-mode")==0) break;
    }

    if ((i+1)>= argc){
        std::cerr << "Unknown mode. Please, try again!\n";
        return 1;
    }

    char *mode = argv[i + 1];
    if (strcmp(mode, "FilePointer")==0){
        startPointerHandling();
    }else if (strcmp(mode, "FileStream")==0){
        startStreamHandling();
    }else{
        std::cerr << "Unknown mode. Please, try again!\n";
        return 1;
    }
    return 0;
}

