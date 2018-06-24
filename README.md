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

Exterior is coloured with potential ( grayscale)   
![](10_99991.png)  

Exterior is white with black equipotential curves    
![](10_99981.png)  

Boundary using noise detection  
![](10_99971.png)  

Noise pixels  
![](10_99961.png)  

Text output of the program:   


```bash
render image = compute and write image data bytes to the array 
File 10_99991.pgm saved. 
ClearExterior =  make exterior solid color = white

draw equipotential curve thru point c = (1.0300000000000000; 1.7000000000000000) pixel = (1988, 56)
 	start point
	for c = (1.030000;1.700000)	noise measure =         0.000723	potential = 2.356168
	c is inside the array : iy = 1988 iy = 56	and outside M set
	end point	ix = 1988 iy = 56 i = 113988 potential = 2.3577207229474340
	curve is closed = stop ( good) after 30 steps (pixels)


draw equipotential curve thru point c = (1.0500000000000000; 0.0000000000000000) pixel = (1999, 1000)
 	start point
		error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
for c = (1.050000;0.000000)	noise measure =              inf	potential = 0.000000
	c is on the array boundary: ix = 1999 iy = 1000	and outside M set
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	error  from giv_i : bad input: ix = 2000 
	drawing stopped because of bad FCCode = -2 after 0 steps ( pixels)
 
draw equipotential curve thru point c = (0.9000000000000000; 0.0000000000000000) pixel = (1916, 1000)
 	start point
	for c = (0.900000;0.000000)	noise measure =         0.002595	potential = 0.990101
	c is inside the array : iy = 1916 iy = 1000	and outside M set
	end point	ix = 1916 iy = 1000 i = 2001916 potential = 0.9901033608952807
	curve is closed = stop ( good) after 4357 steps (pixels)


draw equipotential curve thru point c = (0.7000000000000000; 0.0000000000000000) pixel = (1805, 1000)
 	start point
	for c = (0.700000;0.000000)	noise measure =         0.004516	potential = 0.598991
	c is inside the array : iy = 1805 iy = 1000	and outside M set
	end point	ix = 1805 iy = 1000 i = 2001805 potential = 0.5989911428328348
	curve is closed = stop ( good) after 3825 steps (pixels)


draw equipotential curve thru point c = (0.5000000000000000; 0.0000000000000000) pixel = (1694, 1000)
 	start point
	for c = (0.500000;0.000000)	noise measure =         0.011120	potential = 0.212801
	c is inside the array : iy = 1694 iy = 1000	and outside M set
	end point	ix = 1694 iy = 1000 i = 2001694 potential = 0.2127903458916913
	curve is closed = stop ( good) after 3687 steps (pixels)


draw equipotential curve thru point c = (0.4000000000000000; 0.0000000000000000) pixel = (1638, 1000)
 	start point
	for c = (0.400000;0.000000)	noise measure =         0.024412	potential = 0.063219
	c is inside the array : iy = 1638 iy = 1000	and outside M set
	end point	ix = 1638 iy = 1000 i = 2001638 potential = 0.0631906592052049
	curve is closed = stop ( good) after 4125 steps (pixels)


draw equipotential curve thru point c = (0.3500000000000000; 0.0000000000000000) pixel = (1610, 1000)
 	start point
	for c = (0.350000;0.000000)	noise measure =         0.045792	potential = 0.018384
	c is inside the array : iy = 1610 iy = 1000	and outside M set
	problem: FCCode not found 
	drawing stopped because of bad FCCode = -1 after 9237 steps ( pixels)
 
draw equipotential curve thru point c = (0.3000000000000000; 0.0000000000000000) pixel = (1583, 1000)
 	start point
	for c = (0.300000;0.000000)	noise measure =         0.129012	potential = 0.001244
	c is inside the array : iy = 1583 iy = 1000	and outside M set
	problem: FCCode not found 
	drawing stopped because of bad FCCode = -1 after 407 steps ( pixels)
 File 10_99981.pgm saved. 
Find boundary of Mandelbrot set using  noise measure
File 10_99971.pgm saved. 
Find noisy pixels
File 10_99961.pgm saved. 
for c = (0.000000;0.000000)	noise measure =         0.000000	potential = 2.000000
for c = (0.100000;0.000000)	noise measure =         0.000000	potential = 2.000000
for c = (0.200000;0.000000)	noise measure =         0.000000	potential = 2.000000
for c = (0.250000;0.000000)	noise measure =         0.250000	potential = 2.000000
for c = (0.260000;0.000000)	noise measure = 376231582.043187	potential = 0.000000
for c = (0.270000;0.000000)	noise measure =         0.557260	potential = 0.000004
for c = (0.280000;0.000000)	noise measure =         0.307864	potential = 0.000059
for c = (0.290000;0.000000)	noise measure =         0.187233	potential = 0.000371
for c = (0.300000;0.000000)	noise measure =         0.129012	potential = 0.001244
for c = (0.350000;0.000000)	noise measure =         0.045792	potential = 0.018384
for c = (0.400000;0.000000)	noise measure =         0.024412	potential = 0.063219
for c = (0.450000;0.000000)	noise measure =         0.015637	potential = 0.130537
for c = (0.500000;0.000000)	noise measure =         0.011120	potential = 0.212801
for c = (0.600000;0.000000)	noise measure =         0.006643	potential = 0.398419
for c = (0.700000;0.000000)	noise measure =         0.004516	potential = 0.598991
for c = (0.800000;0.000000)	noise measure =         0.003336	potential = 0.795892
for c = (0.900000;0.000000)	noise measure =         0.002595	potential = 0.990101
for c = (1.000000;0.000000)	noise measure =         0.002091	potential = 1.174337


Parameter plane with Mandelbrot set
corners: CxMin = -2.550000	CxMax = 1.050000	 CyMin = -1.800000	 CyMax 1.800000
corners: ixMin = 0	ixMax = 1999	 iyMin = 0	 iyMax 1999
exterior = CPM/M
IterationMax = 100001
EscapeRadius = 10
iPixelRadius = ixMax* 0.002 = 1 so big pixel = 4 (small) pixels 
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

