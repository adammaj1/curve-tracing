TOC



# dictionary

## tracing 

```mermaid
graph TD
A[Start point] --> B(Compute next point)
B --> C{meet stop criteria ? }
C --> |No|B
C -->|Yes| D[End]

```

## scanning
* "scanning means to check every pixel"

# cases
* trace a curve in the array of precomputed values ( read value of new point from the array). Array = image 
* trace a curve in complex 2D plane ( compute each point)

# curve types
* closed / not closed ( ray)
* simple, 

## equipotentials

![](10_100001.png)


Text output of the program:   


```bash
time ./a.out
memory is OK 
render image = compute and write image data bytes to the array 
File 10_100000.pgm saved. 

draw equipotential curve thru point c = (1.0300000000000000; 1.7000000000000000) pixel = (1988, 56)
 	start point	c is inside the array : iy = 1988 iy = 56	and outside M set
	end point	ix = 1988 iy = 56 i = 113988 potential = 2.3577207229474340
	curve is closed = stop ( good) after 30 steps (pixels)


draw equipotential curve thru point c = (1.0500000000000000; 0.0000000000000000) pixel = (1999, 1000)
 	start point	c is on the array boundary: ix = 1999 iy = 1000	and outside M set
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	drawing stopped because of bad FCCode = -2 after 0 steps ( pixels)
 
draw equipotential curve thru point c = (0.9000000000000000; 0.0000000000000000) pixel = (1916, 1000)
 	start point	c is inside the array : iy = 1916 iy = 1000	and outside M set
	end point	ix = 1916 iy = 1000 i = 2001916 potential = 0.9901033608952807
	curve is closed = stop ( good) after 4357 steps (pixels)


draw equipotential curve thru point c = (0.7000000000000000; 0.0000000000000000) pixel = (1805, 1000)
 	start point	c is inside the array : iy = 1805 iy = 1000	and outside M set
	end point	ix = 1805 iy = 1000 i = 2001805 potential = 0.5989911428328348
	curve is closed = stop ( good) after 3825 steps (pixels)


draw equipotential curve thru point c = (0.5000000000000000; 0.0000000000000000) pixel = (1694, 1000)
 	start point	c is inside the array : iy = 1694 iy = 1000	and outside M set
	end point	ix = 1694 iy = 1000 i = 2001694 potential = 0.2127903458916913
	curve is closed = stop ( good) after 3687 steps (pixels)


draw equipotential curve thru point c = (0.4000000000000000; 0.0000000000000000) pixel = (1638, 1000)
 	start point	c is inside the array : iy = 1638 iy = 1000	and outside M set
	end point	ix = 1638 iy = 1000 i = 2001638 potential = 0.0631906592052049
	curve is closed = stop ( good) after 4125 steps (pixels)


draw equipotential curve thru point c = (0.3500000000000000; 0.0000000000000000) pixel = (1610, 1000)
 	start point	c is inside the array : iy = 1610 iy = 1000	and outside M set
	problem: FCCode not found 
	drawing stopped because of bad FCCode = -1 after 9237 steps ( pixels)
 
draw equipotential curve thru point c = (0.3000000000000000; 0.0000000000000000) pixel = (1583, 1000)
 	start point	c is inside the array : iy = 1583 iy = 1000	and outside M set
	problem: FCCode not found 
	drawing stopped because of bad FCCode = -1 after 407 steps ( pixels)
 File 10_99999.pgm saved. 


Parameter plane with Mandelbrot set
corners: CxMin = -2.550000	CxMax = 1.050000	 CyMin = -1.800000	 CyMax 1.800000
corners: ixMin = 0	ixMax = 1999	 iyMin = 0	 iyMax 1999
exterior = CPM/M
IterationMax = 100001
EscapeRadius = 10
iPixelRadius = ixMax* 0.002 = 1 so big pixel = 4 (small) pixels 

real	0m32,784s
user	4m11,839s
sys	0m0,167s
```



