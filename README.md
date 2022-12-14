2D ( time independent) scalar field ( potential). Create [vector field](https://en.wikibooks.org/wiki/Fractals/Mathematics/Vector_field) and draw field lines and equipotential lines

# TOC
* [equipotentials](README.md#equipotentials)
* [filed lines]()


# equipotentials

Exterior is coloured with potential ( grayscale)   
```c
p = log(potential)/K;
color = 255* (1+cos(TwoPi*p))/2.0;
```  

![](./images/10_99991.png)  

Exterior is white with black equipotential curves    
![](./images/10_99981.png)  

Boundary using noise detection  

```c
double BoundaryMeasure = 1.15; // higher value = thinner boundary
// FindBoundary
if (NoiseMeasure> BoundaryMeasure) A[i] = 255 ;	// white
```  
![](./images/10_99971.png)  
     
Noise pixels  
```c
double NoiseMeasureThreshold = 0.045; // arbitrary for c = 0.365000000000000  +0.000000000000000 i    period = 0 
//  FindNoisyPixels
if (NoiseMeasure> NoiseMeasureThreshold) A[i] = 255 ;	// white
```  

![](./images/10_99961.png)  




# field lines = external rays 

here field lines are [external rays](https://en.wikipedia.org/wiki/External_ray)
* do not cross with each other but 2 or more lines may land on the same point ( root or Misiurewicz point)  
* are [perpendicular ( normal)](https://www.intmath.com/applications-differentiation/1-tangent-normal.php) to equipotential lines  = are gradient lines of potential ( scalar field)





# Text output of the program:   


```bash
memory is OK 

real	0m28,965s
user	3m47,483s
sys	0m0,092s

render image = compute and write image data bytes to the array 
File 10_89990.pgm saved. 
ClearExterior =  make exterior solid color = white
 exterior p = 0.751188 

draw equipotential curve thru point c = (0.9000000000000000; 0.0000000000000000) pixel = (1916, 1000)
 	start point
	for c = (0.900000;0.000000)	noise measure = 0.0025952006903814	potential = 0.9901006463279854
	c is inside the array : iy = 1916 iy = 1000	and outside M set
	end point	ix = 1916 iy = 1000 i = 2001916 potential = 0.9901033608952807
	curve is closed = stop ( good) after 4357 steps (pixels)


draw equipotential curve thru point c = (0.7000000000000000; 0.0000000000000000) pixel = (1805, 1000)
 	start point
	for c = (0.700000;0.000000)	noise measure = 0.0045160797467720	potential = 0.5989907665960282
	c is inside the array : iy = 1805 iy = 1000	and outside M set
	end point	ix = 1805 iy = 1000 i = 2001805 potential = 0.5989911428328348
	curve is closed = stop ( good) after 3825 steps (pixels)


draw equipotential curve thru point c = (0.5000000000000000; 0.0000000000000000) pixel = (1694, 1000)
 	start point
	for c = (0.500000;0.000000)	noise measure = 0.0111195774508909	potential = 0.2128012374973248
	c is inside the array : iy = 1694 iy = 1000	and outside M set
	end point	ix = 1694 iy = 1000 i = 2001694 potential = 0.2127903458916913
	curve is closed = stop ( good) after 3687 steps (pixels)


draw equipotential curve thru point c = (0.4000000000000000; 0.0000000000000000) pixel = (1638, 1000)
 	start point
	for c = (0.400000;0.000000)	noise measure = 0.0244119823222931	potential = 0.0632189280903892
	c is inside the array : iy = 1638 iy = 1000	and outside M set
	end point	ix = 1638 iy = 1000 i = 2001638 potential = 0.0631906592052049
	curve is closed = stop ( good) after 4125 steps (pixels)

File 10_89980.pgm saved. 
Find boundary of Mandelbrot set using  noise measure
File 10_89970.pgm saved. 
Find noisy pixels
File 10_89960.pgm saved. 
for c = (0.000000;0.000000)	noise measure = 0.0000000000000000	potential = 0.0000000000000000
for c = (0.100000;0.000000)	noise measure = 0.0000000000000000	potential = 0.0000000000000000
for c = (0.200000;0.000000)	noise measure = 0.0000000000000000	potential = 0.0000000000000000
for c = (0.250000;0.000000)	noise measure = 0.2500000000000000	potential = 0.0000000000000000
for c = (0.260000;0.000000)	noise measure = 3.1457717601949291	potential = 0.0000000019934531
for c = (0.270000;0.000000)	noise measure = 0.5572597205697883	potential = 0.0000044162911707
for c = (0.280000;0.000000)	noise measure = 0.3078640888246843	potential = 0.0000587486278177
for c = (0.290000;0.000000)	noise measure = 0.1872334952074938	potential = 0.0003708182242248
for c = (0.300000;0.000000)	noise measure = 0.1290122547411083	potential = 0.0012438403001236
for c = (0.350000;0.000000)	noise measure = 0.0457918910257952	potential = 0.0183838747379665
for c = (0.400000;0.000000)	noise measure = 0.0244119823222931	potential = 0.0632189280903892
for c = (0.450000;0.000000)	noise measure = 0.0156374406145566	potential = 0.1305368896713344
for c = (0.500000;0.000000)	noise measure = 0.0111195774508909	potential = 0.2128012374973248
for c = (0.600000;0.000000)	noise measure = 0.0066430404569894	potential = 0.3984187631443595
for c = (0.700000;0.000000)	noise measure = 0.0045160797467720	potential = 0.5989907665960282
for c = (0.800000;0.000000)	noise measure = 0.0033359942064616	potential = 0.7958924429230689
for c = (0.900000;0.000000)	noise measure = 0.0025952006903814	potential = 0.9901006463279854
for c = (1.000000;0.000000)	noise measure = 0.0020908718498594	potential = 1.1743374869011141


Parameter plane with Mandelbrot set
corners: CxMin = -2.550000	CxMax = 1.050000	 CyMin = -1.800000	 CyMax 1.800000
corners: ixMin = 0	ixMax = 1999	 iyMin = 0	 iyMax 1999
exterior = CPM/M
IterationMax = 90000
EscapeRadius = 10
iPixelRadius = ixMax* 0.002 = 1 so big pixel = 4 (small) pixels 
```

[Why real time is lower then user time ? ](https://unix.stackexchange.com/questions/40694/why-real-time-can-be-lower-than-user-time)

# cases
* dimension : 2D / 3D / ...
* input
  * trace a curve in the array of precomputed values ( read value of new point from the array). Array = image 
  * trace a curve in complex 2D plane ( compute each point)
* curve types 
  * closed / not closed ( ray)
  * simple,   
  * critical points / [singularities ](https://en.wikipedia.org/wiki/Singular_point_of_a_curve)
* grid
  * structured / unstructured
  * quadratic / triangular ( Coxeter-Freudenthal decomposition (triangulation))
* [pixel connectivity](https://en.wikipedia.org/wiki/Pixel_connectivity)
* stoping criteria
  * boundary of the Grid ( image)
  * maximal curve length
  * Maximum compute time 
* trace 
  * forward / backward   or clockwise/counterclockwise
  * how many seed points
  * [fixed step / change ](https://www.khanacademy.org/math/multivariable-calculus/multivariable-derivatives/partial-derivative-and-gradient-articles/a/the-gradient)
  * algorithm  

# algorithm

Input: 
* plane (parameter plane or dynamic plane)
* scalar function ( potential)
* vector function 

Steps:
* create scalar field using scalar function ( potential)
* create vector field from scalar field using vector function ( gradient of the potential)
* compute/draw :
  * filed lines ( stream lines )
  * contour lines ( [[Fractals/Iterations_in_the_complex_plane/equipotetential|equipotential lines]] )
  * map whole field using Line Integral Convolution (LIC) 


  

# dictionary

tracing a curve means compute successive points on the curve, one by one, until stopping criteria are met


```mermaid
graph TD
A[Start point] --> B(Compute next point)
B --> C{meet stop criteria ? }
C --> |No|B
C -->|Yes| D[End]
```


Tracing a curve on the triangular grid  
![Tracing a curve on the triangular grid](./images/Simplicial.gif)   
[Image by Michael E. Henderson](https://commons.wikimedia.org/wiki/File:Simplicial.gif) 

"scanning means to check every pixel". Other names : detection, extraction

Gradient
* The gradient of a scalar field  is a vector that represents the magnitude and the direction of the greatest increase rate of the field 



# code 
* [s.c](./src/s.c) - trace equipotential curves on the parameter plane ( my own code))
* [boundary.c](./src/boundary.c) - Boundary Tracing Generation Method, traces the outline of areas of a single color and fills them in. Copyright (c) 1994-1997 Michael R. Ganss. All Rights Reserved.
* [lines.c](./src/lines.c) - detect-lines, extract lines and their width from images. Copyright (C) 1996-1998 Carsten Steger. from [GRASP](http://www.lsc-group.phys.uwm.edu/~ballen/grasp-distribution/)
* [y.c](./src/y.c) - Mandelbrot boundary tracing example for [Youtube video : Writing a Mandelbrot Fractal Renderer with Boundary Tracing Algorithm](https://www.youtube.com/watch?v=rVQMaiz0ydk) ??? ?? Joel Yliluoma
* [jung.c](./src/jung.c) - code by [Wolf Jung](http://www.mndynamics.com/indexp.html) (C) 2007-2017  
* [fractint.c](./src/fractint.c) - code for the bound_trace from fractint 
* [gradient.mac](./src/gradient.mac) - Maxima CAS code for numerical aproximation of gradient, equiopotential direction and making images [text output of the program](./src/c_0_301_0.0001.txt)
* [grad_f.mac](./src/grad_f.mac) - Maxima CAS code for numerical aproximation of gradient


## in other repositories
* [mandelbrot-ex_ray-out](https://gitlab.com/adammajewski/mandelbrot-ex_ray-out)
* [dynamic_external_angle](https://gitlab.com/adammajewski/dynamic_external_angle)
* [m_d_exray_in](https://gitlab.com/adammajewski/m_d_exray_in)
* [ray-backward-iteration](https://gitlab.com/adammajewski/ray-backward-iteration)
* [NonInteractiveParameterRayInMPFR](https://gitlab.com/adammajewski/NonInteractiveParameterRayInMPFR)
* [dynamic_ray_newton](https://gitlab.com/c_files/dynamic_ray_newton)
* [parameter_ray_in_newton_mpfr](https://gitlab.com/c_files/parameter_ray_in_newton_mpfr)




# links
* [Argument tracing by Wolf Jung](http://www.mndynamics.com/indexp.html#XR)
  * [code in wikibooks](https://en.wikibooks.org/wiki/Fractals/mandel#Argument_tracing)
* [A Rasterizing Algorithm for Drawing Curves by Alois Zingl](http://members.chello.at/easyfilter/bresenham.pdf)
* [Meandering triangles ( marching triangles)](https://en.wikipedia.org/wiki/Marching_squares#Meandering_triangles)
* [Otis by Tomoki Kawahira](http://www.math.titech.ac.jp/~kawahira/programs/aboutotis.html)
* [Numerical_continuation](https://en.wikipedia.org/wiki/Numerical_continuation)
  * [Piecewise_linear_continuation](https://en.wikipedia.org/wiki/Piecewise_linear_continuation)
* [Isoline ](http://debian.man.ac.uk/.f/pub/cgu/iavsc/avs5/Module_Src/mappers/Isoline_Slice/Isoline_Slic.html)
* [CURVE TRACING AND CURVE DETECTION IN IMAGES by Karthik Raghupathy](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.571.3262&rep=rep1&type=pdf)
* curve tracing algorithm, proposed by Steger 
  * [Carsten Steger, ???An unbiased detector of curvilinear structures,??? IEEE Transactions on Pattern Analysis and Machine Intelligence, February 1998.](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.42.2266&rep=rep1&type=pdf)
  * [Unbiased Extraction of Curvilinear Structures from 2D and 3D Images by Carsten Steger](https://iuks.in.tum.de/_media/members/steger/publications/1998/diss-1998-steger.pdf)
  * [Curviliniar_Detector in matlab by Emmanouil Kapernaros](https://github.com/kapcom01/Curviliniar_Detector)
  * [Curve tracing by Eugene Katrukha](http://katpyxa.info/feedbacks/?p=154) and [code ](https://github.com/jalmar/CurveTracing)
  * [Ridge (Line) Detection Plugin (Fiji) by Thorsten Wagner, Mark Hiner](http://imagej.net/Ridge_Detection) and [code](https://github.com/thorstenwagner/ij-ridgedetection)



# see also

## Recursive subdivision 
* The process of subdividing an object (either geometric object, or a data structure) recursively until some criteria is met.

## Image noise
* [Image noise in wikibooks](https://en.wikibooks.org/wiki/Fractals/Image_noise)

## Feature detection
* [Feature detection in computer_vision](https://en.wikipedia.org/wiki/Feature_detection_(computer_vision))



### boundary scaning
* [Boundary Scanning by Robert P. Munafo](http://mrob.com/pub/muency/boundaryscanning.html)
* [How to ???inform??? successive ContourPlot calculations in Mathematica?](https://mathematica.stackexchange.com/questions/103673/how-to-inform-successive-contourplot-calculations/103681)




### boundary tracing
* [wikipedia : Boundary_tracing](https://en.wikipedia.org/wiki/Boundary_tracing)
* [The Boundary Tracing algorithm by Evgeny Demidov](https://www.ibiblio.org/e-notes/MSet/big_m.htm)
* [Fast Contour-Tracing Algorithm Based on a Pixel-Following Method for Image Sensors by Jonghoon Seo, et al.](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4813928/)
* [Tracing Boundaries in 2D Images by V. Kovalevsky](http://www.kovalevsky.de/Topology/Algorithms_2D_e.htm)
* [the Moore-Neighbor tracing algorithm by Abeer George Ghuneim ](http://www.imageprocessingplace.com/downloads_V3/root_downloads/tutorials/contour_tracing_Abeer_George_Ghuneim/moore.html)  
* [Square Tracing Algorithm by Abeer George Ghuneim ](http://www.imageprocessingplace.com/downloads_V3/root_downloads/tutorials/contour_tracing_Abeer_George_Ghuneim/square.html) 
* [conturs in OpenCV and Python](http://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_imgproc/py_contours/py_table_of_contents_contours/py_table_of_contents_contours.html)
* [Bisqwit]()


### contour tracing
* [Drawing M-set by contour lines method](https://groups.google.com/forum/#!topic/sci.fractals/t9Udefcs20Q)
  * [M. Romera, G. Pastor and F. Montoya, "Graphic Tools to Analyse One-Dimensional Quadratic Maps", Computers & Graphics, 20/2 (1996), 333-339 ](http://www.tic.itefi.csic.es/gerardo/publica/Romera96.pdf)
  * M. Romera, G. Pastor and F. Montoya, "Drawing the Mandelbrot set by the method of escape lines", Fractalia, 5, n.?? 17 (1996), 11-13.
* [an explicit conformal isomorphism between the complement of the Mandelbrot set M and the complement of the closed unit disk D](https://math.stackexchange.com/questions/748875/demonstrating-that-the-mandelbrot-set-is-connected)
* [CONREC = A Contouring algorithm of some surface represented as a regular triangular mesh by Paul Bourke](http://paulbourke.net/papers/conrec/)


code
* [contour-tracing: c++, OpenCV](https://github.com/aaalgo/contour-tracing/blob/master/contour-tracing.h)
* [Moore Neighbor Contour Tracing Algorithm in C++ BY ERIK SMISTAD](https://www.eriksmistad.no/moore-neighbor-contour-tracing-algorithm-in-c/)  

### Contour scanning or edge detection
* [wikibooks](https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D#Edge_detection)

### streamline tracing
* [streamlines](https://github.com/anvaka/streamlines) - The library by Andrei Kashcha, which   builds streamlines for arbitrary vector fields, trying to keep uniform distance between them.
* [fieldplay](https://earth.nullschool.net/)- by Andrei Kashcha
* [How I built a wind map with WebGL](https://blog.mapbox.com/how-i-built-a-wind-map-with-webgl-b63022b5537f) by Vladimir Agafonkin
* [HARSH BHATIA](http://www.sci.utah.edu/~hbhatia/research.php)
* [stackoverflow question: how-to-plot-streamlines-when-i-know-u-and-v-components-of-velocitynumpy-2d-ar](https://stackoverflow.com/questions/8296617/how-to-plot-streamlines-when-i-know-u-and-v-components-of-velocitynumpy-2d-ar)
* [stackoverflow question: how-to-create-streamline-like-arrow-lines-in-gnuplot](https://stackoverflow.com/questions/33240722/how-to-create-streamline-like-arrow-lines-in-gnuplot?noredirect=1&lq=1)
* [wikipedia : Image-based_flow_visualization](https://en.wikipedia.org/wiki/Image-based_flow_visualization)
* [Robust Polylines Tracing for N-Symmetry Direction Field on Triangulated Surfaces by NICOLAS RAY and DMITRY SOKOLOV](http://alice.loria.fr/publications/papers/2014/STREAM/RobustStreamlines.pdf)
* [presentation by Abdelkrim Mebarki](ftp://ftp-sop.inria.fr/prisme/amebarki/presentationEN.pdf)
* [CGAL package by Abdelkrim Mebarki](https://doc.cgal.org/latest/Stream_lines_2/index.html#Section_2D_Streamlines_Example)
* [matplotlib](https://stackoverflow.com/questions/30786274/streamlines-on-a-triangulation-with-matplotlib)
* [math.stackexchange question: solving-for-streamlines-from-numerical-velocity-field/1950329#1950329](https://math.stackexchange.com/questions/1926636/solving-for-streamlines-from-numerical-velocity-field/1950329#1950329)

### field lines
* [Grid-Independent Detection of Closed Stream Lines in 2D Vector Fields by H. Theisel, T. Weinkauf, H.-C. Hege, H.-P. Seidel](https://www.csc.kth.se/~weinkauf/gallery/cattheisel04b.html)
* [the Morse-Smale complex in python by  Nithin Shivashankar.](http://vgl.csa.iisc.ac.in/mscomplex/primer.html)
* [stackoverflow question: computing-and-drawing-vector-fields](https://stackoverflow.com/questions/25342072/computing-and-drawing-vector-fields)
* [An external ray is an integral curve of the gradient vector field ???G on Bc(???).](http://qcpages.qc.cuny.edu/~yjiang/HomePageYJ/Download/2004MandLocConn.pdf)

### Visualization of Algebraic Curves - curve sketching
* [AN ACCURATE ALGORITHM FOR RASTERIZING ALGEBRAIC CURVES by Gabriel Taubin](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.72.9588&rep=rep1&type=pdf)
* [Visualizing Arcs of Implicit Algebraic Curves, Exactly and Fast by Pavel Emeliyanenko, Eric Berberich, Michael Sagraloff1](https://people.mpi-inf.mpg.de/~msagralo/curvevisualization.pdf)



## numerical differentiation = numerically computing the gradient of a field
gradient = "direction and rate of fastest increase". If at a point p, the gradient of a function of several variables is not the zero vector
*  the direction of the gradient is the direction of fastest increase of the function at p
* its magnitude is the rate of increase in that direction

discrete differential geometry

### 1D
In 1D case derivative of the function f at point x gives [the slope](https://en.wikipedia.org/wiki/Slope) of the tangent line at the point x

$` f'(x) = \lim_{h\to0} \frac{f(x+h) - f(x)}{h} =  \tan (\theta)`$

It is aproximated by the maximal finite differnce: 

$` f'(x) \approx  \max \lbrace \frac{f(x+h) - f(x)}{h} \rbrace `$


### 2D

In 2D case gradient (generalization of the derivative) of function f at point (x,y) gives the slope of the plane (flat surface) tangent to the 3D surface z = f(x,y) 
* Numerical Differentiation in two variables ( complex number = x+y*i) by approximation by [centered finite differences scheme](https://uk.mathworks.com/help/matlab/ref/gradient.html)



#### FED

[Finite-Difference Method = FDM](https://ebrary.net/7100/business_finance/what_finite-difference_method)


$` \frac{f(x_{m+1}, y_n) - f(x_{m-1}, y_n)}{2h_x} , \frac{f(xm, yn+1) ??? f(xm, yn???1)}{2h_y} `$





Example code : "gradient direction computation based on image brightness. I've made a matrix bright[width][height] containing brightness values for every pixel of the image"
```c
	// https://stackoverflow.com/questions/4003615/gradient-direction-computation
   double grad_x(int x,int y){
    	if(x==width-1 || x==0) return bright[x][y];
    	return bright[x+1][y]-bright[x-1][y];
    }
    double grad_y(int x,int y){
    	if(y==height-1 || y==0) return bright[x][y];
    	return bright[x][y+1]-bright[x][y-1];
    }
```




#### checking n points on the circle around center = n-th order method 



![](./images/c_0_301_0.0001.png)  


![](./images/c_0_301_0.0001_s.png)  




Different outputs of numerical gradient function:
* angle of the gradient vector (and the radius ) 
* point directed by the gradient vector


  
  
Modifications:
* Adaptive step size  


[Edge Handling](https://en.wikipedia.org/wiki/Kernel_(image_processing)#Edge_Handling)
* Corner cases 
[Description by Nils Pipenbrinck](https://stackoverflow.com/questions/4003615/gradient-direction-computation)

>>>
The corner cases are a problem because you don't have enough data to calculate a gradient in the same way as the other pixels. One way to deal with them is to simply not calculate the corner cases and live with a slightly smaller image.

If this is not an option you can also extrapolate the missing data. If you assume that the gradient changes smoothly it works like this:

In your x-gradient calculations you may have calculated the derivate A for pixel 1 and B for pixel 2. If you want to extrapolate a value for pixel 0 (the corner case) 
the value a-(b-a) could be used.

pixel1: gradient = 100
pixel2: gradient = 80

extrapolate using a-(b-a): 

pixel0: gradient = 100 - (80-100)) = 120
>>>




Links:
* [math.stackexchange question: how-to-approximate-numerically-the-gradient-of-the-function-on-a-triangular-mesh](https://math.stackexchange.com/questions/2627946/how-to-approximate-numerically-the-gradient-of-the-function-on-a-triangular-mesh/2628057#2628057)
* [Numerical differentiation by Gonzalo Galiano Casas and Esperanza Garcia Gonzalo](https://www.unioviedo.es/compnum/labs/lab07_der_int/lab07_der_int.html)
* [gradient of the potential by Linas Vepstas](https://gitlab.com/adammajewski/LinasArtGallery_MandelbrotSet/blob/master/README.md#gradient-of-the-potential)
* [PYTHON LABS by Gonzalo Galiano Casas and Esperanza Garc??a Gonzalo](https://www.unioviedo.es/compnum/labs/lab07_der_int/lab07_der_int.html)
* [Finite-difference approximation  by Tim Vieira](https://timvieira.github.io/blog/post/2017/04/21/how-to-test-gradient-implementations/)
* [wikipedia : Finite_difference ](https://en.wikipedia.org/wiki/Finite_difference#Relation_with_derivatives)

Methods
* Euler (  a first order method  = RK1)
* Midpoint (  a second order method)
* Runge-Kutta methods  = RK4
  * [Adaptive Distance Grid Based Algorithm for Farthest Point Seeding Streamline Placement by Abdelkrim Mebarki](https://www.researchgate.net/publication/305693462_Adaptive_Distance_Grid_Based_Algorithm_for_Farthest_Point_Seeding_Streamline_Placement) -"use the Runge-Kutta second order integration scheme to construct the polyline for approximating our streamline."
  * [the Runge-Kutta of 4th order method = RK4 ](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods)
  * [1D - numerical integration by Glenn Fiedler](https://gafferongames.com/post/integration_basics/)
  * [2D - Runge???Kutta 4 integrator by Marek Fi??er](http://www.marekfiser.com/Projects/Real-time-visualization-of-3D-vector-field-with-CUDA/4-Vector-field-integrators-for-stream-line-visualization)
  * [An Intuitive Description of Runge-Kutta Integration by Daren Scot Wilso](https://wigglewave.wordpress.com/2012/11/09/intuitive-description-of-runge-kutta-integration/)
  * [stackoverflow question : runge-kutta-rk4-integration-for-game-physics](https://stackoverflow.com/questions/1668098/runge-kutta-rk4-integration-for-game-physics)
  * [parameter_external_angle/tavis.cpp  tavis.cpp](https://gitlab.com/adammajewski/parameter_external_angle/blob/master/tavis.cpp) 
  * [The Runge-Kutta Method for 2-Dimensional Systems](http://wps.prenhall.com/wps/media/objects/884/905485/chapt4/proj4.3A/proj4-3A.pdf)


# Key words
* discrete differential geometry
** mesh
* Digital Topology
* digital image processing
* binary 2D image
* discrete complex dynamics
* complex quadratic polynomial
* parameter plane
* lines tangent and normal to curve at a point 
* trace 
  * a curve
  * a boundary
  * a contour
  * [polylines](https://en.wikipedia.org/wiki/Polygonal_chain)
* curve
  * isocurve ( isoline): equipotential curve
* Fields
  * [Visualizing Electromagnetism by Sen-ben Liao, Peter Dourmashkin, and John Belcher.](http://web.mit.edu/viz/EM/visualizations/coursenotes/modules/guide01.pdf)
  * [slope field](https://en.wikipedia.org/wiki/Slope_field)
* 2D scalar field  
  * gradient 
    * [Visualizing the Variability of Gradients in Uncertain 2D Scalar Fields by Tobias Pfaffelmoser, Mihaela Mihai and Rudiger Westermann ](https://wwwcg.in.tum.de/research/research/publications/2013/visualizing-the-variability-of-gradients-in-uncertain-2d-scalar-fields.html)
    * [Array computing and curve plotting (in python) by Hans Petter Langtangen ](http://hplgit.github.io/primer.html/doc/pub/plot/._plot-readable007.html)
    * [Visualization of scalar and vector fields ( in matlab) by ??yvind Ryan, Hans Petter Langtangen](http://folk.uio.no/oyvindry/mat1110/2016/3dplot_inf1100.pdf)
    * [visualization-with-matlab](http://www.bu.edu/tech/support/research/training-consulting/online-tutorials/visualization-with-matlab/)
    * [Simulating Gradient Contour and Mesh of a Scalar Field ( in Matlab) by Usman Ali Khan, Bismah Tariq, Khalida Raza, Saima Malik, Aoun Muhammad ](https://waset.org/publications/11609/simulating-gradient-contour-and-mesh-of-a-scalar-field)
    * [chebfun is an open-source software system for numerical computing with functions.](http://www.chebfun.org/docs/guide/guide16.html)
    * [Paraview](https://www.paraview.org/)
  * A streamline is an integral curve of the vector field  
  * quiver plot: plot of the 2-D vector field ( vectors as arrows with components (u,v) at the points (x,y) )
    * [octave](https://octave.sourceforge.io/octave/function/quiver.html)
    * matlab
      * [matlab](http://www4.ncsu.edu/eos/users/w/white/www/white/ma341/lec2.PDF)
      * [Numerical differentiation](https://www.unioviedo.es/compnum/labs/lab07_der_int/lab07_der_int.html)
    * [ImageJ](https://imagej.net/Quiver_Plot) - needs 2D array of the direction of each vector, and a 2D array of the magnitude of each vector. [Code](https://github.com/Llamero/Quiver_Plot/blob/master/src/main/java/Quiver_Package/Quiver_Plot.java)
    * [matplotlib](https://plot.ly/matplotlib/quiver-plots/) and [doc](https://matplotlib.org/api/_as_gen/matplotlib.pyplot.quiver.html)
    * [OpenCv](https://stackoverflow.com/questions/10161351/opencv-how-to-plot-velocity-vectors-as-arrows-in-using-single-static-image)
* numerical differentiation = numerically computing the gradient of a function
* Mathematical optimization = finding numerically minimums (or maximums or zeros) of a function
  * [ Ga??l Varoquaux](https://www.scipy-lectures.org/advanced/mathematical_optimization/#gradient-based-methods)
* [FLOW VISUALIZATION](http://www.flowvis.org/)
  * [seed](https://slvg.soe.ucsc.edu/seed.html)
  * [dual seed ](https://www.zib.de/hotz/publications/paper/rosanwo09_dualSeeding.pdf)
* [2D Velocity Fields](http://avis.soe.ucsc.edu/texflow.html)
* Applications:
  *  streamline tracing on triangular and quadrilateral grids
  * Numerical continuation 
    * Simplicial or piecewise linear continuation 
  * Visualization of Algebraic Curves - curve sketching





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

### Subdirectory

```git
mkdir images
git add *.png
git mv  *.png ./images
git commit -m "move"
git push -u origin master
```
then link the images:

```txt
![](./images/n.png "description") 

```

```git
gitm mv -f 
```




Local repo : ~/c/mandel/p_e_angle/trace_last/test5

