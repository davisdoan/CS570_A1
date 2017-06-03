#include <iostream>
#include <fstream>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
using namespace std;

#define N 7

void *worker_thread(void *arg)
{
    printf("This is worker_thread()\n");
    pthread_exit(NULL);
}

int main(){
    cout << "Hello World";
    ofstream file; //creates file stream 
    int myPid;
    myPid = getpid(); // grab pid
    file.open("QUOTE.txt");
    file <<  myPid; // write pid to the file
    file.close();

    // create semaphore
    sem_t mySemaphore;
    sem_init(&mySemaphore, 0, 1); // (your semaphore, [zero is local], initialized semaphore value

    // create 7 threads
    pthread_t my_thread[N]; // create array of 7 threads
    
    printf("in main: creating thread \n");
    
    long id;
    for(id=1; id <=N; id++){
      int ret = pthread_create(&my_thread[id],NULL, &worker_thread, (void*)id);
      if(ret != 0) {
          printf("Error: pthread_Create() failed!\n");
          exit(EXIT_FAILURE);
       }   
     }

   pthread_exit(NULL);

    return 0;
}
