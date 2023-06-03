import socket
import random
import struct
import time


HOST = "127.0.0.1"
PORT = 8081

INTERVAL = 1


def random_():
    rdint = lambda: random.uniform(0, 1)

    return [rdint() for _ in range(64)]


def main():
    sock = socket.socket()

    sock.connect((HOST, PORT))

    while True:
        buffer = random_()
        buf = struct.pack('64f', *buffer)
        sock.send(buf)
        time.sleep(INTERVAL)

if __name__ == "__main__":
    main()
