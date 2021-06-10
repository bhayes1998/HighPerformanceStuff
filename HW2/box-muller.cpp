// Copyright [2020] <Bryan Hayes> 

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <random>

#define RUNLENGTH 20000000
#define N 100
#define _USE_MATH_DEFINES


using namespace std;

struct drand48_data state;


double uniformRand() {
    double rng = 0;
    drand48_r(&state, &rng);
    return rng;
}

void doBoxMuller(double *ave, double *stdDev, double mu, double sigma) {
    double g1, g2, u1, u2;
    double sum = 0;
    double sumSquare = 0;
    for (long i = 0; i < RUNLENGTH/2; i++) {
        u1 = uniformRand();
        u2 = uniformRand();
        g1 = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
        g1 = mu + sigma * g1;
        g2 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
        g2 = mu + sigma * g2;
        sum += g1 + g2;
        sumSquare += (g1 * g1) + (g2 * g2);
    }
    *ave = sum / (RUNLENGTH);
    double avgSquare = sumSquare / (RUNLENGTH);
    *stdDev = sqrt(avgSquare - (*ave * *ave));
}


int main(int argc, char*argv[]) {
    unsigned int seed = stoul(argv[1]);
    srand48_r(seed, &state);
    for (int i = 0; i < N; i++) {
        double ave, stdDev;
        doBoxMuller(&ave, &stdDev, 42.0, 5.0);
        cout << "Average: " << ave << 
        ", Standard Deviation: " << stdDev << endl;
    }
}
