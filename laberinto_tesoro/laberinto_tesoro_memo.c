#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define REP 30

int matriz[MAX][MAX];
int memo[MAX][MAX];

long long contador = 0;


// Funcion recursiva con memoizacion
int LT_mem(int i, int j) {

    contador++;

    // Si ya fue calculado, se regresa el resultado guardado
    if (memo[i][j] != -1)
        return memo[i][j];


    // Caso base
    if (i == 0 && j == 0) {

        memo[i][j] = matriz[i][j];

        return memo[i][j];
    }


    // Primera fila
    if (i == 0) {

        memo[i][j] = matriz[i][j]
                   + LT_mem(i, j - 1);

        return memo[i][j];
    }


    // Primera columna
    if (j == 0) {

        memo[i][j] = matriz[i][j]
                   + LT_mem(i - 1, j);

        return memo[i][j];
    }


    // Obtener el mejor resultado desde arriba
    int arriba = LT_mem(i - 1, j);

    // Obtener el mejor resultado desde la izquierda
    int izquierda = LT_mem(i, j - 1);


    // Guardar el resultado para no volverlo a calcular
    memo[i][j] = matriz[i][j]
               + (arriba > izquierda ? arriba : izquierda);


    return memo[i][j];
}


// Promedio recortado
double promedio(double t[]) {

    double suma = 0;
    double min = t[0];
    double max = t[0];


    for (int i = 0; i < REP; i++) {

        if (t[i] < min)
            min = t[i];

        if (t[i] > max)
            max = t[i];

        suma += t[i];
    }


    return (suma - min - max) / (REP - 2);
}


int main() {

    int n_max;
    int paso;


    printf("Tamano maximo de la matriz: ");
    scanf("%d", &n_max);

    printf("Intervalo (paso): ");
    scanf("%d", &paso);


    // Validaciones
    if (n_max < 1 || n_max > MAX) {

        printf("El tamano debe estar entre 1 y %d.\n", MAX);

        return 1;
    }


    if (paso < 1) {

        printf("El paso debe ser mayor que 0.\n");

        return 1;
    }


    // Misma semilla para poder comparar
    // con las otras versiones
    srand(1);


    // Crear matriz de tesoros
    for (int i = 0; i < n_max; i++) {

        for (int j = 0; j < n_max; j++) {

            matriz[i][j] = rand() % 20 + 1;
        }
    }


    printf("\nN,Max_Tesoro,Llamadas,Tiempo\n");


    // Probar diferentes tamanos de matriz
    for (int n = n_max; n >= 1; n -= paso) {

        double tiempos[REP];

        int resultado;


        // 30 repeticiones
        for (int r = 0; r < REP; r++) {


            // Inicializar memoria
            for (int i = 0; i < n; i++) {

                for (int j = 0; j < n; j++) {

                    memo[i][j] = -1;
                }
            }


            contador = 0;


            clock_t ini = clock();


            resultado = LT_mem(n - 1, n - 1);


            clock_t fin = clock();


            tiempos[r] =
                (double)(fin - ini)
                / CLOCKS_PER_SEC;
        }


        printf("%d,%d,%lld,%f\n",
               n,
               resultado,
               contador,
               promedio(tiempos));
    }


    return 0;
}
