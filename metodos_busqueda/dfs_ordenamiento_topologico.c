#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo {
    int color; // 0 = WHITE, 1 = GRAY, 2 = BLACK
    int d;     // tiempo de descubrimiento
    int f;     // tiempo de finalizacion
    int pi;    // padre en el arbol
} TNodo;

// estructura para la lista enlazada del orden topologico
typedef struct nodoLista {
    int id;
    struct nodoLista *siguiente;
} TNodoLista;

typedef struct {
    TNodoLista *cabeza;
} TLista;

int tiempo = 0;

// funcion para insertar un elemento al inicio de la lista en O(1)
void insertarLista(TLista *lista, int id) {
    TNodoLista *nuevo = (TNodoLista*)malloc(sizeof(TNodoLista));
    nuevo->id = id;
    nuevo->siguiente = lista->cabeza;
    lista->cabeza = nuevo;
}

// generacion de grafo dirigido aciclico (DAG) con condicion j > i
void crearGrafo(int **matriz, int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            int enlace = rand() % 2;
            if (enlace) {
                matriz[i][j] = 1;
            }
        }
    }
}

void imprimirMatriz(int filas, int columnas, int **m) {
    printf("\nMatriz de Adyacencia (DAG):\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%2d ", m[i][j]);
        }
        printf("\n");
    }
}

void dfsVisit(int **matriz, int u, int vertices, TNodo *nodos, TLista *lista) {
    tiempo++;
    nodos[u].d = tiempo;
    nodos[u].color = 1; // GRAY

    for (int v = 0; v < vertices; v++) {
        if (matriz[u][v] == 1 && nodos[v].color == 0) {
            nodos[v].pi = u;
            dfsVisit(matriz, v, vertices, nodos, lista);
        }
    }

    nodos[u].color = 2; // BLACK
    tiempo++;
    nodos[u].f = tiempo;

    // al terminar el nodo, se inserta al inicio de la lista en O(1)
    insertarLista(lista, u);
}

void ordenamientoTopologico(int **matriz, int vertices) {
    TNodo *V = (TNodo*)malloc(vertices * sizeof(TNodo));
    TLista lista;
    lista.cabeza = NULL;

    for (int i = 0; i < vertices; i++) {
        V[i].color = 0; // WHITE
        V[i].d = -1;
        V[i].f = -1;
        V[i].pi = -1;
    }

    tiempo = 0; // reinicia la variable global

    for (int u = 0; u < vertices; u++) {
        if (V[u].color == 0) {
            dfsVisit(matriz, u, vertices, V, &lista);
        }
    }

    // impresion del orden topologico recorriendo la lista
    printf("\nOrden Topologico Resultante:\n");
    TNodoLista *actual = lista.cabeza;
    while (actual != NULL) {
        printf("Nodo: %d [f: %d]\n", actual->id, V[actual->id].f);
        actual = actual->siguiente;
    }

    // liberacion limpia de la memoria reservada
    actual = lista.cabeza;
    while (actual != NULL) {
        TNodoLista *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }

    free(V);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    if (argc != 2) {
        printf("Uso: %s <numero de vertices>\n", argv[0]);
        return 1;
    }

    int vertices = atoi(argv[1]);
    if (vertices <= 0) {
        printf("Introduzca valor de vertices positivo\n");
        return 1;
    }

    int **matriz = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        matriz[i] = (int*)calloc(vertices, sizeof(int));
    }

    crearGrafo(matriz, vertices);
    imprimirMatriz(vertices, vertices, matriz);

    ordenamientoTopologico(matriz, vertices);

    for (int i = 0; i < vertices; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}