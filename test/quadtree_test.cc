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
    friend std::ostream& operator<< (std::ostream& os, point& p) ;
};

std::ostream& operator<< (std::ostream& os, point& p) {
    os << "(" << p.x << ", " << p.y << ")" ;
    return os ;
}
    
struct box {
    typedef double  coord_type ;
    box( coord_type _x, coord_type _y,
         coord_type _w, coord_type _h )
        : x(_x), y(_y), width(_w), height(_h)
    {}
    template<class N>
    box( N* n )
        : x(n->__x), y(n->__y), width(n->__width), height(n->__height)
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
        point p = *i ;
        cout << p << endl ;
        i++ ;
    }
}

template<class P>
bool sort_by_x( const P& p1, const P& p2 ) {
    return p1.x < p2.x ;
}

int main() {

    cout << "Creating an empty quadtree" << endl ;
    quadtree_type<point,5>::points point_tree(0,0,100,100) ;
    cout << "Done." << endl ;
    
    point p ;
    box b( 0, 50, 50, 50 ) ;
    list<point> truth ;
    srand(1) ;
    size_t N = 50 ;
    for(size_t i=0; i<N; ++i) {
        p.x = rand() % 100 ;
        p.y = rand() % 100 ;
        if( b.x <= p.x && p.x <= (b.x+b.width) ) {
            if( b.y <= p.y && p.y <= (b.y+b.height) ) {
                truth.push_back( p ) ;
            }
        }
        point_tree.insert(p) ;
    }
    truth.sort( sort_by_x<point> ) ;    
//    point_tree.print() ;
    
    // query test
    list<point> result ;
    point_tree.query( b, &result ) ;
    result.sort( sort_by_x<point> ) ;
    cout << "Query done, size of list is: " << result.size() << endl ;

    bool good = compare_list(truth,result) ;
    cout << "Query was " << ( good ? "successful" : "unsuccessful" ) << endl ;
    if( !good ) {
        cout << "Result list: " << endl ;
        print_list( result ) ;
        cout << "Truth list: " << endl ;
        print_list( truth ) ;
    }
}
