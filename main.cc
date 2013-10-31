#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "distribution/distribution.h"

using namespace std;

int main( int argc, char* argv[] ) {

	gaussian* dist = new gaussian(2,10,0.00001) ;
	cout << "returned a value: " << dist->probability(1,10) << endl;
	uniform udist(2.0,7.0) ;
	cout << "uniform dist returns [6,4): " << udist.probability(0.0,3.948) << endl;
	poisson pdist(4) ;
	cout << "poisson lambda=4, k=5: " << pdist.probability(5.0) << endl;
	
	srand(time(NULL)) ;
	double n = 0.25 ;
	bernoulli bdist(n) ;
	cout << "Bernoulli with p=" << n << endl;
	for(int i=0; i<3; ++i) {
		double chance = (rand()%100) / 100.0 ;
		cout << "chance: " << chance
		     << "\tsuccess/fail: " << bdist.probability(chance)
		     << endl;
	}
	
	double prob [] = { 0.1, 0.25, 0.1, 0.2, 0.35 } ;
	string set [] = {"apple", "orange", "banana", "pineapple", "mango"} ;
	discrete_distribution<string,double,5> d_dist(set,prob) ;
	
	double p = (rand()%100) / 100.0 ;
	cout << "probability: " << p
		<< "\tsample_elem: "
		<< d_dist.probability(p) << endl;
	return 0;
	
}
