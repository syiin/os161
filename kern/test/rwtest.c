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
#define NTHREADS 32
#define RWLOOPS 3

//static struct rwlock *testrwlock = NULL;

//static 
//void
//rwtestthread(void *junk, unsigned long num)
//{
//	int i;
//
//	for (i=0; i<RWLOOPS; i++)
//	{
//		rwlock_acquire_read(testrwlock);
//	}
//}

int 
rwtest(int nargs, char **args) 
{
	(void)nargs;
	(void)args;

	int i;
	struct rwlock * test_rw; 

	kprintf_n("Starting rwt2...\n");
	for (i = 0; i < CREATELOOPS; i++)
	{
		kprintf_t(".");
		//create rwlock
		test_rw = rwlock_create("test_rwlock");
		if(test_rw == NULL)
		{
			panic("rwtest: rwlock_create failed\n");
		}
		else
		{
			kprintf_n("rw locks successfully created\n");
		}
	}

//	for (i = 0; i < CREATELOOPS; i++)
//	{
//		kprintf_t(".");
//		result = thread_fork("rwtest", NULL, );
//	}
 
	success(TEST161_FAIL, SECRET, "rwt1");

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
