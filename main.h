#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>
#include "sync.h"

int c = 0;
int numThreads;
int numItterations;
int testID;
pthread_mutex_t count_mutex;
pthread_spinlock_t count_spin;
my_mutex_t my_count_mutex;
my_spinlock_t my_spinlock;

unsigned long long timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

