#include <iostream>
#include "MaximizacionGenetica.h"

int main()
{
    MaximizacionGenetica Max = MaximizacionGenetica();
    Max.algoritmo_genetico(30, 0.1, 2, "11010011", 8, 1000);
    //int adaptacion[MAX_SUJETOS] = { 0 };      //si se desea ver el valor final de la funcion en el arreglo de adaptacion
    //Max.funcion_de_adaptacion(30, 24, adaptacion);
    return (0);
}