# code
* [boundary.c](boundary.c) - Boundary Tracing Generation Method, traces the outline of areas of a single color and fills them in. Copyright (c) 1994-1997 Michael R. Ganss. All Rights Reserved.
* [s.c](s.c) - trace equipotential curves on the parameter plane
* [mandelbrot-ex_ray-out](https://gitlab.com/adammajewski/mandelbrot-ex_ray-out)
* [dynamic_external_angle](https://gitlab.com/adammajewski/dynamic_external_angle)
* [m_d_exray_in](https://gitlab.com/adammajewski/m_d_exray_in)
* [ray-backward-iteration](https://gitlab.com/adammajewski/ray-backward-iteration)
* [NonInteractiveParameterRayInMPFR](https://gitlab.com/adammajewski/NonInteractiveParameterRayInMPFR)
* [dynamic_ray_newton](https://gitlab.com/c_files/dynamic_ray_newton)
* [parameter_ray_in_newton_mpfr]https://gitlab.com/c_files/parameter_ray_in_newton_mpfr


# links
* [Argument tracing by Wolf Jung](http://www.mndynamics.com/indexp.html#XR)
  * [code in wikibooks](https://en.wikibooks.org/wiki/Fractals/mandel#Argument_tracing)

# see also
* [Boundary Scanning by Robert P. Munafo](http://mrob.com/pub/muency/boundaryscanning.html)
* [How to “inform” successive ContourPlot calculations in Mathematica?](https://mathematica.stackexchange.com/questions/103673/how-to-inform-successive-contourplot-calculations/103681)
* [Drawing M-set by contour lines method](https://groups.google.com/forum/#!topic/sci.fractals/t9Udefcs20Q)
  * [M. Romera, G. Pastor and F. Montoya, "Graphic Tools to Analyse One-Dimensional Quadratic Maps", Computers & Graphics, 20/2 (1996), 333-339 ](http://www.tic.itefi.csic.es/gerardo/publica/Romera96.pdf)
  * M. Romera, G. Pastor and F. Montoya, "Drawing the Mandelbrot set by the method of escape lines", Fractalia, 5, n.º 17 (1996), 11-13.
## boundary tracing
* [wikipedia : Boundary_tracing](https://en.wikipedia.org/wiki/Boundary_tracing)
* [The Boundary Tracing algorithm by Evgeny Demidov](https://www.ibiblio.org/e-notes/MSet/big_m.htm)
* [Fast Contour-Tracing Algorithm Based on a Pixel-Following Method for Image Sensors by Jonghoon Seo, et al.](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4813928/)
* [the Moore-Neighbor tracing algorithm by Abeer George Ghuneim ](http://www.imageprocessingplace.com/downloads_V3/root_downloads/tutorials/contour_tracing_Abeer_George_Ghuneim/moore.html)  
* [Square Tracing Algorithm by Abeer George Ghuneim ](http://www.imageprocessingplace.com/downloads_V3/root_downloads/tutorials/contour_tracing_Abeer_George_Ghuneim/square.html) 

# Key words
* digital image processing
* discrete complex dynamics
* complex quadratic polynomial
* parameter plane
* trace 
  * a curve
  * a boundary
  * a contour






# technical notes
GitLab uses:
* the Redcarpet Ruby library for [Markdown processing](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md)
* [KaTeX](https://khan.github.io/KaTeX/) to render [math written with the LaTeX syntax](https://gitlab.com/gitlab-org/gitlab-ce/blob/master/doc/user/markdown.md), but [only subset](https://khan.github.io/KaTeX/function-support.html). [Here is used version](https://github.com/gitlabhq/gitlabhq/blob/a0715f079c143a362a7f6157db45020b8432003e/vendor/assets/javascripts/katex.js)


## git ( gitlab)

```
cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/curve-tracing.git
git add .
git commit -m "Initial commit"
git push -u origin master
```

