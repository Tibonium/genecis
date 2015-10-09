#include <iostream>
#include <cstdio>
#include <genecis/probability/binomial.h>
#include <genecis/probability/bernoulli.h>

USING_NAMESPACE(std)
USING_NAMESPACE(genecis::probability)
USING_NAMESPACE(genecis::math)

int main(int argv, char* argc[])
{
	cout << "11 choose 3: " << choose(11, 3) << endl ;
	cout << "11 choose 3, with probability of success at 10%: " << binomial::pmf(11, 3, 0.1)*100.0 << "%" << endl ;
	cout << "110 choose 50, with probability of success at 10%: " << binomial::pmf(110, 50, 0.1)*100.0 << "%" << endl ;
		
	cout << "Chance for 1 5* in an 11-draw: " << binomial::pmf(11, 1, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in an 11-draw: " << binomial::pmf(11, 2, 0.1)*100.0 << "%" << endl ;
	
	cout << "Chance for 1 5* in a 3-draw: " << binomial::pmf(3, 1, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in a 3-draw: " << binomial::pmf(3, 2, 0.1)*100.0 << "%" << endl ;
	cout << "Chance for 2 5*s in two 3-draws: " << binomial::pmf(6, 2, 0.1)*100.0 << "%" << endl ;

	number_generator::seed() ;
	cout << "Random number between [5, 10]: " << endl ;
	for(int i=0; i<10; ++i) {
		cout << number_generator::uniform(5, 10) << endl ;
	}
	
	int N = 110 ;
	printf("%i!: %e\n", N, factorial(N)) ;

}
