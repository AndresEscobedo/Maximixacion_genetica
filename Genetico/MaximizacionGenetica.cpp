#include "MaximizacionGenetica.h"


MaximizacionGenetica::MaximizacionGenetica() {
    srand(time(NULL));
} // Constructor

MaximizacionGenetica::~MaximizacionGenetica() {

} // Destructor

void MaximizacionGenetica::algoritmo_genetico(int cantidad_actual, double probabilidad_mutar, int cantidad_mutaciones, string mascara_cruce, int longitud_gen, int max_generaciones) {
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
        remplazo_simple(cantidad_actual);
        //reemplazo_elitista(cantidad_actual);
        cantidad_generaciones++;
        if (cantidad_generaciones == max_generaciones)
            break;
    }
} // Algoritmo Genético

void MaximizacionGenetica::remplazo_simple(int cantidad) {
    for (int i = 0; i < cantidad; i++)
        poblacion_actual[i] = nueva_poblacion[i];
} // Reemplazo Simple

void MaximizacionGenetica::remplazo_elitista(int cantidad) {
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
} // Reemplazo Elitista

void MaximizacionGenetica::mutacion(int cantidad, double probabilidad_de_mutar, int cantidad_mutaciones) {
    for (int j = 0; j < cantidad; j++)
    {
        muta_hijo(probabilidad_de_mutar, cantidad_mutaciones, nueva_poblacion[j]);
    }
} // Mutación

void MaximizacionGenetica::muta_hijo(double probabilidad, int cuantas_mutaciones, string hijo) {
    string temp;
    string gen;
    int numero_gen;
    if (((float)rand() / (float)RAND_MAX) > probabilidad) return;
    while (cuantas_mutaciones > 0)
    {
        numero_gen = (rand() % poblacion_actual[0].length());
        cuantas_mutaciones--;
        temp = hijo.substr(0, numero_gen);
        gen = hijo.substr(numero_gen, 1);
        if (gen == "1")
            temp += "0" + hijo.substr(numero_gen + 1);
        else
            temp += "1" + hijo.substr(numero_gen + 1);
        hijo = temp;
    }
} // Muta Hijo

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
} // Crea Nueva Gen

void MaximizacionGenetica::selecciona_padres(int cantidad, string& padre1, string& padre2) {

    float aleatorio;
    int indice_padre1 = 0;
    int indice_padre2 = 0;
    aleatorio = (float)rand() / (float)RAND_MAX;
    for (int j = 0; j < cantidad; j++)
        if (probabilidad_acumulada[j] >= aleatorio)
        {
            padre1 = poblacion_actual[j];
            indice_padre1 = j;
            break;
        }
    do
    {
        aleatorio = (float)rand() / (float)RAND_MAX;
        for (int j = 0; j < cantidad; j++)
            if (probabilidad_acumulada[j] >= aleatorio)
            {
                padre2 = poblacion_actual[j];
                indice_padre2 = j;
                break;
            }
    } while (indice_padre1 == indice_padre2);
} // Selecciona Padres

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
} // Decimal a Binario

void MaximizacionGenetica::cruza_padres(string mascara_cruce, string padre1, string padre2, string& hijo1, string& hijo2) {
    string bit;
    hijo1 = "";
    string mascaraRepetida = mascara_cruce + mascara_cruce + mascara_cruce;
    for (int i = 0; i < mascaraRepetida.length(); i++)
    {
        bit = mascaraRepetida.substr(i, 1);
        if (bit == "1")
            hijo1 += padre1.substr(i, 1);
        else
            hijo1 += padre2.substr(i, 1);
    }
    hijo2 = "";
    for (int i = 0; i < mascaraRepetida.length(); i++)
    {
        bit = mascaraRepetida.substr(i, 1);
        if (bit == "1")
            hijo2 += padre2.substr(i, 1);
        else
            hijo2 += padre1.substr(i, 1);
    }
} // Cruza de Padres

