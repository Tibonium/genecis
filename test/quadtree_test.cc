#include <genecis/tree/quadtree.h>
#include <iostream>
#include <cstdlib>

using namespace std ;
using namespace genecis::tree ;

struct point {
    typedef double  coord_type ;
    coord_type x ;
    coord_type y ;
};

int main() {

    cout << "Creating an empty quadtree" << endl ;
    quadtree_type<point,5>::points point_tree(0,0,100,100) ;
    cout << "Done." << endl ;
    
    point p ;
    srand(1) ;
    int N = 50 ;
    for(int i=0; i<N; ++i) {
        p.x = rand() % 100 ;
        p.y = rand() % 100 ;
        point_tree.insert(p) ;
    }
    
    point_tree.print() ;

}
