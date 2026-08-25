# Árbol de Expansión Mínima — Kruskal y Prim

Esta carpeta contiene varias implementaciones de **Kruskal** y **Prim** para construir un Árbol de Expansión Mínima (MST). El objetivo es comparar diferentes formas de ordenar aristas y seleccionar el siguiente vértice, así como observar el efecto de estructuras como **Union-Find** y **Min-Heap**.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `kruskal_grafo_fijo_qsort.c` | Kruskal sobre un grafo fijo utilizando `qsort`. |
| `kruskal_matriz_csv_qsort.c` | Kruskal leyendo una matriz desde CSV y ordenando aristas con `qsort`. |
| `kruskal_matriz_fija_bubble.c` | Variante de Kruskal que utiliza Bubble Sort para ordenar las aristas. |
| `prim_fuerza_bruta_lineal.c` | Prim con selección lineal del siguiente vértice. |
| `prim_min_heap_cormen.c` | Prim con Min-Heap y arreglo de posiciones para actualizar claves con `decreaseKey`. |
| `prim_min_heap_lazy.c` | Prim con heap "lazy": inserta nuevas prioridades y descarta entradas antiguas cuando se extraen. |

## Kruskal

Kruskal convierte las conexiones de la matriz en una lista de aristas, las ordena de menor a mayor peso y las procesa en ese orden. Para evitar ciclos utiliza una estructura **Union-Find** con compresión de caminos y unión por rango.

Para la versión con `qsort`:

```text
O(V² + E log E)
```

El término O(V²) proviene de recorrer la matriz y O(E log E) del ordenamiento de las aristas. Las operaciones de Union-Find tienen un costo amortizado cercano a constante, expresado como O(α(V)).

La variante que ordena con Bubble Sort puede elevar el ordenamiento hasta **O(E²)**.

## Prim lineal

La versión lineal mantiene arreglos `key`, `padre` e `inMST`. En cada paso busca de forma lineal el vértice pendiente con la menor clave y después revisa su fila de la matriz.

- Complejidad con matriz: **O(V²)**.

## Prim con Min-Heap

### Versión tipo Cormen

Mantiene una posición para cada vértice dentro del heap y utiliza `decreaseKey()` cuando aparece una conexión de menor peso. La extracción y actualización del heap cuestan O(log V).

### Versión Lazy

En lugar de actualizar una entrada existente, inserta una nueva pareja `(vértice, clave)`. Cuando se extrae un vértice que ya pertenece al MST, esa entrada se descarta. Este enfoque simplifica la actualización a cambio de permitir duplicados en el heap.

Como las implementaciones continúan recorriendo filas completas de una matriz de adyacencia, existe un costo O(V²) de exploración; además, las operaciones del heap agregan el costo logarítmico de las inserciones/extracciones.

## Metodología experimental

Las versiones de prueba registran:

- cantidad de vértices,
- costo total del MST,
- contador de instrucciones,
- tiempo de ejecución.

Los programas realizan varias repeticiones y calculan un promedio recortado eliminando el mayor y el menor tiempo antes de guardar los resultados en archivos CSV.

Algunas versiones leen la matriz desde un archivo llamado `Coordenadas.csv`. 


## Conclusiones

Las implementaciones permiten comparar dos familias de algoritmos greedy. Kruskal toma decisiones sobre aristas y necesita evitar ciclos; Prim hace crecer un único árbol seleccionando continuamente la conexión más barata hacia un nuevo vértice. Las variantes también muestran que cambiar la estructura usada para seleccionar mínimos u ordenar aristas puede modificar de forma importante el rendimiento real.

> **Gráficas:** las comparaciones de la materia se encuentran concentradas en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
