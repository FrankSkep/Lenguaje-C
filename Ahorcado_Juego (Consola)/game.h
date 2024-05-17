#ifndef GAME_H
#define GAME_H

#include <ctype.h>
#include "interfaces.h"
#include <string.h>

// Caracteres a utilizar en funcion recuadro();
int caracteres[6] = {201, 187, 200, 188, 205, 186}; // ╔ ╗ ╚ ╝ ═ ║

/**************** PROTOTIPOS DE FUNCIONES  ****************/

// Funciones para la interfaz del juego
void interfaz(char palabra[], int longitud);
void cuadroContenedor();
void ponerSubguiones(char palabra[], int longitud);
void imprimirMarcadores(int puntos, int aciertos, int errores);
void imprimirAbecedario(char abecedario[], int longitud);
void dibujarHorca();
void dibujarCabeza();
void dibujarPecho();
void dibujarBrazoIzq();
void dibujarBrazoDer();
void dibujarPiernaIzq();
void dibujarPiernaDer();
void dibujarExtremidad(int nError);
void mostrarDespedida();

// Funciones para la logica del juego
void limpiarBuffer();
int menuCategorias();
void seleccionarPalabra(char palabra[]);
char pedirLetra();
int buscarCaracter(char letra, char abecedario[], int longitud);
void quitarLetraAbecedario(char letra, char abecedario[], int longitud);
void partidaFinalizada(int gano, int puntos, int aciertos, int errores, char palabra[]);
int jugarDeNuevo();

/************ DESARROLLO DE FUNCIONES  ************/

void interfaz(char palabra[], int longitud)
{
    int i;
    cuadroContenedor(); // Dibuja el cuadrado contenedor

    // Imprime los subguiones acorde a la longitud de la palabra
    ponerSubguiones(palabra, longitud);

    //     Dibuja la horca
    dibujarHorca();

    // Recuadro para abecedario
    color(6, 0);
    recuadro(14, 21, 68, 23, caracteres);
    color(7, 0);
    textoCentroColor(42, 21, 14, 0, "Letras usadas");

    //    Marcador de puntuacion
    cadenaXY_COLOR(60, 7, 11, 0, "Puntuacion:");
    color(9, 0);
    recuadro(58, 6, 77, 8, caracteres);
    color(7, 0);

    //    Recuadro de categoria
    color(5, 0);
    recuadro(32, 6, 53, 8, caracteres);
    color(0, 0);

    // Marcador de aciertos y errores
    cadenaXY_COLOR(45, 15, 10, 0, "Aciertos: ");
    cadenaXY_COLOR(45, 16, 12, 0, "Fallos: ");
}

void cuadroContenedor()
{
    int i;
    //  Recuadro del Titulo
    color(9, 0);
    recuadro(4, 2, 78, 4, caracteres);
    textoCentroColor(42, 3, 12, 0, "EL AHORCADO");

    //   Recuadro contenedor
    color(9, 0);
    recuadro(2, 1, 80, 25, caracteres);
    color(7, 0);
}

void ponerSubguiones(char palabra[], int longitud)
{
    int i;
    for (i = 0; i < longitud; i++)
    {
        cadenaXY(45 + i * 2, 10, "_ ");
    }
}

void imprimirMarcadores(int puntos, int aciertos, int errores)
{
    intXY_COLOR(72, 7, 3, 0, puntos);
    intXY_COLOR(55, 15, 10, 0, aciertos);
    intXY_COLOR(53, 16, 12, 0, errores);
}

void imprimirAbecedario(char abecedario[], int longitud)
{
    int j = 16;
    for (int i = 0; i < longitud; i++)
    {
        charXY_COLOR(j, 22, 14, 0, abecedario[i]);
        j += 2;
    }
}

