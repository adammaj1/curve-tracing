/*

  Adam Majewski
  c console progam
  
  
  trace curve in the binary image ( array )
  
  curves can be : 
  * radial = external ray  ( segments ) from infinity to the boubdary of Mandelbrot set
  * ( potentialy closed ) = eqipotentials, which tend to the boundary of Mandelbrot set  
   
  
  
  
  
  gcc s.c -lm -Wall
  
gcc optimisation: 
  gcc s.c -lm -Wall -march=native -O2  
  
OpenMP
  
  gcc s.c -lm -Wall -march=native -O2  -fopenmp

- without : l	3m16,391s
- with : 	0m30,239s

!!!!


  
  ./a.out
  time ./a.out
  time ./a.out>a.txt

  
  
============ git ========== 
cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/curve-tracing.git
git add .
git commit -m "Initial commit"
git push -u origin master


=============================
convert 10_100001.pgm -resize 600x600 10_100001.png



// tests 
good : 
draw equipotential curve thru point c = (0.5000000000000000; 0.0000000000000000)
 	Start point	ix = 1694 iy = 1000 i = 2001694 potential = 0.2130028091546024
	end point	ix = 1694 iy = 1000 i = 2003694 potential = 0.2129910754510925
	curve is closed = stop ( good) after 3659 steps (pixels)


bad : 

draw equipotential curve thru point c = (0.3500000000000000; 0.0000000000000000)
 	Start point	ix = 1610 iy = 1000 i = 2001610 potential = 0.0183852927674834
	problem: FCCode not found 
	drawing stopped because of bad FCCode = -1 after 8806 steps ( pixels)
	
	
 File 1000_1000.pgm saved. 


Parameter plane with Mandelbrot set
exterior = CPM/M
IterationMax = 1000
EscapeRadius = 1000
iPixelRadius = ixMax* 0.002 = 1 so big pixel = 4 (small) pixels 
 
 
  
*/



#include <stdio.h>
#include <stdlib.h> // malloc
#include <math.h> // M_PI; needs -lm also 
#include <complex.h>
#include <string.h> // strncat
#include <omp.h> //OpenM




// ------------ global variables, see also give_t  ==================================================






 double TwoPi = 2.0*M_PI;
 
const int IterationMax=70000;


/* bail-out value for the bailout test for exaping points
 radius of circle centered ad the origin, exterior of such circle is a target set  */
const double EscapeRadius=101; // it should be >> 2 because then "equipotentials" are crossing at c= -2 
double ER2; //  = EscapeRadius*EscapeRadius; 
double K = log(2.0);


// virtual 2D array and integer ( screen) coordinate
// Indexes of array starts from 0 not 1 
//unsigned int ix, iy; // var
unsigned int ixMin = 0; // Indexes of array starts from 0 not 1
unsigned int ixMax ; //
unsigned int iWidth = 2100; // horizontal dimension of array
 
unsigned int iyMin = 0; // Indexes of array starts from 0 not 1
unsigned int iyMax ; //
unsigned int iHeight = 2100; //  odd number !!!!!! = (iyMax -iyMin + 1) = iyAboveAxisLength + iyBelowAxisLength +1
// The size of array has to be a positive constant integer 
unsigned int iSize ; // = iWidth*iHeight; 

int iPixelRadius; // =ixMax* 0.002; /* half of width or height of big pixel */


double AspectRatio; // width : height  https://en.wikipedia.org/wiki/Aspect_ratio_(image)

/* world ( double) coordinate = parameter plane */
// center and radius : https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#radius
// 
complex double center = -0.75  +0.0*I; // 
double radius = 1.8; 

// corners: https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#Corners
// parameter plane
double CxMin ;
double CxMax;
double CyMin;
double CyMax;
double PixelWidth; // =(CxMax-CxMin)/iXmax;
double PixelHeight; // =(CyMax-CyMin)/iYmax; 


 
// memmory 1D arrays 
unsigned char *AColor; 
double *APotential;
int *ABoundary; 


double NoiseMeasureThreshold = 0.045; // arbitrary for c = 0.365000000000000  +0.000000000000000 i    period = 0 
double BoundaryMeasure = 1.15; // higher value = thinner boundary



/*


directional features(Chain Codes)
  8 directional chain code
  the Freeman Chain Code of Eight Directions[1] (FCCE)
  https://en.wikipedia.org/wiki/Chain_code
  
 http://www.cis.hut.fi/research/IA/paper/publications/bmvc97/node2.html
 3 2 1
 4 c 0
 5 6 7 
 where c = center 
 
 check all pixels of the 8-point neighborhood on a 2D grid
 find most similar value to p0 
 it is the direction
 
 ----
 but there should be 2 directions for equipotential curve ?????
 why it gives the only one : 
 it exludes previous point : if (i>0 && ABoundary[i]==0){ // inside bounds of 1D array and not visited 


   2D lattice ( array) and coorinate 
	+----------+----------+----------+
	|          |          |          |
	|(x-1,y+1) | (x,y+1)  |(x+1,y+1) |
	+----------+----------+----------+
	|(x-1,y)   |  (x,y)   |(x+1,y)   |
	|          |          |          |
	+----------+----------+----------+
	|          | (x,y-1)  |(x+1,y-1) |
	|(x-1,y-1) |          |          |
	+----------+----------+----------
	
	only (dx,dy) = offset 
	
	+----------+----------+----------+
	|          |          |          |
	|(-1, 1)   | (0, 1)   |(1, 1)    |
	+----------+----------+----------+
	|(-1, 0)   | (0, 0)   |(1, 0)    |
	|          |          |          |
	+----------+----------+----------+
	|          | (0,-1)   |(1,-1)    |
	|(-1,-1)   |          |          |
	+----------+----------+----------
	
	so coordinate (FCCE) = (x + dx, y+dy)
	dx = dir[FCCode][0]
	dy = dir[FCCode][1]
	
	
	
	
	the Moore 8 neighborhood 
	comprises eight cells which surround center C
	
	+----------+----------+----------+
	|          |          |          |
	|   NW     |  N	      |  NE      |
	+----------+----------+----------+
	|  W       |  C	      | E        |
	|          |          |          |
	+----------+----------+----------+
	|          |  S       | SE       |
	|  SW      |          |          |
	+----------+----------+----------
	
	the Freeman Chain Code of Eight directions (FCCE) in counterclockwise direction
	
	+----------+----------+----------+
	|          |          |          |
	|   3      |  2	      |  1       |
	+----------+----------+----------+
	|  4       |    C     | 0        |
	|          |          |          |
	+----------+----------+----------+
	|          |  6       | 7        |
	|  5       |          |          |
	+----------+----------+----------
	
	
	but note that y axis is inverted in give_c procedure !!!!!
	



offset[FCCode][0] = dx  offset[FCCode][1] = dy
 
 starts from angle 0 ( = E) ang goes counterclockwise 
 */
 
