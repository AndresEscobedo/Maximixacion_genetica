#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h> 

using namespace std;

const int MAX_SUJETOS = 51;

class MaximizacionGenetica
{
public: 
	MaximizacionGenetica(void);
	~MaximizacionGenetica(void);
	void algoritmo_genetico(int cantidad_actual, double probabilidad_mutar, int cantidad_mutaciones, string mascara_cruce, int longitud_gen, int max_generaciones);

private:
	string poblacion_actual[MAX_SUJETOS];
	string nueva_poblacion[MAX_SUJETOS];
	int adaptacion[MAX_SUJETOS];
	double probabilidad_acumulada[MAX_SUJETOS];

	void remplazo_simple(int cantidad);
	void remplazo_elitista(int cantidad);
	void mutacion(int cantidad, double probabilidad_de_mutar, int cantidad_mutaciones);
	void crea_nueva_generacion(int cantidad, string mascara_de_cruce, int cantidad_para_cruce);
	void selecciona_padres(int cantidad, string& padre1, string& padre2);
	void probabilidades_acumuladas(int* adaptacion, int cantidad_sujetos);
	void funcion_de_adaptacion(int cantidad_sujetos, int* adaptacion);
	int	 Bin2Dec(string Cad);
	string Dec2Bin(int iNUm);
	void genera_poblacion_inicial(int cantidad_sujetos, int longitud_del_gen);
	void cruza_padres(string mascara_cruce, string padre1, string padre2, string& hijo1, string& hijo2);
	void muta_hijo(double probabilidad, int cuantas_mutaciones, string& hijo);


};