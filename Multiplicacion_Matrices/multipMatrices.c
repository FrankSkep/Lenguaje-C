#include <stdio.h>
#define COLS1 3
#define ROWS1 2
#define COLS2 2
#define ROWS2 3

void multiplicar(int A[ROWS1][COLS1], int B[ROWS2][COLS2], int C[ROWS2][COLS1]);
void imprimirResult(int C[ROWS2][COLS1]);

int main()
{
    int matA[ROWS1][COLS1] = {{4, 2, 3},
                              {4, 4, 7}};

    int matB[ROWS2][COLS2] = {{2, 2},
                              {3, 3},
                              {5, 6}};
    int matC[ROWS2][COLS1]; // Resultante

    multiplicar(matA, matB, matC);

    printf("\n> Resultado de multiplicacion de matrices: [\tC\t]\n\n");
    imprimirResult(matC);
    printf("\n");
}

void multiplicar(int A[ROWS1][COLS1], int B[ROWS2][COLS2], int C[ROWS2][COLS1])
{
    int i, j, k;

    for (i = 0; i < ROWS2; i++)
    {
        for (j = 0; j < COLS1; j++)
        {
            C[i][j] = 0;                // acumulador de resultado celda 0,0
            for (k = 0; k < COLS2; k++) // columnas de la segunda matriz
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimirResult(int C[ROWS2][COLS1])
{
    for (int i = 0; i < ROWS2; i++)
    {
        printf("[");
        for (int j = 0; j < COLS1; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("]\n");
    }
}