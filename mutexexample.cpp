// mutex::lock/unlock
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <math.h>

std::mutex mtx;           // mutex for critical section

void print_thread_id (int id, int totalthreads, int maxarray) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  
  std::cout << "thread #" << id << "\n\n";
  int maxouterloop = sqrt(maxarray);
  for (int i = 2; i<11; i++){
  mtx.lock();
    for (int j = 0; i*(j+id)<101; j+=totalthreads){
      std::cout << i*(j+id) << "\n";
    }
  //std::cout << c;
  
  mtx.unlock();
  }

  //std::cout << "\n\n===============END OF " << c << " ================\n\n";

}

int main ()
{
  int numthreads = 6; int mymaxarray = 103;
  std::thread threads[numthreads];
  // spawn 6 threads:
  for (int i=0; i<6; ++i)
    threads[i] = std::thread(print_thread_id,i+1,numthreads, mymaxarray);

  //std::cout << "prior to joining threads\n";

  for (auto& th : threads) th.join();

  //std::cout << "main done executing\n";

  /*
  int id1, id2, id3, id4;
  id1=1;id2=2;id3=3;id4=4;
  
  for (int i = 2; i<7; i++){
    std::cout << "For i: " << i << " :: ";
    for (int j = 0; i*j<101; j+=id4) {
      std::cout << i*(j+id1) << ";";
      std::cout << i*(j+id2) << ";";
      std::cout << i*(j+id3) << ";";
      std::cout << i*(j+id4) << "::";
    }
    std::cout << std::endl;
  }
    */
  
  

  return 0;
}