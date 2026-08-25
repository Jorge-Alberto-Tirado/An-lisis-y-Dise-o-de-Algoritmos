# Autómatas y lenguajes — Reconocimiento de 0ⁿ1ⁿ

Esta carpeta contiene tres programas que verifican si una cadena pertenece al lenguaje formado por la misma cantidad de ceros seguidos de la misma cantidad de unos:

```text
L = { 0ⁿ1ⁿ | n > 0 }
```

El objetivo es resolver el mismo problema utilizando estrategias diferentes y comparar la forma en que cada una representa la información necesaria para validar la cadena.

## Archivos incluidos

| Archivo | Estrategia |
| :--- | :--- |
| `automata_anbn_contador.c` | Cuenta ceros y unos y controla el cambio de fase. |
| `automata_anbn_marcado.c` | Marca símbolos ya emparejados usando `X`. |
| `automata_anbn_pila.c` | Apila un símbolo por cada cero y desapila por cada uno. |

## Versión con contador

Se recorren los caracteres una sola vez. Mientras no aparezca un `1`, se cuentan ceros. Después del cambio de fase ya no se permiten ceros. Al final se verifica que ambos contadores sean iguales y mayores que cero.

- Tiempo: **O(n)**.
- Memoria adicional: **O(1)**.

## Versión por marcado

Cada vez que se encuentra un `0`, el programa lo reemplaza por `X` y busca desde el final un `1` que todavía no haya sido marcado. Finalmente verifica que todos los caracteres se hayan convertido en `X`.

- Tiempo en el peor caso: **O(n²)** por las búsquedas repetidas.
- Memoria adicional: O(1), además de la propia cadena modificada.

## Versión con pila

Por cada `0` se coloca un símbolo en `pila`. Cuando comienzan los `1`, se desapila un elemento por cada uno. La cadena se acepta solamente si no aparecen ceros después de los unos y la pila termina vacía.

- Tiempo: **O(n)**.
- Memoria: **O(n)**.

## Compilación

```bash
gcc "automatas y lenguajes/automata_anbn_contador.c" -o anbn_contador
gcc "automatas y lenguajes/automata_anbn_marcado.c" -o anbn_marcado
gcc "automatas y lenguajes/automata_anbn_pila.c" -o anbn_pila
```

## Ejemplos

```text
0011   -> pertenece
000111 -> pertenece
00111  -> no pertenece
0101   -> no pertenece
111    -> no pertenece
```

## Conclusiones

Los tres programas reconocen el mismo tipo de patrón, pero lo hacen de manera diferente. El uso de contadores es más económico en memoria; el marcado repite búsquedas y puede crecer cuadráticamente; la pila representa directamente la necesidad de recordar cuántos ceros deben emparejarse con unos posteriores.
