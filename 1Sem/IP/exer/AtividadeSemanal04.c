#include <stdio.h>

double areaTrapezio(double baseMaior, double baseMenor, double altura)
{
    double area = 0;

    /* COMPLETAR */
    area = (baseMaior + baseMenor) * altura / 2;
    // printf("Area do trapezio: %f\n", area);

    return area;
}

double areaRetangulo(double base, double altura)
{
    double area = areaTrapezio(base, base, altura);
    printf("Area do retangulo: %f\n", area);
    return area;
}

double areaQuadrado(double lado)
{
    double area = 0;

    /* COMPLETAR */
    area = lado * lado;
    // printf("Area do quadrado: %f\n", area);

    return area;
}

int main()
{
    printf("%f\n", areaTrapezio(3, 2, 1));
    areaRetangulo(11, 27);
    printf("%f\n", areaQuadrado(5));
}