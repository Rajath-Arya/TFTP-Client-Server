#include "main.h"                                      // Include required libraries and function declarations

int main()
{
    while(1)                                           // Keep displaying the menu until the user exits
    {
        printf("\n\n---Menu---\n");
        printf("1. Put file\n2. Get file\n3. Exit\n\n");

        int choice;
        printf("Enter the choice:");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                put_file();                            // Start file upload operation
                break;

            case 2:
                get_file();                            // Start file download operation
                break;

            case 3:
                printf("\nExit.....\n");
                return 0;                              // Terminate the application

            default:
                printf("\n!!Invalid Choice...\n");     // Handle invalid menu selection
        }
    }

    return 0;
}


int put_file()
{
    // Create a UDP socket for communication with the client
    int sock_fd=socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd==-1)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in serv;

    serv.sin_family=AF_INET;                           // Use IPv4 communication
    serv.sin_port=htons(8000);                         // Set server port
    serv.sin_addr.s_addr=inet_addr("127.0.0.1");       // Use localhost as server address

    // Bind the socket to the specified IP address and port
    if(bind(sock_fd, (struct sockaddr*)&serv, sizeof(serv))==-1)
    {
        perror("bind");
        close(sock_fd);
        return 1;
    }

    char request[50];

    struct sockaddr_in client;
    socklen_t size=sizeof(client);

    // Wait for a file request from the client
    int n=recvfrom(sock_fd, request, sizeof(request)-1, 0,
                   (struct sockaddr*)&client, &size);

    if(n==-1)
    {
        perror("recvfrom");
        return 1;
    }

    request[n]='\0';

    char file[20];
    char mode[10];

    // Request format: <filename> <transfer-mode>
    sscanf(request, "%19s %9s", file, mode);

    printf("File requested : %s\n", file);
    printf("Transfer mode : %s\n", mode);

    // Accept only the supported transfer modes
    if(strcmp(mode, "octet")!=0 && strcmp(mode, "netascii")!=0)
    {
        printf("Invalid transfer mode\n");

        close(sock_fd);
        return 1;
    }

    // Open the requested file in read-only mode
    int fd=open(file, O_RDONLY);

    char ack[50];

    if(fd==-1)
    {
        // Inform the client when the requested file does not exist
        strcpy(ack, "File not found!");

        sendto(sock_fd, ack, strlen(ack), 0,
               (struct sockaddr*)&client, sizeof(client));

        close(sock_fd);
        return 1;
    }

    // Inform the client that the requested file is available
    strcpy(ack, "File found");

    sendto(sock_fd, ack, strlen(ack), 0, (struct sockaddr*)&client, sizeof(client));

    // Wait for client's confirmation before starting file transfer
    n=recvfrom(sock_fd, ack, sizeof(ack)-1, 0, (struct sockaddr*)&client, &size);

    if(n==-1)
    {
        perror("recvform");
        close(sock_fd);
        close(fd);
        return 1;
    }

    ack[n]='\0';
    printf("ACK : %s\n", ack);

    char input[512];
    char data_packet[1024];

    // Read the file in chunks and send each chunk through UDP
    while((n=read(fd, input, sizeof(input)))>0)
    {
        int packet_size;

        if(strcmp(mode, "octet")==0)
        {
            // Octet mode sends the original bytes without modification
            memcpy(data_packet, input, n);
            packet_size=n;
        }
        else
        {
            // Netascii mode converts text before transmission
            packet_size=convert_to_netascii(input, n, data_packet);
        }

send_packet_again:

        // Send the prepared data packet to the client
        int sent=sendto(sock_fd, data_packet, packet_size, 0, (struct sockaddr*)&client, sizeof(client));

        if(sent==-1)
        {
            perror("sendto");
            close(fd);
            close(sock_fd);
            return 1;
        }

        printf("Sent %d bytes\n", sent);

        // Wait for acknowledgement for the current packet
        int ack_len=recvfrom(sock_fd, ack, sizeof(ack)-1, 0, (struct sockaddr*)&client, &size);

        if(ack_len==-1)
        {
            perror("recvfrom");
            close(sock_fd);
            close(fd);
            return 1;
        }

        ack[ack_len]='\0';

        printf("ACK : %s\n", ack);

        // Resend the packet when the client reports packet loss
        if(strcmp(ack, "data packet not reached")==0)
        {
            goto send_packet_again;
        }
    }

    if(n==-1)
    {
        perror("read");

        close(sock_fd);
        close(fd);
        return 1;
    }

    printf("File transfer successfull\n");

    close(sock_fd);
    close(fd);

    return 0;
}


