#include <stdio.h>
#include <stdlib.h>
// Este programa está hecho por Garcia Reyes Arely Lizeth, Hernandez Barraza Alejandro y Lozano Perez Johan Andres

#define MAX 10  // Tamaño máximo de la matriz

// Prototipos de funciones
void leerMatriz(float matriz[MAX][MAX], float vector[MAX], int n);
void mostrarMatriz(float matriz[MAX][MAX], float vector[MAX], int n);
int esDominanteDiagonal(float matriz[MAX][MAX], int n);
float calcularDeterminante(float matriz[MAX][MAX], int n);
void corregirElemento(float matriz[MAX][MAX], int n);

int main() {
    int n;
    float matriz[MAX][MAX], vector[MAX];
    printf("Este programa esta hecho por Garcia Reyes Arely Lizeth, Hernandez Barraza Alejandro y Lozano Perez Johan Andres\n");

    printf("Introduce la dimension de la matriz (n x n): ");
    scanf("%d", &n);
    
    leerMatriz(matriz, vector, n);

    char opcion;
    printf("¿Los datos son correctos? (s/n): ");
    scanf(" %c", &opcion);
    
    if (opcion == 'n' || opcion == 'N') {
        corregirElemento(matriz, n);
    }
    else{  mostrarMatriz(matriz, vector, n);}

    float determinante = calcularDeterminante(matriz, n);
    printf("Determinante: %.2f\n", determinante);

    if (determinante == 0) {
        printf("El sistema asociado no tiene solucion.\n");
        return 0;
    }

    if (esDominanteDiagonal(matriz, n)) {
        printf("La matriz es dominante diagonal.\n");
    } else {
        printf("La matriz no es dominante diagonal.\n");
    }

    return 0;
}

// Función para leer la matriz y el vector independiente
void leerMatriz(float matriz[MAX][MAX], float vector[MAX], int n) {
    printf("Introduce los coeficientes de la matriz por renglon:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &matriz[i][j]);
        }
    }
    printf("Introduce los valores del vector independiente:\n");
    for (int i = 0; i < n; i++) {
        printf("Elemento [%d]: ", i + 1);
        scanf("%f", &vector[i]);
    }
}

// Función para mostrar la matriz y el vector independiente
void mostrarMatriz(float matriz[MAX][MAX], float vector[MAX], int n) {
    printf("Matriz y vector independiente:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", matriz[i][j]);
        }
        printf("| %.2f\n", vector[i]);
    }
}

// Función para verificar si la matriz es dominante diagonal
int esDominanteDiagonal(float matriz[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        float suma = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                suma += abs(matriz[i][j]);
            }
        }
        if (abs(matriz[i][i]) <= suma) {
            return 0;  // No es dominante diagonal
        }
    }
    return 1;  // Es dominante diagonal
}

// Función para corregir un elemento específico en la matriz
void corregirElemento(float matriz[MAX][MAX], int n) {
    int fila, columna;
    float nuevo_valor;

    printf("Introduce el número de fila y columna del elemento a corregir (1 a %d): ", n);
    scanf("%d %d", &fila, &columna);

    if (fila >= 1 && fila <= n && columna >= 1 && columna <= n) {
        printf("Introduce el nuevo valor para [%d][%d]: ", fila, columna);
        scanf("%f", &nuevo_valor);
        matriz[fila - 1][columna - 1] = nuevo_valor;
    } else {
        printf("Posición no valida.\n");
    }
}

// Función para calcular el determinante mediante eliminación de Gauss
float calcularDeterminante(float matriz[MAX][MAX], int n) {
    float temp[MAX][MAX];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = matriz[i][j];

    float det = 1;
    for (int i = 0; i < n; i++) {
        if (temp[i][i] == 0) {
            int swap_row = -1;
            for (int k = i + 1; k < n; k++) {
                if (temp[k][i] != 0) {
                    swap_row = k;
                    break;
                }
            }
            if (swap_row == -1) {
                return 0;  // Determinante es 0
            }
            for (int j = 0; j < n; j++) {
                float tmp = temp[i][j];
                temp[i][j] = temp[swap_row][j];
                temp[swap_row][j] = tmp;
            }
            det *= -1;
        }
        det *= temp[i][i];
        for (int j = i + 1; j < n; j++) {
            float factor = temp[j][i] / temp[i][i];
            for (int k = i; k < n; k++) {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    return det;
}
