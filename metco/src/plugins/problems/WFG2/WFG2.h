/***********************************************************************************
 * AUTORES
 *   - Eduardo Manuel Segredo Gonzalez
 * 
 * FECHA
 *    Julio de 2008
 *
 * DESCRIPCION
 *    Individuo para la resolucion del problema de Benchmark WFG2
 *    
 *    El problema WFG2 esta definido en:
 *     "A Scalable Multi-objective Test Problem Toolkit"
 *      Simon Huband, Luigi Barone, Lyndon While and Phil Hingston
 * 
 *    Se han definido los metodos requeridos por la clase Individual: 
 *     - mutation
 *     - crossover 
 *     - evaluate
 *     - init 
 *     - clone
 *
 *    Para mas informacion acerca de la especificacion de un problema, referirse a
 *    al fichero Individual.h
 *
 * ********************************************************************************/


#ifndef __INDIVIDUALWFG2_H__
#define __INDIVIDUALWFG2_H__


#include <iostream>
#include <math.h>

#include "Individual.h"


class WFG2 : public Individual {
 
	public:
  
	// Funcion de inicializacion
	bool init (const vector<string> &params);
	
	
	// Evaluacion y seleccion del individuo
	void evaluate (void);
	
	// Clonacion
	Individual* clone (void) const;
	
	// Rangos
	double inline getMaximum(const int i) const { return 1; }
	double inline getMinimum(const int i) const { return 0; }
	unsigned int inline getOptDirection(const int i) const { return MINIMIZE; }
 
  private:
	
	// Funciones auxiliares al problema
	vector<double> subvector(const vector<double> &v, const int head, const int tail);
	double correct_to_01(const double &a, const double &epsilon = 1.0e-10);
	vector<double> calculate_x (const vector<double> &t_p, const vector<short> &A);
  vector<double> calculate_f (const double &D, const vector<double> &x, const vector<double> &h,
								            	const vector<double> &S);

	// Transiciones genericas
	double s_linear (const double &y, const double &A);
	double r_nonsep(const vector<double> &y, const int A);
	double r_sum (const vector<double> &y, const vector<double> &w);
	
  // Superficies genericas
	double convex(const vector<double> &x, const int m);
  double disc (const vector<double> &x, const int A, const double &alpha, const double &beta);

	// Transiciones del problema WFG2
	vector<double> WFG2_t1(const vector<double> &y, const int k);
	vector<double> WFG2_t2(const vector<double> &y, const int k);
	vector<double> WFG2_t3(const vector<double> &y, const int k, const int M);
	
	// Superficie del problema WFG2
	vector<double> WFG2_shape(const vector<double> &t_p);

	// Funciones propias de los problemas WFG
	vector<short> WFG_create_A (const int M, const bool degenerate);
	vector<double> WFG_calculate_f (const vector< double >& x, const vector< double >& h);
	
	// Constantes del problema WFG2
	static int k;             // Parametros relacionados con la posicion
	static const int l = 20;  // Parametros relacionados con la distancia

};

#endif
