#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include "../include/scss.h"

substr *readFile(char *);

int main(int argc, char** argv) {

    substr *fileData;

    if(argc < 2) {
        printf("Usage: %s <fileName>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    fileData = readFile(filename);

    printf("File size: %d\n", fileData->length);

}

substr *readFile(char *fileName) {

    FILE *fileHandle;
    struct stat fileStat;
    int fileSize;
    substr *fileData;

    fileHandle = fopen(fileName, "r");
    if(stat(fileName, &fileStat) < 0) {
        printf("Error stat on filename: %s\n", fileName);
        exit(1);
    }

    fileData = malloc(sizeof(substr));
    if(!fileData) {
        printf("Error allocating memory\n");
        exit(1);
    }

    fileSize = fileStat.st_size;
    fileData->substring = malloc(fileSize);
    if(!fileData->substring) {
        printf("Error allocating memory\n");
        exit(1);
    }

    fread(fileData->substring, sizeof(char), fileSize, fileHandle);
    fileData->index = 0;
    fileData->length = fileSize;

}