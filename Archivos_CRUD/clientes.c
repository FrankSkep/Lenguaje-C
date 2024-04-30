#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define N 100

// imprimir los que numero de cuenta sea diferente de cero
// fwrite
// solo listar los que tengan num cuenta diferente de cero
// posicion: 50 ejemplo (50 - 1) * tam struct
// solo modificar balance
// si es diferente de cero, deja modificar
// SEEK_SET

typedef struct _DatosCliente
{
    int numCuenta;
    char nombre[30];
    char apellidos[40];
    float balance;
} Tcliente;

int menu();
void leerNombArch(char msg[], char nom[]);
void insertar(FILE *arch, char nom[]);
void borrar(FILE *arch, char nom[]);
void modificar(FILE *arch, char nom[]);

void crearDat(FILE *arch, char nom[]);
void listar(FILE *arch, char nom[]);

void leerCad(const char msg[], char cadena[], int largo);
int leerInt(const char msg[], int ri, int rf);
float leerFloat(const char msg[], float ri, float rf);

int main()
{
    FILE *arch;
    Tcliente regVacio = {0, "", "", 0};
    char nomArch[30];

    int op;
    do
    {
        op = menu();
        system("cls");
        switch (op)
        {
        case 1:
            leerNombArch("> Ingrese nombre de archivo: ", nomArch);
            crearDat(arch, nomArch);
            // arch = fopen(nomArch, "wb");
            // for (int i = 0; i < 100; i++)
            // {
            //     fwrite(&regVacio, sizeof(Tcliente), 1, arch);
            // }
            // fclose(arch);
            // printf("* Archivo creado con exito. *\n");
            break;

        case 2:
            // respaldar archivo
            break;

        case 3:
            // restaurar archivo
            break;

        case 4: // INSERTAR DATOS
            leerNombArch("> Nombre de archivo a insertar datos: ", nomArch);
            insertar(arch, nomArch);
            break;

        case 5: // BORRAR
            leerNombArch("> Nombre de archivo del que desea eliminar: ", nomArch);
            borrar(arch, nomArch);
            break;

        case 6:
            leerNombArch("> Nombre de archivo que va modificar: ", nomArch);
            modificar(arch, nomArch);
            break;

        case 7: // LISTAR
            leerNombArch("> Nombre de archivo a listar: ", nomArch);
            listar(arch, nomArch);
            break;
        }
        system("PAUSE");
    } while (op != 0);
}

int menu()
{
    system("cls");
    printf("\t|= SISTEMA DE CUENTAS BANCARIAS =|\n");
    printf("1. Crear archivo .dat (100 Registros)\n");
    printf("2. Respaldar archivo\n");
    printf("3. Restaurar archivo\n");
    printf("4. Insertar\n");
    printf("5. Borrar\n");
    printf("6. Modificar\n");
    printf("7. Listar\n");
    printf("8. Salir\n");
    int op = leerInt("Escoge una opcion: ", 1, 8);
    return op;
}

void leerNombArch(char msg[], char nom[])
{
    leerCad(msg, nom, 30);
    strcat(nom, ".dat");
}

void crearDat(FILE *arch, char nom[])
{
    Tcliente regVacio = {0, "", "", 0};
    arch = fopen(nom, "wb");
    for (int i = 0; i < N; i++)
    {
        fwrite(&regVacio, sizeof(Tcliente), 1, arch);
    }
    printf("* Archivo creado con exito. *\n");
    fclose(arch);
}

void insertar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch == NULL)
    {
        printf("* El archivo no existe. *\n");
        return;
    }

    system("cls");
    printf("\t|= INSERTAR DATOS =|\n\n");

    Tcliente reg;
    int pos;
    // --- Verificar que la posicion no este ocupada ---
    do
    {
        pos = leerInt("> Posicion en que desea guardar su registro [0, 99]: ", 0, 99);
        fseek(arch, pos * sizeof(Tcliente), SEEK_SET); // Mover el cursor a la posicion dada
        fread(&reg, sizeof(Tcliente), 1, arch);        // Leer el registro en esa posición

        if (reg.numCuenta != 0)
        {
            printf("La posicion ya esta ocupada. Elija otra posicion.\n");
        }
    } while (reg.numCuenta != 0);

    // ---- Datos nuevo cliente ----
    reg.numCuenta = leerInt("> Ingresa numero de cuenta: ", 1000, 9999);
    leerCad("> Ingrese su nombre: ", reg.nombre, 30);
    leerCad("> Ingrese sus apellidos: ", reg.apellidos, 40);
    reg.balance = leerFloat("> Ingrese su balance: ", 0, 2000000);

    // --- Escribir los datos en la posicion dada ---
    fseek(arch, pos * sizeof(Tcliente), SEEK_SET); // Mover cursor ala posicion
    fwrite(&reg, sizeof(Tcliente), 1, arch);       // Escribir el registro en la posicion

    printf("\n* Registro agregado exitosamente. *\n");
    fclose(arch);
}

