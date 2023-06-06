import socket
import struct

import matplotlib.pyplot as plt
from matplotlib.patches import Circle
import numpy as np


HOST = "0.0.0.0"
PORT = 6969

PLT_TITLE = "Rocket Thermal Guidance System Visualization"
PLT_XLABEL = "X"
PLT_YLABEL = "Y"

IMG_BORDER_SIZE = 8
IMG_SIZE = IMG_BORDER_SIZE ** 2

CROSSHAIR_SIZE = 0.08


def buffer_to_grid(buffer: bytes) -> tuple[np.array, int]:
    data = struct.unpack(f"{IMG_SIZE}fI", buffer)

    return np.reshape(data[:IMG_SIZE], (IMG_BORDER_SIZE, IMG_BORDER_SIZE)), data[IMG_SIZE]


def main():
    figure, ax = plt.subplots()

    plt.ion()

    plt.title(PLT_TITLE)
    plt.xlabel(PLT_XLABEL)
    plt.ylabel(PLT_YLABEL)
    plt.show()

    thermal_img = ax.imshow(np.zeros((8, 8)), cmap="coolwarm", interpolation="bilinear")
    crosshair = Circle((IMG_BORDER_SIZE / 2, IMG_BORDER_SIZE / 2), radius=CROSSHAIR_SIZE, color="black")
    ax.add_patch(crosshair)
    figure.canvas.flush_events()

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()

        print('Connected to ' + addr[0] + ':' + str(addr[1]))

        while (data_bytes := conn.recv(260)):
            grid, target_idx = buffer_to_grid(data_bytes)

            crosshair.center = target_idx % IMG_BORDER_SIZE, target_idx // IMG_BORDER_SIZE
            thermal_img.set_data(grid)
            thermal_img.set_clim(vmin=np.min(grid), vmax=np.max(grid))

            figure.canvas.draw()
            figure.canvas.flush_events()



if __name__ == "__main__":
    main()