int get_file()
{
    // Create a UDP socket for receiving the file
    int sock_fd=socket(AF_INET, SOCK_DGRAM, 0);

    if(sock_fd==-1)
    {
        perror("socket");
        return 1;
    }

    char ip_address[16];

    printf("Enter the server IP address : ");
    scanf(" %s", ip_address);

    // Perform basic validation of the entered IPv4 address
    int i=0;
    int count=0;
    int flag=0;

    while(ip_address[i])
    {
        if(ip_address[i]=='.')
        {
            count++;
        }

        if(ip_address[i]!='.' && !isdigit(ip_address[i]))
        {
            flag=1;
            break;
        }

        i++;
    }

    // IPv4 address must contain exactly three dots and only digits
    if(count!=3 || flag!=0)
    {
        printf("!!Invalid IP address\n");

        close(sock_fd);
        return 1;
    }

    struct sockaddr_in serv;

    serv.sin_family=AF_INET;
    serv.sin_port=htons(8000);
    serv.sin_addr.s_addr=inet_addr(ip_address);

    int mode;

    printf("\n--- Transfer Mode Menu---\n");
    printf("1. Octet\n");
    printf("2. Netascii\n\n");

    printf("Enter the transfer mode : ");
    scanf("%d", &mode);

    if(mode!=1 && mode!=2)
    {
        printf("Invalid transfer mode\n");
        return 1;
    }

    char file[20];

    printf("Enter the file to be transferred : ");
    scanf("%19s", file);

    char request[50];

    // Construct request according to the selected transfer mode
    if(mode==1)
    {
        snprintf(request, sizeof(request), "%s octet", file);
    }
    else
    {
        snprintf(request, sizeof(request), "%s netascii", file);
    }

    printf("\nRequest sent : %s\n", request);

    // Send file request to the server
    sendto(sock_fd, request, strlen(request), 0, (struct sockaddr*)&serv, sizeof(serv));

    char ack[50];
    socklen_t size=sizeof(serv);

    // Wait for server response about file availability
    int n=recvfrom(sock_fd, ack, sizeof(ack)-1, 0, (struct sockaddr*)&serv, &size);

    if(n==-1)
    {
        perror("recvfrom");
        close(sock_fd);
        return 1;
    }

    ack[n]='\0';

    printf("Acknowledgement : %s\n", ack);

    if(strcmp(ack, "File not found!")==0)
    {
        printf("Transfer unsuccessfull\n");
        close(sock_fd);
        return 0;
    }

    // Confirm that the client is ready to receive file data
    strcpy(ack, "Acknowledgement Received by client");

    sendto(sock_fd, ack, strlen(ack), 0, (struct sockaddr*)&serv, sizeof(serv));

    // Create or overwrite the destination file
    int fd=open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if(fd==-1)
    {
        perror("open");
        close(sock_fd);
        return 1;
    }

    char data_packet[512];
    char converted[512];

    // Receive file packets until the final smaller packet is received
    while(1)
    {
        n=recvfrom(sock_fd, data_packet, sizeof(data_packet), 0, (struct sockaddr*)&serv, &size);

        if(n==-1)
        {
            // Inform server that the current packet was not received
            strcpy(ack, "data packet not reached");

            sendto(sock_fd, ack, strlen(ack), 0, (struct sockaddr*)&serv, sizeof(serv));

            continue;
        }

        int write_size;

        if(mode==1)
        {
            // Write Octet data directly to the file
            write_size=n;
            write(fd, data_packet, write_size);
        }
        else
        {
            // Convert Netascii data back to normal text before writing
            write_size=convert_from_netascii(data_packet, n, converted);
            write(fd, converted, write_size);
        }

        // Acknowledge successful reception of the current packet
        strcpy(ack, "Data packet reached send next packet");

        sendto(sock_fd, ack, strlen(ack), 0, (struct sockaddr*)&serv, sizeof(serv));

        // A packet smaller than the buffer indicates the end of the file
        if(n<sizeof(data_packet))
        {
            break;
        }
    }

    printf("File transfer successfull\n");

    close(sock_fd);
    close(fd);

    return 0;
}


int convert_to_netascii(char *input, int n, char *output)
{
    int j=0;

    // Convert newline into CR-LF representation for network transmission
    for(int i=0;i<n;i++)
    {
        if(input[i]=='\n')
        {
            output[j++]='\r';
            output[j++]='\n';
        }
        else
        {
            output[j++]=input[i];
        }
    }

    return j;
}


int convert_from_netascii(char *input, int n, char *output)
{
    int i=0;
    int j=0;

    // Convert CR-LF network representation back to newline
    while(i<n)
    {
        if(input[i]=='\r' &&
           i+1<n &&
           input[i+1]=='\n')
        {
            output[j++]='\n';
            i+=2;
        }
        else
        {
            output[j++]=input[i++];
        }
    }

    return j;
}