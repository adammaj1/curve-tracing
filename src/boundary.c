/* 
 * boundary.c --
 *
 *	Boundary Tracing Generation Method, traces the outline of areas
 *      of a single color and fills them in.
 *
 * Copyright (c) 1994-1997 Michael R. Ganss. All Rights Reserved.
 *
 * See section "Copyright" of the on-line help for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#include "conf.h"
#include <tcl.h>
#include <tk.h>
#include "raster.h"
#include "fract.h"
#include "coloring.h"
#include "iterate.h"

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

static int **screen=(int **)NULL,sizex=-1,sizey=-1,offsety=0;
/* Boundary Tracing Method
   
   We start from pixel (x,y) representing (re,im) going right and
   keeping the "wall" to our left until we get back to the starting
   point. For each pixel, the next pixel visited will be computed
   thus:
   
   a) check pixel to left (looking in the current direction, i.e. if
   the current direction is right, the pixel to the left is the one
   above it). If it's part of the wall (i.e. offscreen or a different
   color than the one we're tracking), go to b). If it's not, it is
   the next pixel.
   b) do same for pixel straight ahead. Go there if it's not part of
   the wall.
   c) ditto for pixel to the right. If this pixel is also part of the
   wall, go back one pixel.
   
   When we're back at the starting point we trace the boundary once
   more. Now, whenever we move up, we plot pixels to the right of the
   current one until we hit the wall.

   This method was inspired by a post on sci.fractals by Maarten
   Egmond (cp@stack.urc.tue.nl).
   */
