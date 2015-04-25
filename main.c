#include "main.h"
#include "sync.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void *fnC()
{
    int i;
    for(i=0;i<1000000;i++)
    {   
        c++;
    }   
}

pthread_mutex_t count_mutex;


void *pthreadMutexTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	pthread_mutex_lock(&count_mutex);
	c++;
	pthread_mutex_unlock(&count_mutex);    
	
    }   


}

void *pthreadSpinTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	 pthread_spin_lock(&count_spin);
	c++;
	 pthread_spin_unlock(&count_spin);    
	
    }   


}

void *myMutexTASTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	//my_mutex_lockTAS(&my_count_mutex); //testing and locking this thread twice
	my_mutex_lockTAS(&my_count_mutex);
	c++;
	my_mutex_unlock(&my_count_mutex);
    }
}

void *myMutexTTASTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	//my_mutex_lockTTAS(&my_count_mutex); //testing and locking this thread twice
	my_mutex_lockTTAS(&my_count_mutex);
	c++;
	my_mutex_unlock(&my_count_mutex);
    }
}

void *mySpinlockTASTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	//my_spinlock_lockTAS(&my_spinlock); //testing and locking this thread twice
	my_spinlock_lockTAS(&my_spinlock);
	c++;
	my_spinlock_unlock(&my_spinlock);
    }
}

void *mySpinlockTTASTest()
{
    int i;
    for(i=0;i<numItterations;i++)
    { 
	//my_spinlock_lockTTAS(&my_spinlock); //testing and locking this thread twice
	my_spinlock_lockTTAS(&my_spinlock);
	c++;
	my_spinlock_unlock(&my_spinlock);
    }
}


int runTest(int testID)
{

/*You must create all data structures and threads for you experiments*/
struct timespec start;
	struct timespec stop;
	unsigned long long result; //64 bit integer

	pthread_t *threads = (pthread_t* )malloc(sizeof(pthread_t)*numThreads);	
	int i;
	int rt;

if (testID == 0 || testID == 1 ) /*Pthread Mutex*/
{
	c=0;
	pthread_mutex_init(&count_mutex,0);
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &pthreadMutexTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run MyPthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread Mutex time(ms): %llu\n",result/numItterations);
	
}

if(testID == 0 || testID == 2) /*Pthread Spinlock*/
{
	c=0;
	pthread_spin_init(&count_spin, 0);
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &pthreadSpinTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run MyPthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("Pthread SpinMutex time(ms): %llu\n",result/numItterations);

}

if(testID == 0 || testID == 3) /*MySpinlockTAS*/
{
	c=0;
	my_spinlock_t my_spinlock;
	my_spinlock_init(&my_spinlock);
	

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &mySpinlockTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("MySpinTAS time(ms): %llu\n",result/numItterations);
}

if(testID == 0 || testID == 4){
	c=0;
	my_spinlock_t my_spinlock;
	my_spinlock_init(&my_spinlock);
	

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &mySpinlockTTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("MySpinTTAS time(ms): %llu\n",result/numItterations);

}
if(testID == 0 || testID == 5){
	c=0;
	my_mutex_t my_count_mutex;
	my_mutex_init(&my_count_mutex);
	

	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &myMutexTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("MyMutexTAS time(ms): %llu\n",result/numItterations);

}
if(testID == 0 || testID == 6){
	c=0;
	my_mutex_t my_count_mutex;
	my_mutex_init(&my_count_mutex);
	clock_gettime(CLOCK_MONOTONIC, &start);
	for(i=0;i<numThreads;i++)
	{
	
	 if( rt=(pthread_create( threads+i, NULL, &myMutexTTASTest, NULL)) )
	{
		printf("Thread creation failed: %d\n", rt);
		return -1;	
	}
	
	}
	
	for(i=0;i<numThreads;i++) //Wait for all threads to finish
	{
		 pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &stop);

	printf("Threaded Run Pthread (Mutex) Total Count: %d\n", c);
	result=timespecDiff(&stop,&start);
	printf("MyMutexTTAS time(ms): %llu\n",result/numItterations);


}

	return 0;
}

int testAndSetExample()
{
volatile long test = 0; //Test is set to 0
printf("Test before atomic OP:%li\n",test);
tas(&test);
printf("Test after atomic OP:%li\n",test);
}

int processInput(int argc, char *argv[])
{

/*testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS*/
	/*You must write how to parse input from the command line here, your software should default to the values given below if no input is given*/
	



if (argc>1)
	{
		char *token;
		int i;
		int j=0;
		char *arguments[3];
		for (i=1; i<argc;i++)
		{
			token=strtok(argv[i],"-");
			arguments[j]=token;
			j++;
		}

		numThreads=atoi(arguments[0]);
		numItterations=atoi(arguments[1]);
		testID=atoi(arguments[2]);
	}

	else
	{
		numThreads=4;
		numItterations=1000000;
		testID=0;
	}
	return 0;
}


int main(int argc, char *argv[])
{
	printf("Usage of: %s -t #threads -i #itterations -d testid\n", argv[1]);
	printf("testid: 0=all, 1=pthreadMutex, 2=pthreadSpinlock, 3=mySpinLockTAS, 4=mySpinLockTTAS, 5=myMutexTAS, 6=myMutexTTAS\n");	
	
	

	processInput(argc,argv);
	runTest(testID);
	return 0;

}
