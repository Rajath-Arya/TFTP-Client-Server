# 🌐 TFTP Client-Server Using C

![Language](https://img.shields.io/badge/LANGUAGE-C-blue)
![Platform](https://img.shields.io/badge/PLATFORM-LINUX-green)
![Protocol](https://img.shields.io/badge/PROTOCOL-TFTP-orange)
![Status](https://img.shields.io/badge/STATUS-COMPLETED-brightgreen)

---

## 📖 Overview

The TFTP Client-Server project is a network-based file transfer application developed in C using UDP socket programming.

The project implements client-server communication for file upload and download operations and supports Octet and Netascii transfer modes.

It demonstrates practical concepts of Linux network programming, socket communication, file handling, packet transmission, acknowledgement handling, and error handling.

---

## ✨ Features

- 🌐 UDP-based client-server communication
- 📤 File upload
- 📥 File download
- 🔢 Octet transfer mode
- 📝 Netascii transfer mode
- 📦 Packet-based data transfer
- ✅ Acknowledgement handling
- 🔄 Basic packet retransmission
- 📁 File handling and creation
- 🔍 IPv4 address validation
- ❌ Error handling

---

## 🛠️ Technologies Used

- C Programming
- Linux
- UDP Socket Programming
- TFTP
- Network Programming
- Socket API
- File Handling
- System Calls

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

Implements the client-side file upload, file download, UDP communication, transfer modes, and acknowledgement handling.

### `client_main.h`

Contains client-side header files and function declarations.

### `server.c`

Implements the server-side file transfer operations, UDP communication, file handling, and acknowledgement handling.

### `server_main.h`

Contains server-side header files and function declarations.

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

```bash
./server
```

### Start the Client

```bash
./client
```

The client provides options for:

```text
1. Put file
2. Get file
3. Exit
```

---

## 🧠 Concepts Used

- Client-Server Architecture
- UDP Socket Programming
- Socket Creation and Binding
- IPv4 Networking
- `socket()`
- `bind()`
- `sendto()`
- `recvfrom()`
- File Descriptors
- File I/O
- Packet-Based Communication
- Acknowledgement Handling
- Error Handling
- Netascii Conversion

---

## 🎯 Learning Outcomes

This project helped me understand:

- UDP client-server communication
- Socket programming in C
- Network data transmission
- File upload and download
- File descriptors and system calls
- IPv4 networking
- Packet and acknowledgement handling
- Different file transfer modes
- Linux network programming

---

## 👨‍💻 Author

**Rajath H M**

🔗 GitHub: [Rajath-Arya](https://github.com/Rajath-Arya)

---

⭐ If you found this project useful, consider giving it a star on GitHub!
