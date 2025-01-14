/***********************************************************************************
 * AUTORES
 *   - Ofelia Gonz�lez P�rez
 *   - Gara Miranda Valladares
 *   - Carlos Segura Gonz�lez
 * 
 * FECHA
 *    Noviembre 2007
 *
 * DESCRIPCION
 *    Individuo para la resolucion del problema de Benchmark ZDT1.
 *    El problema ZDT1 esta definido en:
 *       Comparison of Multiobjective Evolutionary Algorithms: Empirical Results
 *       Zitzler, E. and Deb, K. and Thiele, L.
 *    Consiste en:
 *       Minimizar (f1(x1), f2(x))
 *       sujeto a: f2(x) = g(x2,...,xm)*h(f1(x1),g(x2,...,xm))
 *       donde:    
 *         x = (x1,...,xm)
 *         m = 30
 *         f1(x1) = x1
 *         g(x2,...xm) = 1 + 9 SUM[i=2:m][xi/(m-1)]
 *         h(f1,g) = 1 - sqrt(f1/g)
 *         xi en [0,1]
 *
 *     Se han definido los metodos requeridos por Individual: init, mutation,
 *     crossover, evaluate y clone
 * ********************************************************************************/

#ifndef __ZDT1_H__
#define __ZDT1_H__

#include "Individual.h"
#include <math.h>

class ZDT1 : public Individual {
public:
	// Initialization method
	bool init (const vector<string> &params);


	// Evaluation
	void evaluate (void);

	// Ranges
	double inline getMaximum(const int i) const { return 1; }
	double inline getMinimum(const int i) const { return 0; }
	unsigned int inline getOptDirection(const int i) const { return MINIMIZE; }

	// Clone
	Individual* clone (void) const;

private:
	static long delay;
	// Constants
	static const int NPARAM = 30; 
	static const int NOBJ   = 2;
};

#endif
