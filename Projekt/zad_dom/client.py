import socket
import random
import numpy as np
import struct
import time


HOST = "0.0.0.0"
PORT = 6969

INTERVAL = 1


def random_():
    rdint = lambda: random.uniform(0, 1)

    return [rdint() for _ in range(64)]


def main():
    sock = socket.socket()

    sock.connect((HOST, PORT))

    while True:
        buffer = random_()
        idx_max = np.argmax(buffer)
        buf = struct.pack('64fI', *buffer, idx_max)
        sock.send(buf)
        time.sleep(INTERVAL)

if __name__ == "__main__":
    main()
