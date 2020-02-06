#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include "beam.h"

void beamFile(FILE *fp, int sockfd, long int filesiz){

	int n;
	ssize_t total = 0;
	char data[BUFFSIZE] = {0};

	double start = now();
	printf("\n***Reading and Transmitting[sending] Binary Data...\n");
	printf("\n");
	while (( n = fread(data, sizeof(char), BUFFSIZE, fp) ) > 0 ){
		total += n;
		if ( n != BUFFSIZE && ferror(fp) )
			error("[-] Error Reading File data");

		if ( send(sockfd, data, n, 0) < 0)
			error("[-] Error Sending File to client");
		
		ratioProgress(total, filesiz, (now() - start) );
		memset(data, 0, BUFFSIZE);
	}

	printf("\n\n");
	double tt = now() - start;
	beamRate(total, tt);

	if ( total != filesiz )
		error("[-] Failed to completely transfer all Data");
	printf("[+] %ld bytes of data read and sent to client\n", total);
}

void BeamServer(char *filepath, char *server_ip){

	int clientSock, serverSock;
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock < 0)
		error("[-] Failed to create Server Socket");
	printf("[+] Success created Server Socket\n");

	struct sockaddr_in serverAddr, clientAddr;

	socklen_t servlen = sizeof(serverAddr);
	socklen_t clitlen = sizeof(clientAddr);

	memset(&serverAddr, 0, servlen);
	memset(&clientAddr, 0, clitlen);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVERPORT);
	if ( inet_pton(AF_INET, server_ip, &serverAddr.sin_addr) < 0)
		error("[-] IP Address Conversion Error");
	printf("[+] IP Address Conversion Success\n");

	if ( bind(serverSock, (struct sockaddr *) &serverAddr, servlen) < 0)
		error("[-] Binding Error");
	printf("[+] Success: Binding to Address - %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	if ( listen(serverSock, MAX_CONN) < 0)
		error("[-] Listening Error");
	printf("[+] Server Listening on %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

	clientSock = accept(serverSock, (struct sockaddr *) &clientAddr, &clitlen);
	if ( clientSock < 0 )
		error("[-] Accepting Connection Error");
	printf("[+] Accepted Connection from Address - %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	char *filename = basename(filepath);
	if ( filename ==NULL )
		error("[-] Error getting Filename");
	printf("[+] Ready to send file: '%s'\n", filename);
	
	char dataBuff[BUFFSIZE] = {0};
	//send filename
	strncpy(dataBuff, filename, strlen(filename));
	if ( send(clientSock, dataBuff, BUFFSIZE, 0) < 0)
		error("[-] Error sending Filename to Client");
	printf("[+] Success: Sent Filename '%s' to Client\n", filename);
	//send filesize
	long int fs = filesize(filepath);
	if (fs == -1)
		error("[-] Error getting filesize");
	if ( send(clientSock, &fs, sizeof(long int), 0) < 0 )
		error("[-] Error sending file size to Client");
	printf("[+] Success: Sent file size (%ld bytes) to Client\n", fs);

	//Reading into file for transfer
	FILE *fp = fopen(filepath, "rb");
	if (fp == NULL)
		error("[-] Error Opening File for reading");
	printf("[+] Opened File: '%s' for Reading and Transmitting binary data\n", filename);
	printf("[+] Ready to Transfer %ld Bytes of file: %s to Client\n", fs, filename);

	beamFile(fp, clientSock, fs);

	printf("\nCleaning up......\n");
	fclose(fp);
	printf("[+] Closed File: '%s' after Reading and Transmission\n", filename);
	close(serverSock);
	printf("[+] Server Socket Closed\n");

}
