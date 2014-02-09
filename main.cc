#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "distribution/distribution.h"

int main( int argc, char* argv[] ) {

	gaussian* dist = new gaussian(2,10,0.00001) ;
	gaussian dist2(2,11,0.00001) ;
	cout << "does dist == dist2: " << (*dist==dist2) << endl;
	cout << dist2 << endl;
	dist2 = *dist ;
	cout << "does dist == dist2: " << (*dist==dist2) << endl;
	cout << dist2 << endl;
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
	
	double t_prob [] = { 0.1, 0.25, 0.1, 0.2, 0.35 } ;
	vector<double> prob ( t_prob, t_prob + sizeof(t_prob)/sizeof(double) ) ;
	string t_set [] = {"apple", "orange", "banana", "pineapple", "mango"} ;
	vector<string> set ( t_set, t_set + 5 ) ;
	discrete_distribution<string,double> d_dist(set,prob) ;
	
	double p = (rand()%100) / 100.0 ;
	cout << "probability: " << p
		<< "\tsample_elem: "
		<< d_dist.probability(p) << endl;
		
	double new_t_prob [] = { 0.1, 0.25, 0.1, 0.2, 0.15, 0.2 } ;
	vector<double> new_prob ( new_t_prob, new_t_prob + sizeof(new_t_prob)/sizeof(double) ) ;
	cout << "New sample/prob space" << endl;
	d_dist.add_element("apricot",new_prob) ;
	for(unsigned i=0; i<new_prob.size(); ++i) {
		cout << "sample_elem: " << d_dist.sample_space(i)
			<< "\tprobability: " << d_dist.prob_space(i)
			<< endl ;
	}
	p = (rand()%100) / 100.0 ;
	cout << "probability: " << p
		<< "\tsample_elem: "
		<< d_dist.probability(p) << endl;
	
	delete dist ;
	return 0;
	
}
