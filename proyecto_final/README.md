# Proyecto final — Compresor y descompresor Huffman

Esta carpeta contiene la versión entregable del **proyecto final de compresión Huffman**. El sistema está formado por un programa de codificación y otro de decodificación, además de documentación, archivos de ejemplo y ejecutables generados durante las pruebas.

## Archivos principales

| Archivo | Descripción |
| :--- | :--- |
| `codifica.c` | Construye el árbol Huffman y genera el archivo comprimido. |
| `decodifica.c` | Reconstruye el árbol y recupera el contenido original. |
| `Documentacion.md` | Explicación detallada de estructuras y funciones. |
| `Makefile` | Reglas de compilación del proyecto. |
| `mi-mensaje.txt` | Archivo de entrada utilizado como ejemplo. |
| `comprimido.bin` | Archivo binario generado por el codificador. |
| `codifica`, `decodifica`, `arbol` | Archivos ejecutables o auxiliares guardados junto con la entrega. |

## Objetivo

Aplicar estructuras de datos y análisis de algoritmos en un programa completo capaz de comprimir texto mediante códigos Huffman y posteriormente reconstruirlo.

## Flujo del sistema

```text
Archivo de texto
      |
      v
Conteo de frecuencias
      |
      v
Construcción del Min-Heap
      |
      v
Árbol de Huffman
      |
      v
Diccionario de códigos 0/1
      |
      v
Archivo binario comprimido
      |
      v
Lectura de cabecera + reconstrucción del árbol
      |
      v
Decodificación del contenido
```

## Estructuras utilizadas

- `Nodo`: representa los nodos del árbol, con carácter, frecuencia y enlaces izquierdo/derecho.
- `MinHeap`: funciona como cola de prioridad para extraer los caracteres o subárboles con menor frecuencia.
- `diccionario`: relaciona cada carácter con el código binario generado por su recorrido dentro del árbol.

## Codificación

El codificador cuenta las frecuencias del archivo, construye el árbol de Huffman, genera los códigos y después empaqueta los bits en bytes. El archivo comprimido incluye una cabecera con el número total de caracteres, el tamaño del alfabeto y las frecuencias necesarias para reconstruir el árbol durante la decodificación.

## Decodificación

El decodificador lee la cabecera, reconstruye el árbol y recorre cada bit del archivo. Los bits `0` y `1` determinan el movimiento hacia la izquierda o derecha. Cuando se alcanza una hoja se recupera el carácter correspondiente.

## Complejidad

Sea `N` la cantidad de caracteres y `k` la cantidad de símbolos diferentes:

- Conteo de frecuencias: **O(N)**.
- Construcción del árbol con heap: **O(k log k)**.
- Codificación: proporcional al total de bits emitidos.
- Decodificación: proporcional al total de bits leídos.

Para alfabetos pequeños, el costo dominante suele ser recorrer el contenido del archivo.

## Compilación

```bash
cd proyecto_final
make
```

O manualmente:

```bash
gcc codifica.c -o codifica
gcc decodifica.c -o decodifica
```

Ejemplo:

```bash
./codifica mi-mensaje.txt comprimido.bin
./decodifica comprimido.bin
```

## Documentación completa

El archivo `Documentacion.md` contiene una explicación más extensa de `nuevoNodo()`, `minHeapify()`, `extraerMinimo()`, `insertarMinHeap()`, `construirArbolHuffman()`, `generarDiccionario()` y del proceso de lectura/escritura binaria.

## Conclusiones

El proyecto final integra varios conceptos vistos durante la materia dentro de una aplicación funcional. El árbol de Huffman utiliza frecuencias para producir códigos de longitud variable y el Min-Heap permite seleccionar eficientemente los elementos de menor frecuencia mientras se construye el árbol.
