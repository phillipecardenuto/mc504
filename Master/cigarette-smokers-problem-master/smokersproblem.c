/*

  The Cigarette Smokers' Problem

*/

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* semaphors for agents and pushers */
sem_t agentSem, tobacco, paper, match;
sem_t tobaccoSem, paperSem, matchSem, mutex;

/* booleans for items on table */
int isTobacco = 0;
int isPaper = 0;
int isMatch = 0;

void *agent(void *arg) {
  int i;
  int id = *(int*) arg;
  if(id == 1) {
    for(i = 0; i < 6; ++i) {
      usleep(rand() % 200001);
      sem_wait(&agentSem);
      printf("Agent  %d is placing Tobacco and Paper...\n", id);
      sem_post(&tobacco);
      sem_post(&paper);
    }
  }
  else if (id == 2) {
    for (i = 0; i < 6; ++i) {
      usleep(rand() % 200001);
      printf("Agent  %d is placing Paper and Matches...\n", id);
      sem_wait(&agentSem);
      sem_post(&paper);
      sem_post(&match);
    }
  }
  else {
    for (i = 0; i < 6; ++i) {
      usleep(rand() % 200001);
      printf("Agent  %d is placing Matches and Tobacco...\n", id);
      sem_wait(&agentSem);
      sem_post(&match);
      sem_post(&tobacco);
    }
  }
}

void *pusher(void *arg) {
  int i;
  int id = *(int*) arg;
  if (id == 1) {
    for (i = 0; i < 12; ++i) {
      sem_wait(&tobacco);
      sem_wait(&mutex);
      if (isPaper) {
        isPaper = 0;
        sem_post(&matchSem);
      }
      else if (isMatch) {
        isMatch = 0;
        sem_post(&paperSem);
      }
      else {
        isTobacco = 1;
      }
   
    sem_post(&mutex);
    }
  }
  else if (id == 2) {
    for (i =0; i < 12; ++i) {
      sem_wait(&match);
      sem_wait(&mutex);
      if (isTobacco) {
        isTobacco = 0;
        sem_post(&paperSem);
      }
      else if (isPaper) {
	isPaper = 0;
	sem_post(&tobaccoSem);
      }
      else {
        isMatch = 1;
      }
 
      sem_post(&mutex);
    }
  }
  else {
    for (i =0; i < 12; ++i) {
      sem_wait(&paper);
      sem_wait(&mutex);
      if (isMatch) {
        isMatch = 0;
        sem_post(&tobaccoSem);
      }
      else if (isTobacco) {
        isTobacco = 0;
        sem_post(&matchSem);
      }
      else {
        isPaper = 1;
      }
      sem_post(&mutex);
    }
  }
}

void *smoker(void *arg) {
  int i;
  int id = *(int*) arg;
  if (id % 3 == 0) {
    for (i = 0; i < 3; ++i) {
      printf("Smoker %d is waiting on Paper and Matches...\n", id);
      sem_wait(&tobaccoSem);
      printf("Smoker %d is making a cigarette\n", id);
      sem_post(&agentSem);
      printf("Smoker %d is smoking...\n", id);
      usleep(rand() % 500000);
    }
  }
  else if (id % 3 == 1) {
    for (i = 0; i < 3; ++i) {
      printf("Smoker %d is waiting on Matches and Tobacco...\n", id);
      sem_wait(&paperSem);
      printf("Smoker %d is making a cigarette\n", id);
      sem_post(&agentSem);
      printf("Smoker %d is smoking...\n", id);
      usleep(rand() % 500000);
    }
  }
  else {
    for (i = 0; i < 3; ++i) {
      printf("Smoker %d is waiting on Tobacco and Paper...\n", id);
      sem_wait(&matchSem);
      printf("Smoker %d is making a cigarette\n", id);
      sem_post(&agentSem);
      printf("Smoker %d is smoking...\n", id);
      usleep(rand() % 500000);
    }
  }

} 
        
int main(int argc, char* argv[]) {
  
  int index;

  pthread_t smokers[6];
  pthread_t pushers[3];
  pthread_t agents[3];

  srand(time(NULL));

  /* Initialize semaphores for agents */
  sem_init(&agentSem, 0, 1);
  sem_init(&tobacco, 0, 0);
  sem_init(&paper, 0, 0);
  sem_init(&match, 0, 0);

  /* Initialze semaphores for pushers */
  sem_init(&mutex, 0, 1);
  sem_init(&tobaccoSem, 0, 0);
  sem_init(&paperSem, 0, 0);
  sem_init(&matchSem, 0, 0);

  
  /* create smoker threads */
  int smokerID[6];
  for (index = 1; index <= 6; ++index) {
    smokerID[index] = index;
    pthread_create(&smokers[index], NULL, smoker, &smokerID[index]);
  }
  
  /* create pusher threads */
  int pusherID[3];
  for (index = 1; index <= 3; ++index) {
    pusherID[index] = index;
    pthread_create(&pushers[index], NULL, pusher, &pusherID[index]);
  }

  /* create agent threads */
  int agentID[3];
  for (index = 1; index <= 3; ++index) {
    agentID[index] = index;
    pthread_create(&agents[index], NULL, agent, &agentID[index]);
  }
 
  /* wait for smokers to finish */ 
  for (index = 1; index <= 6; ++index)
    pthread_join(smokers[index], NULL);
  
  return 0;
}
