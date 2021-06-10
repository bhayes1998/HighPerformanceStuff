// Copyright (C) 2016 raodm@miamiOH.edu

#include <string>
#include <iostream>

using namespace std;

/** Method to test the operation and performance of series of if-else
    statements.  The if-else statements are synonymous to the switch
    statement in the competing test in this micro-benchmark.

    \param[in] i The value to be operated on. This parameter is
    assumed to be in the range 0 to 9.
*/

int useIf(const int i) {
    if (i == 0) {
        return 1;
    } else if (i == 1) {
        return 3;
    } else if (i == 2) {
        return -1;
    } else if (i == 3) {
        return -3;
    } else if (i == 4) {
        return 4;
    } else if (i == 5) {
        return 1;
    } else if (i == 6) {
        return 5;
    } else if (i == 7) {
        return -4;
    } else if (i == 8) {
        return -5;
    }
    return 0;
}

/** Method to test the operation and performance of switch statement.

    \param[in] i The value to be operated on. This parameter is
    assumed to be in the range 0 to 9.
*/
int useSwitch(const int i) {
    switch (i) {
    case 0: return 1;
    case 1: return 3;
    case 2: return -1;
    case 3: return -3;
    case 4: return 4;
    case 5: return 1;
    case 6: return 5;
    case 7: return -4;
    case 8: return -5;
    case 9:
    default: return 0;
    }
}

/**
   Wrapper method to call useSwitch() method. Sure, it adds some
   method call overheads but it makes the benchmark a bit easier to
   code/understand in a short time.
*/
int switchTest(int sum, const int i) {
    sum += useSwitch(i) + useSwitch(0) + useSwitch(1);
    sum += useSwitch(i) + useSwitch(3) + useSwitch(4);
    sum += useSwitch(i) + useSwitch(5) + useSwitch(6);
    sum += useSwitch(i) + useSwitch(7) + useSwitch(8);
    sum += useSwitch(i) + useSwitch(9) + useSwitch(i);
    return sum;
}


/**
   Wrapper method to call useSwitch() method. Sure, it adds some
   method call overheads but it makes the benchmark a bit easier to
   code/understand in a short time.
*/
int ifTest(int sum, const int i) {
    sum += useIf(i) + useIf(0) + useIf(1);
    sum += useIf(i) + useIf(3) + useIf(4);
    sum += useIf(i) + useIf(5) + useIf(6);
    sum += useIf(i) + useIf(7) + useIf(8);
    sum += useIf(i) + useIf(9) + useIf(i);
    return sum;
}

//   A simple driver that calls benchmark methods many times.

int main(int argc, char *argv[]) {
    const int NumIter = (argc > 2 ? std::stoi(argv[2]) : 2000000000);
    int sum = 0;
    string cmd = "switch";
    if ((argc > 1) && (argv[1] == cmd)) {
      for (int i = 0; (i < NumIter); i++) {
        sum += switchTest(sum, i & 0xf);
        sum += switchTest(sum, i & 0x8);
        sum += switchTest(sum, i & 0xf);
        sum += switchTest(sum, i & 0x8);
      }
    } else {
      for (int i = 0; (i < NumIter); i++) {
        sum += ifTest(sum, i & 0xf);
        sum += ifTest(sum, i & 0x8);
        sum += ifTest(sum, i & 0xf);
        sum += ifTest(sum, i & 0x8);
      }
    }
    // Print some info to ensure the benchmark is operating on data
    cout << "Sum = " << sum << endl;
    return 0;
}
