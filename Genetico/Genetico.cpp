#include <iostream>
#include "MaximizacionGenetica.h"

int main()
{
    MaximizacionGenetica Max = MaximizacionGenetica();
    Max.algoritmo_genetico(30, 0.1, 1, "11110011", 24, 1000);
}
