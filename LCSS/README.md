# Subsecuencia Común Más Larga (LCS) — Recursivo, Top-Down y Bottom-Up

Esta carpeta estudia el problema **Longest Common Subsequence (LCS)** o Subsecuencia Común Más Larga. El objetivo es encontrar la longitud de la subsecuencia más larga que aparece, conservando el orden, en dos cadenas de caracteres.

Se implementaron tres enfoques para comparar el efecto de la programación dinámica sobre un problema con muchos subproblemas repetidos.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `LCS (recursivo).c` | Solución recursiva directa. |
| `LCS con memoización (top-down).c` | Solución recursiva con tabla `memo`. |
| `LCS iterativo (bottom-up).c` | Solución iterativa que llena una tabla `dp`. |

## Versión recursiva

Si los últimos caracteres de ambas cadenas coinciden, se suma uno y se continúa con ambos prefijos. Si no coinciden, se prueban dos posibilidades: eliminar un carácter de la primera cadena o eliminar uno de la segunda.

La versión recursiva puede resolver los mismos estados muchas veces, por lo que su costo crece **exponencialmente** en el peor caso.

## Memoización Top-Down

La función `LCS_mem()` utiliza una matriz `memo[i][j]`. Cuando un estado ya fue calculado, se devuelve inmediatamente sin volver a expandir la recursión.

- Tiempo: **O(n·m)**.
- Memoria: **O(n·m)** más la pila recursiva.

## Programación dinámica Bottom-Up

La versión iterativa llena una tabla `dp` desde los casos base hasta `dp[n][m]`. Cada celda se calcula una sola vez.

- Tiempo: **O(n·m)**.
- Memoria: **O(n·m)**.

## Conteo experimental

Los programas muestran el número de llamadas recursivas o de iteraciones realizadas. Las versiones Top-Down y Bottom-Up también permiten probar prefijos de tamaños diferentes para observar cómo crece el trabajo conforme aumenta el tamaño de entrada.

## Conclusiones

Las tres versiones resuelven el mismo problema, pero la estrategia cambia radicalmente el número de operaciones. La recursión pura repite estados; la memoización los almacena conforme se necesitan y Bottom-Up los construye de manera iterativa. Las dos versiones de programación dinámica reducen el problema a O(n·m).

> **Gráficas:** los resultados comparativos de la materia se concentraron en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.

📊 [Consultar archivo de gráficas](../graficas%20%28version%201%29.xlsb.xlsx)
