#include <stdio.h>
#include <math.h>

float f(float x);

int main()
{
    float a, b, xr, xrAnt, error, epc;

    printf("Ingresa valor de a: ");
    scanf("%f", &a);
    printf("Ingresa valor de b: ");
    scanf("%f", &b);
    printf("Ingresa error maximo permitido: ");
    scanf("%f", &error);

    if((f(a) * f(b)) < 0)
    {
        xrAnt=0;
        do
        {
            xr = (a+b) / 2; // Calcular xr
            epc = fabs((xr - xrAnt)/xr) * 100; // Calcular error
            if((f(a) * f(xr)) == 0)
            {
                printf("\nLa raiz es: %f\n", xr);
                break;
                return 0;
            }

            if((f(a) * f(xr) < 0))
            {
                b = xr;
            }
            
            if((f(a) * f(xr) > 0))
            {
                a = xr;
            }
            xrAnt = xr;

        }while (epc > error);

        printf("\nLa raiz aproximada es: %f\n", xr);
        printf("Con un error de: %f\n\n", epc);
    } else 
    {
        printf("No hay raices en esos intervalos.\n");
    }
}

float f(float x) // Funcion matematica
{
    return (2*x * cos(2*x))-pow(x+1, 2);
}