/**
 * @file discrete_distribution.h
 */

#ifndef DISTRIBUTION_DISCRETE_DISTRIBUTION_H
#define DISTRIBUTION_DISCRETE_DISTRIBUTION_H

#include <string.h>

template <class SAMPLE_TYPE, class PROB_TYPE, unsigned _SIZE> class discrete_distribution :
	public probability_mass_function<SAMPLE_TYPE, PROB_TYPE>
{

	private:
	
		SAMPLE_TYPE *_sample ;
		PROB_TYPE *_prob ;
		
		/**
		 * Defines a new probability for the index of the prob_space
		 *
		 * @param index	Index within the prob_space to replace
		 * @param sample	Sample data to insert at this index
		 */
		inline void sample_space(unsigned index, SAMPLE_TYPE sample) {
			_sample[index] = sample ;
		}
		
		/**
		 * Defines a new probability for the index of the prob_space
		 *
		 * @param index	Index within the prob_space to replace
		 * @param prob		Probability to insert at this index
		 */
		inline void prob_space(unsigned index, PROB_TYPE prob) {
			try {
				_prob[index] = prob ;
				PROB_TYPE one = 0.0 ;
				for(unsigned i=0; i<_SIZE; ++i) {
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
		}
	
	public:
	
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
			for(unsigned i=0; i<_SIZE; ++i) {
				one += _prob[i] ;
				if(p <= one) {return _sample[i] ;}
			}
			return _sample[_SIZE] ;
		}

		/**
		 * A function call that returns the probability
		 * associated with a given element in the sample
		 * space.
		 *
		 * @param x	An element of the sample space.
		 */
		virtual PROB_TYPE probability(SAMPLE_TYPE x) {
			PROB_TYPE result = 0 ;
			return result ;
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
		discrete_distribution(PROB_TYPE* prob) : _prob(prob) {
			try {
				PROB_TYPE one = 0.0 ;
				for(unsigned i=0; i<_SIZE; ++i) {
					one += _prob[i] ;
				}
				if ( !(abs(one-1) <= 1e-14) ) {
					throw one ;
				}
				_sample = new SAMPLE_TYPE[_SIZE] ;
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
		discrete_distribution(SAMPLE_TYPE* sample, PROB_TYPE* prob) :
		_sample(sample), _prob(prob) {
			try {
				PROB_TYPE one = 0.0 ;
				for(unsigned i=0; i<_SIZE; ++i) {
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
		}
};

#endif
