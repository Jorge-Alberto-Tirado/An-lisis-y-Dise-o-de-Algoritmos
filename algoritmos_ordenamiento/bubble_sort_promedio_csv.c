#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// funcion bubble sort
void bubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                int aux = A[j];
                A[j] = A[j + 1];
                A[j + 1] = aux;
            }
        }
    }
}

int main(){

    FILE *archivo = fopen("datos.csv", "r");
    if(archivo == NULL){
        printf("Error: no se pudo abrir datos.csv\n");
        return 1;
    }

    int max_datos = 100000;
    int *datos = malloc(max_datos * sizeof(int));
    int total = 0;

    while(total < max_datos && fscanf(archivo, "%d,", &datos[total]) == 1){
        total++;
    }

    fclose(archivo);

    printf("Datos cargados: %d\n", total);

    int max_n, paso;

    printf("Cuantos elementos quieres ordenar (maximo)? ");
    scanf("%d", &max_n);

    printf("Incremento entre pruebas: ");
    scanf("%d", &paso);

    if(max_n > total){
        printf("Error: max_n supera los datos disponibles\n");
        free(datos);
        return 1;
    }

    printf("\nN,Tiempo_promedio(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        double tiempo_total = 0;

        for(int rep = 0; rep < 30; rep++){

            int *v = malloc(k * sizeof(int));

            // copiar datos
            for(int i = 0; i < k; i++){
                v[i] = datos[i];
            }

            clock_t inicio = clock();

            bubbleSort(v, k);

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            tiempo_total += tiempo;

            free(v);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        printf("%d,%f\n", k, tiempo_promedio);
    }

    free(datos);

    return 0;
}