//
// Copyright 2019 Alan M. Ferrenberg
//

#include <cstdlib>
#include <string>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

double timingTest(int numTrials) {
  double result = 0.0;
  unsigned int seed = time(NULL);

  // Initialize the random number generator
  srand(seed);

  for (int j = 0; j < numTrials; j++) {
    for (int i = 0; i < 10000000; i++) {
      // Generate a random number
      result += tan(rand_r(&seed));
    }
  }
      return result;
}

int main(int argc, char** argv) {
  // Perform 100 trials of 10,000,000 iterations
  double total = timingTest(100);
  cout << "Total = " << total << "\n";
  return 0;
}
