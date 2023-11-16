import socket
import sys

from pwn import *
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 10000)
print('starting up on {} port {}'.format(*server_address))
sock.bind(server_address)

# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print('waiting for a connection')
    connection, client_address = sock.accept()
    try:
        print('connection from', client_address)
        dump=False
        # Receive the data in small chunks and retransmit it
        while True:
            data = connection.recv(16)
            print('received {!r}'.format(data))
            if not data:
                print('no data from', client_address)
                connection.close()
                break
            if(dump and len(data)<7):
                connection.close()
                break
            
            if(dump):
                print(hex(u64(b"\x00"+data[:7])))
                connection.sendall(b"HTTP/1.1 200 OK\r\nContent-Type: application/pdf\r\nContent-Length: 0\r\n\r\n")
                connection.close()
                break
            if(b"\r\n\r\n" in data):
                dump=True

    finally:
        # Clean up the connection
        connection.close()