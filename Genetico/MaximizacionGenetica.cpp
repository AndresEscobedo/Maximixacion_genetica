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
	while (true)
	{
		funcion_de_adaptacion(cantidad_actual, adaptacion);
		probabilidades_acumuladas(adaptacion, cantidad_actual);
		crea_nueva_generacion(cantidad_actual, mascara_cruce, cantidad_para_cruce);
		mutacion(cantidad_actual, probabilidad_mutar, cantidad_mutaciones);
		remplazo_simple(cantidad_actual);
		//remplazo_elitista(cantidad_actual);
		cantidad_generaciones++;
		if (cantidad_generaciones == max_generaciones)
			break;
	}
}

void MaximizacionGenetica::genera_poblacion_inicial(int cantidad_sujetos, int longitud_del_gen)
{
	srand(time(NULL));
	double r = (double)rand() / RAND_MAX;

	for (int i = 0; i < cantidad_sujetos; i++)
	{
		poblacion[i] = "";
		for (int j = 1; j <= longitud_del_gen; j++)
			if (r.NextDouble() < 0.5)
				poblacion[i] += "1";
			else
				poblacion[i] += "0";

	}
}