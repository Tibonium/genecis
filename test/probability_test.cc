#include <iostream>
#include <genecis/probability/binomial.h>

USING_NAMESPACE(std)
USING_NAMESPACE(genecis::probability)
USING_NAMESPACE(genecis::math)

int main(int argv, char* argc[])
{
	cout << "11 choose 3: " << choose(11,3) << endl ; 
	cout << "11 choose 3, with probability of success of 10%: " << binomial::pmf(11, 3, 0.1)*100.0 << "%" << endl ;

}
