#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 50

/*-------- STRUCT MULTIMEDIA --------*/
typedef struct
{
    int clave;
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
void buscar(Multim movies[], int cont);

// Funciones auxiliares
void imprimirRegistro(Multim movie);
void leerCadena(const char msg[], char cadena[], int largo);
int leerInt(const char msg[], int ri, int rf);
void asignarCategTipo(Multim movies, char categ[], char tipo[]);
void burbuMejorada(Multim vect[], int n);
int busqSecuencial(Multim vect[], int m, int num);

int main()
{
    Multim movies[N];
    int cont = 0, op;
    int ordenado = 0;

    do
    {
        system("cls");
        op = menu();
        switch (op)
        {
        case 1:
            insertar(movies, &cont);
            ordenado = 0;
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
            buscar(movies, cont);
            break;
        case 6:
            if (!ordenado)
            {
                burbuMejorada(movies, cont);
                printf("\n* Se ha ordenado por campo 'clave'\n");
                ordenado = 1;
            }
            else
            {
                printf("* Error, ya se encuentra ordenado. *\n");
            }
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
    printf("6. Ordenar\n");
    printf("0. Salir\n");
    op = leerInt("> Escoge una opcion: ", 0, 6);
    system("cls");
    return op;
}

// Recibe la estructura y el contador
void insertar(Multim movies[], int *cont)
{
    int existe = 0; // Bandera para determinar si ya existe esa clave

    printf("\t[ Registrando pelicula / serie #%d ]\n\n", *cont + 1);

    // Entrada de clave no repetida
    int clave;
    do
    {
        clave = leerInt("> Ingresa clave [1000, 2000]: ", 1000, 2000);
    } while (busqSecuencial(movies, *cont, clave) != -1);

    movies[*cont].clave = clave; // Asigno clave valida

    // Entrada de titulo
    leerCadena("> Ingresa titulo: ", movies[*cont].titulo, 30);

    // Entrada de categoria
    printf("\n\t* Categoria *\n");
    printf("[ 1.-Accion / 2.-Terror /3.-Thriller ]\n");
    movies[*cont].categoria = leerInt("> Ingresa categoria: ", 1, 3);

    // Entrada de tipo
    printf("\n\t* Tipo *\n");
    printf("[ 1.-CD / 2.-DVD /3.-Blueray ]\n");
    movies[*cont].tipo = leerInt("> Ingresa tipo: ", 1, 3);

    // Mensaje
    system("cls");
    printf("* Elemento agregado exitosamente. *\n\n");
    imprimirRegistro(movies[*cont]);
    (*cont)++; // Incrementar contador
}

// Borra un elemento mediante su indice
void borrar(Multim movies[], int *cont)
{
    int clave = leerInt("> Clave de elemento a eliminar [1000, 2000]: ", 1000, 2000);
    int pos = busqSecuencial(movies, *cont, clave);

    if (pos != -1)
    {
        imprimirRegistro(movies[pos]);
        if (leerInt("> Desea eliminar ? [1. Si / 2. No]: ", 1, 2) == 1)
        {
            printf("* Registro eliminado. *\n");
            // Mueve un indice atras los elementos posteriores al eliminado
            for (int i = pos; i < *cont; i++)
            {
                movies[i].clave = movies[i + 1].clave;
                strcpy(movies[i].titulo, movies[i + 1].titulo);
                movies[i].categoria = movies[i + 1].categoria;
                movies[i].tipo = movies[i + 1].tipo;
            }
            (*cont)--; // Decrementar contador
        }
        else
        {
            printf("* Eliminacion cancelada. *\n");
        }
    }
    else
    {
        printf("* Elemento no encontrado. *\n");
    }
}

// Modifica elementos de la estructura
void modificar(Multim movies[], int *cont)
{
    int clave, op;

    listar(movies, cont);
    clave = leerInt("> Clave de elemento a modificar [1000, 2000]: ", 1000, 2000);

    int pos = busqSecuencial(movies, *cont, clave);

    if (pos != -1)
    {
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
            movies[pos].clave = leerInt("Ingresa nueva clave [1000, 2000]: ", 1000, 2000);
            break;
        case 2:
            leerCadena("Ingresa nuevo titulo: ", movies[pos].titulo, 30);
            break;
        case 3:
            printf("\n\t* Categorias *\n");
            printf("[ 1.-Accion / 2.-Terror /3.-Thriller ]\n");
            movies[pos].categoria = leerInt("> ", 1, 3);
            break;
        case 4:
            printf("\n\t* Tipos *\n");
            printf("[ 1.-CD / 2.-DVD /3.-Blueray ]\n");
            movies[pos].tipo = leerInt("> ", 1, 3);
            break;
        default:
            printf("Ingrese una opcion valida.\n");
            break;
        }
        printf("\n> Elemento modificado exitosamente.\n");
    }
    else
    {
        printf("* Elemento no encontrado. *\n");
    }
}

// Muestra todos los elementos existentes
void listar(Multim movies[], int *cont)
{
    char categ[11] = "", tipo[11] = ""; // Variables temporales para nombre de categoria y tipo
    printf("+--------------------------------------------------------------------------------+\n");
    printf("|                                CONTENIDO MULTIMEDIA                            |\n");
    printf("|--------------------------------------------------------------------------------|\n");
    printf("|  No. |    Clave    |            Titulo            |   Categoria   |    Tipo    |\n");
    printf("|--------------------------------------------------------------------------------|\n");

    for (int i = 0; i < *cont; i++)
    {
        asignarCategTipo(movies[i], categ, tipo); // Asignar leyenda de categoria y tipo
        printf("| %4d | %-11d | %-28s | %-13s | %-10s |\n", i + 1, movies[i].clave, movies[i].titulo, categ, tipo);
    }
    printf("+--------------------------------------------------------------------------------+\n");
}

// Busca un elemento especifico por su clave
void buscar(Multim movies[], int cont)
{
    int clave; // Variable para leer la clave a buscar

    clave = leerInt("> Ingresa clave de elemento a buscar [1000, 2000]: ", 1000, 2000);

    int pos = busqSecuencial(movies, cont, clave);

    if (pos != -1) // Mostrar datos de busqueda
    {
        printf("\n> Elemento encontrado. Posicion %d\n", pos);
        imprimirRegistro(movies[pos]);
    }
    else
    {
        printf("> Elemento no existente.\n\n");
    }
}

// Funcion para pasar de int a char 'categoria y tipo'
void asignarCategTipo(Multim movies, char categ[], char tipo[])
{
    // Definir nombre de 'Categoria'
    switch (movies.categoria)
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
    switch (movies.tipo)
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

void imprimirRegistro(Multim movie)
{
    char categ[20], tipo[20];
    asignarCategTipo(movie, categ, tipo);
    printf("+----------------------------------+\n");
    printf("|            MULTIMEDIA            |\n");
    printf("|----------------------------------|\n");
    printf("| Clave : %-4d                     |\n", movie.clave);
    printf("| Titulo : %-23s |\n", movie.titulo);
    printf("| Categoria : %-15s      |\n", categ);
    printf("| Tipo : %-10s                |\n", tipo);
    printf("+----------------------------------+\n");
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

// Ordena arreglo struct por burbuja mejorada
void burbuMejorada(Multim vect[], int n)
{
    int cambio = 1;
    Multim aux;

    for (int i = 0; i < n - 1 && cambio; i++)
    {
        cambio = 0; // Reinicia bandera
        for (int j = 0; j < n - i - 1; j++)
        {
            if (vect[j].clave > vect[j + 1].clave)
            {
                aux = vect[j];
                vect[j] = vect[j + 1];
                vect[j + 1] = aux;
                cambio = 1; // Se realizo un cambio
            }
        }
    }
}

// Busqueda secuencial struct (arreglo desordenado)
int busqSecuencial(Multim vect[], int m, int num)
{
    for (int i = 0; i < m; i++)
    {
        if (vect[i].clave == num)
        {
            return i;
        }
    }
    return -1;
}