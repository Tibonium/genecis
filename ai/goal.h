/**
 * @file goal.h
 */

#ifndef GENECIS_AI_GOAL_H
#define GENECIS_AI_GOAL_H

namespace genecis {
namespace ai {

class goal {

	private:
	
		string _goal_name ;
	
	public:
	
		// Constructor
		goal(const string name) : _goal_name(name) {}
	
		friend std::ostream& operator<< (std::ostream& os, const goal& other) ;

};

inline std::ostream& operator<< (std::ostream& os, const goal& other) {
	os << other._goal_name ;
	return os ;
}

}	// end of namespace ai
}	// end of namespace genecis
#endif