void dibujarHorca()
{
    int i, j;

    color(14, 0);
    lineas_Simultaneas(10, 16, 26, 16, 201, 187);
    lineas_Simultaneas(10, 17, 26, 17, 200, 188);
    for (i = 11; i < 15; i++)
        charXY(i, 16, 205);
    for (i = 18; i < 26; i++)
        charXY(i, 16, 205);
    for (i = 11; i < 26; i++)
        charXY(i, 17, 205);
    lineas_Simultaneas(15, 16, 17, 16, 188, 200);
    j = 15;
    for (i = 15; i > 7 && j > 7; i--, j--)
        lineas_Simultaneas(15, i, 17, j, 186, 186);
    charXY(15, 7, 201);
    for (i = 16; i < 23; i++)
        charXY(i, 7, 205);
    charXY(17, 8, 201);
    charXY(23, 7, 187);
    charXY(23, 8, 186);
    for (i = 18; i < 22; i++)
        charXY(i, 8, 205);
    charXY(21, 8, 187);

    color(6, 0);
    for (i = 21; i < 24; i++)
        charXY(i, 9, 178);
}

void dibujarCabeza()
{
    charXY_COLOR(22, 10, 15, 0, 1);
}

void dibujarPecho()
{
    charXY_COLOR(22, 11, 15, 0, 219);
}

void dibujarBrazoIzq()
{
    charXY_COLOR(21, 11, 15, 0, 47);
}

void dibujarBrazoDer()
{
    charXY_COLOR(23, 11, 15, 0, 92);
}

void dibujarPiernaIzq()
{
    charXY_COLOR(21, 12, 15, 0, 47);
}

void dibujarPiernaDer()
{
    charXY_COLOR(23, 12, 15, 0, 92);
}

void dibujarExtremidad(int nError)
{
    switch (nError)
    {
    case 1:
        dibujarCabeza();
        break;
    case 2:
        dibujarPecho();
        break;
    case 3:
        dibujarBrazoIzq();
        break;
    case 4:
        dibujarBrazoDer();
        break;
    case 5:
        dibujarPiernaIzq();
        break;
    case 6:
        dibujarPiernaDer();
        break;
    default:
        break;
    }
}

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int menuCategorias()
{
    int i, op;

    cuadroContenedor(); // Dibuja el rectangulo contenedor

    // Leyendas del menu
    cadenaXY_COLOR(23, 9, 14, 0, "> CATEGORIAS DE PALABRAS DISPONIBLES:");
    cadenaXY_COLOR(27, 11, 6, 0, "1. ");
    cadenaXY_COLOR(27, 12, 6, 0, "2. ");
    cadenaXY_COLOR(27, 13, 6, 0, "3. ");
    cadenaXY_COLOR(27, 14, 6, 0, "4. ");
    cadenaXY_COLOR(30, 11, 11, 0, "Frutas y verduras");
    cadenaXY_COLOR(30, 12, 11, 0, "Dispositivos Electronicos");
    cadenaXY_COLOR(30, 13, 11, 0, "Paises");
    cadenaXY_COLOR(30, 14, 11, 0, "Animales");
    cadenaXY_COLOR(29, 16, 15, 0, "Elije una categoria: -> ");

    gotoxy(53, 16);
    scanf("%d", &op);
    limpiarBuffer(); // Limpiar el búfer de entrada
    return op;
}

void seleccionarPalabra(char palabra[])
{
    /************** PALABRAS DISPONIBLES PARA ADIVINAR **************/
    char *frutasVerduras[10] = {"Manzana", "Platano", "Zanahoria", "Sandia",
                                "Brocoli", "Uva", "Tomate", "Limon", "Lechuga", "Fresa"};
    char *electronicos[10] = {"Celular", "Computadora", "Television", "Tablet",
                              "Bocina", "Camara", "Impresora", "Auriculares", "Ventilador", "Estereo"};
    char *paises[10] = {"China", "India", "Brasil", "Rusia", "Japon", "Alemania",
                        "Inglaterra", "Mexico", "Francia", "Italia"};
    char *animales[10] = {"Leon", "Elefante", "Perro", "Gato", "Tigre", "Oso",
                          "Zorro", "Jirafa", "Serpiente", "Canguro"};

    int op, opcionValida = 0;
    do
    {
        cls();
        op = menuCategorias();

        if (op >= 1 && op <= 4)
        {
            cls();
            opcionValida = 1;
        }
        else
        {
            opcionValida = 0;
            cadenaXY_COLOR(18, 19, 12, 0, "> Categoria no existente, intente nuevamente <");
            gotoxy(21, 20);
            pausa();
        }
    } while (!opcionValida);

    switch (op)
    {
    case 1:
        strcpy(palabra, frutasVerduras[rand() % 10]);
        cadenaXY_COLOR(34, 7, 13, 0, "Frutas y verduras");
        break;
    case 2:
        strcpy(palabra, electronicos[rand() % 10]);
        cadenaXY_COLOR(37, 7, 13, 0, "Electronicos");
        break;
    case 3:
        strcpy(palabra, paises[rand() % 10]);
        cadenaXY_COLOR(40, 7, 13, 0, "Paises");
        break;
    case 4:
        strcpy(palabra, animales[rand() % 10]);
        cadenaXY_COLOR(39, 7, 13, 0, "Animales");
        break;
    default:
        break;
    }
}

