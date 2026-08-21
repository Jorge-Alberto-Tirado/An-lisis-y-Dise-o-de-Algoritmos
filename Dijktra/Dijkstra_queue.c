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

typedef struct {
    int v;
    int dist;
} NodoHeap;

typedef struct {
    int size;
    int capacity;
    NodoHeap *nodos; // indexado desde 1 hasta n
    int *pos;        // pos[v] = indice en nodos[]
} MinHeap;

MinHeap* crearMinHeap(int capacidad) {
    MinHeap *h = malloc(sizeof(MinHeap));
    h->size = 0;
    h->capacity = capacidad;
    h->nodos = malloc((capacidad + 1) * sizeof(NodoHeap));
    h->pos = malloc(capacidad * sizeof(int));
    return h;
}

void swapHeap(MinHeap *h, int i, int j) {
    operaciones++;
    h->pos[h->nodos[i].v] = j;
    h->pos[h->nodos[j].v] = i;

    NodoHeap temp = h->nodos[i];
    h->nodos[i] = h->nodos[j];
    h->nodos[j] = temp;
}

void minHeapify(MinHeap *h, int idx) {
    int smallest = idx;
    int left = 2 * idx;
    int right = 2 * idx + 1;

    operaciones++;

    if (left <= h->size && h->nodos[left].dist < h->nodos[smallest].dist)
        smallest = left;

    if (right <= h->size && h->nodos[right].dist < h->nodos[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swapHeap(h, idx, smallest);
        minHeapify(h, smallest);
    }
}

int estaEnHeap(MinHeap *h, int v) {
    return h->pos[v] <= h->size && h->pos[v] >= 1;
}

NodoHeap extractMin(MinHeap *h) {
    operaciones++;
    NodoHeap root = h->nodos[1];
    NodoHeap lastNode = h->nodos[h->size];

    h->nodos[1] = lastNode;

    h->pos[root.v] = 0;
    h->pos[lastNode.v] = 1;

    h->size--;
    minHeapify(h, 1);

    return root;
}

void decreaseKey(MinHeap *h, int v, int nuevaDist) {
    operaciones++;
    int i = h->pos[v];
    h->nodos[i].dist = nuevaDist;

    while (i > 1 && h->nodos[i].dist < h->nodos[i / 2].dist) {
        swapHeap(h, i, i / 2);
        i = i / 2;
    }
}

void dijkstraQueue(int matriz[MAX_NODOS][MAX_NODOS], int n, int origen, int dist[], int pi[]) {
    MinHeap *h = crearMinHeap(n);

    for (int v = 0; v < n; v++) {
        dist[v] = INF;
        pi[v] = -1;
        h->nodos[v + 1].v = v;
        h->nodos[v + 1].dist = INF;
        h->pos[v] = v + 1;
    }

    dist[origen] = 0;
    h->nodos[origen + 1].dist = 0;
    h->size = n;

    // BUILD-MIN-HEAP colocando la raiz al frente
    decreaseKey(h, origen, 0);

    while (h->size > 0) {
        NodoHeap minNodo = extractMin(h);
        int u = minNodo.v;

        for (int v = 0; v < n; v++) {
            operaciones++;
            if (matriz[u][v] > 0 && estaEnHeap(h, v)) {
                if (dist[u] != INF && dist[u] + matriz[u][v] < dist[v]) {
                    dist[v] = dist[u] + matriz[u][v];
                    pi[v] = u;
                    decreaseKey(h, v, dist[v]);
                }
            }
        }
    }

    free(h->nodos);
    free(h->pos);
    free(h);
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

    FILE *salida = fopen("resultadosQueue.csv", "w");
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
            dijkstraQueue(matriz_global, n, 0, dist, pi);
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
    printf("\nPruebas finalizadas. Resultados en resultadosQueue.csv\n");

    return 0;
}