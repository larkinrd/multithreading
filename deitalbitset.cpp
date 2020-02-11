//fig 20.40 from deital and dietal third edition
//using bitset to demonstrate the sieve of erathosthenes

//Compiles and executes correctly

#include <iostream>

using std::cin;
using std::cout;

using std::endl;

#include <iomanip>

using std::setw;

#include <bitset>
#include <cmath>

int main()
{
    const int size = 1024;
    int i, value, counter;
    std::bitset<size> sieve;

    sieve.flip();

    //preform sieve of eratsothenes
    int finalBit = sqrt (sieve.size() ) + 1;

    for (i=2; i < finalBit; i++)
        if (sieve.test(i))
            for (int j = 2*i; j<size; j+=i)
                sieve.reset(j);
    
    cout << "The prime numbers in the range 2 to 1023 are:\n";

    for (i=2, counter =0; i<size; ++i)
        if(sieve.test(i)){
            cout << setw(5) << i;

            if (++counter % 12 == 0)
                cout << '\n';
        }

    cout << endl;

    //get a value form the user to determine if it is prime
    //SKIPPING THIS AND NOT TYPING IT signed bob

}