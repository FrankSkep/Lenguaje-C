#ifndef INTERFACES_H
#define INTERFACES_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <winbase.h>
#include <conio.h>

/******* PROTOTIPOS DE FUNCIONES *******/
void gotoxy(int x, int y);
void charXY(int x, int y, char c);
void cadenaXY(int x, int y, char texto[]);
void charXY_COLOR(int x, int y, int clrT, int clrF, char c);
void cadenaXY_COLOR(int x, int y, int clrT, int clrF, char texto[]);
void intXY(int x, int y, int n);
void intXY_COLOR(int x, int y, int clrT, int clrF, int n);
void textoCentro(int x, int y, char cadena[]);
void textoCentroColor(int x, int y, int clrT, int clrF, char cadena[]);
void LineaHorizontal(int x1, int y, int x2, char c);
void LineaVertical(int x1, int y, int x2, char c);
void lineas_Simultaneas(int x1, int y1, int x2, int y2, char c1, char c2);
void recuadro(int x1, int y1, int x2, int y2, int tipo[]);
void color(int clrT, int clrF);
void cls();
void pausa();
void delay(unsigned duration);
void clsRegion(int x1, int y1, int x2, int y2);

/******* DESARROLLO DE FUNCIONES *******/
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void charXY(int x, int y, char c)
{
    gotoxy(x, y);
    printf("%c", c);
}

void cadenaXY(int x, int y, char texto[])
{
    gotoxy(x, y);
    printf("%s", texto);
}

void charXY_COLOR(int x, int y, int clrT, int clrF, char c)
{
    color(clrT, clrF);
    charXY(x, y, c);
    printf("\033[0m"); // Volver al color original despues de imprimir lo deseado
}

void cadenaXY_COLOR(int x, int y, int clrT, int clrF, char texto[])
{
    color(clrT, clrF);
    cadenaXY(x, y, texto);
    printf("\033[0m"); // Volver al color original al final
}

void intXY(int x, int y, int n)
{
    gotoxy(x, y);
    printf("%d", n);
}

void intXY_COLOR(int x, int y, int clrT, int clrF, int n)
{
    color(clrT, clrF);
    intXY(x, y, n);
    printf("\033[0m"); // Volver al color original al final
}

void textoCentro(int x, int y, char cadena[])
{
    cadenaXY(x - (strlen(cadena) / 2), y, cadena);
}

void textoCentroColor(int x, int y, int clrT, int clrF, char cadena[])
{
    cadenaXY_COLOR(x - (strlen(cadena) / 2), y, clrT, clrF, cadena);
}

void LineaHorizontal(int x1, int y, int x2, char c)
{
    for (int i = x1; i <= x2; i++)
    {
        charXY(i, y, c);
    }
}

void LineaVertical(int x, int y1, int y2, char c)
{
    for (int i = y1; i <= y2; i++)
    {
        charXY(x, i, c);
    }
}

void lineas_Simultaneas(int x1, int y1, int x2, int y2, char c1, char c2)
{
    charXY(x1, y1, c1);
    charXY(x2, y2, c2);
}

void recuadro(int x1, int y1, int x2, int y2, int tipo[])
{
    // int tipo1[6] = {201, 187, 200, 188, 205, 186}; // ╔ ╗ ╚ ╝ ═ ║
    //     int tipo2[6] = {218, 191, 192, 217, 196, 179}; // ┌ ┐ └ ┘ ─ │
    int i;
    charXY(x1, y1, tipo[0]);
    charXY(x2, y1, tipo[1]);
    charXY(x1, y2, tipo[2]);
    charXY(x2, y2, tipo[3]);

    for (i = x1 + 1; i < x2; i++)
    {
        charXY(i, y1, tipo[4]);
        charXY(i, y2, tipo[4]);
    }

    for (i = y1 + 1; i < y2; i++)
    {
        charXY(x1, i, tipo[5]);
        charXY(x2, i, tipo[5]);
    }
}

void color(int clrT, int clrF)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clrT | clrF);
}

void cls()
{
    system("cls");
}

void pausa()
{
    system("pause");
}

void delay(unsigned duration)
{
    time_t start = time(NULL);
    double end = duration;
    time_t now;
    do
    {
        now = time(NULL);
    } while (difftime(now, start) < end);
}

void clsRegion(int startX, int startY, int endX, int endY)
{
    int i, j;
    for (i = startY; i <= endY; i++)
    {
        for (j = startX; j <= endX; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}

#endif