int offset[8][2] = {// 
	{ 1, 0}, // 0 = East 	= right center 
	{ 1, 1}, // 1 = NE 	= right upper
	{ 0, 1}, // 2 = center upper
	{-1, 1}, // 3 = left upper
	{-1, 0}, // 4 = left center
	{-1,-1}, // 5 = lower left
	{ 0,-1}, // 6 = center lower
	{+1,-1}};// 7 = lower right







// ----------------------  functions ===========================================

 double cnorm(double complex z)
{
  return creal(z) * creal(z) + cimag(z) * cimag(z);
}



// arrray functions ===============================================

/* 
gives position of 2D point (iX,iY) in 1D array  ; 
uses also global variables: ixMax, iyMax,  iWidth 
check bounds 
*/
int give_i(int ix, int iy)
{
	int i;
	// check input 
	if (ix < 0 || ix > ixMax) {printf("\terror  from giv_i : bad input: ix = %d \n", ix); return -1;} 
	if (iy < 0 || iy > iyMax) {printf("\terror  from giv_i : bad input: iy = %d \n", iy); return -2;} 
	// compute return value
	i= ix + iy*iWidth;
	// second check ? not needed ?
	//if (i>iSize || i<0) {printf("error  ix = %d iy = %d i = %d\n", ix, iy, i); return -1;} 

	return i; }



int iPlotBigPoint(int ixSeed, int iySeed, unsigned char iColor, unsigned char A[]){


	int i; /* index of memory dynamic 1D array */
	
	int ix, iy;
	int ixLMin = ixSeed-iPixelRadius;
	int ixLMax = ixSeed+iPixelRadius;
	int iyLMin = iySeed-iPixelRadius;
	int iyLMax = iySeed+iPixelRadius;
	
	
	/* draw big pixel */
       
       
       for(iy= iyLMin; iy<= iyLMax; ++iy) 
       		for(ix= ixLMin; ix<= ixLMax; ++ix)
       			// do not draw corners = "circle"
       			if (!(  
       				(ix == ixLMin && iy == iyLMax) ||
       				(ix == ixLMin && iy == iyLMin) ||
       				(ix == ixLMax && iy == iyLMax) ||
       				(ix == ixLMax && iy == iyLMin) 
       			))
       				{ 
       					i= give_i(ix,iy); /* index of _data array */
       			
       					//printf(" ix = %d iy = %d i = %d\n", ix, iy, i);
       					// && i<=iSize
       					if (i > 0 )A[i]=iColor ; // A[i]=255 -A[i] ;//
       				}
	
	
	
	
	
	
	//printf(" iPlotBigPoint %d \n", A[i]);
	//printf(" ix = %d iy = %d i = %d\n", ix, iy, i);
	return 0;
}

// plots raster point (ix,iy) 
int dPlotPoint(complex double c, unsigned char iColor, unsigned char A[])
{
  	// indices of virtual 2D array
  	unsigned int ix;
  	unsigned int iy;
	
	
	double Cx = creal(c);
	double Cy = cimag(c);
  
  
	//compute integer coordinate  
	if ( Cx<=CxMax && Cx>=CxMin && Cy>=CyMin && Cy<=CyMax ) // check bounds, comment it if you are sure that will be no erors 
	// for n =  9  p/q =          333333333 /         1000000000  	t =  0.3333333330000000		c = (-0.1249999981862006 ; +0.6495190528383290) Naruszenie ochrony pami??ci !!! error
	// point z =  (-0.4365786152835205 ; -0.1839796132996155) is out of drawing rectangle 
	//  error from DrawCriticalOrbit for i = 999999998 

      		{ix = (int)round((Cx-CxMin)/PixelWidth);
      		iy = (int)round((CyMax-Cy)/PixelHeight); // reverse y axis
  		
  		iPlotBigPoint(ix, iy, iColor, A);
  		
  		
  		  		
  		//printf(" PlotPoint function : point C =  (%+.16f ; %+.16f) is inside of drawing rectangle \n",creal(c), cimag(c));
  		return 0;}
  		
  	printf(" error from  PlotPoint function : point C =  (%+.16f ; %+.16f) is out of drawing rectangle \n",creal(c), cimag(c));
  		
  	return 1;
}




 double complex give_c(int iX, int iY){
  double Cx,Cy;
  Cy=CyMax - iY*PixelHeight; //  Invert 
  if (fabs(Cy)< PixelHeight/2.0) Cy=0.0; /* Main antenna */
  Cx=CxMin + iX*PixelWidth;
   
  return Cx+Cy*I;
 
 
}
 


// 
// output 
// potential(c,n) = log2(abs(zn))/2^n
// https://en.wikibooks.org/wiki/Fractals/Iterations_in_the_complex_plane/MandelbrotSetExterior#Real_potential_.3D_CPM.2FM
double GivePotential(double complex C )
  {
   int i=0; // iteration 
   double d = 1.0; // 2^n computed by iteration
   double complex Z = 0.0; // initial value for iteration Z0
   double potential = FP_ZERO; // inside 
   double z_radius2; // = r*r
   
   
   
   for(i=0;i<IterationMax;i++)
    {  
      Z=Z*Z+C; // https://stackoverflow.com/questions/6418807/how-to-work-with-complex-numbers-in-c
      d *= 2.0; 
      z_radius2 = cnorm(Z); //cabs(Z);
      
      if(z_radius2 > ER2) { // exterior of M set
        potential = log2(z_radius2*z_radius2)/d;
        break;
      
      }
    }
   return potential;  
 }
 


