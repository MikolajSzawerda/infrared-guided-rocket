import socket
import struct

import matplotlib.pyplot as plt
import numpy as np


HOST = "127.0.0.1"
PORT = 8081

PLT_TITLE = "Rocket Thermal Guidance System Visualization"
PLT_XLABEL = "X"
PLT_YLABEL = "Y"

IMG_BORDER_SIZE = 8
BUFFER_SIZE = IMG_BORDER_SIZE ** 2


def buffer_to_grid(buffer: bytes) -> np.array:
    data = struct.unpack(f"{BUFFER_SIZE}f", buffer)

    return np.reshape(data, (IMG_BORDER_SIZE, IMG_BORDER_SIZE))


def main():
    figure, ax = plt.subplots()

    plt.ion()

    plt.title(PLT_TITLE)
    plt.xlabel(PLT_XLABEL)
    plt.ylabel(PLT_YLABEL)
    plt.show()

    thermal_img = ax.imshow(np.zeros((8, 8)), cmap="coolwarm", interpolation="bilinear")
    figure.canvas.flush_events()

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)

    conn, addr = s.accept()

    print('Connected to ' + addr[0] + ':' + str(addr[1]))

    while (data_bytes := conn.recv(256)):
        grid = buffer_to_grid(data_bytes)

        thermal_img.set_data(grid)
        thermal_img.set_clim(vmin=np.min(grid), vmax=np.max(grid))

        figure.canvas.draw()
        figure.canvas.flush_events()


if __name__ == "__main__":
    main()
