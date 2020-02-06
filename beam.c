/*
 * Name:	Beam
 * Version:	0.22
 * Author:	Anthony Karoki
 * Alias:	Phystro/PhyTensor
 * Description:	File Sharing/Transmission program using TCP Sockets over LAN environments for Linux systems
 * Copyright (C) Eccentric Tensor Labs (2020)
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "beam.h"

int main(int argc, char *argv[]){

	if ( argc < 4 ){
		printf("Beam\n");
		printf("Client-Server Sharing:\n");
		printf("Usage: %s [OPTION]... [FILE_SOURCE or FILE_DEST]... [SERVER_IP]...\n", argv[0]);
		printf("\tServer: %s -s [FILE_PATH]... [SERVER_IP]...\n", argv[0]);
		printf("\tClient: %s -c [FILE_DEST]... [SERVER_IP]...\n", argv[0]);
		printf("\nFast Copying (copy-paste): (stilll under development...hang in there) \n");
		printf("\tUsage: %s [SOURCE]... [DEST]...\n", argv[0]);

		printf("Extra-Info.\n");
		printf(" ~ The very act of measuring time taken uses about 1.6 microseconds on average per measurement.\n");
		printf(" ~ The transfer rates or speeds indicated are NOT an instantaneous measure, rather an average measurement.\n");

		exit(1);
	}

	if ( strncmp("-s", argv[1], 2) == 0 )
		BeamServer(argv[2], argv[3]);

	if ( strncmp("-c", argv[1], 2) == 0 )
		BeamClient(argv[2], argv[3]);

	return 0;
}
