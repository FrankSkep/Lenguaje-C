#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j; // Variables iteradoras

    for (i = 1; i <= 10; i++) // Ciclo que controla la tabla actual
    {
        for (j = 1; j <= 10; j++) // Ciclo que evalua la tabla actual
        {
            printf("%d x %d = %d\n", i, j, i * j);
        }
        printf("\n");
        system("PAUSE");
        system("CLS");
    }
}
