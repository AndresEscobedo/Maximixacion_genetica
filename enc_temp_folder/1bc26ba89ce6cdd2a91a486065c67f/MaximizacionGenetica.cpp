#include "MaximizacionGenetica.h"

MaximizacionGenetica::MaximizacionGenetica()
{

}
MaximizacionGenetica::~MaximizacionGenetica()
{

}

void MaximizacionGenetica::algoritmo_genetico(int cantidad_actual, double probabilidad_mutar, int cantidad_mutaciones, string mascara_cruce, int longitud_gen, int max_generaciones)
{
	int adaptacion[MAX_SUJETOS] = { 0 };
	int cantidad_para_cruce = cantidad_actual / 2;
	int cantidad_generaciones = 0;

	genera_poblacion_inicial(cantidad_actual, longitud_gen);
	while (true)
	{
		funcion_de_adaptacion(cantidad_actual, longitud_gen, adaptacion);
		//probabilidades_acumuladas(adaptacion, cantidad_actual);
		//crea_nueva_generacion(cantidad_actual, mascara_cruce, cantidad_para_cruce);
		//mutacion(cantidad_actual, probabilidad_mutar, cantidad_mutaciones);
		//remplazo_simple(cantidad_actual);
		//remplazo_elitista(cantidad_actual);
		cantidad_generaciones++;
		if (cantidad_generaciones == max_generaciones)
			break;
	}
}

void MaximizacionGenetica::funcion_de_adaptacion(int cantidad_sujetos, int longitud_gen, int* adaptacion) //xy - xz + yz
{
	int* numero = new int[3];
	for (int i = 0; i < cantidad_sujetos; i++)
	{
		numero = Bin2Dec(poblacion_actual[i], longitud_gen);

		adaptacion[i] = (int)(numero[0]*numero[1] - numero[0]*numero[2] + numero[1]*numero[2]);
	}
}

int* MaximizacionGenetica::Bin2Dec(string Cad, int longitud_gen)
{
	int XYZ[3] = { 0 };
	int potencia;
	string splitCadena[3];

	for (int i = 0; i < 3; i++)
	{
		splitCadena[i] = Cad.substr((longitud_gen * i)/3, longitud_gen/3);
	}
	
	for (int j = 0; j < 3; j++)
	{
		potencia = 0;
		for (int i = splitCadena[j].length() - 1; i >= 0; i--, potencia++)
		{
			XYZ[j] += (stoi(splitCadena[j].substr(i, 1)) * (int)pow(2, potencia));
		}
	}
	return XYZ;
}

void MaximizacionGenetica::genera_poblacion_inicial(int cantidad_sujetos, int longitud_del_gen)
{
	srand(time(NULL));
	double r = 0;

	for (int i = 0; i < cantidad_sujetos; i++)
	{
		poblacion_actual[i] = "";
		for (int j = 1; j <= longitud_del_gen; j++)
		{
			r = (double)rand() / RAND_MAX;
			if (r < 0.5)
				poblacion_actual[i] += "1";
			else
				poblacion_actual[i] += "0";
		}
	}
}