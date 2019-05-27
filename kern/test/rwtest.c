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
#define NTHREADS 3
#define RWLOOPS 3

static struct rwlock *test_rw = NULL;

static 
void
rwlocktestthread(void *junk, unsigned long num)
{
	(void)junk;
	(void)num;

	rwlock_acquire_read(test_rw);
	rwlock_release_read(test_rw);
	return;
}

int 
rwtest(int nargs, char **args) 
{
	(void)nargs;
	(void)args;

	int i, result;

	kprintf_n("Starting rwt1...\n");
	kprintf_t(".");
	
	//create rwlock
	test_rw = rwlock_create("test_rwlock");
	if(test_rw == NULL)
	{
		panic("rwtest1: rwlock_create failed\n");
	}
	else
	{
		kprintf_n("rw locks successfully created\n");
	}
	
	for (i=0; i < NTHREADS; i++)
	{
		kprintf_t(".");
		result = thread_fork("synchtest", NULL, rwlocktestthread, NULL, i);
		if (result) {
			panic("rwtest1: thread_fork failed: %s\n",
				strerror(result));
		}
	}

	for (i=0; i<NTHREADS; i++) {
		rwlock_release_read(test_rw);
	}

	rwlock_destroy(test_rw);
	test_rw = NULL;

	kprintf_t("\n");
	success(TEST161_SUCCESS, SECRET, "rwt1");

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
