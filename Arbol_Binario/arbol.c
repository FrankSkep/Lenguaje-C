#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo
{
    int Dato;
    struct Nodo *izqPtr;
    struct Nodo *derPtr;
} Nodo;

Nodo *crearNodo(int dato);
void insertar(Nodo *nodo, int dato);
void inorden(Nodo *nodo);
void preorden(Nodo *nodo);
void postorden(Nodo *nodo);

int main()
{
    int datos[8] = {54, 32, 60, 87, 34, 15, 104, 90};
    int n = 8;

    Nodo *raiz = crearNodo(datos[0]);

    for (int i = 1; i < n; i++)
    {
        insertar(raiz, datos[i]);
    }

    printf("Recorrido Inorden: ");
    inorden(raiz);
    printf("\n");

    printf("Recorrido Preorden: ");
    preorden(raiz);
    printf("\n");

    printf("Recorrido Postorden: ");
    postorden(raiz);
    printf("\n");

    return 0;
}

Nodo *crearNodo(int dato)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->Dato = dato;
    nodo->izqPtr = NULL;
    nodo->derPtr = NULL;
    return nodo;
}

void insertar(Nodo *nodo, int dato)
{
    if (dato < nodo->Dato)
    {
        if (nodo->izqPtr == NULL)
        {
            nodo->izqPtr = crearNodo(dato);
        }
        else
        {
            insertar(nodo->izqPtr, dato);
        }
    }
    else
    {
        if (nodo->derPtr == NULL)
        {
            nodo->derPtr = crearNodo(dato);
        }
        else
        {
            insertar(nodo->derPtr, dato);
        }
    }
}

void inorden(Nodo *nodo)
{
    if (nodo != NULL)
    {
        inorden(nodo->izqPtr);
        printf("%d ", nodo->Dato);
        inorden(nodo->derPtr);
    }
}

void preorden(Nodo *nodo)
{
    if (nodo != NULL)
    {
        printf("%d ", nodo->Dato);
        preorden(nodo->izqPtr);
        preorden(nodo->derPtr);
    }
}

void postorden(Nodo *nodo)
{
    if (nodo != NULL)
    {
        postorden(nodo->izqPtr);
        postorden(nodo->derPtr);
        printf("%d ", nodo->Dato);
    }
}
