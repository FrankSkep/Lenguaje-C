#include "interfaces.h"
#include "game.h"

#define LONGITUD_AB 26
#define ERRORES_MAX 6

int main()
{
    /******************* ABECEDARIO ******************/
    char abecedario[LONGITUD_AB] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    /******************* VARIABLES NECESARIAS  ******************/
    char palabra[20], palabraAux[20];      // Almacena palabra elegida
    char letra;                            // Almacena letra del usuario
    int longitud;                          // Almacena longitud de palabra
    int contAciertos = 0, contErrores = 0; // Contadores Aciertos y errores
    int puntos = 0;                        // Acumulador de puntos
    int i;                                 // Iterador de ciclos
    int game;                              // Controla si sigue jugando
    int encontro = 0, gano = 0;            // Determina si encontro / gano

    srand(time(NULL)); // Inicializacion semilla para generar num aleatorios

    do /************** BUCLE DEL JUEGO **************/
    {
        cls(); // Limpiar pantalla en cada partida

        // Reinicio de Contadores por partida
        contAciertos = 0;
        contErrores = 0;
        if (gano)
        {
            puntos = puntos;
        }
        else
        {
            puntos = 100;
        }

        // Elije una palabra aleatoriamente de la categoria seleccionada
        seleccionarPalabra(palabra);

        // Guardar palabra elegida para mostrarla al finalizar
        strcpy(palabraAux, palabra);

        longitud = strlen(palabra); // Obtener longitud de la palabra elegida

        interfaz(palabra, longitud); // Dibujar Interfaz del juego

        imprimirAbecedario(abecedario, LONGITUD_AB); // Imprimir el abecedario

        // Imprimir marcadores iniciales
        imprimirMarcadores(puntos, contAciertos, contErrores);

        /***************** BUCLE DE LA PARTIDA *****************/
        do
        {
            // Reinicia 'encontro' a false en cada iteración de la partida actual
            encontro = 0;

            // Pedir letra al usuario
            letra = pedirLetra();

            if (letra == '\0') // Si recibe un caracter nulo, le suma un error y resta puntos
            {
                contErrores++;
                puntos -= 35;
                dibujarExtremidad(contErrores);
            }

            /************* Verifica si esta la letra ingresada  ************/
            for (i = 0; i < longitud; i++)
            {
                if (toupper(letra) == toupper(palabra[i]))
                {
                    encontro = 1;
                    contAciertos++;                             // Incrementa aciertos por cada aparicion de la letra
                    puntos += 30;                               // Agrega 30 puntos
                    charXY_COLOR(45 + i * 2, 10, 15, 0, letra); // Agregar letra usada a subguiones

                    // Quitar del abecedario la letra usada
                    quitarLetraAbecedario(letra, abecedario, LONGITUD_AB);

                    // Elimina de la cadena la letra usada, para evitar repeticiones
                    palabra[i] = ' ';
                }
            }

            /************** Si encontro es falso:  *************/
            if (!encontro)
            {
                contErrores++;                  // Incrementa errores en 1
                puntos -= 35;                   // Quita 35 puntos
                dibujarExtremidad(contErrores); // Dibuja extremidad correspondiente
            }

            // Imprimir marcadores actualizados
            imprimirMarcadores(puntos, contAciertos, contErrores);

        } while (contAciertos < longitud && contErrores < ERRORES_MAX);

        /*************** Resultados de la partida  **************/
        if (contAciertos >= longitud)
        {
            gano = 1;
        }
        if (contErrores >= ERRORES_MAX)
        {
            gano = 0;
        }
        delay(1); // Esperar 1 segundo antes de mostrar pantalla final

        partidaFinalizada(gano, puntos, contAciertos, contErrores, palabraAux);

        game = jugarDeNuevo();

    } while (game == 1);

    /******************* DESPEDIDA  ******************/
    mostrarDespedida();
}