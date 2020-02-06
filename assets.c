#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <stdint.h>

double kb = 1000.0;
double mb = 1000000.0;
double gb = 1000000000.0;

void error(char *report){
	perror(report);
	exit(1);
}

double now(){
	//making time more precise using clock_gettime()
	//takes on average 1.6microseconds to get time;
	uint64_t nano = 1000000000;
	struct timespec tt;

	clock_gettime( CLOCK_MONOTONIC, &tt ); //CLOCK_MONOTONIC_RAW, will take 1.7microseconds to get time
	uint64_t ntime = (tt.tv_sec * nano) + tt.tv_nsec;
	return (double) ntime/nano;
}

long int filesize(const char *filename){
	struct stat fstats;
	//getting file sizes using stat()
	if ( stat(filename, &fstats) == 0 )
		return ( fstats.st_size );
	else{
		return -1;
	}
}

/*
void renderProgressBar(uint64_t current, uint64_t final){
	char load = '=';
	char nonload = '_';
	char *f = "";
	double ratio = (double) current/final;
	double perc = 100 * ratio;
}
*/

void ratioProgress(uint64_t curr_iter, uint64_t final_iter, double timeFrame){
	char space = ' ';
	char stdsize[9];
	char stdunit[9];
	double ave_rate;
	double curr_size;

	double pprog = 100 * ( (double) curr_iter/final_iter );
	
	if (timeFrame != 0.0){
		ave_rate = curr_iter/timeFrame;

		if (curr_iter > 10*kb && curr_iter < mb){
			curr_size = (double) curr_iter/kb;
			strcpy(stdsize, " Kb\0");
		} else if ( curr_iter > mb && curr_iter <gb ){
			curr_size = (double) curr_iter/mb;
			strcpy(stdsize, " Mb\0");
		} else if (curr_iter > gb){
			curr_size = (double) curr_iter/gb;
			strcpy(stdsize, " Gb\0");
		} else{
			curr_size = (double) curr_iter * 1;
			strcpy(stdsize, " Bytes\0");
		}

		if (ave_rate/kb > 10.0 && ave_rate/kb < kb){
			ave_rate = ave_rate/kb;
			strcpy(stdunit, " kb/s");
		} else if (ave_rate/mb > 1.0){
			ave_rate = ave_rate/mb;
			strcpy(stdunit, " mb/s\0");
		} else{
			strcpy(stdunit, " b/s\0");
		}

		printf("Transferring...|%cTime:%c%.2lfsecs...|%cStatus:%c%.2lf%%...|%cCurrent%cSize%c%.3lf%s...|%cRate:%c%.2lf%s...|%c",
				space, space, timeFrame, space, space, pprog,
				space, space, space, curr_size, stdsize,
				space, space, ave_rate, stdunit, space);
		printf("\r");
		fflush(stdout);
	}
}

void beamRate(uint64_t nbytes, double ntime){
	double rate;
	if (ntime != 0.0){
		printf("[+] Data Transfer: %ld Bytes. Average Time Taken: %lf seconds\n", nbytes, ntime);
		rate = nbytes/ntime;
		if ( rate/kb > 10.0 && rate/kb < kb )
			printf("[+] Average Transfer Rates: %.2f kb/s\n", rate/kb);
		else if ( rate/mb > 1.0 )
			printf("[+] Average Transfer Rates: %.2f mb/s\n", rate/mb);
		else if ( rate/gb > 1.0 )
			printf("[+] Average Transfer Rates: %.2f gb/s\n", rate/gb);
		else
			printf("[+] Average Transfer Rates: %.2f bytes/s\n", rate);
	} else{
		printf("[+] Average Transfer Rates: inf [near instantaneous]\n");
	}
}
