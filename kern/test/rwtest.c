/*
 * All the contents of this file are overwritten during automated
 * testing. Please consider this before changing anything in this file.
 */

#include <types.h>
#include <lib.h>
#include <clock.h>
#include <thread.h>
#include <synch.h>
#include <test.h>
#include <kern/test161.h>
#include <spinlock.h>
/*
 * Use these stubs to test your reader-writer locks.
 */

#define CREATELOOPS 8
#define NREADERTHREADS 50
#define NWRITERTHREADS 50
#define NLOOPS 8
#define RWLOOPS 3

struct spinlock status_lock;
static bool test_status = TEST161_FAIL;
static volatile unsigned long testval1;
static volatile unsigned long testval2;
static volatile unsigned long testval3;

static struct semaphore *donesem;
static struct rwlock *test_rw = NULL;

static
bool
failif(bool condition){
  if (condition){
    spinlock_acquire(&status_lock);
    test_status = TEST161_FAIL;
    spinlock_release(&status_lock);
  }
  return condition;
}

static 
void
readtestthread(void *junk1, unsigned long num){
  //acquire the read lock and check that shared critical section was not mutated unexpectedly
  //along the way. 
	(void)junk1;
	(void)num;

  unsigned i;
  random_yielder(4);

	rwlock_acquire_read(test_rw);
  for (i=0; i < NLOOPS; i++){
    kprintf_t(".");
    
    failif(testval2 != testval1 * testval1);
    random_yielder(4);

    failif(testval2%3 != (testval3*testval3)%3);
    random_yielder(4);

    failif(testval3 != testval1%3);
    random_yielder(4);
  }

	rwlock_release_read(test_rw);
  V(donesem);
	return;
}

static 
void
writetestthread(void *junk, unsigned long num){
  //mutate testval1 as a shared critical section and yield the CPU. check that the value
  //is what was expected - ie. was not mutated outside of this function.
	(void)junk;

  unsigned i;

  random_yielder(4);

	rwlock_acquire_write(test_rw);
  for (i=0; i < NLOOPS; i++){
    kprintf_t(".");
    testval1 = num;
    testval2 = num*num;
    testval3 = num%3;

    random_yielder(4);
    failif(rwtest->readers_in != 0);

    testval1 = num*num;
    random_yielder(4);
    failif(testval1 != testval2);

    testval1 = num%3;
    random_yielder(4);
    failif(testval1 != testval3);

    testval1 = num;
    random_yielder(4);
    failif(testval1 != num);

    random_yielder(4);
    failif(rwtest->readers_in != 0);
  }
	rwlock_release_write(test_rw);
  kprintf_t("writer out: %u\n", num);
  V(donesem);
}

int 
rwtest(int nargs, char **args) 
{
	(void)nargs;
	(void)args;

	int i, result;
<<<<<<< HEAD

	kprintf_n("Starting rwt1...\n");
	kprintf_t(".");
	
	//Test rwlock_create()
	test_rw = rwlock_create("test_rwlock");
	if(test_rw == NULL)
	{
		panic("rwtest1: rwlock_create failed\n");
	}
	else
	{
		kprintf_n("rw locks successfully created\n");
	}

  //single read acquire and release
  rw_lock_acquire(test_rw);
  rw_lock_release(test_rw)
	
  //multiple read acquires
	for (i=0; i < NTHREADS; i++)
	{
		kprintf_t(".");
		result = thread_fork("synchtest", NULL, rwlocktestthread, NULL, i);
		if (result) {
			panic("rwtest1: thread_fork failed: %s\n",
				strerror(result));
		}
	}

  //release without holding
  rwlock_release_write(test_rw);
	
  //single acquire write
	rwlock_acquire_write(test_rw);
	rwlock_release_write(test_rw);

	rwlock_destroy(test_rw);
	test_rw = NULL;

	kprintf_t("\n");
	success(TEST161_SUCCESS, SECRET, "rwt1");
=======
  unsigned long num = 9;

  testval1 = num;
  testval2 = num*num;
  testval3 = num%3;
  
  kprintf_n("Starting rwt1...\n");
  for (i=0; i<CREATELOOPS; i++){
    kprintf_t(".");
    rwtest = rwlock_create("rwtest"); //try to create reader-writer lock
    if (rwtest==NULL){
      panic("rwt1: rwlock_create failed\n");
    }

    donesem = sem_create("donesem", 0); //try to create a done semaphore
    if (donesem == NULL){
      panic("rwt1: sem_create failed\n");
    }

    if (i != CREATELOOPS-1){ //clean up we error out early
      rwlock_destroy(rwtest);
      sem_destroy(donesem);
    }
  }

  spinlock_init(&status_lock); 
  test_status = TEST161_SUCCESS;

  for (i=0; i<NREADERTHREADS; i++){
    kprintf_t(".");
    result = thread_fork("reader", NULL, readtestthread, NULL, i); //test readers
    if (result){
      panic("rwt1: thread_fork failed: %s\n", strerror(result));
    }
  }

  for (i=0; i<NWRITERTHREADS; i++){
    kprintf_t(".");
    result = thread_fork("reader", NULL, writetestthread, NULL, i); //test writer
    if (result){
      panic("rwt1: thread_fork failed: %s\n", strerror(result));
    }
  }

  for (i=0; i<(NREADERTHREADS+NWRITERTHREADS);i++){
    kprintf_t(".");
    P(donesem);
  }

  rwlock_destroy(rwtest);
  rwtest= NULL;
  sem_destroy(donesem);
  donesem=NULL;

  kprintf_t("\n");
  success(test_status, SECRET, "rwt1");
>>>>>>> d81e70aa88e43de23ab8a6d6a29289b13898bcef

	return 0;
}

int rwtest2(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt2 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt2");

	return 0;
}

int rwtest3(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt3 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt3");

	return 0;
}

int rwtest4(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt4 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt4");

	return 0;
}

int rwtest5(int nargs, char **args) {
	(void)nargs;
	(void)args;

	kprintf_n("rwt5 unimplemented\n");
	success(TEST161_FAIL, SECRET, "rwt5");

	return 0;
}