void borrar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch == NULL)
    {
        printf("* Error, el archivo no existe. *\n");
        fclose(arch);
        return;
    }

    int cuenta = leerInt("> Ingrese no. cuenta a eliminar: ", 1000, 9999);

    Tcliente reg;
    fseek(arch, 0, SEEK_SET);
    while (fread(&reg, sizeof(Tcliente), 1, arch))
    {
        if (reg.numCuenta == cuenta)
        {
            reg.numCuenta = 0;
            reg.nombre[0] = '\0';
            reg.apellidos[0] = '\0';
            reg.balance = 0;

            fseek(arch, (long int)-sizeof(Tcliente), SEEK_CUR);
            fwrite(&reg, sizeof(Tcliente), 1, arch);
            printf("* Registro eliminado exitosamente. *\n");
            fclose(arch);
            return;
        }
    }
    printf("* El numero de cuenta: %d no existe. *\n", cuenta);
    fclose(arch);
}

void modificar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");
    if (arch == NULL)
    {
        printf("* El archivo no existe. *\n");
        return;
    }

    int cuenta = leerInt("> Ingrese no. cuenta a modificar: ", 1000, 9999);

    Tcliente reg;
    fseek(arch, 0, SEEK_SET);
    while (fread(&reg, sizeof(Tcliente), 1, arch))
    {
        if (reg.numCuenta == cuenta)
        {
            float balance = leerFloat("> Ingrese balance (+) Cargo | (-) Abono: ", -1000000, 2000000);

            if (balance < 0) // Si es Abono
            {
                if (fabs(balance) > reg.balance)
                {
                    printf("* Error cargo, balance insuficiente. *\n");
                    fclose(arch);
                    return;
                }
                else
                {
                    reg.balance += balance;
                    printf("* Abono exitoso. (-) *\n");
                }
            }
            else // Si es cargo
            {
                reg.balance += balance;
                printf("* Cargo exitoso. *\n");
            }
            // Guardar cambios en el archivo
            fseek(arch, (long int)-sizeof(Tcliente), SEEK_CUR);
            fwrite(&reg, sizeof(Tcliente), 1, arch);
            fclose(arch);
            return;
        }
    }
    printf("* Cuenta no existente. *\n");
    fclose(arch);
}

void listar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb");

    if (arch == NULL)
    {
        printf("* El archivo no existe. *\n");
        return;
    }

    system("cls");
    Tcliente cliente;
    printf("+---------------------------------------------------------------------------+\n");
    printf("| Cuenta |        Nombre        |          Apellidos          |   Balance   |\n");
    printf("|---------------------------------------------------------------------------|\n");
    while (fread(&cliente, sizeof(Tcliente), 1, arch))
    {
        if (cliente.numCuenta != 0)
        {
            printf("|  %-4d  | %-20s | %-27s | %-8.2f    |\n", cliente.numCuenta, cliente.nombre, cliente.apellidos, cliente.balance);
        }
    }
    printf("+---------------------------------------------------------------------------+\n");
    fclose(arch);
}

// Lee cadena con fgets
void leerCad(const char msg[], char cadena[], int largo)
{
    printf("%s", msg);
    fgets(cadena, largo, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

// (+) Cargo, (-) Abono

int leerInt(const char msg[], int ri, int rf)
{
    char charNum[25] = "";
    int num = ri - 1;
    do
    {
        printf("%s", msg);
        fgets(charNum, sizeof(charNum), stdin);
        charNum[strcspn(charNum, "\n")] = '\0';
        sscanf(charNum, "%d", &num);
    } while (num < ri || num > rf);
    return num;
}

float leerFloat(const char msg[], float ri, float rf)
{
    char charNum[25] = "";
    float num = ri - 1;
    do
    {
        printf("%s", msg);
        fgets(charNum, sizeof(charNum), stdin);
        charNum[strcspn(charNum, "\n")] = '\0';
        sscanf(charNum, "%f", &num);
    } while (num < ri || num > rf);
    return num;
}