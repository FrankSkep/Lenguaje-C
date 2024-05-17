#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

/*-------- STRUCT MULTIMEDIA --------*/
typedef struct
{
    char clave[10];
    char titulo[30];
    int categoria;
    int tipo;
} Multim;

/*--------- PROTOTIPOS FUNCIONES ---------*/
int menu();
void insertar(Multim movies[], int *cont);
void borrar(Multim movies[], int *cont);
void modificar(Multim movies[], int *cont);
void listar(Multim movies[], int *cont);
void buscar(Multim movies[], int *cont);
void asignarCategTipo(Multim movies[], char categ[], char tipo[], int indice);

// Funciones auxiliares
void leerCadena(const char msg[], char cadena[], int largo);
int leerInt(const char msg[], int ri, int rf);

int main()
{
    Multim movies[N];
    int cont = 0;

    int op;
    do
    {
        system("cls");
        op = menu();
        switch (op)
        {
        case 1:
            insertar(movies, &cont);
            break;
        case 2:
            borrar(movies, &cont);
            break;
        case 3:
            modificar(movies, &cont);
            break;
        case 4:
            listar(movies, &cont);
            break;
        case 5:
            buscar(movies, &cont);
            break;
        case 0:
            printf("> Has salido <\n");
            break;
        default:
            printf("Opcion no existente.\n");
            break;
        }
        system("pause");
    } while (op != 0);

    return 0;
}

/*--------- DESARROLLO FUNCIONES ---------*/

// Muestra menu y lee opcion
int menu()
{
    int op;
    printf("-------------------------------------------------------\n");
    printf("\t    GESTION DE CONTENIDO MULTIMEDIA\n");
    printf("-------------------------------------------------------\n");
    printf("1. Insertar\n");
    printf("2. Borrar\n");
    printf("3. Modificar\n");
    printf("4. Listar\n");
    printf("5. Buscar\n");
    printf("0. Salir\n");
    op = leerInt("> Escoge una opcion: ", 0, 5);
    system("cls");
    return op;
}

// Recibe la estructura y el contador
void insertar(Multim movies[], int *cont)
{
    int existe = 0; // Bandera para determinar si ya existe esa clave

    printf("\t[ Registrando pelicula / serie #%d ]\n\n", *cont + 1);

    // Entrada de clave no repetida
    do
    {
        leerCadena("> Ingresa clave: ", movies[*cont].clave, 10);

        for (int i = 0; i < *cont; i++) // Verifica si la clave no existe ya
        {
            if (strcmp(movies[i].clave, movies[*cont].clave) == 0)
            {
                printf("* La clave ya existe, ingrese nuevamente *\n");
                existe = 1;
            }
            else
            {
                existe = 0;
            }
        }
    } while (existe == 1);

    // Entrada de titulo
    leerCadena("> Ingresa titulo: ", movies[*cont].titulo, 30);

    // Entrada de categoria
    printf("\n\t* Categoria *\n");
    printf("1.-Accion\n2.-Terror\n3.-Thriller\n");
    movies[*cont].categoria = leerInt("> Ingresa categoria: ", 1, 3);

    // Entrada de tipo
    printf("\n\t* Tipo *\n");
    printf("1.-CD\n2.-DVD\n3.-Blueray\n");
    movies[*cont].tipo = leerInt("> Ingresa tipo: ", 1, 3);

    // Mensaje
    system("cls");
    printf("* Elemento agregado exitosamente. *\n\n");
    (*cont)++; // Incrementar contador
}

// Borra un elemento mediante su indice
void borrar(Multim movies[], int *cont)
{
    int num;    // numero elemento a eliminar
    int indice; // definir indice

    listar(movies, cont); // Mostrar elementos disponibles a eliminar

    num = leerInt("\n> No. de elemento a eliminar: ", 0, *cont);

    indice = num - 1;

    if (indice < 0 || indice >= *cont)
    {
        printf("> Elemento no existente\n");
        return;
    }

    // Elimina el elemento en el indice ingresado
    printf("\n> Elemento eliminado: %s : %s\n\n", movies[indice].clave, movies[indice].titulo);

    // Mueve un indice atras los elementos posteriores al eliminado
    for (int i = indice; i < *cont; i++)
    {
        strcpy(movies[i].clave, movies[i + 1].clave);
        strcpy(movies[i].titulo, movies[i + 1].titulo);
        movies[i].categoria = movies[i + 1].categoria;
        movies[i].tipo = movies[i + 1].tipo;
    }
    (*cont)--; // Decrementar contador
}

