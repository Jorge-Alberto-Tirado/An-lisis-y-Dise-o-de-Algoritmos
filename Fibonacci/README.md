# Fibonacci — Recursividad y programación dinámica

Esta carpeta contiene distintas versiones del cálculo de la sucesión de **Fibonacci** para analizar cómo cambia el costo computacional cuando un problema recursivo repetitivo se optimiza mediante **memoización**.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `fibonacci_recursivo_conteo.c` | Ejercicio recursivo usado para observar el crecimiento de llamadas. |
| `fibonacccci trbajo ines.c` | Fibonacci recursivo puro con medición de tiempo y contador de llamadas. |
| `Fibonacci con memoización (programación dinámica).c` | Versión Top-Down que almacena resultados ya calculados en el arreglo `F`. |

## Versión recursiva

La relación utilizada es la conocida definición:

```text
F(n) = F(n-1) + F(n-2)
```

La versión recursiva vuelve a calcular muchas veces los mismos valores. Por ejemplo, para calcular `F(5)` se vuelve a solicitar `F(3)`, `F(2)` y otros subproblemas en diferentes ramas del árbol de recursión.

Su tiempo crece de manera exponencial, aproximadamente **O(φ^n)**, y la profundidad de la pila es O(n).

## Versión con memoización

La versión con programación dinámica utiliza el arreglo `F`. Antes de realizar una llamada recursiva se verifica si el resultado ya fue calculado. De esta manera cada valor de Fibonacci se calcula una sola vez y después se reutiliza.

- Tiempo: **O(n)**.
- Memoria del arreglo de memoización: **O(n)**.
- Pila recursiva: O(n).

## Metodología experimental

Las versiones de prueba solicitan un valor máximo de `n` y un incremento. Para cada tamaño se realizan **30 ejecuciones**, registrando el tiempo y el número de llamadas. El programa muestra los resultados en formato compatible con CSV para facilitar su traslado a Excel y la elaboración de gráficas.

## Qué se observa en la comparación

Para valores pequeños las dos versiones pueden parecer rápidas, pero el número de llamadas de la versión recursiva crece muy rápidamente. La memoización evita esa repetición y transforma el crecimiento exponencial en lineal.

## Conclusiones

Fibonacci es un ejemplo sencillo de por qué la programación dinámica puede cambiar por completo el comportamiento de un algoritmo. El problema matemático es el mismo, pero almacenar resultados intermedios evita volver a resolver subproblemas ya conocidos.

> **Gráficas:** los resultados comparativos de la materia se encuentran concentrados en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.
