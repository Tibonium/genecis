/**
 * @file sphere.h
 */
#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#define GL_GLEXT_PROTOTYPES
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
    
    void draw( container::array<double> center, double dt ) ;

    /**
     * Draws the sphere on the display at the coordinates (x,y,z)
     *
     * @param x     x-coordinate value for the center of the sphere
     * @param y     y-coordinate value for the center of the sphere
     * @param z     z-coordinate value for the center of the sphere
     */
    void draw(GLfloat x, GLfloat y, GLfloat z, double dt ) ;
    
    /**
     * Sets the color of each sector/ring for the sphere
     */
    void color(GLfloat r, GLfloat g, GLfloat b) ;
    
    /**
     * Returns a reference to the sphere's current rotation matrix
     */
    GLfloat* rotation_matrix() {
    	return _rotation ;
    }
    
    /**
     * Accesors for the position
     */
    GLfloat position( const size_type i ) {
    	return _position[i] ;
    }
    
    void position( const size_type i, GLfloat p ) {
    	_position[i] = p ;
    }
    
    container_type* position() {
    	return &_position ;
	}

    /**
     * Accesors for the velocity
     */
    GLfloat velocity( const size_type i ) {
    	return _velocity[i] ;
    }
    
    void velocity( const size_type i, GLfloat v ) {
    	_velocity[i] = v ;
    }
    
    container_type* velocity() {
    	return &_velocity ;
	}
	
    /**
     * Accesors for the acceleration
     */
    GLfloat acceleration( const size_type i ) {
    	return _acceleration[i] ;
    }
    
    void acceleration( const size_type i, GLfloat a ) {
    	_acceleration[i] = a ;
    }
    
    container_type* acceleration() {
    	return &_acceleration ;
	}
	
	void id( GLuint i ) {
		_id = i ;
	}
	
	GLuint id() {
		return _id ;
	}
	
private:

    /**
     * Vertices of the surfaces that make up the sphere
     */
    container_type _vertices ;
    
    /**
     * Normals to the surfaces of the sphere
     */
    container_type _normals ;
    
    /**
     * Texture coordinates
     */
    container_type _texcoords ;
    
    /**
     * Color of each surface that makes up the sphere
     */
    container_type _colors ;
    
    /**
     * Position vector
     */
    container_type _position ;
    
    /**
     * Velocity vector
     */
    container_type _velocity ;
    
    /**
     * Acceleration vector
     */
    container_type _acceleration ;
    
    /**
     * Indices of the vertices
     */
    container::array<GLushort> _indices ;
    
	/**
	 * Color values
	 */
    GLfloat _red ;
    GLfloat _green ;
    GLfloat _blue ;

    /**
     * Rotation matrix for this object
     */
    GLfloat* _rotation ;
    
    /**
     * Sphere's ID
     */
    GLuint _id ;
};

}   // end namespace graphics
}   // end namespace genecis
