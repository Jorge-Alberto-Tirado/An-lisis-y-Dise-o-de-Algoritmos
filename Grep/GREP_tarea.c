#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // LEER TEXTO B (letras_100000.txt)
    FILE *archivo_texto = fopen("letras_100000.txt", "r");
    if (archivo_texto == NULL) {
        printf("Error: no se pudo abrir letras_100000.txt\n");
        return 1;
    }

    int n = 100000;
    char *B = malloc((n + 1) * sizeof(char));
    if (fscanf(archivo_texto, "%s", B) != 1) {
        printf("Error al leer letras_100000.txt\n");
        fclose(archivo_texto);
        free(B);
        return 1;
    }
    fclose(archivo_texto);

    // LEER PATRON BASE A (letras_1000.txt)
    FILE *archivo_patron = fopen("letras_1000.txt", "r");
    if (archivo_patron == NULL) {
        printf("Error: no se pudo abrir letras_1000.txt\n");
        free(B);
        return 1;
    }

    int max_m = 1000;
    char *patron_completo = malloc((max_m + 1) * sizeof(char));
    if (fscanf(archivo_patron, "%s", patron_completo) != 1) {
        printf("Error al leer letras_1000.txt\n");
        fclose(archivo_patron);
        free(B);
        free(patron_completo);
        return 1;
    }
    fclose(archivo_patron);

    printf("M,Operaciones,Tiempo_promedio(segundos)\n");

    // Variar M de 10 a 1000 con incrementos de 10
    for (int m = 10; m <= max_m; m += 10) {

        double tiempos[30];
        double suma_tiempos = 0;
        double min_tiempo = 1e9;
        double max_tiempo = -1;
        long long operaciones_totales = 0;

        // Arreglo temporal para el patron A de longitud M
        char *A = malloc((m + 1) * sizeof(char));
        for (int i = 0; i < m; i++) {
            A[i] = patron_completo[i];
        }
        A[m] = '\0';

        // 30 experimentos
        for (int rep = 0; rep < 30; rep++) {

            long long ops_rep = 0;

            clock_t inicio = clock();

            // ALGORTIMO GREP FUERZA BRUTA
            // Compara siempre los M caracteres sin hacer break
            for (int i = 0; i <= n - m; i++) {
                int encontrado = 1;
                for (int j = 0; j < m; j++) {
                    ops_rep++;
                    if (A[j] != B[i + j]) {
                        encontrado = 0; // No rompe el ciclo, continua comparando
                    }
                }
            }

            clock_t fin = clock();

            double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
            tiempos[rep] = tiempo;
            suma_tiempos += tiempo;
            operaciones_totales = ops_rep; // Es constante para cada repeticion

            if (tiempo < min_tiempo) min_tiempo = tiempo;
            if (tiempo > max_tiempo) max_tiempo = tiempo;
        }

        // Media recortada (eliminando el tiempo mas rapido y el mas lento)
        double tiempo_promedio = (suma_tiempos - min_tiempo - max_tiempo) / 28.0;

        printf("%d,%lld,%.8f\n", m, operaciones_totales, tiempo_promedio);

        free(A);
    }

    free(B);
    free(patron_completo);

    return 0;
}