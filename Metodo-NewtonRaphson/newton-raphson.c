#include <stdio.h>
#include <math.h>

float f(float x);
float dF(float x);

int main()
{
    float x0, x1, error, errorMax, fx0, dfx0;
    int ite=0;

    printf("\n    \t\t[=== METODO DE NEWTON-RAPHSON ===]\n\n");
    printf("Funcion: x^3 + 4x^2 - 10\n\n");

    printf("> Ingresa valor inicial de x0: ");
    scanf("%f", &x0);
    printf("> Ingresa error maximo: ");
    scanf("%f", &errorMax);

    printf("\n ITE\t   Xo\t\t f(x0)\t\t f'(x0)\t\t   x1\t  \t    ERP\n");

    if(dF(x0) == 0)
    {
        printf("Error\n");
        return 0;

    } else {
        do
        {
            fx0 = f(x0);
            dfx0 = dF(x0);

            x1 = x0 - (f(x0) / dF(x0)); // Calculo x0
            error = (fabs(x1-x0)/x1)*100;

            if(f(x1) == 0)
            {
                printf("* La raiz es: %f\n", x1);
            }
            printf(" %d\t %lf\t %lf\t %lf\t %lf\t %lf\n", ite, x0, fx0, dfx0, x1, error);
            x0 = x1;
            ite++;
        }while(error > errorMax);
    }

    printf("\n\n* La raiz aproximada es: %f\n", x1);
    printf("* Error: %f", error);
}

float f(float x)
{
    return pow(x, 3) + (4*pow(x, 2))-10;
}

float dF(float x)
{
    return 3*pow(x, 2) + (8*x);
}