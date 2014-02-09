/**
 * @file goal.h
 */

#ifndef AI_GOAL_H
#define AI_GOAL_H

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

#endif
