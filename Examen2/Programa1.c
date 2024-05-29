/* Programa que lea nombre y calificacion de N alumnos, los guarde en una estructura, y imprima el nombre
del estudiante con la calificacion msa alta */

#include <stdio.h>
#define N 3

typedef struct estudiante
{
    char nombre[30];
    float calif;
} Testudiante;

int main()
{
    Testudiante estudiantes[N];
    Testudiante masAlto = {"", 0.0};

    for (int i = 0; i < N; i++)
    {
        printf("Ingrese su nombre: ");
        gets(estudiantes[i].nombre);
        printf("Ingrese su calificacion: ");
        scanf("%f", &estudiantes[i].calif);
        scanf("%*c");

        if (estudiantes[i].calif > masAlto.calif)
        {
            masAlto = estudiantes[i];
        }
    }
    printf("Estudiante con mejor calificacion: %s : %.2f\n", masAlto.nombre, masAlto.calif);
}