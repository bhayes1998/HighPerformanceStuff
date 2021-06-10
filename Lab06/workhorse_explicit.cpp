#include <cmath>
#include <omp.h>
#include <iostream>
#include <iomanip>

// Copyright 2020 Alan M. Ferrenberg

// Function to do the static cast
long double sc(long int i) {
  return static_cast<long double>(i);
}

long double workhorse(long int n) {
  long double x0 = 0.0, x1 = 0.0, x2 = 0.0, x3 = 0.0, x4 = 0.0, x5 = 0.0;
  long double x6 = 0.0, x7 = 0.0, x8 = 0.0, x9 = 0.0, xa = 0.0, xb = 0.0;
  long double xc = 0.0, xd = 0.0, xe = 0.0, xf = 0.0;
#pragma omp parallel
  {
#pragma omp single 
	  {

#pragma omp task
  {for (long int j0 = 0; j0 < n; j0++) {x0 += 0.5*cosl(sc(j0)/23000.0);}
  for (long int j1 = 0; j1 < n; j1++) {x1 += 0.5*sinl(x0*j1/23000.0);}}
#pragma omp task
  {for (long int j2 = 0; j2 < n; j2++) {x2 += 0.5*tanl(sinl(sc(j2)/23000.0));}
  for (long int j3 = 0; j3 < n; j3++) {x3 += 0.5*tanl(cosl(x2*j3/23000.0));}}
#pragma omp task
  {for (long int j4 = 0; j4 < n; j4++) {x4 += 0.5*cosl(tanl(sc(j4)/23000.0));}
  for (long int j5 = 0; j5 < n; j5++) {x5 += 0.5*tanl(sinl(x4*j5/23000.0));}}
#pragma omp task
  {for (long int j6 = 0; j6 < n; j6++) {x6 += 0.5*cosl(cosl(sc(j6)/23000.0));}
  for (long int j7 = 0; j7 < n; j7++) {x7 += 0.5*cosl(cosl(x6*j7/23000.0));}}
#pragma omp task
  {for (long int j8 = 0; j8 < n; j8++) {x8 += 0.5*sinl(sinl(sc(j8)/23000.0));}
  for (long int j9 = 0; j9 < n; j9++) {x9 += 0.5*sinl(sinl(x8*j9/23000.0));}}
#pragma omp task
  {for (long int ja = 0; ja < n; ja++) {xa += 0.5*tanl(tanl(sc(ja)/23000.0));}
  for (long int jb = 0; jb < n; jb++) {xb += 0.5*tanl(sinl(xa*jb/23000.0));}}
#pragma omp task
  {for (long int jc = 0; jc < n; jc++) {xc += 0.5*sinl(sc(jc)/23000.0);}
  for (long int jd = 0; jd < n; jd++) {xd += 0.5*cosl(xc*jd/23000.0);}}
#pragma omp task
  {for (long int je = 0; je < n; je++) {xe += 0.5*sinl(sc(je)/23000.0);}
  for (long int jf = 0; jf < n; jf++) {xf += 0.5*cosl(abs(xe*jf/23000.0));}}
  }}
  return x1 + x3 + x5 + x7 + x9 + xb + xd + xf;
}

int main(int argc, char *argv[]) {
  // Make sure one command line argument is provided
  if (argc < 2) {
    std::cerr << std::endl << "Usage: workhorse n";
    std::cerr << std::endl << std::endl;    
    exit(1);
  }

  // Size of iteration
  long int n = std::stoi(argv[1]);

  // Don't allow a negative loop size
  if (n < 0) {
    std::cerr << std::endl << "n must be >= 0" << std::endl << std::endl;
    exit(2);
  }
  
  // Invoke workhorse and write out the results
  std::cout << std::endl;
  std::cout << "workhorse(" << n << ") is " << std::setprecision(12);
  std::cout << workhorse(n) << std::endl;
  std::cout << std::endl;

  return 0;
}
