#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double kb = 1000.0;
double mb = 1000000.0;
double gb = 1000000000.0;

void error(char *report){
	perror(report);
	exit(1);
}

long int now(){
	//returns raw time in seconds
	long int tt = time((time_t *)0);
	return tt;
}

void statusProgress(long int dataInflow, long int timeFrames){
	double dataSize, instRate;
	char *s_units, *r_units;
	double timeFrame = (double) timeFrames;
	if (timeFrame == 0){
		dataSize = dataInflow;
		s_units = "bytes";
		r_units = "bytes/s";
		instRate = 0.0;
	}
	else if (timeFrame != 0){
		instRate = (dataInflow)/(timeFrame);
		if (dataInflow > 10.0 * kb && dataInflow < mb){
			dataSize = dataInflow/kb;
			s_units = "Kb";
		} else if (dataInflow > mb && dataInflow < gb){
			dataSize = dataInflow/mb;
			s_units = "Mb";
		} else if (dataInflow > gb){
			dataSize = dataInflow/gb;
			s_units = "Gb";
		} else{
			dataSize = dataInflow;
			s_units = "Bytes";
		}

		if (instRate/kb > 10.0 && instRate/kb < kb){
			instRate = instRate/kb;
			r_units = "kb/s";
		} else if (instRate/mb > 1.0){
			instRate = instRate/mb;
			r_units = "mb/s";
		} else if (instRate/kb < 10.0){
			r_units = "bytes/s";
		}

		printf("[Status: Time Taken:\t%.3f\t\bsecs\t\t\tSize:\t%.3f\t%s\t\t\tRates:\t%.2f\t%s", timeFrame, dataSize, s_units, instRate, r_units);
		printf("\r");
		fflush(stdout);
	}
}

void beamRate(double nbytes, double ntime){
	double rate;
	if (ntime != 0.0){
		//printf("ALL GOOD %f in time %f\n", nbytes, ntime);
		rate = nbytes/ntime;
		if ( rate/kb > 10.0 && rate/kb < kb )
			printf("[+] Average Beaming Rates: %.2f kb/s\n", rate/kb);
		else if ( rate/mb > 1.0 )
			printf("[+] Average Beaming Rates: %.2f mb/s\n", rate/mb);
		else
			printf("[+] Average Beaming Rates: %.2f bytes/s\n", rate);
	} else{
		printf("[+] Average Beaming Rates: inf [near instantaneous]\n");
	}
}
