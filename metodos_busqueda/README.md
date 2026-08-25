# Métodos de búsqueda en grafos — BFS, DFS y ordenamiento topológico

Esta carpeta contiene implementaciones de **Búsqueda en Amplitud (BFS)**, **Búsqueda en Profundidad (DFS)** y **Ordenamiento Topológico** utilizando matrices de adyacencia. El objetivo principal es observar el funcionamiento interno de los recorridos, los estados de los vértices y la forma en que DFS puede utilizarse para construir un orden topológico.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `bfs_matriz_aleatorio.c` | BFS sobre un grafo no dirigido generado aleatoriamente. |
| `bfs_teórico_estatico.c` | BFS sobre un grafo fijo siguiendo el esquema clásico WHITE/GRAY/BLACK, distancia `d` y padre `pi`. |
| `dfs_matriz_recursivo.c` | DFS recursivo sobre una matriz de adyacencia fija. |
| `dfs_ordenamiento_topologico.c` | DFS sobre un DAG y construcción de una lista con el orden topológico. |

## BFS

BFS explora el grafo por niveles y utiliza una cola. Los vértices comienzan sin visitar; al descubrir un vértice se registra su distancia y su padre y se coloca en la cola. Cuando todos sus vecinos fueron revisados, el vértice queda completamente procesado.

La versión aleatoria implementa una cola circular mediante `inicio`, `cantidad` y un arreglo de nodos. La versión teórica utiliza los estados `WHITE`, `GRAY` y `BLACK` y los arreglos `d` y `pi`.

## DFS

DFS avanza tan profundo como sea posible antes de regresar. En `dfs_matriz_recursivo.c` la pila necesaria para el recorrido se obtiene directamente mediante las llamadas recursivas.

## Ordenamiento topológico

`dfs_ordenamiento_topologico.c` genera un grafo dirigido acíclico (DAG) creando aristas solamente cuando `j > i`. Durante DFS registra tiempos de descubrimiento `d`, tiempos de finalización `f` y el padre `pi`. Cuando un vértice termina se inserta al inicio de una lista enlazada; al finalizar, esa lista contiene el orden topológico.

## Complejidad

Debido a que los programas utilizan **matriz de adyacencia**, para revisar los vecinos de un vértice se recorre una fila completa de V posiciones.

| Algoritmo | Complejidad con estas implementaciones |
| :--- | :--- |
| BFS | **O(V²)** |
| DFS | **O(V²)** |
| Ordenamiento topológico basado en DFS | **O(V²)** |
| Encolar / desencolar | O(1) |
| Insertar al inicio de la lista topológica | O(1) |

Con listas de adyacencia, BFS y DFS suelen expresarse como O(V + E), pero la matriz modifica el costo de la exploración de vecinos.


Ejemplo para las versiones que reciben número de vértices:

```bash
./bfs 8
./topo 8
```

## Conclusiones

BFS y DFS visitan los mismos vértices, pero el orden de exploración es diferente: BFS trabaja por niveles y DFS profundiza antes de retroceder. El ordenamiento topológico aprovecha los tiempos de finalización de DFS para colocar primero a los vértices que deben aparecer antes dentro de un DAG.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
