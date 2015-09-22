/**
 * @file graphics_text.cc
 */

#include <genecis/graphics/sphere.h>
#include <genecis/base/gtime.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

using namespace genecis ;
using namespace graphics ;

#define LEFT_CLICK Button1
#define MIDDLE_CLICK Button2
#define RIGHT_CLICK Button3
#define WHEEL_UP Button4
#define WHEEL_DOWN Button5

/// Global variables
Display *dpy ;
Window root, win ;
GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None } ;
XVisualInfo *vi ;
GLXContext glc ;
Colormap cmap ;
XSetWindowAttributes swa ;
XWindowAttributes wa ;
XEvent xev ;

container::array<double> pos(3, 0.0) ;
container::array<double> scale(3, 1.0) ;
Gtime run_time ;
double dt ;

/**
 * Creates the window to draw to
 */
void create_window(double width, double height)
{
	dpy = XOpenDisplay(NULL) ;
	if( dpy == NULL ) {
		fprintf(stderr, "Cannot open display\n") ;
		exit(0) ;
	}

	root = DefaultRootWindow(dpy) ;

	vi = glXChooseVisual(dpy, 0, att) ;
	if( vi == NULL ) {
		fprintf(stderr, "No Matching Visual\n") ;
		exit(0);
	}

	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone) ;
	if( cmap == 0 ) {
		fprintf(stderr, "Cannot create colormap\n") ;
		exit(0);
	}

	swa.event_mask = KeyPressMask | ButtonPressMask | ButtonMotionMask ;
	swa.colormap = cmap ;
	win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa) ;
	XStoreName(dpy, win, "OpenGL Sphere") ;
	XMapWindow(dpy, win) ;
	int s = DefaultScreen(dpy) ;
	XFillRectangle(dpy, win, DefaultGC(dpy,s), 20, 20, 0, 0) ;

	/**
	 * Create the GL context and make it the current context
	 */
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE) ;
	if( glc == NULL ) {
		fprintf(stderr, "Cannot create gl context\n") ;
		exit(0) ;
	}

	glXMakeCurrent(dpy, win, glc) ;
	glEnable(GL_DEPTH_TEST) ;
	glDepthFunc( GL_LESS ) ;
	glClearColor(0.0, 0.0, 0.0, 1.00) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
}

/**
 * Exposes the window and draws the sphere to it
 */
void expose_graphics(container::array<Sphere*> *objects,
	container::array<container::array<double>*> *positions, double dt)
{
	/**
	 * Resize the viewport
	 */
	XGetWindowAttributes(dpy, win, &wa) ;
	glViewport(0, 0, wa.width, wa.height) ;
	float aspect_ratio = (float)(wa.width) / (float)(wa.height) ;
	
	/**
	 * Setup the projection and Modelview
	 */
	glMatrixMode( GL_PROJECTION ) ;
	glLoadIdentity() ;
	glOrtho(-2.50*aspect_ratio, 2.50*aspect_ratio, -2.50, 2.50, 1., 100.) ;

	glMatrixMode( GL_MODELVIEW ) ;
	glLoadIdentity() ;
	gluLookAt(10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0) ;
	glScalef(scale[0], scale[1], scale[2]) ;
	int N = objects->size()-1 ;
	for(int i=0; i<N; ++i) {
		glMultMatrixf( objects->operator[](i)->rotation_matrix() ) ;
	}
	
	/**
	 * Draw the sphere
	 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	for(int i=0; i<N; ++i) {
		objects->operator[](i)->draw( *(positions->operator[](i)), dt ) ;
	}
	
	/**
	 * Swap buffers
	 */
	glXSwapBuffers(dpy, win) ;
}

void rotate_obj(Sphere *s, double dt)
{
	glMatrixMode( GL_MODELVIEW ) ;
	glLoadIdentity() ;
	glRotatef(s->velocity(1)*dt, 0.0, 1.0, 0.0) ;
	glRotatef(s->velocity(2)*dt, 0.0, 0.0, 1.0) ;
	glMultMatrixf( s->rotation_matrix() ) ;
	glGetFloatv( GL_MODELVIEW_MATRIX, s->rotation_matrix() ) ;
}

/**
 * Checks the window event queue for specific interactions
 */
