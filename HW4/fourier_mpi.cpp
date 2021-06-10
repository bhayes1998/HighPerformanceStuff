#include <mpi.h>
#include <cmath>
#include <iostream>

// Copyright 2020 Alan M. Ferrenberg

using std::cerr;
using std::cout;
using std::endl;
using std::stoi;

#define ZERO 0.0000000000000000000000000000000000

void usageError() {
    std::cerr << std::endl << "Usage:" << std::endl;
    std::cerr << std::endl << "pingpong array_size numLoops" << std::endl;
    exit(1);
}

int processArgv(int argc, char *argv[], int *N) {
    int status = 0;

  // Should be 1 argument so argc should be 2
    if (argc == 2) {
        *N = std::stoi(argv[1]);
    } else {
    // There's a problem so print out an error message and return 1
        usageError();
        status = 1;
    }
    return status;
}

void doMPIStuff(int argc, char *argv[], int *numTasks, int *rank) {
    int value;

  // Initialize MPI for this program
    if ((value = MPI_Init(&argc, &argv)) != 0) {
        std::cerr << "Problem with MPI_Init" << std::endl;
        exit(value);
    }

  // Get the number of processes
    if ((value = MPI_Comm_size(MPI_COMM_WORLD, numTasks)) != 0) {
        std::cerr << "Problem with MPI_Comm_size" << std::endl;
        exit(value);
    }

    if (*numTasks < 2) {
        std::cerr << "Program is designed to run with 2 or more tasks"
                << std::endl;
        exit(3);
    }

  // Get my rank
    if ((value = MPI_Comm_rank(MPI_COMM_WORLD, rank)) != 0) {
        std::cerr << "Problem with MPI_Comm_rank" << std::endl;
        exit(value);
    }
}

// Compute the discrete Fourier transform of the function provided
void computeFT(int N, double oR[], double oI[], int k, double* real, double* imag) {
    int n;
    double tempR = ZERO, tempI = ZERO;

    // Loop over the N spatial/temporal values
    for (n = 0; n < N; n++) {
        double arg = 2.0*M_PI*k*n/N;
        double cosArg = cos(arg);
        double sinArg = sin(arg);

      // Accumulate the real and imaginary components of the Fourier transform
      // for frequency k in temporary variables
        tempR += oR[n]*cosArg + oI[n]*sinArg;
        tempI += oI[n]*cosArg - oR[n]*sinArg;
    }
    *real = tempR;
    *imag = tempI;
}

void initialize(int N, double oR[], double oI[], double fR[], double fI[]) {
    double a = 2.0;
  
    oR[0] = a;
    oI[0] = ZERO;
    fR[0] = ZERO;
    fI[0] = ZERO;
  
    for (int n = 1; n < N; n++) {
        oR[n] = sin(a*n)/n;
        oI[n] = ZERO;
        fR[n] = ZERO;
        fI[n] = ZERO;
    }
}

void assistantManager(int N, int numTasks, double fR[], double fI[]) {
    int k = 0, out = 0, end = -1;
    double tempR = 0, tempI = 0;
    for (int i = 1; i < numTasks; i++) {
        int newK = k + i - 1;
        MPI_Send(&newK, 1, MPI_INT, i, i, MPI_COMM_WORLD);
    }
    while (out < N) {
        MPI_Status status;
        MPI_Recv(&tempR, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        MPI_Recv(&tempI, 1, MPI_DOUBLE, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        fR[status.MPI_TAG] = tempR; fI[status.MPI_TAG] = tempI;
        out++;
        k++;
        if (out < N) {
            int newK = k + numTasks - 2;
            MPI_Send(&newK, 1, MPI_INT, status.MPI_SOURCE, status.MPI_SOURCE, MPI_COMM_WORLD);
        } 
    }

    for (int i = 1; i < numTasks; i++) {
        MPI_Send(&end, 1, MPI_INT, i, i, MPI_COMM_WORLD);
    }

    for (int k = 0; k < N; k++) {
        cout << "k value: " << k << ", real: " << fR[k] << ", imag: " << fI[k] << endl;
    }
}

// Manager method 
void manager(int N, int numTasks, double* eTime, double* cTime) {
    double eStart, CPU, eEnd, totalCPU, *oR, *oI, *fR, *fI;
    clock_t t1;

    fR = new double[N];
    fI = new double[N];
    oR = new double[N];
    oI = new double[N];

    initialize(N, oR, oI, fR, fI);

    eStart = MPI_Wtime();
    t1 = clock();

    MPI_Bcast(oR, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(oI, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    assistantManager(N, numTasks, fR, fI);

    t1 = clock() - t1;
    CPU = static_cast<double>(t1)/static_cast<double>(CLOCKS_PER_SEC);
    MPI_Reduce(&CPU, &totalCPU, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    eEnd = MPI_Wtime();
    *eTime = (eEnd - eStart);
    *cTime = totalCPU;

    delete [] oR;   delete [] oI;   delete [] fR;   delete [] fI;
}

// Worker method 
void worker(int N, int rank) {
    double totalCPU, CPU, real, imag;
    double *oR = new double[N];
    double *oI = new double[N];

    clock_t t1;

    t1 = clock();

    int k = 0;
    MPI_Bcast(oR, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(oI, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    while (k >= 0) {
        MPI_Recv(&k, 1, MPI_INT, 0, rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (k >= 0) {
            computeFT(N, oR, oI, k, &real, &imag);
            MPI_Send(&real, 1, MPI_DOUBLE, 0, k, MPI_COMM_WORLD);
            MPI_Send(&imag, 1, MPI_DOUBLE, 0, k, MPI_COMM_WORLD);
        }
    }

    t1 = clock() - t1;
    CPU = static_cast<double>(t1)/static_cast<double>(CLOCKS_PER_SEC);
    MPI_Reduce(&CPU, &totalCPU, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}

// Main method for this program
int main(int argc, char *argv[]) {
    int numTasks, rank, N;
    doMPIStuff(argc, argv, &numTasks, &rank);

    processArgv(argc, argv, &N);


    if (rank == 0) {
        double eTime, cTime; 
        manager(N, numTasks, &eTime, &cTime);
        cerr << "elapsed time = " << eTime;
        cerr << "CPU time = " << cTime << std::endl;
    } else {
        worker(N, rank);
    }

    MPI_Finalize();

  // Exit!
    exit(0);
}
