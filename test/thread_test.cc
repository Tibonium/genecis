/**
 * @file example/tests for thread classes
 */
#include <genecis/thread/thread_base.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std ;
using namespace genecis::thread ;

class test_thread :
        public thread_base<test_thread>
{
public:
    /** Empty constructor **/
    test_thread() : thread_base<test_thread> (), __ID(0), __s("") {}
    /** Default constructor **/
    test_thread( size_t id, const string& s )
        : thread_base<test_thread> (), __ID(id), __s(s)
    {}
    /** Assign operator **/
    test_thread operator=(const test_thread* rhs ) {
        __ID = rhs->__ID ;
        __s = rhs->__s ;
        return *this ;
    }
    /** Destructor **/
    virtual ~test_thread() {}
    /** Run method **/
    virtual void run() {
        cout << "thread " << __ID << " is running, " ;
        cout << __s << endl ;
    }
    /** Spawns a new thread **/
    void join() {
        spawn( &__self ) ;
    }
private:
    size_t __ID ;
    string __s ;
    pthread_t __self ;
};

int main() {

    string fruits[] = {"apple", "orange", "banana", "pear", "peach",
                       "mango", "papaya", "tangerine", "watermelon" } ;
    size_t size( sizeof(fruits)/sizeof(string) ) ;
    test_thread* t = new test_thread[size] ;
    std::srand(std::time(0)) ;
    size_t n = std::rand() % size ;
    for(size_t i=0; i<size; ++i)
    {
        t[i] = new test_thread(i,fruits[i]) ;
        t[i].join() ;
        if( i==n ) {
            cout << "waiting for thread " << n+1 << " to finish" ;
            while( t[n].complete() )
            {
                usleep(10) ;
                cout << "." ;
            }
            cout << "complete" << endl ;
        }
    }

}
