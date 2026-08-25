# Búsqueda de patrones tipo GREP — Fuerza bruta

Esta carpeta contiene una implementación experimental de búsqueda de patrones inspirada en el comportamiento de `grep`. El objetivo es estudiar el costo de localizar un patrón de longitud `M` dentro de un texto de longitud `N` mediante comparación directa o **fuerza bruta**.

## Archivos incluidos

| Archivo | Descripción |
| :--- | :--- |
| `GREP_tarea.c` | Implementación de búsqueda de patrón por comparación directa. |
| `letras_100000.txt` | Texto base `B` de 100000 caracteres. |
| `letras_1000.txt` | Cadena base utilizada para formar patrones `A` de diferentes tamaños. |


## Funcionamiento

El programa carga `letras_100000.txt` como texto principal y `letras_1000.txt` como patrón base. Después prueba tamaños de patrón desde 10 hasta 1000, aumentando de 10 en 10.

Para cada posición posible del texto se comparan los `M` caracteres del patrón. En esta versión **no se interrumpe el ciclo cuando aparece la primera diferencia**; siempre se realizan las M comparaciones. Esto permite que el conteo experimental sea estable y corresponda directamente con la fórmula analizada.

## Número de operaciones

Para un texto de longitud `N` y un patrón de longitud `M`, existen:

```text
N - M + 1
```

posiciones posibles. En cada una se realizan `M` comparaciones, por lo que:

```text
Operaciones = (N - M + 1) · M
```

La complejidad temporal es **O(N·M)**.

## Metodología experimental

Para cada valor de `M` se realizan **30 ejecuciones**. Se registra el tiempo mínimo y máximo y posteriormente se calcula un promedio recortado eliminando esos dos extremos. El programa imprime:

```text
M,Operaciones,Tiempo_promedio(segundos)
```

## Compilación y ejecución

Como los archivos de entrada se abren mediante rutas relativas, la forma más sencilla es ejecutar desde la misma carpeta:

```bash
cd Grep
gcc GREP_tarea.c -o grep_tarea
./grep_tarea
```

Si el ejecutable se inicia desde otra ubicación, deben ajustarse las rutas de `letras_100000.txt` y `letras_1000.txt`.

## Conclusiones

El experimento permite observar cómo el crecimiento simultáneo de N y M afecta a un algoritmo de búsqueda ingenua. Al obligar al programa a realizar todas las comparaciones, el número de operaciones coincide claramente con el modelo O(N·M), lo cual facilita comparar la teoría con los tiempos medidos.

> **Gráficas:** las gráficas obtenidas durante la materia se encuentran en `graficas (version 1).xlsb.xlsx` en la raíz del repositorio.