void check_events(Sphere *s, double dt)
{
    if( XCheckWindowEvent(dpy, win, KeyPressMask, &xev) ) {
    	char *key_string = XKeysymToString(XkbKeycodeToKeysym(dpy, xev.xkey.keycode, 0, 0)) ;

		if( strncmp(key_string, "Home", 4) == 0 ) {
			pos *= 0.0 ;
			s->velocity()->clear() ;
		} else
		if( strncmp(key_string, "Right", 5) == 0 ) {
    		s->velocity( 2, (s->velocity(2) + 200.0*dt) ) ;
    		printf("___ Right ___ Z-Velocity: %f\n", s->velocity(2)) ;
		} else
		if( strncmp(key_string, "Left", 4) == 0 ) {
    		s->velocity( 2, (s->velocity(2) - 200.0*dt) ) ;
    		printf("___ Left  ___ Z-Velocity: %f\n", s->velocity(2)) ;
		} else
		if( strncmp(key_string, "Up", 2) == 0 ) {
			printf("___   Up  ___ Y-Velocity: %f\n", s->velocity(1)) ;
    		s->velocity( 1, (s->velocity(1) + 200.0*dt) ) ;
		} else
		if( strncmp(key_string, "Down", 4) == 0 ) {
			printf("___ Down  ___ Y-Velocity: %f\n", s->velocity(1)) ;
    		s->velocity( 1, (s->velocity(1) - 200.0*dt) ) ;
		} else
		if( strncmp(key_string, "Escape", 5) == 0 ) {
			glXMakeCurrent(dpy, None, NULL) ;
			glXDestroyContext(dpy, glc) ;
			XDestroyWindow(dpy, win) ;
			XCloseDisplay(dpy) ;
			exit(0) ;
		}
    } else
    if( XCheckWindowEvent(dpy, win, ButtonPressMask, &xev) ) {
    	if( xev.xbutton.button == LEFT_CLICK ) {
    		double range = 350.0 * scale[0] ;
    		double half = range / 2.0 ;
    		pos[0] = 0.0 ;
    		pos[1] = xev.xbutton.x - range ;
    		pos[2] = range - xev.xbutton.y ;
    		pos /= half ;
    		printf("The left button was pressed on the mouse. The location in the window is: (%i, %i)\n", xev.xbutton.x, xev.xbutton.y) ;
    	} else
    	if( xev.xbutton.button == RIGHT_CLICK ) {
    		printf("The right button was pressed on the mouse. The location in the window is: (%i, %i)\n", xev.xbutton.x, xev.xbutton.y) ;
    	} else
    	if( xev.xbutton.button == MIDDLE_CLICK ) {
    		printf("The scroll wheel was pressed on the mouse. The location in the window is: (%i, %i)\n", xev.xbutton.x, xev.xbutton.y) ;
    	} else
    	if( xev.xbutton.button == WHEEL_UP ) {
    		printf("The scroll wheel on the mouse was scrolled up\n") ;
			scale[0] += 0.1 ;
			scale[1] += 0.1 ;
			scale[2] += 0.1 ;
    	} else
    	if( xev.xbutton.button == WHEEL_DOWN ) {
			scale[0] -= 0.1 ;
			scale[1] -= 0.1 ;
			scale[2] -= 0.1 ;
			if( scale[0] < 0.0 ) {
				scale *= 0.0 ;
			}
			printf("The scroll wheel on the mouse was scrolled down\n") ;

    	}
    }
}

/**
 * Main
 */
int main(int argc, char *argv[])
{
	Sphere sun(0.25, 100, 100) ;
	sun.id( 1 ) ;
//	sun.color(1.0, 1.0, 1.0) ;
	sun.color(0.7, 0.3, 0.0) ;
	sun.velocity(1, -100.0) ;
	sun.velocity(2, 120.0) ;

	Sphere planet(0.5, 30, 30) ;
	planet.id( 2 ) ;
	planet.color(0.0, 0.0, 0.4) ;
	container::array<double> pos2(3, 2.0) ;
	
	create_window(700, 700) ;
	run_time.start() ;
	
	container::array<Sphere*> objs(2) ;
	objs[0] = &sun ;
	objs[1] = &planet ;
	container::array<container::array<double>*> obj_pos(2) ;
	obj_pos[0] = &pos ;
	obj_pos[1] = &pos2 ;
	
	glMatrixMode( GL_MODELVIEW ) ;
	glLoadIdentity() ;
	glGetFloatv( GL_MODELVIEW_MATRIX, sun.rotation_matrix() ) ;
	double dt ;
	
	while(true) {
		dt = run_time.delta_checkIn() ;
		//rotate_obj( &sun, dt ) ;
		check_events( &sun, dt ) ;
		expose_graphics( &objs, &obj_pos, dt ) ;
	}
	
	//return 0 ;
}
