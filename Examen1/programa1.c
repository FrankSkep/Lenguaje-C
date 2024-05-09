#include <stdio.h>

int elevarNum(int num, int exp);

int main()
{
    int num, exp;
    printf("> Ingresa numero a elevar: ");
    scanf("%d", &num);
    printf("> Ingresa exponente: ");
    scanf("%d", &exp);
    int result = elevarNum(num, exp);
    printf("> Resultado de elevar %d a %d: %d\n", num, exp, result);
}

int elevarNum(int num, int exp)
{
    int result = 1;
    for(int i = 0; i < exp; i++)
    {
        result *= num;
    }
    return result;
}