/**
 * @file discrete_distribution.h
 */

#ifndef GENECIS_DISTRIBUTION_DISCRETE_DISTRIBUTION_H
#define GENECIS_DISTRIBUTION_DISCRETE_DISTRIBUTION_H

#include <cstring>
#include <cstdio>
#include <vector>

namespace genecis {
namespace distribution {

using namespace std ;

template <class SAMPLE_TYPE, class PROB_TYPE> class discrete_distribution :
	public probability_mass_function<SAMPLE_TYPE, PROB_TYPE>
{

	private:
	
		vector<SAMPLE_TYPE> _sample ;
		vector<PROB_TYPE> _prob ;
		unsigned _size ;
		
	public:
			
		/**
		 * Defines a new sample in the sample space. May not increase
		 * the size of the sample space. Use add_element to increase
		 * the size of the probability/sample space
		 *
		 * @param index	Index within the prob_space to replace
		 * @param sample	Sample data to insert at this index
		 */
		inline void sample_space(unsigned index, SAMPLE_TYPE sample) {
			_sample[index] = sample ;
		}
		
		/**
		 * Defines a new probability space
		 *
		 * @param prob		The new probability space
		 */
		inline void prob_space(vector<PROB_TYPE> prob) {
			try {
				PROB_TYPE one = 0.0 ;
				for(unsigned i=0; i<prob.size(); ++i) {
					one += prob[i] ;
				}
				if ( !(abs(one-1) <= 1e-14) ) {
					throw one ;
				}
				_prob = prob ;
			 } catch (PROB_TYPE e) {
			 	cout << "Total probability must equal 1.0, " 
			 		<< "probability is: " << setprecision(18)
			 		<< e << endl;
			 }
		}
		
		/**
		 * Adds a new element to the sample space.
		 *
		 * @param new_sample	The element to be added to the
		 *					sample space.
		 * @param prob			The new probability vector for
		 *					the new sample space.
		 */
		inline void add_element( SAMPLE_TYPE new_sample, 
							vector<PROB_TYPE> new_prob) {
			++_size ;
			_sample.push_back(new_sample) ;
			_prob.resize(new_prob.size()) ;
			for(unsigned i=0; i<_prob.size(); ++i) {
				_prob[i] = new_prob[i] ;
			}
		}

		/**
		 * Redefine the sample space and probability space.
		 *
		 * @param new_sample	The new sample space
		 * @param new_prob		The new probability space
		 */
		inline void rename_space( vector<SAMPLE_TYPE> new_sample,
						 	 vector<PROB_TYPE> new_prob )
		{
			_sample.resize(new_sample.size()) ;
			for(unsigned i=0; i<_prob.size(); ++i) {
				_sample[i] = new_sample[i] ;
			}
			_prob.resize(new_prob.size()) ;
			for(unsigned i=0; i<_prob.size(); ++i) {
				_prob[i] = new_prob[i] ;
			}
			_size = _sample.size() ;
		}
				
		/**
		 * Returns the element of the sample space
		 * at the requested index.
		 *
		 * @param i	index value to look at
		 */
		inline SAMPLE_TYPE sample_space(unsigned i) {
			return _sample[i] ;
		}
		
		/**
		 * Returns the element of the probability
		 * space at the requested index.
		 *
		 * @param i	index value to look at
		 */
		inline PROB_TYPE prob_space(unsigned i) {
			return _prob[i] ;
		}
	
		/**
		 * A function call that returns the element of the
		 * sample space with the associated probability.
		 *
		 * @param p	The value between [0,1] associated
		 *			with the probability of the sample
		 *			space.
		 */
		virtual SAMPLE_TYPE probability(PROB_TYPE p) {
			PROB_TYPE one = 0.0 ;
			for(unsigned i=0; i<_prob.size(); ++i) {
				one += _prob[i] ;
				if(p <= one) {return _sample[i] ;}
			}
			return _sample[_size-1] ;
		}

		/**
		 * A function call that returns the probability
		 * associated with a given element in the sample
		 * space.
		 *
		 * @param x	An element of the sample space.
		 */
		virtual PROB_TYPE probability(SAMPLE_TYPE x) {
			for(unsigned i=0; i<_sample.size(); ++i) {
				if( _sample[i] == x ) {return _prob[i] ;}
			}
			return 0 ;
		}

		/**
		 * Create a discrete distribution from a set of
		 * probabilities only and create an empty array
		 * of _SIZE to be populated with sample elements
		 * at a later time.
		 *
		 * @param prob		Array of probabilities used to
		 *				create a discrete probability set.
		 */
		discrete_distribution(vector<PROB_TYPE> prob) : _prob(prob) {
			try {
				PROB_TYPE one = 0.0 ;
				for(unsigned i=0; i<_prob.size(); ++i) {
					one += _prob[i] ;
				}
				if ( !(abs(one-1) <= 1e-14) ) {
					throw one ;
				}
				_size = _prob.size() ;
				//_sample = new SAMPLE_TYPE[_size] ;
			 } catch (PROB_TYPE e) {
			 	cout << "Total probability must equal 1.0, " 
			 		<< "probability is: " << setprecision(18)
			 		<< e << endl;
			 }
		}

		/**
		 * Create a discrete distribution from a sample
		 * space and associated probabilities.
		 *
		 * @param sample	Array of elements that make up
		 *				the discrete sample space.
		 * @param prob		The associated probabilities of
		 *				the elements of the sample space.
		 */
		discrete_distribution(vector<SAMPLE_TYPE> sample,
			vector<PROB_TYPE> prob) : _sample(sample), _prob(prob) {
			try {
				if( _sample.size() != _prob.size() ) {
				    	int nums[] = { _sample.size(), _prob.size() } ;
					throw nums ;
				}
				_size = _sample.size() ;
				try {
					PROB_TYPE one = 0.0 ;
					for(unsigned i=0; i<_prob.size(); ++i) {
						one += _prob[i] ;
					}
					if ( !(abs(one-1) <= 1e-14) ) {
						throw one ;
					}
				 } catch (PROB_TYPE e) {
				 	cout << "Total probability must equal 1.0, " 
				 		<< "probability is: " << setprecision(18)
				 		<< e << endl;
				 }
			} catch (int* e) {
				printf("Size of sample space(%u) must be equal to", e[0]) ;
				printf(" size of probability space(%u).\n",e[1]);
			}	
		}
		
		/// Destructor
		//~discrete_distribution() {}
};

}	// end of namespace distribution
}	// end of namespace genecis

#endif
