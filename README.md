# Compresor y Descompresor de Archivos con RLE

## Descripción
Este programa implementa un sistema de compresión y descompresión de archivos utilizando el algoritmo **Run-Length Encoding (RLE)**. Se han utilizado llamadas al sistema de archivos en Linux, como `open()`, `read()`, `write()` y `close()`, para gestionar los archivos sin librerías externas.

## Algoritmo de Compresión
El **Run-Length Encoding (RLE)** es un algoritmo de compresión sin pérdida que funciona contando la cantidad de veces que un carácter se repite consecutivamente y almacenando esa información en lugar del texto original.

Ejemplo:
```
Entrada:  aaaaabbbbcc
Salida:   5a4b2c
```

Esto reduce el tamaño del archivo en caso de datos con muchas repeticiones.

## Uso del Programa

### Comandos Disponibles
El programa acepta argumentos de línea de comandos para ejecutar diferentes operaciones:

- `-h`, `--help` → Muestra la ayuda.
- `-v`, `--version` → Muestra la versión del programa.
- `-c <archivo>` → Comprime el archivo indicado.
- `-x <archivo>` → Descomprime el archivo indicado.

### Ejemplos de Uso

#### Comprimir un archivo
```
./compresor -c archivo.txt
```
Esto generará un archivo comprimido `archivo.txt.rle`.

#### Descomprimir un archivo
```
./compresor -x archivo.txt.rle
```
Esto generará un archivo descomprimido `archivo.txt.rle.decompressed`.

#### Mostrar ayuda
```
./compresor -h
```

#### Mostrar versión
```
./compresor -v
```

## Consideraciones
- El programa está diseñado para archivos **binarios**, ya que este formato suele contener secuencias repetitivas (por ejemplo, `001101011`), lo que hace que el uso de RLE sea más eficiente. También puede aplicarse a archivos de texto, aunque su efectividad depende del contenido.
- El método RLE es eficiente en archivos con muchas repeticiones, pero puede no ser útil en archivos sin patrones repetitivos.

## Futuras Mejoras
- Soporte para archivos binarios.
- Implementación de cifrado con `-e` y `-d`.
- Más algoritmos de compresión para mejorar la eficiencia.

