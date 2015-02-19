#include <genecis/tree/quadtree.h>
#include <iostream>

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
    p.x = 10 ;
    p.y = 5 ;
    point_tree.insert(p) ;
    
    point_tree.print_tree() ;

}
