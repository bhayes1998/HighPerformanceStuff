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
#pragma omp parallel for reduction(+:x0, x2, x4, x6, x8, xa, xc, xe)
  for (long int j0 = 0; j0 < n; j0++) {
    x0 += 0.5*cosl(sc(j0)/23000.0);
    x2 += 0.5*tanl(sinl(sc(j0)/23000.0));
    x4 += 0.5*cosl(tanl(sc(j0)/23000.0));
    x6 += 0.5*cosl(cosl(sc(j0)/23000.0));
    x8 += 0.5*sinl(sinl(sc(j0)/23000.0));
    xa += 0.5*tanl(tanl(sc(j0)/23000.0));
    xc += 0.5*sinl(sc(j0)/23000.0);
    xe += 0.5*sinl(sc(j0)/23000.0);
  }
#pragma omp parallel for reduction(+:x1, x3, x5, x7, x9, xb, xd, xf)
  for (long int j1 = 0; j1 < n; j1++) {
    x1 += 0.5*sinl(x0*j1/23000.0);
    x3 += 0.5*tanl(cosl(x2*j1/23000.0));
    x5 += 0.5*tanl(sinl(x4*j1/23000.0));
    x7 += 0.5*cosl(cosl(x6*j1/23000.0));
    x9 += 0.5*sinl(sinl(x8*j1/23000.0));
    xb += 0.5*tanl(sinl(xa*j1/23000.0));
    xd += 0.5*cosl(xc*j1/23000.0);
    xf += 0.5*cosl(abs(xe*j1/23000.0));
  }

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
