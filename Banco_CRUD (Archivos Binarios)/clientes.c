#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

#define N 100

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
void mostrarDatos(Tcliente reg);
void modificar(FILE *arch, char nom[]);
void crearDat(FILE *arch, char nom[]);
void respaldar(FILE *arch, char nom[]);
void listar(FILE *arch, char nom[]);

// Funciones auxiliares
int cuentaNoRepetida(FILE *arch, char nom[]);
void leerNombArch(char msg[], char nom[], const char ext[]);
void leerCad(const char msg[], char cadena[], int largo);
int leerInt(const char msg[], int ri, int rf);
float leerFloat(const char msg[], float ri, float rf);

int main()
{
    FILE *arch;
    char nomArch[30] = "banco.dat", nomArchCrear[30];
    int op;

    do
    {
        op = menu();
        system("cls");
        switch (op)
        {
        case 1: // CREAR .DAT
            leerNombArch("> Ingrese nombre de archivo: ", nomArchCrear, ".dat");
            crearDat(arch, nomArchCrear);
            break;

        case 2: // RESPALDAR .dat EN .txt
            respaldar(arch, nomArch);
            break;

        case 3: // INSERTAR DATOS
            insertar(arch, nomArch);
            break;

        case 4: // BORRAR
            borrar(arch, nomArch);
            break;

        case 5: // MODIFICAR
            modificar(arch, nomArch);
            break;

        case 6: // LISTAR
            listar(arch, nomArch);
            break;

        case 7: // CAMBIAR ARCHIVO
            do
            {
                leerNombArch("> Ingresa nombre del archivo con el que deseas trabajar (Debe existir): ", nomArch, ".dat");
            } while (access(nomArch, F_OK));
            break;

        case 8:
            printf("* HAS SALIDO. *\n");
            break;
        }
        system("PAUSE");
    } while (op != 8);
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
    printf("7. Cambiar archivo de operaciones\n");
    printf("8. Salir\n");
    int op = leerInt("Escoge una opcion: ", 1, 8);
    return op;
}

void crearDat(FILE *arch, char nom[])
{
    if (!access(nom, F_OK))
    {
        printf("* El archivo '%s' ya existe, desea sobreescribirlo?\n", nom);
        if (leerInt("[1. Si | 2. No]: ", 1, 2) == 2)
        {
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

    if (arch)
    {
        printf("-| Respaldando archivo '%s' |-\n\n", nom);
        // --- Respaldar el archivo ---
        FILE *archResp;
        char nomRespal[30];
        leerNombArch("> Ingresa nombre para el respaldo: ", nomRespal, ".txt");
        archResp = fopen(nomRespal, "w"); // Crear archivo para respaldo

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
    else
    {
        printf("* El archivo '%s' no existe. *\n", nom);
    }
}

void insertar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch)
    {
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
        reg.numCuenta = cuentaNoRepetida(arch, nom);
        leerCad("> Ingrese su nombre: ", reg.nombre, 30);
        leerCad("> Ingrese sus apellidos: ", reg.apellidos, 40);
        reg.balance = leerFloat("> Ingrese su balance: ", 0, 2000000);

        // --- Escribir los datos en la posicion dada ---
        fseek(arch, (pos - 1) * sizeof(Tcliente), SEEK_SET); // Mover cursor ala posicion
        fwrite(&reg, sizeof(Tcliente), 1, arch);

        printf("\n* Registro agregado exitosamente. *\n");
        fclose(arch);
    }
    else
    {
        printf("* El archivo '%s' no existe. *\n", nom);
    }
}

int cuentaNoRepetida(FILE *arch, char nom[])
{
    Tcliente reg;

    bool cuentaExistente;
    int numCuenta;

    do
    {
        cuentaExistente = false;
        numCuenta = leerInt("> Ingresa numero de cuenta [1000, 9999]: ", 1000, 9999);

        fseek(arch, 0, SEEK_SET); // Mover al inicio del archivo antes de leer

        while (fread(&reg, sizeof(Tcliente), 1, arch))
        {
            if (numCuenta == reg.numCuenta)
            {
                cuentaExistente = true;
            }
        }
    } while (cuentaExistente);

    return numCuenta;
}

void borrar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch)
    {
        printf("-| Borrando en archivo '%s' |-\n\n", nom);
        int cuenta = leerInt("> Ingrese no. cuenta a eliminar [1000, 9999]: ", 1000, 9999);

        Tcliente reg;
        fseek(arch, 0, SEEK_SET);
        int op;
        while (fread(&reg, sizeof(Tcliente), 1, arch))
        {
            if (reg.numCuenta == cuenta)
            {
                mostrarDatos(reg);

                if (leerInt("* Desea eliminar? [1. Si | 2. No]: ", 1, 2) == 1)
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
                else
                {
                    printf("* Eliminacion cancelada. *\n");
                    return;
                }
            }
        }
        printf("* La cuenta '%d' no existe. *\n", cuenta);
        fclose(arch);
    }
    else
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        fclose(arch);
    }
}

void mostrarDatos(Tcliente reg)
{
    printf("\n-| DATOS CLIENTE |-\n");
    printf("* Cuenta: %d\n", reg.numCuenta);
    printf("* Nombre: %s\n", reg.nombre);
    printf("* Apellios: %s\n", reg.apellidos);
    printf("* Balance: %.2f\n\n", reg.balance);
}

void modificar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb+");

    if (arch)
    {
        printf("-| Modificando archivo '%s' |-\n\n", nom);
        int cuenta = leerInt("> Ingrese no. cuenta a modificar: ", 1000, 9999);

        Tcliente reg;
        int op;
        fseek(arch, 0, SEEK_SET);
        while (fread(&reg, sizeof(Tcliente), 1, arch))
        {
            if (reg.numCuenta == cuenta)
            {
                mostrarDatos(reg);
                op = leerInt("* Desea modificar su balance? [1. Si | 2. No]: ", 1, 2);

                if (op == 1)
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
                else
                {
                    printf("* Modificacion cancelada. *\n");
                    return;
                }
            }
        }
        printf("* La cuenta '%d' no existe. *\n", cuenta);
        fclose(arch);
    }
    else
    {
        printf("* El archivo '%s' no existe. *\n", nom);
    }
}

void listar(FILE *arch, char nom[])
{
    arch = fopen(nom, "rb");

    if (arch)
    {
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
    else
    {
        printf("* El archivo '%s' no existe. *\n", nom);
        return;
    }
}

// Funciones auxiliares
void leerNombArch(char msg[], char nom[], const char ext[])
{
    leerCad(msg, nom, 30);
    strcat(nom, ext);
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