// Modifica elementos de la estructura
void modificar(Multim movies[], int *cont)
{
    int indice, num, op;

    listar(movies, cont);
    num = leerInt("\n> Ingresa No. de elemento a modificar: ", 0, *cont);
    indice = num - 1; // Convertir numero ingresado a indice para iterar arreglo

    if (indice < 0 || indice >= *cont)
    {
        printf("> Elemento no existente\n");
        return;
    }

    // Pedir datos a modificar
    printf("\nQue parametro deseas modificar: \n");
    printf("1. Clave\n");
    printf("2. Titulo\n");
    printf("3. Categoria\n");
    printf("4. Tipo\n");
    op = leerInt("> ", 1, 4);

    switch (op)
    {
    case 1:
        leerCadena("Ingresa nueva clave: ", movies[indice].clave, 10);
        break;
    case 2:
        leerCadena("Ingresa nuevo titulo: ", movies[indice].titulo, 30);
        break;
    case 3:
        printf("*Categorias*\n1.-Accion\n2.-Terror\n3.-Thriller\n");
        movies[indice].categoria = leerInt("> ", 1, 3);
        break;
    case 4:
        printf("*Tipos*\n1.-CD\n2.-DVD\n3.-Blueray\n");
        movies[indice].tipo = leerInt("> ", 1, 3);
        break;
    default:
        printf("Ingrese una opcion valida.\n");
        break;
    }
    printf("\n> Elemento modificado exitosamente.\n");
}

// Muestra todos los elementos existentes
void listar(Multim movies[], int *cont)
{
    char categ[11] = "", tipo[11] = ""; // Variables temporales para nombre de categoria y tipo
    printf("----------------------------------------------------------------------------------\n");
    printf("|  No. |    Clave    |            Titulo            |   Categoria   |    Tipo    |\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < *cont; i++)
    {
        asignarCategTipo(movies, categ, tipo, i); // Asignar leyenda de categoria y tipo

        printf("| %4d | %-11s | %-28s | %-13s | %-10s |\n", i + 1, movies[i].clave, movies[i].titulo, categ, tipo);
    }
    printf("----------------------------------------------------------------------------------\n");
}

// Busca un elemento especifico por su clave
void buscar(Multim movies[], int *cont)
{
    char clave[10];                     // Variable para leer la clave a buscar
    char categ[11] = "", tipo[11] = ""; // Variables temporales para mostrar nombre de cat y tipo

    leerCadena("> Ingresa clave de elemento a buscar: ", clave, 10);

    for (int i = 0; i < *cont; i++)
    {
        if (strcmp(movies[i].clave, clave) == 0)
        {
            asignarCategTipo(movies, categ, tipo, i);
            printf("\n> Elemento encontrado. \n[ Datos ]\n\n");
            printf("* Posicion: %d\n", i + 1);
            printf("* Clave: %s\n", clave);
            printf("* Titulo: %s\n", movies[i].titulo);
            printf("* Categoria: %s\n", categ);
            printf("* Tipo: %s\n", tipo);
            return; // Sale de la funcion al encontrar el elemento
        }
    }
    // Si termina el ciclo, no existe el elemento
    printf("> Elemento no existente.\n\n");
}

// Funcion para pasar de int a char 'categoria y tipo'
void asignarCategTipo(Multim movies[], char categ[], char tipo[], int indice)
{
    // Definir nombre de 'Categoria'
    switch (movies[indice].categoria)
    {
    case 1:
        strcpy(categ, "Accion");
        break;
    case 2:
        strcpy(categ, "Terror");
        break;
    case 3:
        strcpy(categ, "Thriller");
        break;
    default:
        strcpy(categ, "Indefinido");
        break;
    }

    // Definir nombre de 'tipo'
    switch (movies[indice].tipo)
    {
    case 1:
        strcpy(tipo, "CD");
        break;
    case 2:
        strcpy(tipo, "DVD");
        break;
    case 3:
        strcpy(tipo, "Blueray");
        break;
    default:
        strcpy(tipo, "Indefinido");
        break;
    }
}

// Presentar un mensaje y Leer cadena con fgets
void leerCadena(const char msg[], char cadena[], int largo)
{
    printf("%s", msg);
    fgets(cadena, largo, stdin);
    cadena[strcspn(cadena, "\n")] = '\0'; // Eliminar salto de linea
}

// Valida entrada de un numero entero
int leerInt(const char msg[], int ri, int rf)
{
    int num = -1;
    char charNum[25];
    do
    {
        printf("%s", msg);
        fgets(charNum, sizeof(charNum), stdin);
        charNum[strcspn(charNum, "\n")] = '\0'; // Eliminar salto de linea
        sscanf(charNum, "%d", &num);
        if (num < ri || num > rf)
        {
            printf("* Entrada no valida, ingrese nuevamente *\n");
        }
    } while (num < ri || num > rf);
    return num;
}