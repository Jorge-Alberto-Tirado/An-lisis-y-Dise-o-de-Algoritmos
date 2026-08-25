# Laberinto del tesoro — Recursividad y programación dinámica

Esta carpeta estudia un problema de caminos sobre una matriz. Cada celda contiene una cantidad de tesoro y el objetivo es llegar hasta la posición inferior derecha acumulando la **máxima cantidad posible**, moviéndose únicamente desde arriba o desde la izquierda.

Se implementaron tres estrategias para observar la diferencia entre recursividad pura y programación dinámica.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `laberinto_tesoro_recursivo.c` | Solución recursiva sin almacenamiento de resultados. |
| `laberinto_tesoro_memo.c` | Versión con memoización. En el estado actual del repositorio el archivo contiene solamente una parte del programa de pruebas. |
| `laberinto_tesoro_iterativo_dp.c` | Solución Bottom-Up con matriz `dp`. |

## Relación del problema

Para una celda interior `(i,j)`, el mejor valor se obtiene tomando el máximo entre llegar desde arriba o desde la izquierda:

```text
DP[i][j] = matriz[i][j] + max(DP[i-1][j], DP[i][j-1])
```

Las celdas de la primera fila y de la primera columna solamente tienen una dirección posible de llegada.

## Versión recursiva

La función `LT_rec()` vuelve a calcular muchas posiciones desde diferentes ramas de la recursión. Por ello el número de llamadas crece de manera exponencial. En una matriz cuadrada de lado `n`, el número de caminos posibles aumenta aproximadamente de forma combinatoria.

## Memoización

La idea de `LT_mem()` es almacenar el resultado de cada celda para que una posición no tenga que resolverse más de una vez.

- Tiempo esperado: **O(n²)** para una matriz n × n.
- Memoria: **O(n²)**.


## Bottom-Up

La versión iterativa recorre cada celda de la matriz una sola vez y llena `dp` desde la esquina superior izquierda hasta la inferior derecha.

- Tiempo: **O(n²)**.
- Memoria: **O(n²)**.

## Metodología experimental

Las versiones completas generan una matriz reproducible con `srand(1)` y valores aleatorios entre 1 y 20. Para cada tamaño se ejecuta el algoritmo **30 veces** y se utiliza un promedio recortado eliminando el menor y el mayor tiempo.

El programa recursivo incorpora un límite práctico para evitar que el crecimiento exponencial haga que la prueba se vuelva demasiado lenta.




## Conclusiones

El ejercicio muestra cómo un mismo problema de caminos puede pasar de un crecimiento exponencial a O(n²) al almacenar los resultados intermedios. Memoización y Bottom-Up evitan resolver repetidamente las mismas celdas y permiten trabajar con matrices mucho mayores.

> **Gráficas:** los resultados comparativos de la materia se encuentran en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
