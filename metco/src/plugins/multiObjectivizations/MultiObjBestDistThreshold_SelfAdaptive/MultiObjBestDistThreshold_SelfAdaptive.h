/***********************************************************************************
 * AUTHORS
 *   - Eduardo Segredo Gonz�lez 
 *   - Carlos Segura Gonz�lez
 * 
 * *********************************************************************************/


#ifndef MULTIOBJBESTDISTTHRESHOLD_SELFADAPTIVE_H 
#define MULTIOBJBESTDISTTHRESHOLD_SELFADAPTIVE_H 

#include "MultiObjectivization.h"

#define BESTPOP_THRVALUE 0
#define MEANPOP_THRVALUE 1
#define CORRESP_THRVALUE 2

class MultiObjBestDistThreshold_SelfAdaptive : public MultiObjectivization {
  public:
		void convertToMultiObjective(vector<Individual *> *parents, vector<Individual *> *offSprings, vector<Individual *> *reference,  int ordObj, int numberGeneration);
		int getOptDirection() { return MAXIMIZE; }
  	bool init(const vector<string> &params);
  private:
		double shiftValue;
		int thrLocation;
};

#endif