static void Trace(int xoffset, int yoffset, int maxx, int maxy,
		  int x, int y,
		  double re, double im)
{
  int sx,sy,c,w,dir=RIGHT,fill=0,x1;
  int *s;
  
  c=FractColor(FractIterate(re,im,re,im,0)); /* the color we're tracing */

  sx=x; sy=y;

  do
    {
      if(!fill&&screen[y][x]<0) /* plot current pixel */
	{
	  screen[y][x]=c;
	  RasterPutpixel(raster,x,y,c);
	  if(symmetric)
	    RasterPutpixel(raster,x,symy-(y-yoffset),c);
	}
      
      switch(dir)
	{
	case RIGHT:
	  /* check left */
	  if(y-1>=yoffset)
	    {
	      if((w=screen[y-1][x])<0)
		{
		  w=FractColor(FractIterate(re,im-stepy,re,im-stepy,0));
		  screen[y-1][x]=w;
		  RasterPutpixel(raster,x,y-1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y-1-yoffset),w);
		}
	      if(w==c) /* go left */
		{
		  dir=UP;
		  im-=stepy;
		  y--;
		  break;
		}
	    }
	  /* check ahead */
	  if(x+1<=maxx)
	    {
	      if((w=screen[y][x+1])<0)
		{
		  w=FractColor(FractIterate(re+stepx,im,re+stepx,im,0));
		  screen[y][x+1]=w;
		  RasterPutpixel(raster,x+1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x+1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go ahead */
		{
		  /* dir is still RIGHT */
		  re+=stepx;
		  x++;
		  break;
		}
	    }
	  /* check right */
	  if(y+1<=maxy)
	    {
	      if((w=screen[y+1][x])<0)
		{
		  w=FractColor(FractIterate(re,im+stepy,re,im+stepy,0));
		  screen[y+1][x]=w;
		  RasterPutpixel(raster,x,y+1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y+1-yoffset),w);
		}
	      if(w==c) /* go right */
		{
		  dir=DOWN;
		  im+=stepy;
		  y++;
		  break;
		}
	    }
	  /* go back */
	  if(x==sx&&y==sy) /* if direction is RIGHT and we're at the */
			   /* starting point, going back means return */
	    return;
	  dir=LEFT;
	  re-=stepx;
	  x--;
	  break;
	  
	case LEFT:
	  /* check left */
	  if(y+1<=maxy)
	    {
	      if((w=screen[y+1][x])<0)
		{
		  w=FractColor(FractIterate(re,im+stepy,re,im+stepy,0));
		  screen[y+1][x]=w;
		  RasterPutpixel(raster,x,y+1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y+1-yoffset),w);
		}
	      if(w==c) /* go left */
		{
		  dir=DOWN;
		  im+=stepy;
		  y++;
		  break;
		}
	    }
	  /* check ahead */
	  if(x-1>=xoffset)
	    {
	      if((w=screen[y][x-1])<0)
		{
		  w=FractColor(FractIterate(re-stepx,im,re-stepx,im,0));
		  screen[y][x-1]=w;
		  RasterPutpixel(raster,x-1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x-1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go ahead */
		{
		  /* dir is still LEFT */
		  re-=stepx;
		  x--;
		  break;
		}
	    }
	  /* check right */
	  if(y-1>=yoffset)
	    {
	      if((w=screen[y-1][x])<0)
		{
		  w=FractColor(FractIterate(re,im-stepy,re,im-stepy,0));
		  screen[y-1][x]=w;
		  RasterPutpixel(raster,x,y-1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y-1-yoffset),w);
		}
	      if(w==c) /* go right */
		{
		  dir=UP;
		  im-=stepy;
		  y--;
		  break;
		}
	    }
	  /* go back */
	  dir=RIGHT;
	  re+=stepx;
	  x++;
	  break;
	  
	case UP:
	  if(fill) /* fill current line by going right until we hit a */
		   /* pixel with a different color than c */
	    {
	      s=&screen[y][maxx];
	      x1=-maxx+x+1;
	      for(; x1!=0; x1++)
		{
		  if(s[x1]<0)
		    s[x1]=c;
		  else
		    if(s[x1]!=c)
		      break;
		}
	      x1+=maxx;
	      if(x1-2>x)
		{
		  RasterPutline(raster,x+1,y,x1-1,c);
		  if(symmetric)
		    RasterPutline(raster,x+1,symy-y,x1-1,c);
		}
	    }
	  /* check left */
	  if(x-1>=xoffset)
	    {
	      if((w=screen[y][x-1])<0)
		{
		  w=FractColor(FractIterate(re-stepx,im,re-stepx,im,0));
		  screen[y][x-1]=w;
		  RasterPutpixel(raster,x-1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x-1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go left */
		{
		  dir=LEFT;
		  re-=stepx;
		  x--;
		  break;
		}
	    }
	  /* check ahead */
	  if(y-1>=yoffset)
	    {
	      if((w=screen[y-1][x])<0)
		{
		  w=FractColor(FractIterate(re,im-stepy,re,im-stepy,0));
		  screen[y-1][x]=w;
		  RasterPutpixel(raster,x,y-1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y-1-yoffset),w);
		}
	      if(w==c) /* go ahead */
		{
		  /* dir is still UP */
		  im-=stepy;
		  y--;
		  break;
		}
	    }
	  /* check right */
	  if(x+1<=maxx)
	    {
	      if((w=screen[y][x+1])<0)
		{
		  w=FractColor(FractIterate(re+stepx,im,re+stepx,im,0));
		  screen[y][x+1]=w;
		  RasterPutpixel(raster,x+1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x+1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go right */
		{
		  dir=RIGHT;
		  re+=stepx;
		  x++;
		  break;
		}
	    }
	  /* go back */
	  dir=DOWN;
	  im+=stepy;
	  y++;
	  break;
	  
	case DOWN:
	  /* check left */
	  if(x+1<=maxx)
	    {
	      if((w=screen[y][x+1])<0)
		{
		  w=FractColor(FractIterate(re+stepx,im,re+stepx,im,0));
		  screen[y][x+1]=w;
		  RasterPutpixel(raster,x+1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x+1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go left */
		{
		  dir=RIGHT;
		  re+=stepx;
		  x++;
		  break;
		}
	    }
	  /* check ahead */
	  if(y+1<=maxy)
	    {
	      if((w=screen[y+1][x])<0)
		{
		  w=FractColor(FractIterate(re,im+stepy,re,im+stepy,0));
		  screen[y+1][x]=w;
		  RasterPutpixel(raster,x,y+1,w);
		  if(symmetric)
		    RasterPutpixel(raster,x,symy-(y+1-yoffset),w);
		}
	      if(w==c) /* go ahead */
		{
		  /* dir is still DOWN */
		  im+=stepy;
		  y++;
		  break;
		}
	    }
	  /* check right */
	  if(x-1>=xoffset)
	    {
	      if((w=screen[y][x-1])<0)
		{
		  w=FractColor(FractIterate(re-stepx,im,re-stepx,im,0));
		  screen[y][x-1]=w;
		  RasterPutpixel(raster,x-1,y,w);
		  if(symmetric)
		    RasterPutpixel(raster,x-1,symy-(y-yoffset),w);
		}
	      if(w==c) /* go right */
		{
		  dir=LEFT;
		  re-=stepx;
		  x--;
		  break;
		}
	    }
	  /* go back */
	  dir=UP;
	  im-=stepy;
	  y--;
	  break;
	}

      if(x==sx&&y==sy) /* we're back where we started */
	{
	  if(fill) /* we're done */
	    return;
	  fill=1;  /* trace again, filling encircled area */
	  dir=RIGHT;
	}
    }
  while(1);
}

void BoundaryCompute(double minr, double mini, double maxr, double maxi,
		     int xoffset, int yoffset, int maxx, int maxy)
{
  int x,y;
  double re,im;

  if(maxx!=sizex||maxy!=sizey||yoffset!=offsety)
    {
      for(y=offsety; y<=sizey; y++)
	free(screen[y]);
      if(screen)
	free(screen);
      screen=(int **)malloc((maxy+1)*sizeof(int*));
      for(y=0; y<yoffset; y++)
	screen[y]=(int *)NULL;
      for(y=yoffset; y<=maxy; y++)
	screen[y]=(int *)malloc((maxx+1)*sizeof(int));
      sizex=maxx;
      sizey=maxy;
      offsety=yoffset;
    }
  
  for(y=yoffset; y<=maxy; y++)
    memset(screen[y],-1,(maxx+1)*sizeof(int));

  for(y=yoffset, im=mini; y<=maxy; y++, im+=stepy)
    {
      for(x=xoffset, re=minr; x<=maxx; x++, re+=stepx)
	if(screen[y][x]<0)
	  Trace(xoffset,yoffset,maxx,maxy,x,y,re,im);
      
#ifndef MULTITHREADING
      FractCheckEvent();
#endif
      if(abbruch) return;
    }
}
