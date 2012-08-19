#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <X11/extensions/Xrandr.h>
#include "xdo_functions.h"
#include "opensnap.h"

int main(int argc, char **argv)
{
	Display *dsp = XOpenDisplay( NULL );
	if( !dsp ){ return 1; }
	
	
	int screenWidth, screenHeight;
	getScreenSize(dsp,screenWidth,screenHeight);
	
	Window win;
	getFocusedWindow(dsp,&win);
	

	int screenNumber = DefaultScreen(dsp);
	int takeaction=0;
    int verbose=0;
	mousestate mousepos;
	XEvent event;
	Window activeWindow;
	char launch[MY_MAXPATH];
    char configbase[MY_MAXPATH];
    strcpy(configbase,"~/.config/opensnap/");

    int opt=0;
    while((opt = getopt(argc,argv,"c:dv")) != -1){
        switch(opt){
            case 'c':
               strncpy(configbase,optarg,MY_MAXPATH);
               configbase[MY_MAXPATH-1]='\0';
               break;
            case 'd':
               if(daemon(0,0) == -1){
                   perror("daemon");
                   exit(EXIT_FAILURE);
               }
               break;
            case 'v':
               verbose=1;
               break;
        }
    }
	
	while(1){
		getMousePosition(dsp, &event, &mousepos);
        if(verbose)
            printf("Mouse Coordinates: %d %d %d\n", mousepos.x, mousepos.y, mousepos.state );
		if(mousepos.state == LEFTCLICK){
            if(mousepos.y==0)
			    takeaction=HIT_TOP;
            else if(mousepos.x==0)
                takeaction=HIT_LEFT;
            else if(mousepos.x>=screenWidth-1)
                takeaction=HIT_RIGHT;
            else if(mousepos.y>=screenHeight-1)
                takeaction=HIT_BOTTOM;
            else
                takeaction=0;
		}
		if(mousepos.state==0){
            if(takeaction){
				getFocusedWindow(dsp,&activeWindow);
				sendMouseUp(dsp,&activeWindow);
            }
            if(takeaction==HIT_TOP){
				sprintf(launch,"/bin/sh %s/%s %u",configbase,"hit_top",activeWindow);
				system(launch);
            }
            if(takeaction==HIT_LEFT){
				sprintf(launch,"/bin/sh %s/%s %u",configbase,"hit_left",activeWindow);
				system(launch);
                
            }
            if(takeaction==HIT_RIGHT) {
				sprintf(launch,"/bin/sh %s/%s %u",configbase,"hit_right",activeWindow);
				system(launch);
            }
            if(takeaction==HIT_BOTTOM){
				sprintf(launch,"/bin/sh %s/%s %u",configbase,"hit_bottom",activeWindow);
				system(launch);
            }
			takeaction=0;
		}
		usleep(10000);
	}
	XCloseDisplay(dsp);
		
	return 0;
}

void sendMouseUp(Display *dsp, Window *w){
	XEvent event;
	memset(&event, 0x00, sizeof(event));
	event.type = ButtonRelease;
	event.xbutton.button = 1;
	event.xbutton.state = 0x100;
	event.xbutton.same_screen = True;
	XSendEvent(dsp, *w, True, 0xfff, &event);
	XFlush(dsp);
	
}

void getMousePosition(Display *dsp, XEvent *event, mousestate *cords){
	XQueryPointer(dsp, RootWindow(dsp, DefaultScreen(dsp)),
		&event->xbutton.root, &event->xbutton.window,
		&event->xbutton.x_root, &event->xbutton.y_root,
		&event->xbutton.x, &event->xbutton.y,
		&event->xbutton.state);
	cords->x=event->xbutton.x;
	cords->y=event->xbutton.y;
	cords->state=event->xbutton.state;
}


void getScreenSize(Display *dsp, int &width, int &height){
	int num_sizes;
	Rotation original_rotation;

	Window root = RootWindow(dsp, 0);
	XRRScreenSize *xrrs = XRRSizes(dsp, 0, &num_sizes);

	XRRScreenConfiguration *conf = XRRGetScreenInfo(dsp, root);
	SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

	width=xrrs[original_size_id].width;
	height=xrrs[original_size_id].height;

}

void getFocusedWindow(Display *dsp,Window *w){
	Window twin;
	int revert;
	XGetInputFocus(dsp,&twin,&revert);
	xdo_window_find_client(dsp,twin,w,XDO_FIND_PARENTS);
}
