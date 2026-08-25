# Algoritmos de ordenamiento — Comparación experimental

Esta carpeta reúne diferentes algoritmos y variantes de ordenamiento implementados en C. El objetivo fue comparar su comportamiento mediante tiempos de ejecución y, en varias versiones de Selection Sort, mediante un conteo explícito de comparaciones que puede contrastarse con la fórmula teórica.

Los programas utilizan como entrada los valores almacenados en `datos.csv`, ubicado en la raíz del repositorio.

## Archivos incluidos

| Archivo | Método |
| :--- | :--- |
| `bogo_sort_promedio_csv.c` | Bogo Sort / Permutation Sort por mezclas aleatorias. |
| `bubble_sort_promedio_csv.c` | Bubble Sort. |
| `merge_sort_promedio_csv.c` | Merge Sort. |
| `selection_sort_borrado_fisica_csv.c` | Selection por máximos con borrado físico y `realloc`. |
| `selection_sort_borrado_logico_csv - copia.c` | Variante adicional de Selection con borrado lógico. |
| `selection_sort_logico_csv.c` | Selection con arreglo auxiliar `activo`. |
| `selection_sort_swap_csv.c` | Selection Sort colocando el máximo mediante intercambio. |
| `selection_sort_swap_ultimo_csv.c` | Selection con borrado lógico sustituyendo por el último elemento. |

## Metodología de las pruebas

Los programas cargan los datos desde `datos.csv`, solicitan un tamaño máximo y un incremento, y ejecutan cada tamaño **30 veces** para obtener un tiempo promedio. Antes de cada repetición se copia nuevamente el conjunto base para que todas las ejecuciones comiencen con los mismos datos.

En las variantes de Selection Sort se registra además un contador de comparaciones y se contrasta con:

```text
n(n - 1) / 2
```

que corresponde al número de comparaciones del esquema clásico de Selection Sort.

## Complejidades

| Algoritmo | Tiempo esperado / típico | Peor caso |
| :--- | :--- | :--- |
| Bogo Sort | O(n·n!) aproximadamente | No tiene cota práctica determinista; puede continuar indefinidamente |
| Bubble Sort | O(n²) en esta implementación sin corte temprano | O(n²) |
| Merge Sort | O(n log n) | O(n log n) |
| Selection Sort por swap | O(n²) | O(n²) |
| Selection con borrado lógico | O(n²) | O(n²) |
| Selection con borrado físico | O(n²), con costo adicional por desplazamientos y `realloc` | O(n²) |

## Particularidades

### Bogo Sort

La función `permutationSort()` mezcla aleatoriamente el arreglo hasta que `estaOrdenado()` devuelve verdadero. Debido a su crecimiento extremadamente alto, el programa incluye un límite de seguridad y no continúa con tamaños mayores a 10 elementos.

### Bubble Sort

Compara pares adyacentes y desplaza progresivamente los elementos mayores hacia el final. La versión almacenada no incluye una bandera para terminar anticipadamente si el arreglo ya quedó ordenado.

### Merge Sort

Divide recursivamente el arreglo en mitades y utiliza `merge()` para fusionar los segmentos ya ordenados. Su crecimiento O(n log n) permite trabajar con entradas mucho mayores que los métodos cuadráticos.

### Variantes de Selection Sort

Las diferentes versiones mantienen la misma idea de seleccionar repetidamente el elemento máximo, pero cambian la forma en que se elimina o mueve el elemento seleccionado. Esto permite observar cómo dos algoritmos con la misma complejidad asintótica pueden tener tiempos reales diferentes debido al manejo de memoria y al costo de sus operaciones internas.


Al ejecutar desde la raíz, los programas pueden localizar `datos.csv` usando el nombre esperado por el código.

## Conclusiones

Esta práctica permite comparar tanto el crecimiento teórico como el rendimiento real. Bogo Sort muestra un crecimiento impráctico, Bubble y Selection presentan comportamiento cuadrático y Merge Sort mantiene un crecimiento O(n log n). Las variantes de Selection también evidencian que la complejidad Big-O no refleja por sí sola todos los costos de implementación.

> **Gráficas:** las curvas obtenidas durante la materia se encuentran en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
