#ifndef RLE_H
#define RLE_H

#include <iostream>
#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>

// Función para comprimir un archivo usando RLE
void compressFile(const char* inputFile, const char* outputFile);

// Función para descomprimir un archivo comprimido con RLE
void decompressFile(const char* inputFile, const char* outputFile);

#endif // RLE_H
