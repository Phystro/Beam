#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "beam.h"

void wbeamFile(FILE *fp, int sockfd, long int filesiz){

	int n;
	ssize_t total = 0;
	char data[BUFFSIZE] = {0};

	//start clock for timing
	double start = now();
	printf("\n***Receiving and Writing Binary Data...\n");
	printf("\n");
	while ( (n = recv(sockfd, data, BUFFSIZE, 0)) > 0){
		total += n;
		//n = bytes per buffer; total = cumulative bytes
		if ( n < 0 )
			error("[-] Error Receiving File");
		
		if ( fwrite(data, sizeof(char), n, fp) != n )
			error("[-] Error Writing File");

		ratioProgress(total, filesiz, (now() - start) );
		memset(data, 0, BUFFSIZE);
	}

	printf("\n\n");
	double tt = now() - start;
	//printf("\n\n[+] %lf seconds - Total Time Taken: size: %ld\n", tt, total);
	//(tt == 0) ? printf("inf[near instantaneous]\n") : printf("[+] %lf bytes/secs - Average Beaming and Writing Rate\n", total/tt);
	beamRate(total, tt);

	if ( total != filesiz )
		error("[-] Error Receiving and Writing Complete Data");
	printf("[+] %ld bytes of data Received and Written\n", total);
}

void BeamClient(char *filedest, char *server_ip){

	int clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSock < 0)
		error("[-] Failed to create Client Socket");
	printf("[+] Success created Client Socket\n");

	struct sockaddr_in serverAddr;
	socklen_t servlen = sizeof(serverAddr);
	memset(&serverAddr, 0, servlen);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVERPORT);
	if ( inet_pton(AF_INET, server_ip, &serverAddr.sin_addr) < 0 )
		error("[-] IP Address Conversion Error");
	printf("[+] IP Address Conversion Success");

	if ( connect(clientSock, (const struct sockaddr *) &serverAddr, servlen) < 0)
		error("[-] Connection Error! Failed to make connection");
	printf("[+] Successful Connection made\n");

	char filename[BUFFSIZE] = {0};
	//receive filename
	if ( recv(clientSock, filename, BUFFSIZE, 0) < 0)
		error("[-] Error Receiving Filename from Server");
	printf("[+] Received Filename as: '%s'\n", filename);

	//receive file size
	long int fs;
	if ( recv(clientSock, &fs, sizeof(long int), 0) < 0 )
		error("[-] Error Receiving File Size from Server");
	printf("[+] Received File Size as: %ld Bytes\n", fs);

	printf("[+] Ready to receive %ld Bytes of file: '%s' from: %s:%d\n", fs, filename, inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
	strcat(filedest, "/");
	strcat(filedest, filename);
	
	FILE *fp = fopen(filedest, "wb");
	if (fp < 0)
		error("[-] Error Opening File\n");
	printf("[+] Created and Opened File for Writing Binary Data\n");

	wbeamFile(fp, clientSock, fs);

	printf("\n[+] Saved file '%s' in specified Filepath: %s\n", filename, filedest);

	printf("\n[+]Cleaning Up.........\n");
	fclose(fp);
	printf("[+] Closed File: '%s' after Receiving and Writing.\n", filename);
	close(clientSock);
	printf("[+] Client Socket Closed.\n");
}