int ComputeAndSavePixelColor(int ix, int iy, unsigned char A[]){

	unsigned char color = 0;
	double potential;
	complex double c;
	double p;
	int i; 
	
	
	
	c = give_c(ix,iy);
	potential = GivePotential(c);
	i = give_i(ix, iy);
			
	if (potential == FP_ZERO) 
		color = 0;
		else {
			p = log(potential)/K;
     			color = 255* (1+cos(TwoPi*p))/2.0;
     			//color = 255; // simply white for black equipotentials

		
		}
	A[i] = color; // save color
	APotential[i] = potential; // save also potential 
	
	return 0;


}


/* draw to the array and save it to pgm image */
int MakeImage(unsigned char A[]){

	int ix,iy;
	
	
	// draw
	printf("render image = compute and write image data bytes to the array \n");
 	#pragma omp parallel for  schedule(dynamic) private(ix,iy) shared(ixMax , iyMax)
  	for(iy=0;iy<iyMax;iy++)
    		for(ix=0;ix<ixMax;ix++)
      			    
			ComputeAndSavePixelColor(ix, iy, A); 
			
			

	
	return 0;
}



/*
 
  
  
  
  Gives direction ( coded in FCCode) to the left equal pixel , so it trace conterclockwise 
  
  
*/
int GiveNextChainCodeEqual(int ix0, int iy0, double p0){
	
	//double pTemp;
	double dpTemp;
	double p = 100000.0; // big
	double dp = 100.0; // big 
	int ix, iy; 
	int i; 
	
	int f = -1; // result = final FCCode
	int FCCode;//
	
	// find FCCode for which dp is the smallest 
	
	for (FCCode = 0; FCCode < 8; FCCode ++){ // 
	
		// translate FCCode t0 ix, iy
		ix = ix0 + offset[FCCode][0];
		iy = iy0 + offset[FCCode][1];
		
		// (ix,iy) -> i
		i = give_i(ix,iy);// new point
	
		if (i>0 && ABoundary[i]==0){ // inside bounds of 1D array and not visited 
			p = APotential[i];
			if (p != FP_ZERO) { // not interior
				dpTemp = fabs(p - p0);
				if (dpTemp<dp){
					f =  FCCode; // 
					dp = dpTemp;}}}
					
					
		}
	
	
	
		
	if (f == -1) {printf("\tproblem: FCCode not found \n"); return -1;}	
		
	if(i<0 ) f = -2;
	 else if( ABoundary[i]>0) FCCode = -3; // check if point was visitred
	
	return f;
	
}

// https://en.wikibooks.org/wiki/Fractals/Image_noise

double GiveNoiseMeasure (int ix0, int iy0, int i0){


	int FCCode;//
	
	int i;
	int ix, iy;
	
	double p0;
	double p; 
	double dp; // abs(p - p0)
	double dpMax = 0.0; // max dp 
	double dpArithmeticMean = 0.0;
	double n = 0.0;
	
	
	
	p0 = APotential[i0];
	
	
	
	for (FCCode = 0; FCCode < 8; FCCode ++){
	
		// translate FCCode t0 ix, iy
		ix = ix0 + offset[FCCode][0];
		iy = iy0 + offset[FCCode][1];
		
		// (ix,iy) -> i
		i = give_i(ix,iy);// new point
	
		if (i>0){ // inside bounds of 1D array 
			//if( ABoundary[i]!=0) printf(" point was visited \n");
			p = APotential[i];
			// compute dp 
			if ( p ==  FP_ZERO) 
				{if (p0 == FP_ZERO) 
					dp = 0.0;
					else dp = p0;}
				else dp = fabs(p-p0); // (p && p0) != FP_ZERO
			 
		if (dp>dpMax) dpMax = dp;
		dpArithmeticMean += dp;
		//printf("FCCode = %d , p = %.16f dp = %.16f\n", FCCode,p, fabs(p-p0) );
		n +=1.0;
		}
	
	
	
	}
	
	dpArithmeticMean /= n; //  
	
	
	
	return dpArithmeticMean/p0; // ratio
}


// input is a (double) complex number so D 
double GiveNoiseMeasureD(double complex c){

	int i;
	int ix, iy;
	double m;
	double p;
	// world to screen conversion
	ix = (int)round((creal(c)-CxMin)/PixelWidth);
      	iy = (int)round((CyMax-cimag(c))/PixelHeight); // reverse y axis
      	i = give_i(ix,iy);
      	m = GiveNoiseMeasure(ix,iy,i);
      	p = APotential[i];
      	if (p == FP_ZERO) p = 0.0;
      	printf("for c = (%f;%f)\tnoise measure = %.16f\tpotential = %.16f\n", creal(c), cimag(c), m, p );
      	return m;

}



/* 

n to FCCode translation used in CheckMooreNeighborhood function
number of cell from 8 point neighborhood
 	1,2,3
	4,5,6
	7,8,9

	so 5 = center
	
*/

int n2FCCode(int n){

	int FCCode = -1;
	if (n<1 || n> 9) {printf("\t bad n \t"); return -2;}
	switch (n) {
		case 1: FCCode = 3; break;
		case 2: FCCode = 2; break;
		case 3: FCCode = 1; break;
		case 4: FCCode = 4; break;
		case 5: FCCode = 8; break;
		case 6: FCCode = 0; break;
		case 7: FCCode = 5; break;
		case 8: FCCode = 6; break;
		case 9: FCCode = 7; break;
		}

	return FCCode;
}


