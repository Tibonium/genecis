#include <genecis/tree/quadtree.h>
#include <iostream>
#include <cstdlib>
#include <list>

using namespace std ;
using namespace genecis::tree ;

struct point {
    typedef double  coord_type ;
    point() {}
    point( coord_type __x, coord_type __y )
        : x(__x), y(__y)
    {}
    coord_type x ;
    coord_type y ;
};

struct box {
    typedef double  coord_type ;
    box( coord_type _x, coord_type _y,
         coord_type _w, coord_type _h )
        : x(_x), y(_y), width(_w), height(_h)
    {}
    coord_type x ;
    coord_type y ;
    coord_type width ;
    coord_type height ;
};

template<class L>
bool compare_list( const L& truth, const L& result ) {
    bool ans = true ;
    size_t size( truth.size() ) ;
    if( size == result.size() ) {
        typename L::const_iterator t = truth.begin() ;
        typename L::const_iterator r = result.begin() ;
        while( t != truth.end() ) {
            if( (t->x != r->x) || (t->y != r->y) )
                ans = false ; break ;
            t++ ;
            r++ ;
        }
    } else {
        ans = false ;
    }
    return ans ;
}

template<class L>
void print_list( const L& out ) {
    typename L::const_iterator i = out.begin() ;
    while( i != out.end() ) {
        cout << "(" << i->x << ", " << i->y << ")" << endl ;
        i++ ;
    }
}

int main() {

    cout << "Creating an empty quadtree" << endl ;
    quadtree_type<point,5>::points point_tree(0,0,100,100) ;
    cout << "Done." << endl ;
    
    point p ;
    srand(1) ;
    size_t N = 50 ;
    for(size_t i=0; i<N; ++i) {
        p.x = rand() % 100 ;
        p.y = rand() % 100 ;
        point_tree.insert(p) ;
    }
    
//    point_tree.print() ;
    
    // query test
    box b( 0, 0, 50, 50 ) ;
    list<point> result, truth ;
    truth.push_back( point(11,42) ) ;
    truth.push_back( point(13,26) ) ;
    truth.push_back( point(40,26) ) ;
    truth.push_back( point(46,29) ) ;
    truth.push_back( point(43,50) ) ;
    truth.push_back( point(21,19) ) ;
    truth.push_back( point(5,25) ) ;
    truth.push_back( point(49,21) ) ;
    truth.push_back( point(29,2) ) ;
    truth.push_back( point(36,5) ) ;
    truth.push_back( point(39,12) ) ;
    point_tree.query( b, &result ) ;
    cout << "Query done, size of list is: " << result.size() << endl ;
    cout << "Result list: " << endl ;
    print_list( result ) ;
    cout << "Truth list: " << endl ;
    print_list( truth ) ;
    cout << "Query was " << ( (compare_list(truth,result)) ? "successful" : "unsuccessful" ) << endl ;
}
