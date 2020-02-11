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
#include <limits>
#include <vector>

int main()
{
    const unsigned int size = 4294967295;
    //const unsigned int size = 50000;
    unsigned int i, j, value, counter;
    std::vector<bool> sieve(size);
    //std::bitset<size> sieve;

    sieve.flip();

    //preform sieve of eratsothenes
    unsigned int finalBit = sqrt (sieve.size() ) + 1;

    for (i=2; i < finalBit; i++)
        if (sieve.at(i))
            for (j = 2*i; j<size; j+=i)
                sieve.at(j) = false;
    
    //cout << "The prime numbers in the range 2 to 4294967295 are:\n";
    cout << "The prime numbers in the range 2 to 967295 are:\n";

    for (i=2, counter =0; i<size; ++i)
        if(sieve.at(i)){
            cout << setw(8) << i;

            if (++counter % 8 == 0)
                cout << '\n';
        }

    cout << endl;

    //get a value form the user to determine if it is prime
    //SKIPPING THIS AND NOT TYPING IT signed bob

}