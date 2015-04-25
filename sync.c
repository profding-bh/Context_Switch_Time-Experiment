/*
 * NAME, etc.
 *
 * sync.c
 *
 */

#define _REENTRANT
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include "sync.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Spinlock routines
 */

int my_spinlock_init(my_spinlock_t *mutex)
{
    mutex=(my_spinlock_t *)malloc(sizeof(my_spinlock_t *));
    mutex->state=0;
    mutex->counter=0;
    mutex->tid=pthread_self();
    mutex->ptid=pthread_self();
    return 0;
}

int my_spinlock_destroy(my_spinlock_t *mutex)
{
    	free(mutex);
	return 0;
}

int my_spinlock_unlock(my_spinlock_t *mutex)
{
    mutex->counter=0;
    mutex->tid=mutex->ptid;
    mutex->state=0; //unlock
    return 0;
}

int my_spinlock_lockTAS(my_spinlock_t *mutex)
{   
	while(1){
	    if(mutex->counter==0){
		while(tas(&mutex->state)){};
		mutex->counter++;
		mutex->tid=pthread_self();
		return 0;
		}
	     else if(mutex->tid==pthread_self()){
		return 0;
		}
	}
	return -1;
}


int my_spinlock_lockTTAS(my_spinlock_t *mutex)
{
	while(1){
	    if(mutex->counter==0){
		while(mutex->state==1){};
		if(tas(&mutex->state)==0){
			mutex->counter++;
			mutex->tid=pthread_self();
			return 0;
			}
		}
	     else if(mutex->tid==pthread_self()){
		return 0;
		}
	}
	return -1;
}

int my_spinlock_trylock(my_spinlock_t *mutex)
{
	if(mutex->state==0){
		if(tas(&mutex->state)==0){
			mutex->counter++;
			mutex->tid=pthread_self();
		}
		return 0;
	}
		return -1;
}
/*
 * Mutex routines
 */

int my_mutex_init(my_mutex_t *mutex)
{
    mutex=(my_mutex_t *)malloc(sizeof(my_mutex_t *));
    mutex->state=0;
    mutex->counter=0;
    mutex->tid=pthread_self();
    mutex->ptid=pthread_self();
    return 0;
}

int my_mutex_destroy(my_mutex_t *mutex)
{
    free(mutex);
    return 0;
}

int my_mutex_unlock(my_mutex_t *mutex)
{
    mutex->counter=0;
    mutex->tid=mutex->ptid;
    mutex->state=0; //unlock
    return 0;
}

int my_mutex_lockTAS(my_mutex_t *mutex)
{  
    useconds_t delay=10000;
    while(1){
        if(mutex->counter==0){
		while(tas(&mutex->state)){};
		mutex->counter++;
		mutex->tid=pthread_self();
		return 0;
		}
	     else if(mutex->tid==pthread_self()){
		return 0;
		}
        usleep(rand()%delay);
        if(delay<40000)
            delay=2*delay;
        }
    return -1;
}


int my_mutex_lockTTAS(my_mutex_t *mutex)
{  
    useconds_t delay=10;
    while(1){
        if(mutex->counter==0){
		while(mutex->state==1){};
		if(tas(&mutex->state)==0){
			mutex->counter++;
			mutex->tid=pthread_self();
			return 0;
			}
		}
	     else if(mutex->tid==pthread_self()){
		return 0;
		}
        usleep(rand()%delay);
        if(delay<40)
            delay=2*delay;
        }
   return -1;
}

int my_mutex_trylock(my_mutex_t *mutex)
{	if(mutex->state==0){
		if(tas(&mutex->state)==0){
			mutex->counter++;
			mutex->tid=pthread_self();
		}
		return 0;
	}
		return -1;
}
