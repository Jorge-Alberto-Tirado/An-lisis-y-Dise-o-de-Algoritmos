# Problema de la Mochila 0/1 — Comparación de estrategias

Esta carpeta contiene varias soluciones al problema clásico de la **Mochila 0/1 (Knapsack)**. Cada objeto tiene un peso y un valor, y el objetivo es seleccionar un subconjunto que maximice el valor total sin superar la capacidad de la mochila.

El propósito de la práctica fue comparar fuerza bruta, recursividad y programación dinámica.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `knapsack (fuerzabruta).c` | Enumera subconjuntos mediante máscaras de bits. |
| `knapsack (recursivo).c` | Evalúa recursivamente incluir o excluir cada objeto. |
| `knapsack con memoización (top-down).c` | Guarda estados `(n, capacidad)` ya calculados. |
| `knapsack iterativo (bottom-up).c` | Construye una tabla dinámica de manera iterativa. |
| `mochila_01_comparativa.c` | Reúne varias versiones para facilitar la comparación experimental. |

## Fuerza bruta

La versión por fuerza bruta genera las `2^n` combinaciones posibles mediante máscaras de bits. Para cada combinación vuelve a revisar los objetos para calcular peso y valor.

- Tiempo: **O(n·2^n)**.
- Memoria adicional: O(1), sin contar los arreglos de entrada.

## Recursión pura

Para cada objeto se evalúan dos caminos cuando el objeto cabe: incluirlo o no incluirlo. Esto genera un árbol de llamadas que en el peor caso crece como **O(2^n)**.

## Memoización Top-Down

La tabla `memo[n][capacidad]` evita repetir estados ya resueltos.

- Tiempo: **O(n·W)**.
- Memoria: **O(n·W)**.

Aquí `W` representa la capacidad de la mochila. En los experimentos del repositorio la capacidad se mantiene fija en 50.

## Bottom-Up

La versión iterativa construye una tabla `dp` con una fila por cantidad de objetos y una columna por capacidad disponible.

- Tiempo: **O(n·W)**.
- Memoria: **O(n·W)**.

## Metodología experimental

Los programas generan los pesos y valores usando una semilla fija (`srand(1)`), de modo que las versiones puedan trabajar con datos reproducibles. La mayoría de las pruebas realizan **30 repeticiones** y utilizan promedio recortado eliminando el tiempo mínimo y máximo.

La versión de fuerza bruta utiliza un número menor de repeticiones debido al crecimiento exponencial y limita el tamaño máximo para evitar tiempos excesivos.



## Conclusiones

El problema de la mochila muestra de manera clara la diferencia entre explorar todas las posibilidades y reutilizar resultados. Las soluciones exponenciales son útiles para entender el problema, pero la programación dinámica permite trabajar con tamaños de entrada mucho mayores cuando la capacidad W es manejable.

> **Gráficas:** los resultados de las pruebas se encuentran concentrados en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
