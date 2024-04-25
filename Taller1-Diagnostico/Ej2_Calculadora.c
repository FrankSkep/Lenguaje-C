#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

float calcular(char operador, float n1, float n2)
{
    switch (operador)
    {
    case '+':
        return n1 + n2;
        break;

    case '-':
        return n1 - n2;
        break;

    case '*':
        return n1 * n2;
        break;

    case '/':
        if (n2 != 0)
        {
            return n1 / n2;
        }
        else
        {
            printf("No se puede dividir entre cero.");
            return true;
        }
        break;

    default:
        printf("\n  **Operador no valido **\n");
        return true;
        break;
    }
}

void limpiarBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int main()
{
    char opc, continuar;
    float n1, n2, resultado;

    while (true)
    {
        printf("\n|==== CALCULADORA ===|\n\n");
        printf("Ingresa el primer numero: ");
        scanf("%f", &n1);
        limpiarBufferEntrada();

        printf("Ingresa el operador (+, -, *, /): ");
        scanf("%c", &opc);

        printf("Ingresa el segundo numero: ");
        scanf("%f", &n2);

        resultado = calcular(opc, n1, n2);
        limpiarBufferEntrada();

        if (resultado != true)
        {
            printf("\n> El resultado de %.2f %c %.2f es: %.2f", n1, opc, n2, resultado);
        }

        limpiarBufferEntrada();
        printf("\nDeseas hacer otra operacion? (s/n): ");
        scanf("%c", &continuar);
        continuar = tolower(continuar);

        system("CLS");

        if (continuar == 's')
        {
            continue;
        }
        else
        {
            if (continuar == 'n')
            {
                break;
            }
            else
            {
                printf("Opcion desconocida.\n");
                system("PAUSE");
                system("CLS");
            }
        }
    }
}