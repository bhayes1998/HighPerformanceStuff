#include <omp.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>


// Copyright 2020 by Bryan Hayes

#define RUNLENGTH 1000000

using std::stoi;
using std::stoul;
using std::cout;
using std::endl;
using std::setprecision;

// Each thread will have its own copy of the random number state which must
// persist throughout the program.  Make this state be a global variable and
// define it as threadprivate

struct drand48_data state;
#pragma omp threadprivate(state)

// Function to initialize the random number states for each thread.  Each
// thread gets a unique seed based on the single seed provided as an argument
void initRNG(unsigned int seed) {
#pragma omp parallel
  {
    int k = omp_get_thread_num();

    // set the initial seed and state with thread-safe version
    srand48_r(seed+23*k, &state);
  }
  return;
}

double randomNum() {
  double rng = 0.0;
  drand48_r(&state, &rng);
  return rng;
}

// This function uses Monte Carlo integration to estimate pi
double monteCarloIntegration(int numBlocks) {
  double sum = 0.0;
  double x, y, d;
  int count = 0;
  for (int i = 0; i < numBlocks; i++) {
  count = 0;
#pragma omp parallel for reduction(+:count) private(x, y, d) 
    for (int j = 0; j < 1000000; j++) {
      drand48_r(&state, &y);
      drand48_r(&state, &x);
      d = pow(x, 2) + pow(y, 2);
      if (d < 1)
        count++;
    }
    sum += (4.0*count) / (1000000.0);
  }

  double pi = sum/numBlocks;
  return pi;
}


// Main program
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Incorrect arguments" << endl;
    return 1;
  }
  
  int n = stoi(argv[1]);
  unsigned int seed = stoul(argv[2]);

  initRNG(seed);
  
  double estimate = monteCarloIntegration(n);
  cout << "Pi Estimate: " << setprecision(12) << estimate << endl;
  return 0;
}
