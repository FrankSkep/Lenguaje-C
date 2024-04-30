#include <stdio.h>

// imprimir los que numero de cuenta sea diferente de cero
// fwrite
// solo listar los que tengan num cuenta diferente de cero
// posicion: (50 - 1) * tam struct
// solo modificar balance
// si es diferente de cero, deja modificar
// SEK_SET

typedef struct _DatosCliente
{
    int numCuenta;
    char nombre[30];
    char apellidos[40];
    float balance; // cantidad de dinero que tiene
}Tcliente;

void menu();
Tcliente registrar();

int main()
{
    FILE *arch;
    Tcliente regCliente = {0, "", "", 0};

    arch = fopen("arch.dat", "w");
    
    // posicion: (50 - 1) * tam struct

    // LLenar archivo con registros vacios
    for(int i = 0; i < 100; i++)
    {
        fwrite(&regCliente, sizeof(Tcliente), 1, arch);
    }
    Tcliente datoLeido;
    fread(&datoLeido, sizeof(Tcliente), 1, arch);
    printf("%d", datoLeido.numCuenta);
}

void menu()
{
    printf("1. Crear archivo .dat (100 Registros)\n");
    printf("2. Respaldar archivo\n");
    printf("3. Restaurar archivo\n");
    printf("4. Insertar\n");
    printf("5. Borrar\n");
    printf("6. Modificar\n");
    printf("7. Listar\n");
    printf("8. Salir\n");
}

// (+) Cargo, (-) Abono

Tcliente registrar()
{
    
}

void crearDat()
{

}