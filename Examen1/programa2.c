#include <stdio.h>
#include <stdlib.h>

int sumaNumeros(int nums[], int m);
void leerCadena(const char msg[], char cad[]);

int main()
{
    char strs[4][30];
    for(int i = 0; i < 4; i++)
    {
        leerCadena("> Ingrese cadena: ", strs[i]);
    }

    int arrNumeros[4] = {atoi(strs[0]), atoi(strs[1]), atoi(strs[2]), atoi(strs[3])};
    int suma = sumaNumeros(arrNumeros, 4);
    printf("La suma de los numeros es: %d", suma);
}

int sumaNumeros(int nums[], int m)
{
    int suma = 0;
    for(int i = 0; i < m; i++)
    {
        suma += nums[i];
    }
    return suma;
}

void leerCadena(const char msg[], char cad[])
{
    printf("%s", msg);
    gets(cad);
}