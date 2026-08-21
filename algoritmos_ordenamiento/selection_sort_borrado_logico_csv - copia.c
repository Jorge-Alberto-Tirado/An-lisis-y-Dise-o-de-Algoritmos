#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// borrado logico: marca la posicion con un valor centinela (-1)
void remover_elemento_logico(int *vector, int indice){
    vector[indice] = -1;
}

int main(){

    // LEER ARCHIVO UNA SOLA VEZ
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

    printf("\nN,Instrucciones,Formula,Tiempo_promedio(segundos)\n");

    for(int k = paso; k <= max_n; k += paso){

        int size_s = k;
        int contador = 0;
        double tiempo_total = 0;

        // 30 repeticiones
        for(int rep = 0; rep < 30; rep++){

            int size = k;

            int *v = malloc(size * sizeof(int));
            int *s = malloc(size * sizeof(int));

            // copiar datos desde el archivo
            for(int i = 0; i < size; i++){
                v[i] = datos[i];
            }

            contador = 0;
            int elementos_visibles = size;

            clock_t inicio = clock();

            while(elementos_visibles >= 2){
                
                // buscar el primer elemento no borrado para inicializar el mayor
                int indice = -1;
                int mayor = -1;
                
                for(int i = 0; i < size; i++){
                    if(v[i] != -1){
                        mayor = v[i];
                        indice = i;
                        break;
                    }
                }

                // buscar el verdadero mayor entre los elementos no borrados
                for(int i = indice + 1; i < size; i++){
                    if(v[i] != -1){
                        if(v[i] > mayor){
                            mayor = v[i];
                            indice = i;
                        }
                        contador++;
                    }
                }

                // aplicar borrado logico
                remover_elemento_logico(v, indice);
                elementos_visibles--;
                s[elementos_visibles] = mayor;

                // si solo queda un elemento valido
                if(elementos_visibles == 1){
                    for(int i = 0; i < size; i++){
                        if(v[i] != -1){
                            s[0] = v[i];
                            remover_elemento_logico(v, i);
                            elementos_visibles--;
                            break;
                        }
                    }
                }
            }

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

            tiempo_total += tiempo;

            free(v);
            free(s);
        }

        double tiempo_promedio = tiempo_total / 30.0;

        int formula = size_s * (size_s - 1) / 2;

        printf("%d|%d|%d|%f\n", size_s, contador, formula, tiempo_promedio);
    }

    free(datos);

    return 0;
}