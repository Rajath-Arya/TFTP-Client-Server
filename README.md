# 🌐 TFTP Client-Server Using C

![Language](https://img.shields.io/badge/LANGUAGE-C-blue)
![Platform](https://img.shields.io/badge/PLATFORM-LINUX-green)
![Protocol](https://img.shields.io/badge/PROTOCOL-TFTP-orange)
![Status](https://img.shields.io/badge/STATUS-COMPLETED-brightgreen)

---

## 📖 Overview

The TFTP Client-Server project is a network-based file transfer application developed in C using UDP socket programming.

The project implements a client and server that communicate over a network to transfer files. It supports both file upload and file download operations along with Octet and Netascii transfer modes.

The implementation demonstrates practical Linux network programming concepts including UDP sockets, client-server communication, file handling, packet transmission, acknowledgements, data conversion, and error handling.

---

## ✨ Features

- 🌐 Client-server communication using UDP
- 📤 File upload from client to server
- 📥 File download from server to client
- 🔢 Octet transfer mode
- 📝 Netascii transfer mode
- 📦 Data transfer using packets
- ✅ Acknowledgement handling
- 🔄 Packet retransmission when a packet is not received
- 📁 File creation and file handling
- 🔍 IPv4 address validation
- ❌ File-not-found handling
- ⚠️ Invalid transfer mode detection
- 🔌 Socket creation and communication
- 🛡️ Basic error handling

---

## 🛠️ Technologies Used

- C Programming
- Linux
- UDP Socket Programming
- TFTP Concepts
- Network Programming
- Socket API
- File Handling
- System Calls
- IPv4 Networking
- Netascii Data Conversion

---

## 📁 Project Structure

```text
TFTP-Client-Server/
│
├── client.c
├── client_main.h
├── server.c
├── server_main.h
└── README.md
```

### `client.c`

Implements the client-side functionality including:

- File upload requests
- File download requests
- Server IP address input
- Transfer mode selection
- UDP communication
- File creation and writing
- Acknowledgement handling
- Octet and Netascii data conversion

### `client_main.h`

Contains the required header files and function declarations used by the client.

### `server.c`

Implements the server-side functionality including:

- Receiving client requests
- File upload handling
- File download handling
- UDP socket creation and binding
- File reading and writing
- Acknowledgement handling
- Packet transmission
- Octet and Netascii transfer support

### `server_main.h`

Contains the required header files and function declarations used by the server.

---

## 🚀 Compilation

### Compile the Server

```bash
gcc server.c -o server
```

### Compile the Client

```bash
gcc client.c -o client
```

---

## ▶️ Run the Program

### Start the Server

Run the server first:

```bash
./server
```

### Start the Client

In another terminal:

```bash
./client
```

The client provides the following menu:

```text
---Menu---
1. Put file
2. Get file
3. Exit
```

---

## 📤 Put File

The **Put File** operation is used to transfer a file to the other side.

The program:

1. Creates a UDP socket.
2. Opens the requested file.
3. Sends file data in packets.
4. Waits for acknowledgements.
5. Retransmits a packet if it is reported as not received.
6. Continues until the complete file is transferred.

---

## 📥 Get File

The **Get File** operation is used to download a file.

The client:

1. Accepts the server IP address.
2. Validates the IPv4 address.
3. Selects the transfer mode.
4. Requests the required file.
5. Receives the file in packets.
6. Sends acknowledgements for received packets.
7. Creates or overwrites the destination file.
8. Continues until the complete file is received.

---

## 🔄 Transfer Modes

### Octet Mode

Octet mode transfers the file data without modification.

```text
Binary data → Network → Binary data
```

This mode is suitable for transferring files where the original byte representation must be preserved.

### Netascii Mode

Netascii mode converts newline characters before transmission.

```text
\n → \r\n
```

The receiver converts the data back:

```text
\r\n → \n
```

This mode is intended for text-based file transfer.

---

## 📡 Network Communication

The project uses UDP sockets for communication.

The server listens on:

```text
IP Address : 127.0.0.1
Port       : 8000
Protocol   : UDP
```

The following socket functions are used:

```c
socket()
bind()
sendto()
recvfrom()
close()
```

---

## 📦 Packet and Acknowledgement Handling

File data is transferred in chunks using UDP datagrams.

After receiving a data packet, the receiver sends an acknowledgement to the sender.

If the sender receives:

```text
data packet not reached
```

the current packet is transmitted again.

This provides a basic mechanism for handling packet delivery failures.

---

## 🧠 Concepts Used

- Client-Server Architecture
- UDP Communication
- Socket Programming
- IPv4 Addressing
- `socket()`
- `bind()`
- `sendto()`
- `recvfrom()`
- File Descriptors
- `open()`
- `read()`
- `write()`
- File Creation
- Acknowledgement Mechanism
- Packet-Based Data Transfer
- Error Handling
- Netascii Conversion
- Dynamic Buffer Handling

---

## 🎯 Learning Outcomes

This project helped me understand:

- How client-server applications communicate over a network
- UDP socket programming in C
- Creating and binding network sockets
- Sending and receiving data using UDP
- Implementing file upload and download operations
- Handling file descriptors and system calls
- Implementing basic acknowledgement mechanisms
- Working with IPv4 addresses
- Understanding different file transfer modes
- Converting text data between normal and Netascii formats
- Handling communication and file-related errors

---

## 🚀 Future Improvements

- Implement standard TFTP packet formats
- Add timeout-based retransmission
- Add support for configurable server ports
- Improve packet sequence and block-number handling
- Add support for larger file names
- Improve network error handling
- Add support for multiple simultaneous clients
- Improve compatibility with standard TFTP clients and servers
- Add a Makefile for easier compilation

---

## 👨‍💻 Author

**Rajath H M**

🔗 GitHub: [Rajath-Arya](https://github.com/Rajath-Arya)

---

⭐ If you found this project useful, consider giving it a star on GitHub!
