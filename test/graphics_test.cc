/**
 * @file graphics_text.cc
 */

#include <genecis/graphics/sphere.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

using namespace genecis::graphics ;

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
	glClearColor(0.00, 0.00, 0.40, 1.00) ;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
}

/**
 * Exposes the window and draws the sphere to it
 */
void expose_graphics(Sphere *s)
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
	gluLookAt(10., 0., 0., 0., 0., 0., 0., 0., 1.) ;
	
	/**
	 * Draw the sphere
	 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;
	s->draw(0, 0, 0) ;
	
	/**
	 * Swap buffers
	 */
	glXSwapBuffers(dpy, win) ;
}

/**
 * Checks the window event queue for specific interactions
 */
void check_events()
{
    if( XCheckWindowEvent(dpy, win, KeyPressMask, &xev) ) {
    	char *key_string = XKeysymToString(XkbKeycodeToKeysym(dpy, xev.xkey.keycode, 0, 0)) ;

		if(strncmp(key_string, "Escape", 5) == 0) {
			glXMakeCurrent(dpy, None, NULL) ;
			glXDestroyContext(dpy, glc) ;
			XDestroyWindow(dpy, win) ;
			XCloseDisplay(dpy) ;
			exit(0) ;
		}
    } else
    if( XCheckWindowEvent(dpy, win, ButtonPressMask, &xev) ) {
    	if( xev.xbutton.button == LEFT_CLICK ) {
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
    	} else
    	if( xev.xbutton.button == WHEEL_DOWN ) {
    		printf("The scroll wheel on the mouse was scrolled down\n") ;
    	}
    }
}

/**
 * Main
 */
int main(int argc, char *argv[])
{
	Sphere sun(0.5, 20, 48) ;
	sun.color(0.7, 0.3, 0.0) ;
	create_window(700, 700) ;
	expose_graphics(&sun) ;
	
	while(true) {
		check_events() ;
		glXSwapBuffers(dpy, win) ;
	}
	
	//return 0 ;
}
