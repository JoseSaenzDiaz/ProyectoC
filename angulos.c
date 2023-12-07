#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Vertice;
double prodcruz(Vertice a, Vertice b) {
    return a.x * b.y - a.y * b.x;
}

double angentrevectores(Vertice a, Vertice b) {
    double prodvertices = a.x * b.x + a.y * b.y;
    double magnitudA = sqrt(a.x * a.x + a.y * a.y);
    double magnitudB = sqrt(b.x * b.x + b.y * b.y);

    return acos(prodvertices / (magnitudA * magnitudB));
}

int ordenvertices(const void *a, const void *b) {
    Vertice verticeA = *(Vertice *)a;
    Vertice verticeB = *(Vertice *)b;
    double angA = atan2(verticeA.y, verticeA.x);
    double angB = atan2(verticeB.y, verticeB.x);
    return (angA > angB) - (angA < angB);
}

void centro(Vertice *vertices, int numVertices) {
    // Calcular el centroide del polígono
    Vertice centropol = {0.0, 0.0};
    for (int i = 0; i < numVertices; ++i) {
        centropol.x += vertices[i].x;
        centropol.y += vertices[i].y;
    }
    centropol.x /= numVertices;
    centropol.y /= numVertices;

    qsort(vertices, numVertices, sizeof(Vertice), ordenvertices);
}

int convexidad(Vertice *vertices, int numVertices) {
    int signo = 0;
    for (int i = 0; i < numVertices; ++i) {
        Vertice ini = vertices[(i - 1 + numVertices) % numVertices];
        Vertice act = vertices[i];
        Vertice fin = vertices[(i + 1) % numVertices];

        Vertice vector1 = {ini.x - act.x, ini.y - act.y};
        Vertice vector2 = {fin.x - act.x, fin.y - act.y};

        double pcruz = prodcruz(vector1, vector2);

        if (pcruz != 0) {
            if (signo == 0) {
                signo = (pcruz > 0) ? 1 : -1;
            } else if ((pcruz > 0 && signo == -1) || (pcruz < 0 && signo == 1)) {
                return 0; // Cóncavo
            }
        }
    }

    return 1; // Convexo
}

void angulosinternos(Vertice *vertices, int numVertices) {
    if (numVertices < 3) {
        printf("El poligono debe tener al menos 3 vertices.\n");
        return;
    }

    centro(vertices, numVertices);

    printf("El poligono es %s.\n", convexidad(vertices, numVertices) ? "convexo" : "concavo");

    for (int i = 0; i < numVertices; ++i) {
        Vertice ini = vertices[(i - 1 + numVertices) % numVertices];
        Vertice act = vertices[i];
        Vertice fin = vertices[(i + 1) % numVertices];

        Vertice vector1 = {ini.x - act.x, ini.y - act.y};
        Vertice vector2 = {fin.x - act.x, fin.y - act.y};

        double pcruz = prodcruz(vector1, vector2);
        double ang = angentrevectores(vector1, vector2);

        ang = ang * 180 / M_PI;

        printf("Ángulo en el vértice %d: %.2f\n", i, ang);
    }
}

int main() {
    int numVertices;
    printf("Ingrese el número de vértices del poligono: ");
    scanf("%d", &numVertices);

    if (numVertices < 3) {
        printf("El poligono debe tener al menos 3 vertices.\n");
        return 1;
    }

    Vertice *vertices = (Vertice *)malloc(numVertices * sizeof(Vertice));

    printf("Ingrese las coordenadas de los vértices:\n");
    for (int i = 0; i < numVertices; ++i) {
        printf("Vértice %d: ", i + 1);
        scanf("%lf %lf", &(vertices[i].x), &(vertices[i].y));
    }

    angulosinternos(vertices, numVertices);

    free(vertices);

    return 0;
}
