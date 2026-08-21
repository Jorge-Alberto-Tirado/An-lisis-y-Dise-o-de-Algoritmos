#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#define MAX_NODOS 1000
#define REPETICIONES 30
#define INF INT_MAX

long long operaciones = 0;
int matriz_global[MAX_NODOS][MAX_NODOS];

// busca el nodo con la menor distancia entre los que siguen en la cola
int extractMinLineal(int dist[], int enCola[], int n) {
    int min = INF;
    int min_idx = -1;

    for (int v = 0; v < n; v++) {
        operaciones++;
        if (enCola[v] && dist[v] < min) {
            min = dist[v];
            min_idx = v;
        }
    }
    return min_idx;
}

void dijkstraLineal(int matriz[MAX_NODOS][MAX_NODOS], int n, int origen, int dist[], int pi[]) {
    int *enCola = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        pi[i] = -1;
        enCola[i] = 1;
    }

    dist[origen] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = extractMinLineal(dist, enCola, n);

        if (u == -1) break;

        enCola[u] = 0;

        for (int v = 0; v < n; v++) {
            operaciones++;
            if (matriz[u][v] > 0 && enCola[v]) {
                if (dist[u] != INF && dist[u] + matriz[u][v] < dist[v]) {
                    dist[v] = dist[u] + matriz[u][v];
                    pi[v] = u;
                }
            }
        }
    }

    free(enCola);
}

void leerMatrizCSV(const char *nombreArchivo, int matriz[MAX_NODOS][MAX_NODOS]) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        printf("Error: no se pudo abrir %s\n", nombreArchivo);
        exit(1);
    }

    char linea[20000];
    int fila = 0;

    while (fgets(linea, sizeof(linea), f) != NULL && fila < MAX_NODOS) {
        int columna = 0;
        char *token = strtok(linea, ",");

        while (token != NULL && columna < MAX_NODOS) {
            matriz[fila][columna] = atoi(token);
            token = strtok(NULL, ",");
            columna++;
        }
        fila++;
    }
    fclose(f);
}

double promedioTrimmed(double tiempos[], int total) {
    double suma = 0.0;
    double min = tiempos[0];
    double max = tiempos[0];

    for (int i = 0; i < total; i++) {
        suma += tiempos[i];
        if (tiempos[i] < min) min = tiempos[i];
        if (tiempos[i] > max) max = tiempos[i];
    }
    return (suma - min - max) / (double)(total - 2);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);

    leerMatrizCSV("MatrizGenerada.csv", matriz_global);
    printf("Matriz cargada correctamente.\n\n");

    int n_max, paso;
    printf("Cantidad maxima de nodos (max %d)? ", MAX_NODOS);
    scanf("%d", &n_max);

    printf("Incremento entre pruebas (paso): ");
    scanf("%d", &paso);

    if (n_max > MAX_NODOS) n_max = MAX_NODOS;

    FILE *salida = fopen("resultadosLineal.csv", "w");
    fprintf(salida, "N,Operaciones,Tiempo_promedio(segundos)\n");

    printf("\nN,Operaciones,Tiempo_promedio(segundos)\n");

    for (int n = paso; n <= n_max; n += paso) {
        double tiempos[REPETICIONES];
        long long ops_totales = 0;

        int *dist = malloc(n * sizeof(int));
        int *pi = malloc(n * sizeof(int));

        for (int rep = 0; rep < REPETICIONES; rep++) {
            operaciones = 0;

            clock_t inicio = clock();
            dijkstraLineal(matriz_global, n, 0, dist, pi);
            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            tiempos[rep] = tiempo;
            ops_totales += operaciones;
        }

        double tiempo_prom = promedioTrimmed(tiempos, REPETICIONES);
        long long ops_prom = ops_totales / REPETICIONES;

        printf("%d,%lld,%.8f\n", n, ops_prom, tiempo_prom);
        fprintf(salida, "%d,%lld,%.8f\n", n, ops_prom, tiempo_prom);

        free(dist);
        free(pi);
    }

    fclose(salida);
    printf("\nPruebas finalizadas. Resultados en resultadosLineal.csv\n");

    return 0;
}