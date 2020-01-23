/*
 * Name:	Beam
 * Version:	0.1
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
		printf("Usage:\n");
		printf("\tServer: %s -s [FILEPATH] [SERVER_IP]\n\n", argv[0]);
		printf("\tClient: %s -c [FILE_DESTINATION] [SERVER_IP]\n", argv[0]);
		exit(1);
	}

	if ( strncmp("-s", argv[1], 2) == 0 )
		BeamServer(argv[2], argv[3]);

	if ( strncmp("-c", argv[1], 2) == 0 )
		BeamClient(argv[2], argv[3]);

	return 0;
}
