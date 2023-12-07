/*
Proyecto 3 C
José Ignacio Sáenz C27032
Santiago Herra C13721
Danna Guevara C23562
El programa asigna de forma dinámica memoria para la creación de una matriz.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool esEntero(const char* string) { // Funcion que revisa si una entrada es entera
    while (*string) {
        if (!isdigit(*string)) { // Revisa que la entrada este compuesta de digitos
            return false;
        }
        string++;
    }
    return true;
}
// Se define el tipo de estructura matriz
typedef struct {
    int** matriz; // puntero a un puntero
    int filas; // # de filas
    int columnas; // # de columnas
} InfoDeMatriz;

// Función solicitada por el proyecto
int definirMatriz(InfoDeMatriz* matrizInfo) {
    // Solicita filas y columnas y las adjunta a los parametros de estructura
    printf("Ingrese la cantidad de filas: ");
    scanf("%d", &(matrizInfo->filas));
    printf("Ingrese la cantidad de columnas: ");
    scanf("%d", &(matrizInfo->columnas));
    // Reserva memoria de forma dinamica
    matrizInfo->matriz = (int**)malloc(matrizInfo->filas * sizeof(int*));
    if (matrizInfo->matriz == NULL) {
        printf("Error al reservar memoria para las filas.\n"); 
        return -1;      
    } 
    printf("Ingrese las entradas de la matriz. \n");
    // Declara el error, devuelve -1 si no se logro reservar la memoria
    for (int i = 0; i < matrizInfo->filas; ++i) {
        matrizInfo->matriz[i] = (int*)malloc(matrizInfo->columnas * sizeof(int));
        if (matrizInfo->matriz[i] == NULL) {
            printf("Error al reservar memoria para la fila %d.\n", i + 1);
            return -1;
        }
        // Solicita al usuario las entradas de la matriz
        for (int j = 0; j < matrizInfo->columnas; ++j) {
            char entrada[20];  // Tamaño arbitrario para revisar si la entrada es entera
            int valor; // Valor de la entrada
            printf("Entrada [%d][%d]: ", i, j);
            scanf("%s", entrada);
            if (!esEntero(entrada)) { // Revisar que sea entero y no flotante o char
                printf("El valor ingresado no es entero.\n"); // Declara el error
                return -1;
            }

            // Almacenar el valor entero en la matriz
            sscanf(entrada, "%d", &valor);
            matrizInfo->matriz[i][j] = valor;
        }
    // Imprime la direccion de memoria del primer numero de cada fila
    printf("Direccion de memoria para la fila %d: %p\n", i + 1, (void*)&(matrizInfo->matriz[i][0]));
    }
    // Imprime la matriz ingresada por el usuario
    printf("Matriz ingresada:\n");
    for (int i = 0; i < (matrizInfo->filas); ++i) { // Ciclo que recorre la matriz
        for (int j = 0; j < (matrizInfo->columnas); ++j) {
            printf("%d ", (matrizInfo->matriz[i][j])); //Utiliza parametros de estrucura
        }
        printf("\n"); // Brinda formato a la impresion
    }
    return 0;
}

int main() {
    InfoDeMatriz mi;

    // Verifica la ocurrencia de algun error
    if (definirMatriz(&mi) == -1) {
        printf("Error al correr la funcion.\n");
        return -1;
    }
    // Liberar la memoria dinamicam al final del programa
    for (int i = 0; i < mi.filas; ++i) {
        free(mi.matriz[i]);
    }
    free(mi.matriz);

    return 0;
}
