#include <iostream>
#include "MaximizacionGenetica.h"

int main()
{
    MaximizacionGenetica Max = MaximizacionGenetica();
    Max.algoritmo_genetico(30, 0.1, 2, "11010011", 24, 100000);
    int adaptacion[MAX_SUJETOS] = { 0 };
    Max.funcion_de_adaptacion(30, 24, adaptacion);
    return (0);
}
