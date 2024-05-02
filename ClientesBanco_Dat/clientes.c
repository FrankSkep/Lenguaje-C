#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 100

// imprimir los que numero de cuenta sea diferente de cero
// posicion: 50 ejemplo (50 - 1) * tam struct
// solo modificar balance
// si es diferente de cero, deja modificar

typedef struct _DatosCliente
{
    int numCuenta;
    char nombre[30];
    char apellidos[40];
    float balance;
} Tcliente;

int menu();
void insertar(FILE *arch, char nom[]);
void borrar(FILE *arch, char nom[]);
void modificar(FILE *arch, char nom[]);
void crearDat(FILE *arch, char nom[]);
void respaldar(FILE *arch, char nom[]);
void listar(FILE *arch, char nom[]);

// Funciones auxiliares
void leerNombArch(char msg[], char nom[], const char ext[]);
bool NoExisteArchivo(FILE *archivo);
void leerCad(const char msg[], char cadena[], int largo);
int leerInt(const char msg[], int ri, int rf);
float leerFloat(const char msg[], float ri, float rf);

int main()
{
    FILE *arch;
    char nomArch[30];

    int op;
    do
    {
        op = menu();
        system("cls");
        switch (op)
        {
        case 1: // CREAR .DAT
            leerNombArch("> Ingrese nombre de archivo: ", nomArch, ".dat");
            crearDat(arch, nomArch);
            break;

        case 2: // RESPALDAR .dat EN .txt
            leerNombArch("> Ingrese nombre de archivo a respaldar: ", nomArch, ".dat");
            respaldar(arch, nomArch);
            break;

        case 3: // INSERTAR DATOS
            leerNombArch("> Nombre de archivo a insertar datos: ", nomArch, ".dat");
            insertar(arch, nomArch);
            break;

        case 4: // BORRAR
            leerNombArch("> Nombre de archivo del que desea eliminar: ", nomArch, ".dat");
            borrar(arch, nomArch);
            break;

        case 5: // MODIFICAR
            leerNombArch("> Nombre de archivo que desea modificar: ", nomArch, ".dat");
            modificar(arch, nomArch);
            break;

        case 6: // LISTAR
            leerNombArch("> Nombre de archivo a listar: ", nomArch, ".dat");
            listar(arch, nomArch);
            break;

        case 7:
            printf("* HAS SALIDO. *\n");
            break;
        }
        system("PAUSE");
    } while (op != 7);
}

int menu()
{
    system("cls");
    printf("\t-|= CLIENTES BANCO =|-\n\n");
    printf("1. Crear archivo .dat (100 Registros)\n");
    printf("2. Respaldar archivo a .txt\n");
    printf("3. Insertar registro\n");
    printf("4. Borrar registro\n");
    printf("5. Modificar balance\n");
    printf("6. Listar registros\n");
    printf("7. Salir\n");
    int op = leerInt("Escoge una opcion: ", 1, 8);
    return op;
}

void crearDat(FILE *arch, char nom[])
{
    int op;
    arch = fopen(nom, "rb");
    if (arch != NULL)
    {
        printf("* El archivo '%s' ya existe, desea sobreescribirlo?\n", nom);
        op = leerInt("[1. Si | 2. No]: ", 1, 2);
        if (op != 1)
        {
            fclose(arch);
            return;
        }
    }

    // Inicializar archivo con datos vacios
    Tcliente regVacio = {0, "", "", 0};
    arch = fopen(nom, "wb");
    for (int i = 0; i < N; i++)
    {
        fwrite(&regVacio, sizeof(Tcliente), 1, arch);
    }
    system("cls");
    printf("\n* Archivo '%s' creado e inicializado con exito. *\n\n", nom);
    fclose(arch);
}

void respaldar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb");

    if (arch == NULL)
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        return;
    }

    printf("-| Respaldando archivo '%s' |-\n\n", nom);
    // --- Respaldar el archivo ---
    FILE *archResp;
    char nomRespal[30];
    leerNombArch("> Ingresa nombre para el respaldo: ", nomRespal, ".txt");
    archResp = fopen(nomRespal, "w");

    Tcliente reg;
    int i = 0;
    fprintf(archResp, "+-------------------------------------------------------------------------------------------+\n");
    fprintf(archResp, "| No. Reg | No. Cuenta |        Nombre        |          Apellidos          |    Balance    |\n");
    fprintf(archResp, "|-------------------------------------------------------------------------------------------|\n");
    while (fread(&reg, sizeof(Tcliente), 1, arch))
    {
        if (reg.numCuenta != 0)
        {
            fprintf(archResp, "| %-7d |  %-8d  | %-20s | %-27s | %-13.2f |\n", i + 1, reg.numCuenta, reg.nombre, reg.apellidos, reg.balance);
        }
        i++;
    }
    fprintf(archResp, "+-------------------------------------------------------------------------------------------+\n");
    printf("* Archivo '%s' respaldado correctamente en '%s'. *\n", nom, nomRespal);

    fclose(arch);
    fclose(archResp);
}

