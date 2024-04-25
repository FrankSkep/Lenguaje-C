#include "interfaces.h"
#define MAX_LEN 100

/******** PROTOTIPOS DE FUNCIONES ********/
void dibujarInterfaz();
void numerosCuadro(int clrT, int clrF);
void dibujarCuadro(int x, int y, int clr);
int generarColor();
int entradaJugador();
int jugarDeNuevo();
void reproducirColor(int color);
void imprimirPuntos(int puntos);

int main()
{
    int secuencia[MAX_LEN];
    int longitudSecuencia;
    int entradaUsuario, juego, correcto, puntos;
    int i;
    srand(time(NULL));

    do /********** BUCLE DEL JUEGO  **********/
    {
        cls();                 // Limpia pantalla en cada partida
        dibujarInterfaz();     // Dibuja interfaz inicial del juego
        longitudSecuencia = 0; // Reinicia la longitud a 0
        correcto = 1;          // Reinicia Variable correcto a True
        puntos = 0;            // Reinicia puntuacion en cada partida
        Sleep(135);            // Espera 135 milisegundos

        do /********** BUCLE PARTIDA ACTUAL  **********/
        {
            secuencia[longitudSecuencia++] = generarColor(); // Genera color aleatorio

            // Mostrar en pantalla la secuencia de colores
            for (i = 0; i < longitudSecuencia; i++)
            {
                reproducirColor(secuencia[i]);
            }

            // Comparar entradas del usuario con la secuencia
            for (i = 0; i < longitudSecuencia && correcto; i++)
            {
                entradaUsuario = entradaJugador();

                if (entradaUsuario != secuencia[i])
                {
                    correcto = 0;
                    cadenaXY_COLOR(30, 23, 12, 0, " Te has equivocado! ");
                }
            }

            if (correcto) // Si completa la secuencia, imprime mensaje y espera 1.2 segundos
            {
                cadenaXY_COLOR(27, 23, 10, 0, " Correcto, sigue jugando ");
                Sleep(550);               // Esperar 550 segundos
                clsRegion(1, 23, 79, 23); // Limpiar zona de mensajes
                puntos += 10;             // Suma 10 puntos por cada vez que complete la secuencia
            }
            imprimirPuntos(puntos);

        } while (correcto); // El juego sigue mientras no se equivoque

        Sleep(1500);
        juego = jugarDeNuevo();

    } while (juego == 1);
}

/******** DESARROLLO DE FUNCIONES ********/
void dibujarInterfaz()
{
    int tipo1[6] = {201, 187, 200, 188, 205, 186}; // ╔ ╗ ╚ ╝ ═ ║
    int tipo2[6] = {218, 191, 192, 217, 196, 179}; // ┌ ┐ └ ┘ ─ │

    // Recuadro contenedor principal
    color(6, 0);
    recuadro(0, 0, 80, 21, tipo1);
    color(15, 0);

    //**** Recuadro para los colores ****
    recuadro(22, 3, 58, 15, tipo2);
    // Linea vertical
    LineaVertical(40, 4, 14, 179);
    charXY(40, 3, 194);  // Borde superior
    charXY(40, 15, 193); // Borde inferior
    // Linea horizontal
    LineaHorizontal(23, 9, 57, 196);
    charXY(22, 9, 195); // borde izquierda
    charXY(58, 9, 180); // borde derecha
    charXY(40, 9, 197); // Cruz central

    // Recuadro para mensajes
    color(6, 0);
    recuadro(0, 22, 80, 24, tipo1);

    // Titulo juego
    color(14, 0);
    textoCentro(40, 0, " S I M O N ");

    // Titulo mensajes
    textoCentro(40, 22, " AVISOS ");

    // Pausa
    textoCentroColor(40, 17, 13, 0, "Presiona cualquier tecla para iniciar");
    getch();
    clsRegion(20, 17, 59, 20);

    // Texto  puntuacion
    cadenaXY_COLOR(34, 17, 14, 0, "Puntucion: ");
    numerosCuadro(8, 0);
}

void numerosCuadro(int clrT, int clrF)
{
    charXY_COLOR(31, 6, 8, 0, '1');
    charXY_COLOR(49, 6, 8, 0, '2');
    charXY_COLOR(31, 12, 8, 0, '3');
    charXY_COLOR(49, 12, 8, 0, '4');
}

void dibujarCuadro(int x, int y, int clr)
{
    int i, j;

    // Pinta el cuadro del color correspondiente
    for (i = 0; i < 15; i++) // Controla las columnas
    {
        for (j = 0; j < 5; j++) // Controla las filas
        {
            charXY_COLOR(x + i, y + j, clr, 0, 219);
        }
    }
    Sleep(925);

    // El cuadro vuelve al color normal
    for (i = 0; i < 15; i++) // Controla las columnas
    {
        for (j = 0; j < 5; j++) // Controla las filas
        {
            charXY_COLOR(x + i, y + j, 0, 0, 32);
        }
    }
    numerosCuadro(8, clr);
    Sleep(320); // Esperar antes de imprimir el siguiente
}

int generarColor()
{
    return rand() % 4 + 1; // Genera numero aleatorio 1, 4
}

int entradaJugador()
{
    int num;
    cadenaXY_COLOR(28, 19, 15, 0, "> Escribe la secuencia: ");
    gotoxy(52, 19);
    scanf("%d", &num);
    clsRegion(51, 19, 53, 19);
    return num;
}

int jugarDeNuevo()
{
    int op;
    // Menu para jugar de nuevo
    clsRegion(1, 23, 79, 23);  // Limpiar zona de mensajes
    clsRegion(28, 19, 52, 19); // Limpia zona de entrada
    cadenaXY_COLOR(23, 23, 10, 0, "1-. Jugar de nuevo ");
    charXY(42, 23, '|');
    cadenaXY_COLOR(44, 23, 12, 0, " 0-. Salir -> ");
    // Leer opcion
    gotoxy(58, 23);
    scanf("%d", &op);
    return op;
}

void reproducirColor(int color)
{
    switch (color)
    {
    case 1:
        dibujarCuadro(24, 4, 9); // Azul claro
        break;

    case 2:
        dibujarCuadro(42, 4, 10); // Verde claro
        break;

    case 3:
        dibujarCuadro(24, 10, 12); // Rojo claro
        break;

    case 4:
        dibujarCuadro(42, 10, 13); // Amarillo
        break;
    }
}

void imprimirPuntos(int puntos)
{
    gotoxy(45, 17);
    printf("%d", puntos);
}