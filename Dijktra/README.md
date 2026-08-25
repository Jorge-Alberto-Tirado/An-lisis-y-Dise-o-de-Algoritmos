# Caminos mínimos con Dijkstra — Búsqueda lineal y Min-Heap

Esta carpeta contiene dos implementaciones del algoritmo de **Dijkstra** para calcular las distancias mínimas desde un vértice origen hacia los demás vértices de un grafo ponderado. El objetivo principal fue comparar dos formas de seleccionar el siguiente vértice con menor distancia: una búsqueda lineal y una cola de prioridad implementada con un **Min-Heap**.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `Dijkstra_lineal.c` | Implementación de Dijkstra donde el mínimo se busca recorriendo linealmente los vértices pendientes. |
| `Dijkstra_queue.c` | Implementación de Dijkstra utilizando un `MinHeap`, con operaciones como `extractMin`, `decreaseKey` y `minHeapify`. |
| `MatrizGenerada.csv` | Matriz de adyacencia ponderada usada como entrada para las pruebas. |
| `resultadosLineal.csv` | Resultados experimentales de la versión lineal. |
| `resultadosQueue.csv` | Resultados experimentales de la versión con Min-Heap. |

## Funcionamiento general

Las dos versiones inicializan los arreglos `dist` y `pi`, colocando la distancia del vértice origen en cero y el resto en infinito. Después se selecciona repetidamente el vértice pendiente con menor distancia y se revisan todas las posiciones de su fila en la matriz de adyacencia para realizar las relajaciones correspondientes.

La diferencia principal está en la forma de obtener el mínimo:

- En `Dijkstra_lineal.c`, `extractMinLineal()` recorre los vértices pendientes y selecciona el de menor distancia.
- En `Dijkstra_queue.c`, los vértices se mantienen dentro de un `MinHeap`. La raíz contiene el menor valor y `decreaseKey()` actualiza la prioridad cuando se encuentra una ruta más corta.

## Metodología experimental

Cada tamaño del problema se ejecuta **30 veces**. Los programas registran el número de operaciones y el tiempo de ejecución. Para disminuir el efecto de mediciones atípicas se utiliza un **promedio recortado**: se elimina el tiempo mínimo y el máximo y se promedian las 28 mediciones restantes.

Los resultados se guardan en archivos CSV con las columnas de tamaño, operaciones y tiempo promedio.

## Complejidad

| Versión / operación | Complejidad aproximada |
| :--- | :--- |
| `extractMinLineal()` | O(V) |
| Dijkstra lineal con matriz | **O(V²)** |
| `extractMin()` / `decreaseKey()` en heap | O(log V) |
| Recorrido de vecinos con matriz | O(V) por vértice, O(V²) en total |
| Dijkstra con Min-Heap y matriz | O(V² + E log V) |

Aunque el Min-Heap mejora la selección del mínimo, esta implementación sigue recorriendo una fila completa de la matriz por cada vértice. Por eso el costo O(V²) de revisar la matriz continúa siendo importante.

## Compilación y ejecución

Como los programas abren `MatrizGenerada.csv` usando una ruta relativa, la forma más sencilla es entrar primero a la carpeta:

```bash
cd Dijktra
gcc Dijkstra_lineal.c -o dijkstra_lineal
gcc Dijkstra_queue.c -o dijkstra_heap

./dijkstra_lineal
./dijkstra_heap
```

Si se ejecutan desde otra ubicación, debe ajustarse la ruta de `MatrizGenerada.csv` dentro del programa.

## Conclusiones

La práctica permite observar que una estructura de datos más eficiente puede reducir el costo de ciertas operaciones, pero la representación del grafo también influye en la complejidad total. El uso de una matriz de adyacencia obliga a revisar V posiciones por cada vértice procesado, mientras que el Min-Heap mejora principalmente la operación de selección y actualización de prioridades.

> **Gráficas:** las comparaciones generadas durante la materia se concentraron en el archivo `graficas (version 1).xlsb.xlsx` ubicado en la raíz del repositorio.
