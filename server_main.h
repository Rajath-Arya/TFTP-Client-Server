#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>

// Function to receive a file from the client
int put_file();

// Function to send a file to the client
int get_file();

// Function to convert normal text data into Netascii format
int convert_to_netascii(char *input, int n, char *output);

// Function to convert Netascii data back to normal text format
int convert_from_netascii(char *input, int n, char *output);

#endif