/* used for testing 


	CheckMooreNeighborhood 
	FCCode = 3 , p = 0.0172499795393015 dp = -0.0014810494136638		FCCode = 2 , p = 0.0183472494146965 dp = -0.0003837795382688		FCCode = 1 , p = 0.0194811798131318 dp = 0.0007501508601665	
	FCCode = 4 , p = 0.0172866177310314 dp = -0.0014444112219338		center  pixel = (1610,1000) p0 = 0.0187310289529653 		FCCode = 0 , p = 0.0195177500282344 dp = 0.0007867210752691	
	FCCode = 5 , p = 0.0172911963906845 dp = -0.0014398325622808		FCCode = 6 , p = 0.0183884519130351 dp = -0.0003425770399302		FCCode = 7 , p = 0.0195223204303752 dp = 0.0007912914774100	
	CheckMooreNeighborhood  end, dpMax = 0.0007912914774100 so FCCodeAsc = 7 



*/


int CheckMooreNeighborhood(int ix0, int iy0){


	int FCCode;//
	int FCCodeAsc;//for dpMaxPos 
	int FCCodeDesc;// for dpMaxNeg
	int FCCodeEqual;// for dpMin
	int i;
	int ix, iy;
	int n; // number of cell : 
	/*  	1,2,3
		4,5,6
		7,8,9
		so 5 = center
	
	*/
	
	double p= 0.0; 
	double p0;
	//
	double dpMaxPos = 	0.0;
	double dpMaxNeg =    -100.0;
	double dpMin = 	      100.0;
	double dpTemp =         0.0;
	
	printf("\tCheckMooreNeighborhood \n");
	
	// (ix,iy) -> i
	i = give_i(ix0,iy0);// center
	p0 = APotential[i];
	
	
	for (n = 1; n < 10; n ++){
		
		// translate n to FCCode
		FCCode = n2FCCode( n);
		
		
		//printf("\tFCCode = %d , p = %.16f dp = %.16f\t", FCCode,p, fabs(p-p0) );
		if (FCCode !=8)
			{
			// translate FCCode t0 ix, iy
			ix = ix0 + offset[FCCode][0];
			iy = iy0 + offset[FCCode][1];
		
			// (ix,iy) -> i
			i = give_i(ix,iy);// new point
			
	
			if (i>0){ // inside bounds of 1D array 
				//if( ABoundary[i]!=0) printf(" point was visited \n");
				p = APotential[i];
				if (p ==  FP_ZERO) p = 0.0; // 
				
				dpTemp = p - p0;
				//
				if ( dpTemp > dpMaxPos ) {
					dpMaxPos = dpTemp;	
					FCCodeAsc = FCCode;}
				//	
				if ( dpTemp < 0.0 && dpTemp < dpMaxNeg ) {
					dpMaxNeg = dpTemp;	
					FCCodeDesc = FCCode;}
				//	
				if ( fabs(dpTemp) < dpMin ) {
					dpMin = dpTemp;	
					FCCodeEqual = FCCode;}	
					
				 
				printf("\tFCCode = %d , p = %.16f dp = %.16f\t", FCCode,p,dpTemp  );
				if (n % 3 == 0 ) printf("\n");// change row
				}
			
			}
			else printf("\tcenter  pixel = (%d,%d) p0 = %.16f \t\t", ix0, iy0, p0);
	
	}
	
	
	
	
	
	
	printf("\tdpMaxPos = %.16f so FCCodeAsc =  %d\n", dpMaxPos, FCCodeAsc);
	printf("\tdpMaxNeg = %.16f so FCCodeDesc = %d\n", dpMaxNeg, FCCodeDesc);
	printf("\tdpMin = %.16f so FCCodeEqual = %d\n", dpMin, FCCodeEqual);
	printf("\tCheckMooreNeighborhood  end\n");
	return 0;

}






/*
 give_i_AndDescribePixel
 extended give_i
*/
int give_i_(int ix, int iy){


	int i;
	double potential; 
	
	
	if (ix==ixMin || ix == ixMax || iy==iyMin || iy == iyMax) 
		printf("\tc is on the array boundary: ix = %d iy = %d", ix, iy); 
		else printf("\tc is inside the array : iy = %d iy = %d", ix, iy); 
	// (ix,iy) -> i
	i = give_i(ix,iy);// new point
	
	//	
	if (i>0){ // inside bounds of 1D array 
		potential = APotential[i];
		if (potential == FP_ZERO) 
			printf("\tand inside M set\n"); 
			else printf("\tand outside M set\n"); 
		}
	
	
	
	return i;

}




