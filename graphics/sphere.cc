#include <genecis/graphics/sphere.h>
#include <ctime>
#include <cstring>

using namespace genecis::graphics ;

/**
 * Constructor
 */
Sphere::Sphere(integral_type radius, size_type rings, size_type sectors)
    : _vertices(rings * sectors * 3, 0),
      _normals(rings * sectors * 3, 0),
      _texcoords(rings * sectors * 2, 0),
      _colors(rings * sectors * 3, 0),
      _position(3, 0), _velocity(3, 0),
      _acceleration(3,0),
      _indices(rings * sectors * 4, 0),
      _red(0), _green(0), _blue(0), _id(0)
{
    integral_type const R = 1./(integral_type)(rings-1) ;
    integral_type const S = 1./(integral_type)(sectors-1) ;
    
    container_type::iterator v = _vertices.begin() ;
    container_type::iterator n = _normals.begin() ;
    container_type::iterator t = _texcoords.begin() ;
    
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
    
    container::array<GLushort>::iterator i = _indices.begin() ;
    for(size_type r=0; r<(rings - 1); ++r) {
        for(size_type s=0; s<(sectors - 1); ++s) {
            *i++ = r * sectors + s ;
            *i++ = r * sectors + (s + 1) ;
            *i++ = (r + 1) * sectors + (s + 1) ;
            *i++ = (r + 1) * sectors + s ;
        }
    }

    _rotation = new GLfloat[rings * sectors * 3] ;
    std::fill_n( _rotation, rings*sectors*3, 0) ;
}

/**
 * Destructor
 */
Sphere::~Sphere()
{
	if( _rotation ) {
		delete _rotation ;
		_rotation = NULL ;
	}
}

void Sphere::draw(container::array<double> center, double dt)
{
	draw(center(0), center(1), center(2), dt) ;
}

/**
 * Draws the sphere centered at (x,y,z)
 */
void Sphere::draw(GLfloat x, GLfloat y, GLfloat z, double dt)
{
    glMatrixMode( GL_MODELVIEW ) ;
	glPushMatrix() ;
	glRotatef( _velocity(1)*dt, 0.0, 1.0, 0.0 ) ;
	glRotatef( _velocity(2)*dt, 0.0, 0.0, 1.0 ) ;
	glMultMatrixf( _rotation ) ;
	glGetFloatv( GL_MODELVIEW_MATRIX, _rotation ) ;
    glTranslatef( x, y, z ) ;
    
    glEnableClientState( GL_VERTEX_ARRAY ) ;
    glEnableClientState( GL_NORMAL_ARRAY ) ;
    glEnableClientState( GL_TEXTURE_COORD_ARRAY ) ;
    glEnableClientState( GL_COLOR_ARRAY ) ;
    
    glVertexPointer( 3, GL_FLOAT, 0, _vertices.begin() ) ;
    glNormalPointer( GL_FLOAT, 0, _normals.begin() ) ;
    glTexCoordPointer( 2, GL_FLOAT, 0, _texcoords.begin() ) ;
    glColorPointer( 3, GL_FLOAT, 0, _colors.begin() ) ;
    
    glDrawElements( GL_QUADS, _indices.size(), GL_UNSIGNED_SHORT, _indices.begin() ) ;
	glPopMatrix() ;
    
//    glGenBuffers( 1, &_id ) ;
//    glBindBuffer( GL_ARRAY_BUFFER, _id ) ;
//    glBufferData( GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*_vertices.size(), _vertices.begin(), GL_DYNAMIC_DRAW ) ;
//    glEnableVertexAttribArray( 0 ) ;
//    glVertexAttribPointer( _id, 4, GL_FLOAT, GL_FALSE, 0, 0 ) ;
//    
//    glGenBuffers( 1, &_id ) ;
//    glBindBuffer( GL_ARRAY_BUFFER, _id ) ;
//    glBufferData( GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*_indices.size(), _indices.begin(), GL_DYNAMIC_DRAW ) ;
//    glEnableVertexAttribArray( 0 ) ;
//    glVertexAttribPointer( _id, 4, GL_FLOAT, GL_FALSE, 0, 0 ) ;
//    glBufferData( GL_ARRAY_BUFFER, sizeof(_vertices) + sizeof(_indices), 0, GL_STATIC_DRAW ) ;
//    glBufferSubData( GL_ARRAY_BUFFER, 0, _vertices.size(), _vertices.begin() ) ;
//    glBufferSubData( GL_ARRAY_BUFFER, _vertices.size(), _indices.size(), _indices.begin() ) ;
//    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indices.begin() ) ;
//    glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, _indices.size(), _indicies.begin() ) ;

//    glDrawArrays( GL_QUADS, 0, _vertices.size() ) ;
//    glDisableVertexAttribArray( _id ) ;
//	glDrawElements( GL_QUADS, _indices.size(), GL_UNSIGNED_SHORT, _indices.begin() ) ;
}

/**
 * Sets the color of the sphere
 */
void Sphere::color(GLfloat r, GLfloat g, GLfloat b)
{
	std::srand(0) ;
	//_red = r ;
	//_green = g ;
	//_blue = b ;
	int N = _colors.size() ;
	double res = 1.0 / N ;
	
	for(int i=0; i<N; i+=3) {
		_colors[i] =  std::fmod((r + i*res), 1.0) ;
		_colors[i+1] = std::fmod((g + i*res), 1.0) ;
		_colors[i+2] = std::fmod((b + i*res), 1.0) ;
	}
}
