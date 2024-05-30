/* Leer nombre y edad de una persona, escribirlas en un archivo llamado 'datos.txt'
 y imprimir contenido del archivo */

#include <stdio.h>

void generarTxt(char nombre[], int edad);

int main()
{
    char nombre[30];
    int edad;

    printf("Ingresa tu nombre: ");
    gets(nombre);
    printf("Ingresa tu edad: ");
    scanf("%d", &edad);
    generarTxt(nombre, edad);
}

void generarTxt(char nombre[], int edad)
{
    FILE *arch = fopen("datos.txt", "w");
    if (arch)
    {
        fprintf(arch, "%s-%d", nombre, edad);
        fclose(arch);

        arch = fopen("datos.txt", "r");
        if (arch)
        {
            char car;
            while ((car = fgetc(arch)) != EOF)
            {
                printf("%c", car);
            }
            fclose(arch);
        }
    }
}