int DrawEquipotential(double complex c, unsigned char iColor, unsigned char A[]){

	double potential;
	double p0; // potential of the whole equipotential line 
	
	// world to screen conversion
	int ix0 = (int)round((creal(c)-CxMin)/PixelWidth);
      	int iy0 = (int)round((CyMax-cimag(c))/PixelHeight); // reverse y axis
  	int i0; // = give_i(ix0,iy0);
  	int i;
  	
  	int ix = ix0;
  	int iy = iy0;
  	
  	int n=0;
  	int nMax = 20000;
  	int FCCode;
  	
  	
  	printf("\ndraw equipotential curve thru point c = (%.16f; %.16f) pixel = (%d, %d)\n ", creal(c), cimag(c), ix0,iy0);
  	
  	printf("\tstart point\n\t"); 
  	GiveNoiseMeasureD(c);	
  	i0 = give_i_(ix0,iy0); // compute and describe 
  	if ( i0<0){ printf("\tc is out of drawing rectangle. End. \n"); return 1;}
  	
  	p0 = APotential[i0];
  	if (p0 ==  FP_ZERO) p0 = 0.0; // 
	ABoundary[i0]=1; // mark as visited, but not starting point because it wil be omited in GiveNextChainCodeEqual and curve do not close 
	//if (p0 == FP_ZERO) { printf("\tstart point c is inside. End.\n"); return 1;}
	//else 
	//printf("\tplot point n = %d\n", n);
	iPlotBigPoint(ix0, iy0, iColor, A);
	//A[i0] = 255 - A[i0];
	// printf("\tStart point\tix = %d iy = %d i = %d potential = %.16f\n",   ix, iy, i0 , p0);
	potential = p0;
	
	
	
		
			
	
	
	// draw next points   
	for(n=0; n<nMax; n++){
	
		//printf("\t n = %d\n", n);
		
		if (n == 2) ABoundary[i0]=0; // mark start point as not visited,  because it wil be omited in GiveNextChainCodeEqual and curve do not close 
		
		//CheckMooreNeighborhood(ix, iy,p0);
		// choose next point
		FCCode = GiveNextChainCodeEqual( ix,  iy,  p0);
		if (FCCode <0 || FCCode>7) {printf("\tdrawing stopped because of bad FCCode = %d after %d steps ( pixels)\n ", FCCode, n); return 1;}
		
		// translate FCCode t0 ix, iy
		ix += offset[FCCode][0];
		iy += offset[FCCode][1];
		
		// (ix,iy) -> i
		i = give_i(ix,iy); // new point
		if ( i<0){ printf("\tpoint out of drawing rectangle. End. \n"); return 1;}
		
		// Termination Condition = stoping criteria
		if(ix==ix0 && iy == iy0 ) 
			{printf("\tend point\tix = %d iy = %d i = %d potential = %.16f\n", ix, iy, i, potential );
			printf("\tcurve is closed = stop ( good) after %d steps (pixels)\n\n", n);
						 
			return 0;}
		
		
		
		
		if (i>0) 
			{
			//printf("\tn = %d FCCode = %d ix = %d iy = %d i = %d potential = %.16f\n", n ,FCCode,  ix, iy, i, potential );
			if (ABoundary[i]==1) { 	printf("\tproblem: next point c was visited = loop ?\n"); 
						//CheckMooreNeighborhood(ix, iy,p0);
						return 2;}
			potential = APotential[i];
			
			if (potential == FP_ZERO) { printf("\tc is inside. End. \n"); return 3;}
			
			//
			iPlotBigPoint(ix, iy, iColor, A);
			//A[i] = 255 - A[i]; //iColor;
			ABoundary[i]=1; // mark as visited
			
			
			}
			//else {printf("\terror from DrawEquipotential : bad i \n"); return -1; }	
	}
	
	// end after n = nMax
	potential = APotential[give_i(ix, iy)];
	if (potential ==FP_ZERO) potential = 0.0;
	printf("\tend point\tix = %d iy = %d i = %d potential = %.16f\n", ix, iy, i,  potential );
	printf("\tcurve is not closed = stop ( bad !!) after %d steps (pixels)\n\n", n);
	
	return 0; // 

}



/*
 
  Gives direction ( coded in FCCode) to the pixel with most greater potential 
  gradient ascent, hill climbing
  External ray out 
  !!!!!! not works !!!!!
  
 */
int GiveNextChainCodeAscent(int ix0, int iy0, double p0){
	
	//double pTemp;
	double dpTemp;
	double p = 0.0; // low
	double dp = 0.0; // low 
	int ix, iy; 
	int i; 
	
	int f = -1; // result = final FCCode
	int FCCode;//
	
	// find FCCode for which dp is the smallest 
	if (p0 == FP_ZERO) {printf("\tproblem from GiveNextChainCodeAscent: p0 = FP_ZERO  \n");return -1;}
	
	for (FCCode = 0; FCCode < 8; FCCode ++){ // 
	
		// translate FCCode t0 ix, iy
		ix = ix0 + offset[FCCode][0];
		iy = iy0 + offset[FCCode][1];
		
		// check border
		if (ix == 0 || ix == ixMax) {printf("\tend of image, stop : ix = %d \n", ix); return -2;} 
		if (iy == 0 || iy == iyMax) {printf("\tend of image, stop : iy = %d \n", iy); return -3;} 
		
		// (ix,iy) -> i
		i = give_i(ix,iy);// new point
	
		if (i>0 ){ // inside bounds of 1D array and not visited 
			p = APotential[i];
			if (p != FP_ZERO) { // not interior
				dpTemp = (p - p0);
				if (dpTemp>dp && dpTemp > 0.0){ 
					f =  FCCode; // 
					dp = dpTemp;}}}
					
					
		}
	
	
	
		
	if (f == -1) {printf("\tproblem from GiveNextChainCodeAscent: FCCode not found \n"); return -2;}	
		
	//if(i<0 ) f = -2;
	 //else if( ABoundary[i]>0) FCCode = -3; // check if point was visitred
	
	return f;
	
}

/*


cases: 
* A = ascending
* E = equal
* D = descending
* C = center


* A *
E C E
* D *

E A E
* C * 
* D *


* A *
* C *
E D E 




*/


int GiveAscent(int ix0, int iy0, double p0){

	int FCCode;//
	
	int ix, iy, i;
	double p;
	
	
	// equipotential
	FCCode = GiveNextChainCodeEqual(ix0,iy0,p0);
	if (FCCode <0 || FCCode>7) {printf("\tGiveAscent: bad FCCode = %d \n ", FCCode); return -1;}
		
	// perpendicular to equipotential
	// but it not works in case of concave/convex 
	// compute bot equal code and find code between them !!!!
	// see cases : normal = ( e_left + e_right )/2
	FCCode = (FCCode - 2) ;
	if (FCCode < 0) FCCode += 7;
	
	
	// check if p grows
	// translate FCCode t0 ix, iy
	ix = ix0 + offset[FCCode][0];
	iy = iy0 + offset[FCCode][1];
	// check border
	if (ix == 0 || ix == ixMax) {printf("\tend of image, stop : ix = %d \n", ix); return -2;} 
	if (iy == 0 || iy == iyMax) {printf("\tend of image, stop : iy = %d \n", iy); return -3;} 
	// (ix,iy) -> i
	i = give_i(ix,iy);// new point
	
	p = APotential[i];
	if (p<p0) FCCode +=4; // if p not grows then reverse direction
	if (FCCode >7 ) FCCode -= 7;
	
	
	
	
	
	
	return FCCode;  
}



