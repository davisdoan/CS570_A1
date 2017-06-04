#include <iostream>
#include <fstream>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define N 7

void *worker_thread(void *arg)
{
    printf("This is worker_thread()\n");
    //open the quote file and write threads id followed by "THE QUOTE"(followed by carriage return and NEWLINE)
     //FILE *fp=fopen("QUOTE.TXT", "a");
//     file.open("QUOTE.txt");
     // get the thread id
     
     ofstream file;
     long threadId;
     
     // quotes
     char evenQuote[100]="Controlling complexity is the essence of computer programming. --Brian Kernigan";     
     char oddQuote[150]="Computer science is no more about computers than astronomy is about telescopes. --Edsger Dikstra";
     
     threadId = (long)arg;


     
     file.open("QUOTE.txt", std::ios_base::app);
     
     // if even
     if(threadId % 2 == 0){
       file << "Thread id " << threadId << " " << evenQuote << "\r\n";
     } else {
       file << "Thread id " << threadId << " " << oddQuote <<  "\r\n";
     }
     // if odd

     file.close();

     //write to the console "Thread <id> is running" followed by a new line
    //close the quote.txt file
    //release the semaphore flag
    //repeat the above 7 times
    pthread_exit(NULL);
}

int main(){
    cout << "Hello World";
    ofstream file; //creates file stream 
    int myPid;
    myPid = getpid(); // grab pid
    file.open("QUOTE.txt");
    file << "Your Process PID is " <<  myPid << "\r\n"; // write pid to the file
    file.close();

    // create semaphore
    sem_t mySemaphore;
    sem_init(&mySemaphore, 0, 1); // (your semaphore, [zero is local], initialized semaphore value

    // create 7 threads
    pthread_t my_thread[N]; // create array of 7 threads
    
    printf("in main: creating thread \n");
    
   // initialize thread attribute
   pthread_attr_t myAttr;
   pthread_attr_init(&myAttr);
   pthread_attr_setdetachstate(&myAttr, PTHREAD_CREATE_JOINABLE);

   long id;
    for(id=1; id <=N; id++){
      //make the seven threads 
      int ret = pthread_create(&my_thread[id], &myAttr, &worker_thread, (void*)id);
//      pthread_join(&my_thread[id],NULL);
      if(ret != 0) {
          printf("Error: pthread_Create() failed!\n");
          exit(EXIT_FAILURE);
       }   
     }

   // free resources used by the attribute
   pthread_attr_destroy(&myAttr); 

   // join all the threads
   void *status; 
   for(id=1; id <=N; id++){
       pthread_join(my_thread[id],&status);
   }
   
   // semaphore destroy
   sem_destroy(&mySemaphore); 
   
   // exit gracefully
   printf("Job Completed, bye!\n");
   pthread_exit(NULL);
    return 0;
}