void MaximizacionGenetica::funcion_de_adaptacion(int cantidad_sujetos, int longitud_gen, int* adaptacion) { //xy - xz + yz

    int numero[3] = { 0 };
    for (int i = 0; i < cantidad_sujetos; i++)
    {
        Bin2Dec(poblacion_actual[i], longitud_gen, numero);

        adaptacion[i] = (int)(numero[0] * numero[1] - numero[0] * numero[2] + numero[1] * numero[2]);
    }
} // Func de Adaptación Local

void MaximizacionGenetica::funcion_de_adaptacion(string poblacion[], int cantidad_sujetos, int longitud_gen, int* adaptacion) { //xy - xz + yz
    int numero[3] = { 0 };
    for (int i = 0; i < cantidad_sujetos; i++)
    {
        Bin2Dec(poblacion[i], longitud_gen, numero);

        adaptacion[i] = (int)(numero[0] * numero[1] - numero[0] * numero[2] + numero[1] * numero[2]);
    }
} // Función de Adaptación Poblacion Parcial

int* MaximizacionGenetica::Bin2Dec(string Cad, int longitud_gen, int XYZ[]) {
    int potencia;
    string splitCadena[3];
    int numero = 0;
    for (int i = 0; i < 3; i++)
    {
        splitCadena[i] = Cad.substr((longitud_gen * i) / 3, longitud_gen / 3);
    }

    for (int j = 0; j < 3; j++)
    {
        potencia = 0;
        XYZ[j] = 0;
        numero = 0;
        for (unsigned long i = splitCadena[j].length(); i > 0; i--, potencia++)
        {
            numero += (stoi(splitCadena[j].substr(i-1, 1)) * (int)pow(2, potencia));
            XYZ[j] += (stoi(splitCadena[j].substr(i-1, 1)) * (int)pow(2, potencia));
        }
    }
    return XYZ;
} // Binario a Decimal

void MaximizacionGenetica::genera_poblacion_inicial(int cantidad_sujetos, int longitud_del_gen) {
    double r = 0;

    for (int i = 0; i < cantidad_sujetos; i++)
    {
        poblacion_actual[i] = "";
        for (int j = 1; j <= longitud_del_gen; j++)
        {
            r = (double)rand() / (double)RAND_MAX;
            if (r < 0.5)
                poblacion_actual[i] += "1";
            else
                poblacion_actual[i] += "0";
        }
    }
} // Genera Población Inicial

void MaximizacionGenetica::normalizarAdaptacion(int* adaptacion, float* adaptacionNormal, int cantidad_sujetos)
{
    int max = INT16_MIN;
    int min = INT16_MAX;

    for (int i = 0; i < cantidad_sujetos; i++)
    {
        if (adaptacion[i] > max)
            max = adaptacion[i];
        else if (adaptacion[i] < min)
            min = adaptacion[i];
    }
    if (min > 0)
        for (int i = 0; i < cantidad_sujetos; i++)
            adaptacionNormal[i] = (float)(adaptacion[i]);
    else
        for (int i = 0; i < cantidad_sujetos; i++)
        {
            adaptacionNormal[i] = (float)(adaptacion[i] - min) / (float)(max - min);
               
        }
}

void MaximizacionGenetica::probabilidades_acumuladas(int* adaptacion, int cantidad_sujetos) 
{
    float suma = 0.0;
    float* adaptacionNormal = new float[cantidad_sujetos];
    normalizarAdaptacion(adaptacion, adaptacionNormal, cantidad_sujetos);
    for (int i = 0; i < cantidad_sujetos; i++)
        suma += adaptacionNormal[i];
    probabilidad_acumulada[0] = adaptacionNormal[0] / suma;
    for (int i = 1; i < cantidad_sujetos; i++)
        probabilidad_acumulada[i] = probabilidad_acumulada[i - 1] + adaptacionNormal[i] / suma;

} // Probabilidades Acumuladas
