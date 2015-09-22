/**
 * @file Gtime.h
 */
 
#include <ctime>
#include <sys/time.h>
 
class Gtime {
public:

	typedef std::size_t		size_type ;
	typedef double			value_type ;
	
	/**
	 * Empty constructor
	 */
	Gtime() {}
	
	/**
	 * Empty destructor
	 */
	virtual ~Gtime() {}
	
	/**
	 * Starts the time clock
	 */
	void start() {
		gettimeofday(&_start, NULL) ;
		_previous = _start ;
	}
	
	/**
	 * Returns the start time, in seconds.
	 */
	double initial_time() {
		return (_start.tv_sec + 0.000001*_start.tv_usec) ;
	}
	
	/**
	 * Returns the current time of day, in seconds.
	 */
	double current_time() {
		struct timeval tmp ;
		gettimeofday(&tmp, NULL) ;
		return (tmp.tv_sec + 0.000001*tmp.tv_usec) ;
	}
	
	/**
	 * Returns the amount of time that has elasped from
	 * start and now., in seconds.
	 */
	double time_elapsed() {
		struct timeval now ;
		gettimeofday(&now, NULL) ;
		return ((now.tv_sec - _start.tv_sec) + 0.000001*(now.tv_usec - _start.tv_usec)) ;
	}
	
	/**
	 * Returns the difference in time betweem the last check
	 * in time, t0 is first time called, and now, in seconds.
	 */
	double delta_checkIn() {
		struct timeval now ;
		gettimeofday(&now, NULL) ;
		double dtime = ((now.tv_sec - _previous.tv_sec) + 0.000001*(now.tv_usec - _previous.tv_usec)) ;
		_previous = now ;
		return dtime ;
	}
	
private:

	struct timeval _start ;
	struct timeval _previous ;

};
