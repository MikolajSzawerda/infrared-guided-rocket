import socket
import random
import numpy as np
import struct
import time
import numpy as np


<<<<<<< HEAD
HOST = "0.0.0.0"
=======
HOST = "192.168.43.77"
>>>>>>> 1318ed4 (Added two servos)
PORT = 6969

INTERVAL = 1


def random_(X, Y):
    matrix = np.zeros((8, 8))
    matrix[X, Y] = 40
    X = (X+1)%8
    Y = (Y+1)%8
    return matrix.flatten()


def main():
    sock = socket.socket()

    sock.connect((HOST, PORT))
    x, y = 0, 0
    while True:
<<<<<<< HEAD
        buffer = random_()
        idx_max = np.argmax(buffer)
        buf = struct.pack('64fI', *buffer, idx_max)
=======
        buffer = random_(x, y)
        buf = struct.pack('64f', *buffer)
        x = (x+1)%8
        y = (y+1)%8
>>>>>>> 1318ed4 (Added two servos)
        sock.send(buf)
        time.sleep(INTERVAL)

if __name__ == "__main__":
    main()
