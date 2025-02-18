#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>

#define BUFFER_SIZE 1024 // Tamaño del búfer para leer el archivo

// Función para comprimir un archivo usando Run-Length Encoding (RLE)
void compressFile(const char* inputFile, const char* outputFile) {
    int inFd = open(inputFile, O_RDONLY); // Abrir archivo de entrada en modo solo lectura
    if (inFd < 0) {
        perror("Error opening input file"); // Imprimir error si no se puede abrir
        return;
    }
    
    int outFd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Crear archivo de salida
    if (outFd < 0) {
        perror("Error opening output file"); // Imprimir error si no se puede abrir
        close(inFd);
        return;
    }
    
    char buffer[BUFFER_SIZE]; // Búfer para almacenar datos leídos del archivo
    ssize_t bytesRead;
    
    // Leer el archivo en bloques de BUFFER_SIZE
    while ((bytesRead = read(inFd, buffer, BUFFER_SIZE)) > 0) {
        std::vector<char> compressed;
        for (ssize_t i = 0; i < bytesRead;) {
            char currentChar = buffer[i]; // Carácter actual a comprimir
            int count = 1;
            
            // Contar cuántas veces seguidas aparece el mismo carácter
            while (i + count < bytesRead && buffer[i + count] == currentChar && count < 255) {
                count++;
            }
            
            // Guardar el número de repeticiones y el carácter
            compressed.push_back(count);
            compressed.push_back(currentChar);
            
            i += count; // Avanzar al siguiente carácter diferente
        }
        
        // Escribir los datos comprimidos en el archivo de salida
        write(outFd, compressed.data(), compressed.size());
    }
    
    close(inFd); // Cerrar archivo de entrada
    close(outFd); // Cerrar archivo de salida
}

// Función para descomprimir un archivo comprimido con RLE
void decompressFile(const char* inputFile, const char* outputFile) {
    int inFd = open(inputFile, O_RDONLY); // Abrir archivo comprimido en modo lectura
    if (inFd < 0) {
        perror("Error opening input file");
        return;
    }
    
    int outFd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // Crear archivo de salida
    if (outFd < 0) {
        perror("Error opening output file");
        close(inFd);
        return;
    }
    
    char buffer[2]; // Búfer para leer los pares (número de repeticiones, carácter)
    
    // Leer el archivo comprimido de dos en dos bytes
    while (read(inFd, buffer, 2) == 2) {
        int count = static_cast<unsigned char>(buffer[0]); // Número de repeticiones
        
        // Escribir el carácter el número de veces indicado
        for (int i = 0; i < count; i++) {
            write(outFd, &buffer[1], 1);
        }
    }
    
    close(inFd);
    close(outFd);
}

int main(int argc, char* argv[]) {
    if (argc < 2) { // Verificar que se haya ingresado al menos un argumento
        std::cerr << "Uso: " << argv[0] << " [opciones]" << std::endl;
        return 1;
    }
    
    std::string opcion = argv[1];
    
    // Mostrar ayuda
    if (opcion == "--help" || opcion == "-h") {
        std::cout << "Uso: " << argv[0] << " [opciones]" << std::endl;
        std::cout << "  --help, -h       Muestra esta ayuda" << std::endl;
        std::cout << "  --version, -v    Muestra la versión" << std::endl;
        std::cout << "  -c <archivo>     Comprime el archivo indicado" << std::endl;
        std::cout << "  -x <archivo>     Descomprime el archivo indicado" << std::endl;
        return 0;
    }
    // Mostrar versión
    else if (opcion == "--version" || opcion == "-v") {
        std::cout << "Versión 1.0" << std::endl;
        return 0;
    }
    // Compresión
    else if (opcion == "-c" && argc == 3) {
        std::string outputFile = std::string(argv[2]) + ".rle";
        compressFile(argv[2], outputFile.c_str());
    }
    // Descompresión
    else if (opcion == "-x" && argc == 3) {
        std::string outputFile = std::string(argv[2]) + ".decompressed";
        decompressFile(argv[2], outputFile.c_str());
    } else {
        std::cerr << "Opción desconocida o parámetros incorrectos. Use -h para ayuda." << std::endl;
        return 1;
    }
    
    return 0;
}