int TestFCCCode(complex double c){


	int ix0, iy0;
	int ix,iy;
	double p0;
	double p;
	int i0;
	int i;
	int FCCodeEqual ; //= GiveNextChainCodeEqual(ix0,iy0,p0);
	int FCCodeAsc; // = GiveAscent(ix0,iy0,p0);
	
	// world to screen conversion
	ix0 = (int)round((creal(c)-CxMin)/PixelWidth);
      	iy0 = (int)round((CyMax-cimag(c))/PixelHeight); // reverse y axis
	i0 = give_i(ix0, iy0);
	p0 = APotential[i0];
	//
	FCCodeEqual = GiveNextChainCodeEqual(ix0,iy0,p0);
	FCCodeAsc = GiveAscent(ix0,iy0,p0);
	
	
	// translate FCCode t0 ix, iy
	ix = ix0 + offset[FCCodeAsc][0];
	iy = iy0 + offset[FCCodeAsc][1];
	// check border
	if (ix == 0 || ix == ixMax) {printf("\tend of image, stop : ix = %d \n", ix); return -2;} 
	if (iy == 0 || iy == iyMax) {printf("\tend of image, stop : iy = %d \n", iy); return -3;} 
	// (ix,iy) -> i
	i = give_i(ix,iy);// new point
	
	p = APotential[i];
	if (p<p0) FCCodeAsc +=4;
	if (FCCodeAsc >7 ) FCCodeAsc -= 7;
	
	
	
	printf("\n\n\tTestFCCCode c= (%.16f; %.16f)\tpixel = (%d;%d)\tFCCodeEqual = %d\t FCCodeAsc = %d\n",creal(c), cimag(c), ix0, iy0, FCCodeEqual, FCCodeAsc);
	CheckMooreNeighborhood(ix0,iy0);
	
	
	return FCCodeAsc;

}


int TestRay0(){

	int f;
	int e = 0; // errors
	double dc = 0.1; // dc = c_(n+1) - c_n
	double c = 0.45; // c = c0; then c += dc;
	int i; 

	printf("\ntest for tracing  external ray 0 : fccode should be: 0 for ascening (out) , or 4 for descending ( in), 2 and 6 for equal\n");
	
	for (i = 0; i<10; i++){
	
		f = TestFCCCode(c);	
		if (f ==0) 
			printf("\tgood asc\n"); 
			else {printf("\tbad asc\n"); e +=1;}
		c += dc;
		if (c > CxMax) break;
	
	}
	
  	  	 	
  	if (e ==0) 
  		printf("\n\tAll ascending good from GiveAscent. Test passed !!!! \n\n\n"); 
  		else printf("\t bad %d asc from GiveAscent\n\n\n", e);
  	
  	return e;

}





int TestRay1over2(){

	int f;
	int e = 0; // errors

	printf("\ntest for tracing  external ray 1/2 : fccode should be:  4 for ascening (out) , or 0 for descending ( in), 2 and 6 for equal\n");
  	f = TestFCCCode(2.26);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}
  	f = TestFCCCode(2.27);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}
  	f = TestFCCCode(2.28);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}
  	f = TestFCCCode(2.29);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}
  	f = TestFCCCode(2.30);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}
  	f = TestFCCCode(2.31);	if (f ==4) printf("\tgood asc\n"); else {printf("\tbad asc\n"); e +=1;}

	if (e ==0) 
		printf("\n\tAll ascending good. Test passed !!!\n"); 
		else printf("\t bad %d asc\n", e);
		
	return e;
}








/*


angle ( agument) of complex number in turns
https://en.wikipedia.org/wiki/Turn_(geometry)
*/
double GiveTurn( double complex z){
double t;

  t =  carg(z);
  t /= TwoPi; // now in turns
  if (t<0.0) t += 1.0; // map from (-1/2,1/2] to [0, 1) 
  return (t);
}

int DrawExtRayOut(double complex c,  unsigned char iColor, unsigned char A[]){

	double p;
	double p0; // potential of the whole equipotential line 
	
	// world to screen conversion
	int ix0 = (int)round((creal(c)-CxMin)/PixelWidth);
      	int iy0 = (int)round((CyMax-cimag(c))/PixelHeight); // reverse y axis
  	//int i0; // = 
  	int i;
  	
  	int ix = ix0;
  	int iy = iy0;
  	
  	int n=0;
  	int nMax = 2000;
  	int FCCode;
  	double t;
  	double NoiseMeasure;
  	
  	
  	printf("draw external ray\n");
	p0 = GivePotential(c);
	printf("\tstart point c = (%.16f;%.16f) \tpotential = %f\tpixel = (%d,%d)\n",creal(c), cimag(c),p0, ix, iy);
	if (p0 == FP_ZERO) { printf("\tbad start point : c is inside\n"); return 1;}
	NoiseMeasure = GiveNoiseMeasure (ix,iy,give_i(ix0,iy0));
	if (NoiseMeasure< NoiseMeasureThreshold) {printf("\tprobably bad start point: noise = %.16f\n ", NoiseMeasure); //return 1;
		} 
	
	//CheckMooreNeighborhood(ix, iy);
	dPlotPoint(c, 0,  A);
	
	
	p = p0;
		
	// draw next points   
	for(n=0; n<nMax; n++){
	
		// choose next point
		FCCode = GiveAscent( ix,  iy,  p);
		if (FCCode <0 || FCCode>7) {printf("\tdrawing stopped because of bad FCCode = %d after %d steps ( pixels)\n ", FCCode, n); return 1;}
		//
		
		// translate FCCode t0 ix, iy
		ix += offset[FCCode][0];
		iy += offset[FCCode][1];
		// test for ray 0
		//if (FCCode !=0 ) CheckMooreNeighborhood(ix, iy);
		
		
		// (ix,iy) -> i
		i = give_i(ix,iy); // new point
		if ( i<0){ printf("\tpoint out of drawing rectangle. End. \n"); return 1;}
	
		//
		p = APotential[i];
		iPlotBigPoint(ix, iy, iColor, A);
		c = give_c(ix,iy);
	   	t = GiveTurn(c);
		printf("\tnew point c = (%.16f;%.16f) \t pixel = (%d;%d)\tFCCode = %d\tpotential = %f\texternal angle = %.16f\n",creal(c), cimag(c), ix,iy, FCCode, p, t);
		//printf("\tnew point: potential = %.16f\t pixel = (%d,%d)\n", p, ix, iy);
	}
	
	c = give_c(ix,iy);
	t = GiveTurn(c);
	printf("\tend point c = (%.16f;%.16f) \t pixel = (%d;%d)\tpotential = %f\texternal angle = %.16f\n",creal(c), cimag(c), ix,iy, p, t);
	return 0;

}




