#ifndef __BEAM__
#define __BEAM__

#define SERVERPORT 12120
#define MAX_CONN 5

#define BUFFSIZE 8192

#define DEFAULT_OUT_ROOT "/root/Downloads/"
#define DEFAULT_OUT_NON_ROOT "$HOME/Downloads/"

double now();
long int filesize(const char *filename);
void beamRate(u_int64_t nbytes, double ntime);
void ratioProgress(u_int64_t curr_item, u_int64_t total_iter, double timeFrame);
void error(char *report);
void BeamServer(char *filepath, char *server_ip);
void BeamClient(char *filedest, char *server_ip);

#endif //__BEAM__
