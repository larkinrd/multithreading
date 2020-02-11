/*****************************************************************************
* https://cs.lmu.edu/~ray/notes/trivialcpexamples/
* TO COMPILE USE: g++ -pthread <filename.cpp> -o <outputfilename>
* RESULTED IN: COULD NOT EVEN COMPILE
* 
* thirdmtexample.cpp:27:43: error: cast from ‘void*’ to ‘int’ loses precision [-fpermissive]
*   for (int divisor = 2; divisor <= (int)candidate; divisor++)  
* 
* primes.cpp
*
* This program prints all primes up to and including its integer argument
* n.  It works by running threads for all values k in 2..n which determine
* if k is prime and print k if it is.
*
*****************************************************************************/

#include <iostream>
#include <pthread.h>

using namespace std;

#define TRY(code, message) if (code) {cout << message << '\n'; exit(-1);}

// The mutex to use to print safely.
pthread_mutex_t writing;

// Takes in an integer and prints it if and only if it is prime.
// The printing needs to be done within a critical section.
void* check(void* candidate) {
    for (int divisor = 2; divisor <= (int)candidate; divisor++) {
        if (divisor == (int)candidate) {
            TRY(pthread_mutex_lock(&writing), "Can't lock mutex");
            cout << (int)candidate << ' ';
            TRY(pthread_mutex_unlock(&writing), "Can't unlock mutex");
        } else if ((int)candidate % divisor == 0) {
            break;
        }
    }
    return NULL;
}

// Prints primes up to n.  It stores all the threads in an array so
// that it can wait on them all to finish.  Then it cleans up.
void findPrimes(int n) {
    pthread_t* checkers;

    if (n < 2) return;

    checkers = (pthread_t*)malloc((n-1) * sizeof(pthread_t));
    TRY(pthread_mutex_init(&writing, NULL), "Can't create mutex");
    for (int i = 2; i <= n; i++) {
        TRY(pthread_create(&checkers[i-2], NULL, &check, (void*)i),
                "Cannot create one or more of the threads");
    }

    for (int i = 0; i < n-1; i++) {
        int ignored;
        TRY(pthread_join(checkers[i], (void**)&ignored), "Join failed");
    }

    TRY(pthread_mutex_destroy(&writing), "Can't destroy mutex");
    free(checkers);
}

// Invokes findPrimes with a command line argument.
int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "This application requires exactly one parameter\n";
    } else {
        findPrimes(atoi(argv[1]));
    }
    return 0;
}