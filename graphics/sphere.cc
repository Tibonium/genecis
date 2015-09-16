#include <genecis/graphics/sphere.h>
#include <ctime>
#include <cstring>

using namespace genecis::graphics ;

/**
 * Constructor
 */
Sphere::Sphere(integral_type radius, size_type rings, size_type sectors)
    : vertices(rings * sectors * 3, 0),
      normals(rings * sectors * 3, 0),
      texcoords(rings * sectors * 2, 0),
      colors(rings * sectors * 3, 0),
      indices(rings * sectors * 4, 0),
      _red(0), _green(0), _blue(0)
{
    integral_type const R = 1./(integral_type)(rings-1) ;
    integral_type const S = 1./(integral_type)(sectors-1) ;
    
    container_type::iterator v = vertices.begin() ;
    container_type::iterator n = normals.begin() ;
    container_type::iterator t = texcoords.begin() ;
    
    for(size_type r=0; r<rings; ++r) {
        for(size_type s=0; s<sectors; ++s) {
            integral_type const y = std::sin(-M_PI_2 + M_PI * r * R) ;
            integral_type const x = std::cos(2*M_PI * s * S) * std::sin(M_PI * r * R) ;
            integral_type const z = std::sin(2*M_PI * s * S) * std::sin(M_PI * r * R) ;
            
            *t++ = s * S ;
            *t++ = r * R ;
            
            *v++ = x * radius ;
            *v++ = y * radius ;
            *v++ = z * radius ;
            
            *n++ = x ;
            *n++ = y ;
            *n++ = z ;
        }
    }
    
    container::array<GLushort>::iterator i = indices.begin() ;
    for(size_type r=0; r<(rings - 1); ++r) {
        for(size_type s=0; s<(sectors - 1); ++s) {
            *i++ = r * sectors + s ;
            *i++ = r * sectors + (s + 1) ;
            *i++ = (r + 1) * sectors + (s + 1) ;
            *i++ = (r + 1) * sectors + s ;
        }
    }
}

/**
 * Destructor
 */
Sphere::~Sphere()
{

}

/**
 * Draws the sphere centered at (x,y,z)
 */
void Sphere::draw(GLfloat x, GLfloat y, GLfloat z)
{
    glMatrixMode( GL_MODELVIEW ) ;
    glPushMatrix() ;
    glTranslatef( x, y, z ) ;
    
    glEnableClientState( GL_VERTEX_ARRAY ) ;
    glEnableClientState( GL_NORMAL_ARRAY ) ;
    glEnableClientState( GL_TEXTURE_COORD_ARRAY ) ;
    glEnableClientState( GL_COLOR_ARRAY ) ;
    
    glVertexPointer( 3, GL_FLOAT, 0, &vertices[0] ) ;
    glNormalPointer( GL_FLOAT, 0, &normals[0] ) ;
    glTexCoordPointer( 2, GL_FLOAT, 0, &texcoords[0] ) ;
    glColorPointer( 3, GL_FLOAT, 0, &colors[0] ) ;
    
    glDrawElements( GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0] ) ;
    glPopMatrix() ;
}

void Sphere::color(GLfloat r, GLfloat g, GLfloat b)
{
	std::srand(0) ;
	//_red = r ;
	//_green = g ;
	//_blue = b ;
	int N = colors.size() ;
	
	for(int i=0; i<N; i+=3) {
		colors[i] = r ; //(double)i / N ;
		colors[i+1] = g ; //(double)i / N ;
		colors[i+2] = b ; //(double)i / N ;
	}
}