void insertar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch == NULL)
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        return;
    }

    system("cls");
    printf("-| Insertando datos en archivo '%s' |-\n\n", nom);

    Tcliente reg;
    int pos;
    // --- Verificar que la posicion no este ocupada ---
    do
    {
        pos = leerInt("> Posicion en que desea guardar su registro [1, 100]: ", 1, 100);
        fseek(arch, (pos - 1) * sizeof(Tcliente), SEEK_SET);
        fread(&reg, sizeof(Tcliente), 1, arch); // Leer registro de posicion dada

        if (reg.numCuenta != 0)
        {
            printf("La posicion ya esta ocupada. Elija otra posicion.\n");
        }
    } while (reg.numCuenta != 0);

    // ---- Datos nuevo cliente ----
    reg.numCuenta = leerInt("> Ingresa numero de cuenta [1000, 9999]: ", 1000, 9999);
    leerCad("> Ingrese su nombre: ", reg.nombre, 30);
    leerCad("> Ingrese sus apellidos: ", reg.apellidos, 40);
    reg.balance = leerFloat("> Ingrese su balance: ", 0, 2000000);

    // --- Escribir los datos en la posicion dada ---
    fseek(arch, (pos - 1) * sizeof(Tcliente), SEEK_SET); // Mover cursor ala posicion
    fwrite(&reg, sizeof(Tcliente), 1, arch);

    printf("\n* Registro agregado exitosamente. *\n");
    fclose(arch);
}

void borrar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch == NULL)
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        fclose(arch);
        return;
    }

    printf("-| Borrando en archivo '%s' |-\n\n", nom);
    int cuenta = leerInt("> Ingrese no. cuenta a eliminar [1000, 9999]: ", 1000, 9999);

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
    printf("* La cuenta '%d' no existe. *\n", cuenta);
    fclose(arch);
}

void modificar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");
    if (arch == NULL)
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        return;
    }

    printf("-| Modificando archivo '%s' |-\n\n", nom);
    int cuenta = leerInt("> Ingrese no. cuenta a modificar: ", 1000, 9999);

    Tcliente reg;
    fseek(arch, 0, SEEK_SET);
    while (fread(&reg, sizeof(Tcliente), 1, arch))
    {
        if (reg.numCuenta == cuenta)
        {
            float balance = leerFloat("> Ingrese monto (+) Cargo | (-) Abono: ", -1000000, 2000000);

            if (balance < 0) // Si es Abono
            {
                if (fabs(balance) > reg.balance)
                {
                    printf("* Error abono, balance insuficiente. *\n");
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
    printf("* La cuenta '%d' no existe. *\n", cuenta);
    fclose(arch);
}

void listar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb");

    if (arch == NULL)
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        return;
    }

    system("cls");
    printf("-| Listando archivo '%s' |-\n", nom);
    Tcliente cliente;
    int i = 0;
    printf("+-------------------------------------------------------------------------------------------+\n");
    printf("| No. Reg | No. Cuenta |        Nombre        |          Apellidos          |    Balance    |\n");
    printf("|-------------------------------------------------------------------------------------------|\n");
    while (fread(&cliente, sizeof(Tcliente), 1, arch))
    {
        if (cliente.numCuenta != 0)
        {
            printf("| %-7d |  %-8d  | %-20s | %-27s | %-13.2f |\n", i + 1, cliente.numCuenta, cliente.nombre, cliente.apellidos, cliente.balance);
        }
        i++;
    }
    printf("+-------------------------------------------------------------------------------------------+\n");
    fclose(arch);
}

// Funciones auxiliares
void leerNombArch(char msg[], char nom[], const char ext[])
{
    leerCad(msg, nom, 30);
    strcat(nom, ext);
}

// Verifica se pudo abrir un archivo
bool NoExisteArchivo(FILE *archivo)
{
    return (archivo == NULL);
}

// Lee cadena con fgets
void leerCad(const char msg[], char cadena[], int largo)
{
    printf("%s", msg);
    fgets(cadena, largo, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

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