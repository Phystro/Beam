#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void error(char *report){
	perror(report);
	exit(1);
}

long int now(){
	//returns raw time in seconds
	long int tt = time((time_t *)0);
	return tt;
}

void beamRate(double nbytes, double ntime){
	double kb = 1000.0;
	double mb = 1000000.0;
	double rate;
	if (ntime != 0.0){
		//printf("ALL GOOD %f in time %f\n", nbytes, ntime);
		rate = nbytes/ntime;
		if ( rate/kb > 10.0 && rate/kb < kb )
			printf("[+] Beaming Rates: %.00f kb/s\n", rate/kb);
		else if ( rate/mb > 1.0 )
			printf("[+] Beaming Rates: %.00f mb/s\n", rate/mb);
		else
			printf("[+] Beaming Rates: %.00f bytes/s\n", rate);
	} else{
		printf("[+] Beaming Rates: inf [near instantaneous]\n");
	}
}
