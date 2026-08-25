# Compresión de archivos con Huffman

Esta carpeta contiene un proyecto de **codificación y decodificación Huffman** desarrollado en C. El programa analiza la frecuencia de los caracteres de un archivo, construye un árbol binario de Huffman mediante un **Min-Heap**, genera códigos binarios de longitud variable y guarda el resultado en un archivo comprimido.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `codifica.c` | Analiza frecuencias, construye el árbol, genera el diccionario y produce el archivo comprimido. |
| `decodifica.c` | Reconstruye el árbol a partir de la cabecera del archivo binario y recupera el texto original. |
| `Documentacion.md` | Explicación detallada de estructuras y funciones del proyecto. |
| `Makefile` | Automatiza la compilación. |
| `mi-mensaje.txt` | Archivo de texto usado como ejemplo. |
| `comprimido.bin` | Ejemplo de archivo generado por el codificador. |

## Estructuras principales

### `Nodo`

Representa un nodo del árbol de Huffman y almacena:

- `caracter`
- `frecuencia`
- apuntadores `izq` y `der`

### `MinHeap`

Se utiliza como cola de prioridad para mantener accesibles los nodos con menor frecuencia. Incluye el tamaño actual, la capacidad y un arreglo de apuntadores a nodos.

## Proceso de codificación

1. `procesarArchivoTexto()` recorre el archivo y cuenta la frecuencia de cada carácter.
2. `crearYConstruirMinHeap()` crea el montículo mínimo.
3. `construirArbolHuffman()` extrae repetidamente los dos nodos menos frecuentes, los une en un nuevo nodo y lo reinserta.
4. `generarDiccionario()` recorre el árbol: izquierda agrega `0` y derecha agrega `1`.
5. `comprimirYGuardar()` almacena una cabecera con la información necesaria para reconstruir el árbol y después empaqueta los bits en bytes.

## Proceso de decodificación

El decodificador lee la cabecera del archivo, reconstruye el mismo árbol de Huffman y procesa cada bit. Un `0` mueve el recorrido hacia el hijo izquierdo y un `1` hacia el derecho. Al llegar a una hoja se recupera el carácter y se reinicia el recorrido desde la raíz.

## Complejidad

Sea `N` el número de caracteres del archivo y `k` el número de símbolos distintos:

| Etapa | Complejidad aproximada |
| :--- | :--- |
| Conteo de frecuencias | O(N) |
| Construcción inicial del heap | O(k) |
| Construcción del árbol | O(k log k) |
| Generación de códigos | O(k) sobre los nodos del árbol, sin contar longitud de las cadenas de código |
| Codificación | Proporcional al número de bits generados |
| Decodificación | Proporcional al número de bits del archivo comprimido |

## Compilación y uso

Con el `Makefile`:

```bash
cd Proyecto_Huffman
make
```

También puede compilarse manualmente:

```bash
gcc codifica.c -o codifica
gcc decodifica.c -o decodifica
```

Ejemplo:

```bash
./codifica mi-mensaje.txt comprimido.bin
./decodifica comprimido.bin
```

## Documentación ampliada

Para una explicación función por función puede consultarse `Documentacion.md`, que describe la creación de nodos, las operaciones del Min-Heap, la construcción del árbol y los procesos de codificación y decodificación.

## Conclusiones

Huffman combina varias estructuras estudiadas durante el curso: árboles binarios, montículos mínimos, colas de prioridad, recursividad y manejo de archivos binarios. El proyecto muestra cómo una elección algorítmica basada en frecuencias permite asignar códigos cortos a los símbolos más comunes y reducir el tamaño del contenido almacenado.
