/**
 * @file sphere.h
 */
#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#include <genecis/container/array.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glu.h>

namespace genecis {
namespace graphics {

class Sphere {
public:

    typedef std::size_t     size_type ;
    typedef double          integral_type ;
    typedef container::array<GLfloat>   container_type ;

    /**
     * Constructor
     *
     * @param radius
     * @param rings
     * @param sectors
     */
    Sphere(integral_type radius, size_type rings, size_type sectors) ;
    
    /**
     * Empty Destructor
     */
    virtual ~Sphere() ;
    
    /**
     * Draws the sphere on the display at the coordinates (x,y,z)
     *
     * @param x     x-coordinate value for the center of the sphere
     * @param y     y-coordinate value for the center of the sphere
     * @param z     z-coordinate value for the center of the sphere
     */
    void draw(GLfloat x, GLfloat y, GLfloat z) ;

private:

    /**
     * Vertices of the surfaces that make up the sphere
     */
    container_type vertices ;
    
    /**
     * Normals to the surfaces of the sphere
     */
    container_type normals ;
    
    /**
     * Texture coordinates
     */
    container_type texcoords ;
    
    /**
     * Indices
     */
    container::array<GLushort> indices ;

};

}   // end namespace graphics
}   // end namespace genecis
