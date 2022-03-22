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
		probabilidades_acumuladas(adaptacion, cantidad_actual);
		crea_nueva_generacion(cantidad_actual, mascara_cruce, cantidad_para_cruce);
		mutacion(cantidad_actual, probabilidad_mutar, cantidad_mutaciones);
		reemplazo_simple(cantidad_actual);
		reemplazo_elitista(cantidad_actual);
		cantidad_generaciones++;
		if (cantidad_generaciones == max_generaciones)
			break;
	}
}

void MaximizacionGenetica::reemplazo_simple(int cantidad) {
	for (int i = 0; i < cantidad; i++)
		poblacion_actual[i] = nueva_poblacion[i];
}

void MaximizacionGenetica::reemplazo_elitista(int cantidad)
{
	string todos[2 * MAX_SUJETOS];
	int adaptacion[2 * MAX_SUJETOS];
	int cantidad_total = 0;
	int temp_int;
	string temp_string;
	for (int i = 0; i < cantidad; i++)
		todos[cantidad_total++] = poblacion_actual[i];
	for (int i = 0; i < cantidad; i++)
		todos[cantidad_total++] = nueva_poblacion[i];
	funcion_de_adaptacion(todos, cantidad_total, 24, adaptacion);
	for (int i = 0; i < cantidad_total - 1; i++)
		for (int j = i + 1; j < cantidad_total; j++)
			if (adaptacion[i] < adaptacion[j])
			{
				temp_int = adaptacion[i];
				adaptacion[i] = adaptacion[j];
				adaptacion[j] = temp_int;
				temp_string = todos[i];
				todos[i] = todos[j];
				todos[j] = temp_string;
			}
	for (int i = 0; i < cantidad; i++)
		poblacion_actual[i] = todos[i];
}

void MaximizacionGenetica::mutacion(int cantidad, double probabilidad_de_mutar, int cantidad_mutaciones) {
	for (int j = 0; j < cantidad; j++)
	{
		muta_hijo(probabilidad_de_mutar, cantidad_mutaciones, poblacion_actual[j]);
	}
}

void MaximizacionGenetica::muta_hijo(double probabilidad, int cuantas_mutaciones, string hijo) {
	string temp;
	string gen;
	int numero_gen;
	if ( ((double)rand() / 100) > probabilidad) return;
	while (cuantas_mutaciones > 0)
	{
		numero_gen = (rand() % sizeof(poblacion_actual));
		cuantas_mutaciones--;
		temp = hijo.substr(0, numero_gen);
		gen =hijo.substr(numero_gen, 1);
		if (gen == "1")
			temp += "0" + hijo.substr(numero_gen + 1);
		else
			temp += "1" + hijo.substr(numero_gen + 1);
		hijo = temp;
	}
}
void MaximizacionGenetica::crea_nueva_generacion(int cantidad, string mascara_de_cruce, int cantidad_para_cruce) {
	string padre1 = "";
	string padre2 = "";
	string hijo1 = "";
	string hijo2 = "";
	int cantidad_nueva_poblacion = 0;
	for (int i = 1; i <= cantidad_para_cruce; i++)
	{
		selecciona_padres(cantidad, padre1, padre2);
		cruza_padres(mascara_de_cruce, padre1, padre2, hijo1, hijo2);
		nueva_poblacion[cantidad_nueva_poblacion++] = hijo1;
		nueva_poblacion[cantidad_nueva_poblacion++] = hijo2;
	}
}

void MaximizacionGenetica::selecciona_padres(int cantidad, string& padre1, string& padre2)
{
	double aleatorio;
	int indice_padre1 = 0;
	int indice_padre2 = 0;
	aleatorio = ((double)rand() / 100);
	for (int j = 0; j < cantidad; j++)
		if (probabilidad_acumulada[j] >= aleatorio)
		{
			padre1 = poblacion_actual[j];
			indice_padre1 = j;
			break;
		}
	do
	{
		aleatorio = ((double)rand() / 100);
		for (int j = 0; j < cantidad; j++)
			if (probabilidad_acumulada[j] >= aleatorio)
			{
				padre2 = poblacion_actual[j];
				indice_padre2 = j;
				break;
			}
	} while (indice_padre1 == indice_padre2);
}

string MaximizacionGenetica::Dec2Bin(int iNum) {
	string strNum = "";
	int division = iNum;
	int resto;
	do
	{
		resto = division % 2;
		division = division / 2;
		if (resto == 0)
			strNum = "0" + strNum;
		else
			strNum = "1" + strNum;
	} while (division != 0);
	return strNum;
}

void MaximizacionGenetica::cruza_padres(string mascara_cruce, string padre1, string padre2, string& hijo1, string& hijo2) {
	string bit;
	hijo1 = "";
	for (int i = 0; i < sizeof(mascara_cruce); i++)
	{
		bit = mascara_cruce.substr(i, 1);
		if (bit == "1")
			hijo1 += padre1.substr(i, 1);
		else
			hijo1 += padre2.substr(i, 1);
	}
	hijo2 = "";
	for (int i = 0; i < sizeof(mascara_cruce); i++)
	{
		bit = mascara_cruce.substr(i, 1);
		if (bit == "1")
			hijo2 += padre2.substr(i, 1);
		else
			hijo2 += padre1.substr(i, 1);
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

void MaximizacionGenetica::funcion_de_adaptacion(string poblacion[], int cantidad_sujetos, int longitud_gen, int* adaptacion) //xy - xz + yz
{
	int* numero = new int[3];
	for (int i = 0; i < cantidad_sujetos; i++)
	{
		numero = Bin2Dec(poblacion[i], longitud_gen);

		adaptacion[i] = (int)(numero[0] * numero[1] - numero[0] * numero[2] + numero[1] * numero[2]);
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

void MaximizacionGenetica::probabilidades_acumuladas(int* adaptacion, int cantidad_sujetos)
{
	double suma = 0.0;
	for (int i = 0; i < cantidad_sujetos; i++)
		suma += adaptacion[i];
	probabilidad_acumulada[0] = adaptacion[0] / suma;
	for (int i = 1; i < cantidad_sujetos; i++)
		probabilidad_acumulada[i] = probabilidad_acumulada[i - 1] + adaptacion[i] / suma;

}