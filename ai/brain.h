/**
 * @file brain.h
 */
 
#ifndef GENECIS_AI_BRAIN_H
#define GENECIS_AI_BRAIN_H

#include <fstream>
#include <sstream>
#include <iomanip>
#include "decision.h"
#include "goal.h"

namespace genecis {
namespace ai {

using namespace std ;

/**
 * Artifical intelligence decision maker. This class is the heart of
 * the AI program. It unites all classes that allow the AI to make a 
 * decision and stores the decisions and the "decision past" inside 
 * a "memory bank" to be recalled each time a decision needs to be made.
 *
 * A goal is passed into the brain, where it is stored and parameters
 * of "favorability" are constructed. These "favorability" factors
 * are stored within the brain and are used to determine if a decision
 * can be "favorable" or "unfavorable".
 *
 * The decision is then compared against each "memory bank" entry
 * and determines if it is a "good guess". If the decision is determined
 * to be a "good guess", the brain then attempts the decision and 
 * evaluates the outcome.
 *
 * If the outcome is "favorable", the decision is then passed on to
 * and waits for another decision to be passed into the brain. However,
 * if the decision is determined to be "unfavorable", the brain inputs
 * this into the "memory bank" and then attempts to find a more
 * "favorable" decision from the "memory bank".
 *
 * If no "favorable" decision exists, the brain may choose from three
 * options. 
 * 1. It may choose to accept the least "unfavorable", the lesser
 *    of two evils, and attempt the decision regardless of its
 *	  "favorability" factor.
 * 2. It may choose to select a random decision, regardless of the
 *    "favorability" factor and use that decision.
 * 3. Attempt to create a "new" decision and use that decision.
 * 
 */

class brain {

	private:
	
		fstream _memoery_bank ;
		goal* _goal ;
	
	public:
	
		// Constructor
		brain(goal* end_game) : _goal(end_game) {
			ostringstream filename ;
			filename << _goal << ".mb" ;
			string _name = filename.str() ;
			const char* membank_name = (char*)_name.c_str() ;
			_memory_bank.open(membank_name, fstream::in | 
					 	fstream::out | fstream::app) ;
		}
		
		// Destructor
		~brain() {
			_memory_bank.close() ;
		}

};

}	// end of namespace ai
}	// end of namespace genecis
#endif