// https://en.wikibooks.org/wiki/Fractals/Computer_graphic_techniques/2D/plane#radius
int SetPlane(complex double center, double radius){
	CxMin = creal(center) - AspectRatio*radius;
	CxMax = creal(center) + AspectRatio*radius;;
	CyMin = cimag(center) - radius;
	CyMax = cimag(center) + radius;
	


	return 0;


}


// 
int setup(){




	unsigned int i; // index of 1D array

	printf("setup start\n");
	
	ER2 = EscapeRadius*EscapeRadius; 
		
	// plane 
	iSize = iWidth*iHeight; // size = number of points in array 
	iyMax = iHeight - 1 ; // Indexes of array starts from 0 not 1 so the highest elements of an array is = array_name[size-1].
  	ixMax = iWidth - 1;
  	AspectRatio = (double) iWidth/iHeight;// width : height  https://en.wikipedia.org/wiki/Aspect_ratio_(image)
  	SetPlane( center, radius);
	PixelWidth = (CxMax-CxMin)/ixMax;
	PixelHeight = (CyMax-CyMin)/iyMax;
	
	iPixelRadius =ixMax* 0.001; /* half of width or height of big pixel */
	
	/* create dynamic 1D arrays for colors ( shades of gray ) */
  	AColor = malloc( iSize * sizeof(unsigned char) );
  	APotential = malloc(iSize * sizeof(double));
  	ABoundary = malloc(iSize*sizeof(int));
  	
  	if (AColor == NULL || APotential ==NULL || ABoundary== NULL)
    	{
      		fprintf(stderr,"\tCould not allocate memory\n");
      		return 1;
    	}
  	else fprintf(stderr,"\tmemory is OK \n");
  	

  	// clear array
	for(i= 0; i<=iSize; ++i) ABoundary[i] = 0; 

	
	
	printf("setup end\n");
		
	return 0;
}


// Check Orientation of image : mark first quadrant 
// it should be in the upper right position
// uses global var :  ...
int CheckOrientation (unsigned char A[])
{
  int ix, iy;		// pixel coordinate 
  double complex c;		//  
  int i;			/* index of 1D array */
  
  for (iy = iyMin; iy <= iyMax; ++iy)
    
      
      for (ix = ixMin; ix <= ixMax; ++ix)
	{

	  // from screen to world coordinate 
	  c = give_c (ix,iy);
	  
	  if (creal(c) > 0 && cimag(c) > 0){
	  	i = give_i (ix, iy);	/* compute index of 1D array from indices of 2D array */
	  	//printf("color = %d ",A[i] );
	    	A[i] = 255 - A[i];	// check the orientation of Z-plane by marking first quadrant */
	    	//printf("color = %d \n",A[i] );
	    	}

	}
    

  return 0;
}





int info(){


	printf("\n\nParameter plane with Mandelbrot set\n");
	printf("\tcenter c= (%f;%f)\t radius = %f\t mag = %f\n",creal(center), cimag(center), radius,1.0/radius);
	printf("\tcorners: CxMin = %f\tCxMax = %f\t CyMin = %f\t CyMax %f\n",CxMin, CxMax, CyMin, CyMax);
	printf("\tcorners: ixMin = %d\tixMax = %d\t iyMin = %d\t iyMax %d\n",ixMin, ixMax, iyMin, iyMax);
	printf("exterior = CPM/M\n");
	printf("IterationMax = %d\n", IterationMax);
	printf("EscapeRadius = %.0f\n",EscapeRadius);
	printf("iPixelRadius = ixMax* 0.002 = %d so big pixel = %d (small) pixels \n", iPixelRadius, 4*iPixelRadius*iPixelRadius); // ???
	printf("NoiseMeasureThreshold = %.16f\n", NoiseMeasureThreshold );
	printf("BoundaryMeasure = %.16f\n", BoundaryMeasure);
	return 0;
}



// // make exterior white
// uses global var :  ...
int ClearExterior (unsigned char A[])
{
  int ix, iy;		// pixel coordinate 
  		//  
  int i;			/* index of 1D array */
  
  for (iy = iyMin; iy <= iyMax; ++iy)
        for (ix = ixMin; ix <= ixMax; ++ix)
	{

	  i = give_i (ix, iy);	/* compute index of 1D array from indices of 2D array */
	  if ( APotential[i] != FP_ZERO) A[i] = 255 ;	// check if exterior
	  
	}
    
  printf("ClearExterior =  make exterior solid color = white\n");
  return 0;
}




// // make exterior white
// uses global var :  ...
int FindBoundary (unsigned char A[])
{
  int ix, iy;		// pixel coordinate 
  int i; 			/* index of 1D array */
  
  double NoiseMeasure;
  
 
	
  for (iy = 1; iy < iyMax-1; ++iy) // do not check border points, or change GiveNoiseMeasure 
        for (ix = 1; ix < ixMax-1; ++ix)
	{

	  i = give_i (ix, iy);	/* compute index of 1D array from indices of 2D array */
	  if (i>-1 && APotential[i] != FP_ZERO){ 
	  	
	  	
	  	NoiseMeasure = GiveNoiseMeasure (ix,iy,i);
	  	if (NoiseMeasure> BoundaryMeasure) A[i] = 255 ;	// white
	  	}
	  
	}
    
  printf("Find boundary of Mandelbrot set using  potential\n");
  return 0;
}


