#include "MOEA_D.h"
#include <float.h>
#include <random>

const int MOEA_D::PARAMS = 4;

// Inicializa los parámetros iniciales del algoritmo
bool MOEA_D::init(const vector<string> &params) {
    if(params.size() != MOEA_D::PARAMS){
        cerr << "Error\nParams for MOEAD_D are: <neighborhood_size> <replacedSolutions> <mutationProb> <seed>" << endl;
        return false;
    } else {
        neighSize = stoi(params[0]);
        replacedSolutions = stoi(params[1]);
        mutationProb = stof(params[2]);
        seed = stof(params[3]);
        neighborhood.resize(getPopulationSize(), std::vector<int>());
        lambdaV.resize(getPopulationSize(), std::vector<double>());
        childs.resize(0);
        return true;
    }
}

// Define una generación de búsqueda del algoritmo
void MOEA_D::runGeneration() {
    if(getGeneration() == 0){
        initWeights();
        initNeighborhood(population);
        initZVector();
    } else {
        reproduce();
        updateReferencePoint(childs);
        updateNeighbors();
    }
}

void MOEA_D::initWeights() {
    const int objs = (*population)[0]->getNumberOfObj();
    const int size = getPopulationSize();
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.01, 1.0);
    for(int i = 0; i < size; i++) {
        lambdaV[i].resize(objs);
        for(int j = 0; j < objs; j++){
            lambdaV[i][j] = distribution(generator);
        }
    }
}

void MOEA_D::initNeighborhood() {
    const int size = getPopulationSize();
    vector<double> distance(size);
    vector<int> idx(size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            distance[j] = getEuclideanDistanceFromCoeff(lambdaV[i], lambdaV[j]);
            idx[j] = j;
        }
        minFastSort(distance, idx);
        neighborhood[i].resize(neighSize);
        for(int k = 0; k < neighSize; k++){
            neighborhood[i][k] = idx[k];
        }
    }
}

double MOEA_D::getEuclideanDistanceFromCoeff(const vector<double>& coeff1,
                                            const vector<double>& coeff2)
                                            const {
	double dist = 0;
    const int size = coeff1.size();
	for (int i = 0; i < size; i++){
		dist += (coeff1[i] - coeff2[i]) * (coeff1[i] - coeff2[i]);
	}
	return sqrt(dist);
}

void MOEA_D::minFastSort(vector<double>& distances, vector<int>& idx) {
    const int size = getPopulationSize();
    for (int i = 0; i < neighSize; i++) {
        for (int j = i + 1; j < size; j++) {
            if (distances[i] > distances[j]) {
                double temp = distances[i];
                distances[i] = distances[j];
                distances[j] = temp;
                int id = idx[i];
                idx[i] = idx[j];
                idx[j] = id;
            }
        }
    }
}

void MOEA_D::initZVector() {
    zVector = unique_ptr<Individual>(this->getSampleInd());
    const int objs = (*population)[0]->getNumberOfObj();
    for(int i = 0; i < objs; i++) {
        zVector->setVar(i, 1.0e+30);
    }
    updateReferencePoint(population);
}

void MOEA_D::updateReferencePoint(vector<Individual*>& ind) {
    const int objs = (*population)[0]->getNumberOfObj();
    const int size = ind->size();
    for(int i = 0; i < objs; i++) {
        for(int j = 0; j < size; j++) {
            if((*ind)[j]->getInternalOptDirection(i) == MINIMIZE) {
                if(isless((*ind)[j]->getObj(i), zVector->getObj(i))) {
                    zVector->setObj(i, (*ind)[j]->getObj(i));
                }
            } else {
                if(isgreater((*ind)[j]->getObj(i), zVector->getObj(i))) {
                    zVector->setObj(i, (*ind)[j]->getObj(i));
                }
            }
        }
    }
}

void MOEA_D::reproduce() {
    int size = getPopulationSize();
    std::random_device rd;
    std::mt19937 range(rd());
    std::uniform_int_distribution<int> uni(0, size);
    for(int i = 0; i < size; i++) {
        int l = uni(range);
        int k = uni(range);
        unique_ptr<Individual> indL = (*population)[l]->clone();
        unique_ptr<Individual> indK = (*population)[k]->clone();
        indL->crossover(indK);
        indL->mutation(mutationProb);
        childs.push_back(indL);
    }
}

void MOEA_D::improvement() {
    return;
}

void MOEA_D::updateNeighbors() {

}

// Rellena un frente con las soluciones actuales
void MOEA_D::getSolution(MOFront *p) {
   for (unsigned int i = 0;  i < population->size(); i++) {
      p->insert((*population)[i]);
   }
}

// Muestra la información relativa al algoritmo
void MOEA_D::printInfo(ostream &os) const {
   os << "TODO" << endl;
}
