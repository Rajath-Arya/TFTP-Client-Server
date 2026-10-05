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

int put_file();                 // Function to send a file to the server
int get_file();                 // Function to receive a file from the server
int convert_to_netascii(char *input, int n, char *output);   // Convert data to Netascii format
int convert_from_netascii(char *input, int n, char *output); // Convert Netascii data to normal text

#endif