/*
  code from qmnplane.cpp by Wolf Jung (C) 2007-2017
  http://www.mndynamics.com/indexp.html

  part of Mandel 5.15, which is free software; you can
  redistribute and / or modify them under the terms of the GNU General
  Public License as published by the Free Software Foundation; either
  version 3, or (at your option) any later version. In short: there is
  no warranty of any kind; you must redistribute the source code as well.




  https://en.wikibooks.org/wiki/Fractals/mandel


*/




/*

Hit the key g to draw the equipotential line through the current point z (outside of Kc) or c (outside of M), or to specify the potential level.


the following code will be rewritten completely!!!
 void QmnPlane::green
 recursive function
*/ 

void green(  	mndynamics *f, 
		int st, 
		mdouble g, 
		int quality,
  		QColor color) //5, white
{ //trace the boundary ...

  if (g <= 0 || type) return;
  
  uint m = 1; 
  f->prepare(st, nmax, m, &g); //just to set nmax
  
  int i, k, i0, k0, i1, k1, i2, k2, j, vert, side, sg, start, T;
  
  //stop();
  
  
  // set color
  QPainter *p = new QPainter(buffer); 
  p->setPen(color);
  
  for (T = 20 - kmax; T < kmax - 20; T += imax*2/quality)
    { 	for (vert = 0; vert <= 1; vert++)
	{ for (side = -1; side <= 1; side += 2)
	    {
	      start = 10000; //no startpoint
	      if (vert) //vertical lines from above and below
		{ 	if (f->green(st, hmid - ph*side*kmax + pw*T, vmid - pw*side*kmax + ph*T) <= g)
		    continue;
		  for (j = kmax-1; j >= -kmax/2; j--)
		    { if (f->green(st, hmid + ph*side*j + pw*T, vmid - pw*side*j + ph*T) <= g)
			{start = side*j; break;} 
		    }
		}
	      else//vert: horizontal lines from left and right
		{ 	if (f->green(st, hmid + pw*side*imax - ph*T, vmid + ph*side*imax - pw*T) <= g)
		    continue;
		  for (j = imax-1; j >= -imax/2; j--)
		    { if (f->green(st, hmid + pw*side*j - ph*T, vmid + ph*side*j - pw*T) <= g)
			{start = side*j; break;} }
		}// else vert
		
		
		
	      if (start == 10000) continue; //no startpoint
	      
	      for (sg = -1; sg <= 1; sg += 2) //go in both directions
		{ if (vert)
		    { k0 = start; k1 = k0 + side; k2 = k1; i0 = T; i1 = T; i2 = i1 + sg;}
		  else
		    { i0 = start; i1 = i0 + side; i2 = i1; k0 = T; k1 = T; k2 = k1 + sg;}
		    
		  for (j = 1; j < 8*imax; j++)
		    { if (i0 < -imax || i0 >= imax || k0 < -kmax || k0 >= kmax) break;
		      else p->drawLine(imax + i0, kmax + k0, imax + i0, kmax + k0);
		      
		      
		      if (f->green(st, hmid + pw*i2 + ph*k2, vmid + ph*i2 - pw*k2) <= g)
			{i = i0; k = k0; i0 = i2; k0 = k2; i2 += (i1 - i); k2 += (k1 - k);}
		      else
			{i = i1; k = k1; i1 = i2; k1 = k2; i2 += (i0 - i); k2 += (k0 - k);}
		    }//for j
		}//for sg
	    }//for side
	}//for vert
    }//for T
  delete p; update();
} //green
