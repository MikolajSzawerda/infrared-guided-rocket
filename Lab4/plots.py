import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
plt.tight_layout()

def reject_outliers(data, m = 2.):
    d = np.abs(data - np.median(data))
    mdev = np.median(d)
    s = d/mdev if mdev else np.zeros(len(d))
    return data[s<m]

params = [
    "3 klientów 1 rdzeń pełne obciążenie",
    "3 klientów 2 rdzenie pełne obciążenie",
    "3 klientów 2 rdzeń brak obciążenia",
    "1 klient 4 rdzenie brak obciążenia",
]

fig, ax = plt.subplots(4, 1, figsize=(15, 15))
for i in range(4):

    clients = [
        pd.read_csv(filename, header=None, names=["id", "got", "delivered", "delta"], skiprows=[0])
        for filename in [f'dane/part3/p{i+1}/{x}' for x in os.listdir(f'dane/part3/p{i+1}') if 'cli' in x]
    ]
    for client in clients:
        ax[i].hist(client['delta'], bins=30)
        ax[i].set_title(params[i])
fig.suptitle("Czasy opóźnienia klientów")
fig.savefig("plots/zad4_hist.png")

# fig2, ax = plt.subplots(1, 1)
# df = pd.read_csv(f"dane/part3/p4/server.txt", header=None, names=["id", "time", "deltatime"], skiprows=[0])
# ax[(i, 0)].hist(reject_outliers(df["deltatime"]))
