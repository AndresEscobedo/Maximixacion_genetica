#include "MaximizacionGenetica.h"

MaximizacionGenetica::MaximizacionGenetica()
{

}
MaximizacionGenetica::~MaximizacionGenetica()
{

}

void MaximizacionGenetica::algoritmo_genetico(int cantidad_actual, double probabilidad_mutar, int cantidad_mutaciones, string mascara_cruce, int longitud_gen, int max_generaciones)
{
	int adaptacion[MAX_SUJETOS];
	int cantidad_para_cruce = cantidad_actual / 2;
	int cantidad_generaciones = 0;

	genera_poblacion_inicial(adaptacion);
}

void MaximizacionGenetica::genera_poblacion_inicial(int* adaptacion)
{

}