#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void copiarArchivo(FILE *Origen, FILE *Destino);
void getString(const char msg[], char cadena[], int size);

int main()
{
    FILE *archOrigen, *archDest;
    char nombreOrigen[30], nombreDest[30];

    int op;
    do
    {
        system("cls");
        printf("\t|= PROGRAMA PARA RESPALDAR ARCHIVOS =|\n");

        getString("\n> Ingresa nombre del archivo que deseas copiar: ", nombreOrigen, sizeof(nombreOrigen));
        strcat(nombreOrigen, ".txt");

        getString("\n> Ingresa nombre del archivo destino: ", nombreDest, sizeof(nombreDest));
        strcat(nombreDest, ".txt");

        archOrigen = fopen(nombreOrigen, "r"); // Abre en modo lectura el archivo origen

        if (archOrigen == NULL)
        {
            printf("\n* El archivo que desea copiar no existe. *\n\n");
            system("pause");
            continue;
        }
        // Abre o Crea el archivo destino, solo si existe el de origen
        archDest = fopen(nombreDest, "w");

        // Realizar la copia
        copiarArchivo(archOrigen, archDest);

        // Cerrar archivos
        fclose(archOrigen);
        fclose(archDest);

        printf("\n> Copia finalizada <\n");
        printf("Desea copiar otro archivo? [1- Si | 2- No]: ");
        scanf("%d", &op);
        scanf("%*c");

    } while (op != 2);
}

void copiarArchivo(FILE *Origen, FILE *Destino)
{
    char car;
    while ((car = fgetc(Origen)) != EOF)
    {
        fputc(car, Destino);
    }
}

void getString(const char msg[], char cadena[], int size)
{
    printf("%s", msg);
    fgets(cadena, size, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}