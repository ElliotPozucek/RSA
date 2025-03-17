#include "test_prime.h"

void test_prime() {
    // test numbers, must be all prime
    unsigned int test_numbers[] = {2, 6113, 505639, 127123, 865121, 11, 1, 2000629, 4200007793, 1000002161, 29};
    cout << "Testing prime number verification..." << endl;
    for (unsigned int number : test_numbers) {
        cout << "Testing number: " << number;
        if (prime(number) && square_root_test(number)) {
            cout << " is prime and should be prime." << endl;
        } else {
            cout << " is not prime and should be prime." << endl;
        }
    }
}