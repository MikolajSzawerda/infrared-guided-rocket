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
        for filename in [f'dane/part4/p{i+1}/{x}' for x in os.listdir(f'dane/part4/p{i+1}') if 'cli' in x]
    ]
    for client in clients:
        ax[i].hist(client['delta'], bins=30)
        ax[i].set_title(params[i])
fig.suptitle("Czasy opóźnienia klientów")
# fig.savefig("plots/zad4_hist.png")

params2 = [
    "0 klient z aktywnym oczekiwaniem",
    "Każdy z aktywnym oczekiwaniem"
]
fig2, ax = plt.subplots(2, 3, figsize=(15, 10))
for i, n in enumerate(['a', 'b']):
    clients = [
        pd.read_csv(filename, header=None, names=["id", "got", "delivered", "delta"], skiprows=[0])
        for filename in sorted([f'dane/part5/{n}/{x}' for x in os.listdir(f'dane/part5/{n}') if 'cli' in x])
    ]
    for k, client in enumerate(clients):
        ax[(i, k)].hist(client["delta"], alpha=0.5)
        ax[(i, k)].set_title(f'{params2[i]}: klient {k}')
fig2.suptitle("Zmiana usypiania na aktywne oczekiwanie")
# fig2.savefig("plots/zad5_hist.png")

fig3, ax = plt.subplots()
df = pd.read_csv(f"dane/part4/p4/server.txt", header=None, names=["id", "time", "deltatime"], skiprows=[0])
ax.hist(reject_outliers(df["deltatime"]), bins=30)
fig3.suptitile("Błędny rozkład czasu serwowania")
fig3.savefig("plots/zad6_hist.png")
