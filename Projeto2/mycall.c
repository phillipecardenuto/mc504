#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/time.h>
#include <asm/time.h>
	

asmlinkage long sys_mycall( unsigned long int begin , unsigned long int end) {
	long int timeu ;
	/*ITERVAL ERROR*/
	if (end <= begin)
		return -1;
	struct timeval time;
	do_gettimeofday(&time);
	timeu = time.tv_usec;
	/*ERROR TIMEU*/
	if (timeu < 0)
		return -2;
	timeu = timeu % end;
	return timeu*(end - begin)/end + begin;
}
