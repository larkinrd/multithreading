/*****************************************************************************
* https://cs.lmu.edu/~ray/notes/trivialcpexamples/
* TO COMPILE USE: g++ -pthread <filename.cpp> -o <outputfilename>
* RESULTED IN: Segmentation fault when executing
* 
* trinary.cpp
*
* This program illustrates three simple threads running concurrently: one that
* writes zeros, one that writes ones, and one that writes twos.  Each thread
* writes to standard output.  The result should be a large trinary number.
*
*****************************************************************************
* pthread_create (thread, attr, start_routine, arg) 
** thread: - An opaque, unique identifier for the new thread returned by the subroutine.
* attr      An opaque attribute object that may be used to set thread attributes. You can specify a 
*           thread attributes object, or NULL for the default values.
* start_routine - The C++ routine that the thread will execute once it is created.
* arg -     A single argument that may be passed to start_routine. It must be passed by reference as
*           a pointer cast of type void. NULL may be used if no argument is to be passed.
*****************************************************************************/

#include <iostream>
#include <pthread.h>
#include <thread> //for std::this_thread
#include <mutex>
#include <chrono>

using namespace std;
std::mutex mymutex;

void* print_zeros(void* ignored) {
    
    for (int i = 0; i < 10; i++) {
        mymutex.lock();
        cout << '0';
        mymutex.unlock();
        //std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    //START ROBERT ADDED
    
    cout << "\n\n===============END OF ZEROS================\n\n";
    //END ROBERT ADDED
    return NULL;
}

void* print_ones(void* ignored) {
    for (int i = 0; i < 10; i++) {
        mymutex.lock();
        cout << '1';
        mymutex.unlock();
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    //START ROBERT ADDED
    cout << "\n\n===============END OF ONES================\n\n";
    //std::this_thread::sleep_for (std::chrono::seconds(5));
    //END ROBERT ADDED
    return NULL;
}

int main() {
    pthread_t zero_thread;
    pthread_t one_thread;


    // Create two threads and run them immediately
    int rc = pthread_create(&zero_thread, NULL, &print_zeros, NULL);
    if (rc) cout << "Cannot create the zero-writing thread", exit(rc);
    rc = pthread_create(&one_thread, NULL, &print_ones, NULL);
    if (rc) cout << "Cannot create the one-writing thread", exit(rc);

    // Run this in parallel with the other two threads
    for (int i = 0; i < 15; i++) {
        mymutex.lock();
        cout << '2';
        mymutex.unlock();
    }

    //START ROBERT ADDED
    cout << "\n\n===============END OF TWOS================\n\n";
    //END ROBERT ADDED
    
    // Wait for the other two threads to finish
    int result = 0;
    rc = pthread_join(zero_thread, (void**)&result);
    
    if (rc) {
        mymutex.lock();
        cout << "Cannot join the zero-writing thread";
        //cout << "\n\n\nrc is: " << rc << "\n\n\n";
        exit(rc);
        mymutex.lock();
    }
    
    //cout << "\n\n\nrc is: " << rc << "\n\n\n";
    rc = pthread_join(one_thread, (void**)&result);
    
    if (rc) {
        mymutex.lock();
        cout << "Cannot join the one-writing thread"; 
        //cout << "\n\n\nrc is: " << rc << "\n\n\n";
        exit(rc);
        mymutex.unlock();
    }

    //std::this_thread::sleep_for (std::chrono::seconds(5));
    //pthread_exit(NULL);
    

    return result;
    
}