/* make exterior white
 uses global var :  ...
 wher potential is positive ( >0 ) and < BoundaryMeasure
*/
int FindNoisyPixels (unsigned char A[])
{
  int ix, iy;		// pixel coordinate 
  int i; 			/* index of 1D array */
  
  double NoiseMeasure;
  
	
  for (iy = 1; iy < iyMax-1; ++iy) // do not check border points, or change GiveNoiseMeasure 
        for (ix = 1; ix < ixMax-1; ++ix)
	{

	  i = give_i (ix, iy);	/* compute index of 1D array from indices of 2D array */
	  if (i>-1 && APotential[i] != FP_ZERO) {
	  	NoiseMeasure = GiveNoiseMeasure (ix,iy,i);
	  	if (NoiseMeasure> NoiseMeasureThreshold) A[i] = 255 ;	// 
	  	}
	  
	}
    
  printf("Find noisy pixels near boundary of Mandelbrot set with boundary )\n");
  return 0;
}


// fill array 
// uses global var :  ...
// scanning complex plane 
int ClearArray(unsigned char A[] )
{
  
  	unsigned int i; // index of 1D array

  	// every pixel of the image is black
	for(i= 0; i<=iSize; ++i) A[i] = 0; 
			     	
	return 0;
}

/*
 save data array to pgm file 
SaveArray2PGMFile(data0 , iterMax+9, "marked first quadrant should be up and right", 100, 100); // save array (image) to pgm filename
*/

int SaveArray2PGMFile( unsigned char A[], double ER,int IterationMax , char* comment, int iWidth, int iHeight, int iSize )
{
  
  FILE * fp;
  const unsigned int MaxColorComponentValue=255; /* color component is coded from 0 to 255 ;  it is 8 bit color file */
  char name [100]; /* name of file */
  snprintf(name, sizeof name, "%d_%d",(int)ER, IterationMax); /*  */
  char *filename =strncat(name,".pgm", 4);
  
  
  
  /* save AColor to the pgm file  */      
  fp= fopen(filename,"wb"); /*create new file,give it a name and open it in binary mode  */
  fprintf(fp,"P5\n # %s\n %u %u\n %u\n", comment, iWidth, iHeight, MaxColorComponentValue);  /*write header to the file*/
  fwrite(A,iSize,1,fp);  /*write image data bytes to the file in one step */
  
  //
  printf("File %s saved. ", filename);
  if (comment != NULL)  
  	printf ("comment = %s \n", comment); 
  	else printf ("\n"); 
  fclose(fp);

  return 0;
}




int SetDown(){
  	free(AColor);
  	free(APotential);
  	free(ABoundary);
  	info();
  	return 0;


}
   


/* -----------------------------------------  main   -------------------------------------------------------------*/
int main()
{

		
	setup(); // corners: CxMin = -2.550000	CxMax = 1.050000	 CyMin = -1.800000	 CyMax 1.800000
	
	
	
	// images 
	ClearArray(AColor); // all black
	MakeImage(AColor);
	SaveArray2PGMFile( AColor, EscapeRadius, IterationMax+1, NULL,  iWidth, iHeight, iSize );
	
	//
	ClearExterior(AColor); // make exterior white
	
	
	
	
	
	
	
	
	//DrawEquipotential( 1.03+1.7*I,	0, AColor); // bad because of image boundary 
	//DrawEquipotential( 1.05, 	0, AColor); // bad on boundary:  error  from giv_i : bad input: ix = 2000 
	DrawEquipotential( 1.0, 	0, AColor); // bad on boundary:  error  from giv_i : bad input: ix = 2000 
	DrawEquipotential( 0.9, 	0, AColor); //good
	DrawEquipotential( 0.8, 	0, AColor); // good
	DrawEquipotential( 0.7, 	0, AColor); // good
	DrawEquipotential( 0.6, 	0, AColor); // good
	DrawEquipotential( 0.5, 	0, AColor); // good
	DrawEquipotential( 0.4, 	0, AColor); // good 
	// DrawEquipotential( 0.35, 	0, AColor); // bad because of chaotic data
	// DrawEquipotential( 0.3, 	0, AColor); // bad because of chaotic data
	
	//CheckOrientation(AColor) ;
	 
	SaveArray2PGMFile( AColor, EscapeRadius, IterationMax+2, NULL,  iWidth, iHeight, iSize );
	
	
	//DrawExtRayOut( 0.4+0.7*I, 0, AColor);
	//DrawExtRayOut( -0.5+0.76*I, 0, AColor);
	DrawExtRayOut( 0.7, 0, AColor); // ray 0 
	DrawExtRayOut( -2.01, 0, AColor); // ray 1/2 , good 	
	
	SaveArray2PGMFile( AColor, EscapeRadius, IterationMax+3, NULL,  iWidth, iHeight, iSize );
	
  	ClearArray(AColor); // all black
  	FindBoundary(AColor);
  	SaveArray2PGMFile( AColor, EscapeRadius, IterationMax+4, NULL,  iWidth, iHeight, iSize ); 
  	//
  	ClearArray(AColor); // all black
  	FindNoisyPixels(AColor);
  	SaveArray2PGMFile( AColor, EscapeRadius, IterationMax+5, NULL,  iWidth, iHeight, iSize ); 
  	
  	
  	
  	
  	// tests
  	
  	printf("\ntest to find limits of NoiseMeasure\n");
  	GiveNoiseMeasureD(0.0);
  	GiveNoiseMeasureD(0.1);
  	GiveNoiseMeasureD(0.2);
  	GiveNoiseMeasureD(0.25);
  	GiveNoiseMeasureD(0.26);
  	GiveNoiseMeasureD(0.27);
  	GiveNoiseMeasureD(0.28);
  	GiveNoiseMeasureD(0.29);
  	GiveNoiseMeasureD(0.3);
  	GiveNoiseMeasureD(0.35);
  	GiveNoiseMeasureD(0.4);
  	GiveNoiseMeasureD(0.45);
  	GiveNoiseMeasureD(0.5);
  	GiveNoiseMeasureD(0.6);
  	GiveNoiseMeasureD(0.7);
  	GiveNoiseMeasureD(0.8);
  	GiveNoiseMeasureD(0.9);
  	GiveNoiseMeasureD(1.0);
  	
  	//TestRay0();
  	//TestRay1over2();
  	
  	
  	
  	
  	
  	
  	
	SetDown();
 
  return 0;
}
