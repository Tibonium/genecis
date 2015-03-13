/**
 * @file thread_base.h
 */
#pragma once

#include <pthread.h>
#include <cstddef>

namespace genecis {
namespace thread {

template<class T> void* __run(void* obj) ;

template<class T>
class thread_base {

public:

    typedef T   derived_type ;
    typedef std::size_t     size_type ;
    typedef pthread_mutex_t    read_write_mutex ;

    /**
     * Run method
     */
    virtual void run() = 0 ;

    /**
     * Join method
     */
    void spawn( pthread_t* t ) {
        pthread_create( t, NULL, __run<derived_type>, dynamic_cast<derived_type*>(this) ) ;
    }

    /**
     * Interrupt method
     */
    void interrupt() {
        pthread_cancel(*this) ;
        pthread_testcancel() ;
    }

    /**
     * Complete method
     */
    bool complete() {
        return __running ;
    }

    static read_write_mutex  __key ;
    static bool __running ;

protected:

    /**
     * Constructor
     */
    thread_base() {}

    /**
     * Destructor
     */
    virtual ~thread_base() {}

};

template<class T> pthread_mutex_t thread_base<T>::__key ;
template<class T> bool thread_base<T>::__running = false ;

/**
 * Increments count to keep track of the number
 * of threads that are running.
 */
template<class T>
void start() {
    pthread_mutex_lock( &thread_base<T>::__key ) ;
    thread_base<T>::__running = true ;
    pthread_mutex_unlock( &thread_base<T>:: __key ) ;
}

/**
 * Decrements the count to keep track of the
 * number of threads that are currently running.
 */
template<class T>
void finish() {
    pthread_mutex_lock( &thread_base<T>::__key ) ;
    thread_base<T>::__running = false ;
    pthread_mutex_unlock( &thread_base<T>::__key ) ;
}

/**
 * Run engine for threads
 */
template<class T>
void* __run(void* obj) {
    try {
        T* __obj = (T*) obj ;
        start<T>() ;
        __obj->run() ;
        finish<T>() ;
        pthread_exit(NULL) ;
    } catch (int e) {
        pthread_exit(NULL) ;
    }
}

}   // end of namespace thread
}   // end of namespace genecis