char pedirLetra()
{
    char letra;
    cadenaXY_COLOR(45, 12, 14, 0, "Letra: ");
    gotoxy(52, 12);
    letra = getchar();
    limpiarBuffer();
    return letra;
}

int buscarCaracter(char letra, char cadena[], int longitud)
{
    int i;

    for (i = 0; i < longitud; i++)
    {
        if (toupper(cadena[i]) == toupper(letra))
        {
            return i;
        }
    }
}

void quitarLetraAbecedario(char letra, char abecedario[], int longitud)
{
    int posicion = buscarCaracter(letra, abecedario, longitud);

    // Inserta un espacio en el lugar de la letra usada;
    charXY(16 + posicion * 2, 22, ' ');
}

void partidaFinalizada(int gano, int puntos, int aciertos, int errores, char palabra[])
{
    int i;
    cls();
    cuadroContenedor();
    dibujarHorca();

    color(15, 0);
    recuadro(32, 7, 72, 16, caracteres);

    if (gano)
    {
        for (i = 1; i <= errores; i++)
        {
            dibujarExtremidad(i);
        }
        cadenaXY_COLOR(38, 8, 10, 0, "> FELICIDADES, HAS GANADO ! <");
    }
    else
    {
        for (i = 1; i <= errores; i++)
        {
            dibujarExtremidad(i);
        }
        cadenaXY_COLOR(34, 8, 4, 0, "> HAS PERDIDO ! SUERTE LA PROXIMA ! <");
    }
    cadenaXY_COLOR(38, 10, 11, 0, "> La solucion era:");
    cadenaXY_COLOR(57, 10, 14, 0, palabra);

    cadenaXY_COLOR(38, 13, 14, 0, "* Puntuacion final: ");
    gotoxy(58, 13);
    printf("%d", puntos);
    cadenaXY_COLOR(38, 14, 14, 0, "* Aciertos: ");
    gotoxy(50, 14);
    printf("%d", aciertos);
    cadenaXY_COLOR(38, 15, 14, 0, "* Errores: ");
    gotoxy(49, 15);
    printf("%d", errores);
}

int jugarDeNuevo()
{
    int opcion, i, entradaCorrecta;
    color(15, 0);
    recuadro(25, 20, 61, 22, caracteres);
    color(0, 0);
    cadenaXY_COLOR(27, 21, 2, 0, "1-.Jugar de Nuevo");
    charXY(45, 21, '|');
    cadenaXY_COLOR(47, 21, 12, 0, "2-.Salir");
    cadenaXY(56, 21, "-> ");

    do
    {
        gotoxy(59, 21);
        scanf("%d", &opcion);
        limpiarBuffer(); // Limpiar el búfer de entrada
        if (opcion == 1 || opcion == 2)
        {
            return opcion;
        }
        else
        {
            entradaCorrecta = 0;
        }
    } while (!entradaCorrecta);
}

void mostrarDespedida()
{
    cls();
    recuadro(18, 10, 63, 16, caracteres);
    cadenaXY_COLOR(22, 12, 10, 0, "> Gracias por jugar, vuelve pronto ! <");
    gotoxy(22, 14);
    pausa();
}

#endif