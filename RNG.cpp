#include "head.h"
#include <random> 

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dis(0, 1); 

double RNG(){
	return dis(gen);
}
