#ifndef __BEAM__
#define __BEAM__

#define SERVERPORT 12120
#define MAX_CONN 5

#define BUFFSIZE 8192

#define DEFAULT_OUT_ROOT "/root/Downloads/"
#define DEFAULT_OUT_NON_ROOT "$HOME/Downloads/"

long int now();
void beamRate(double nbytes, double ntime);
void error(char *report);
void statusProgress(long int dataInflow, long int timeFrames);
void BeamServer(char *filepath, char *server_ip);
void BeamClient(char *filedest, char *server_ip);

#endif //__BEAM__
