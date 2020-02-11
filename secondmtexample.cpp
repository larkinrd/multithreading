/*****************************************************************************
* https://cs.lmu.edu/~ray/notes/trivialcpexamples/
* TO COMPILE USE: g++ -pthread <filename.cpp> -o <outputfilename>
* RESULTED IN: CAN'T FIGURE OUT WHAT IT IS REALLY DOING, GET COMPILER WARNING
* 
* summer.cpp
*
* Short program illustrating a function that sums up an integer array by
* summing each half concurrently.
*
*****************************************************************************/

#include <iostream>
#include <vector>
#include <cassert>
#include <pthread.h>

using namespace std;

struct Slice {
    vector<int> data;
    unsigned low;
    unsigned high;
    Slice(vector<int> d, unsigned l, unsigned h): data(d), low(l), high(h) {}
};

// Takes in a pointer to a slice and sums the values in the slice from
// the low index (inclusive) to the high index (exclusive) and returns
// the sum.
void* sum_slice(void* arg) {
    Slice* s = (Slice*)arg;
    int sum = 0;
    for (int i = s->low; i < s->high; i++) {
        sum += s->data[i];
    }
    return (void*)sum;
}

// Returns the sum of the values in vector a.  It does this internally
// using two threads; the main thread and a newly created one.
int sum_vector(const vector<int>& a) {
    int sum1;
    int sum2 = 0;

    // A thread gets only one argument, so manufacture one.
    pthread_t thread;
    Slice first_half(a, 0, a.size() / 2);

    // Sum half on a new thread; the other half on the current thread.
    int rc = pthread_create(&thread, NULL, &sum_slice, &first_half);
    if (rc) cout <<"Cannot create thread", exit(rc);
    for (int i = a.size() / 2; i < a.size(); i++) sum2 += a[i];

    // Wait until the thread finishes and capture its return value.
    rc = pthread_join(thread, (void**)&sum1);
    if (rc) cout << "Cannot join thread", exit(rc);

    //START ROBERT ADDED
    cout << "sum1 is: " << sum1 << " sum2 is: " << sum2 << "\n";
    //END ROBERT ADDED
    return sum1 + sum2;
}

// Test vectors
int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 100, 200, 300, 400};
vector<int> a(array, array + 10);
vector<int> b(array + 10, array + 14);
vector<int> c;
vector<int> d(20000, 7);

int main() {
    assert(sum_vector(a) == 55);
    assert(sum_vector(b) == 1000);
    assert(sum_vector(c) == 0);
    assert(sum_vector(d) == 140000);
    cout << "All tests passed with values\n";

/* START ROBERT ADDED
    cout << "a is: "; 
    for (int i = 0; i < a.size(); i++ ) {
    cout << a[i] << ","; //Could you a.at(0)
    }
    cout << "\n";

    cout << "b is: "; 
    for (int i = 0; i < b.size(); i++ ) {
    cout << b[i] << ","; //Could you a.at(0)
    }
    cout << "\n";

        cout << "c is: "; 
    for (int i = 0; i < c.size(); i++ ) {
    cout << c[i] << ","; //Could you a.at(0)
    }
    cout << "\n";

/*
    cout << "d is: "; 
    for (int i = 0; i < d.size(); i++ ) {
    cout << d[i] << ","; //Could you a.at(0)
    }
    cout << "\n";
    END ROBERT ADDED*/
}