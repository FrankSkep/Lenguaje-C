#include <stdio.h>
#include <stdlib.h>

void leerCadena(const char msg[], char cad[]);

int main()
{
    char strs[4][30];
    int suma = 0;
    for (int i = 0; i < 4; i++)
    {
        leerCadena("> Ingrese cadena: ", strs[i]);
        suma += atoi(strs[i]);
    }
    printf("La suma de los numeros es: %d", suma);
}

void leerCadena(const char msg[], char cad[])
{
    printf("%s", msg);
    gets(cad);
}
