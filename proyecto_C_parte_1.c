//Proyecto C parte 1
//Santiago Herra C13721 Danna Guevara C23562 Jose Ignacio Saenz C27032

//En este codigo se intento un analisis de fuerza bruta mediante recursion para poder realizar un problema de calculo de rutas minimas
//en un plano bidimensional. La solcion fue basada en recursion planteando que se haria la recursion para poder buscar todas las rutas posibles
// y se compararian para poder escoger la minima.

#include <stdio.h>
#include <limits.h>

#define MAX_CIUDADES 27

int conseguir_indice(char ciudad) {
    if (ciudad >= 'A' && ciudad <= 'Z') {
        return ciudad - 'A';
    } else {
        return -1;
    }
}

void calculateCurrentRoute(int num_ciudades, int matriz_ciudad[num_ciudades][num_ciudades], int visitado[num_ciudades], int ciudad_act, int contador_ciu, int *distancia_act, int camino_act[num_ciudades], int endIdx) {
    visitado[ciudad_act] = 1;
    camino_act[contador_ciu] = ciudad_act;

    if (ciudad_act == endIdx) {
        int distance = 0;
        for (int i = 0; i < num_ciudades - 1; ++i) {
            if (matriz_ciudad[camino_act[i]][camino_act[i + 1]] < 0) {
                visitado[ciudad_act] = 0;  //restaurar el estado
                return;
            }
            distance += matriz_ciudad[camino_act[i]][camino_act[i + 1]];
        }

        if (distance < *distancia_act) {
            *distancia_act = distance;
        }
        visitado[ciudad_act] = 0;  //restaurar el estado
        return;
    }
    // generar ciclo de busqueda de rutas adyacentes
    for (int i = 0; i < num_ciudades; ++i) {
        if (!visitado[i] && matriz_ciudad[ciudad_act][i] >= 0) {
            calculateCurrentRoute(num_ciudades, matriz_ciudad, visitado, i, contador_ciu + 1, distancia_act, camino_act, endIdx);
        }
    }

    visitado[ciudad_act] = 0;
}

int main() {
    int num_ciudades;
    char start, end;
    int valor;

    // pedir información usuario
    printf("Indica la cantidad de cuidades a utilizar (el maximo es %d): ", MAX_CIUDADES);
    scanf("%d", &num_ciudades);

    int matriz_ciudad[MAX_CIUDADES][MAX_CIUDADES];

    // crear matriz
    for (int i = 0; i < num_ciudades; i++) {
        for (int j = 0; j < num_ciudades; j++) {
            printf("Escriba el valor de la posicion (%c,%c):", 'A' + i, 'A' + j);
            scanf("%d", &valor);
            matriz_ciudad[i][j] = valor;
            matriz_ciudad[j][i] = valor;
        }
    }

    // imprimir matriz
    printf("El plano bidimensional estara basado en los valores dados en la matriz, esta matriz es:\n");
    for (int i = 0; i < num_ciudades; i++) {
        for (int j = 0; j < num_ciudades; j++) {
            printf("%d\t", matriz_ciudad[i][j]);
        }
        printf("\n");
    }

    // obtener indice segun las ciudades dadas
    printf("Ingrese el punto de inicio: ");
    scanf(" %c", &start);
    printf("Ingrese el punto de destino: ");
    scanf(" %c", &end);

    int startIdx = conseguir_indice(start);
    int endIdx = conseguir_indice(end);

    if (startIdx == -1 || endIdx == -1) {
        printf("Error: Ciudad no válida.\n");
        return 1;  // terminar el programa con un código de error
    }

    // iniciar el calculo de rutas multiples
    int camino_act[MAX_CIUDADES];
    int visitado[MAX_CIUDADES];
    int ciudades_visitadas[MAX_CIUDADES];

    int distancia_min = INT_MAX;

    // bucle para realizar el calculo varias veces
    for (int i = 0; i < num_ciudades; ++i) {
        for (int j = 0; j < num_ciudades; ++j) {
            visitado[j] = 0;  // inicializar el array visitado en cada iteracion
        }

        int distancia_act = INT_MAX;

        calculateCurrentRoute(num_ciudades, matriz_ciudad, visitado, startIdx, 0, &distancia_act, camino_act,endIdx);

        // actualizar la distancia minima
        if (distancia_act < distancia_min) {
            distancia_min = distancia_act;
            for(int k = 0; k < num_ciudades; ++k){
                ciudades_visitadas[k] = camino_act[k];
            }
        }
    }

    // print final
    if (distancia_min == INT_MAX) {
        printf("No hay ruta válida.\n");
    } else {
        printf("La distancia más corta es: %d\n", distancia_min);
        printf("La ruta mas corta es: ");
        for(int y = 0; y < num_ciudades; ++y){
            printf("%c", 'A' + ciudades_visitadas[y]);
        }
        printf("\n");
    }

    return 0;
}
