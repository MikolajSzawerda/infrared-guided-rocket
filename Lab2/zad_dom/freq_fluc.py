from time import sleep

s = True
period = 20
duty = 0.5
h_period = int(duty*period)
t = 1
h_t = 0
clock_tick = 1
while True:
    if t % 200 == 0:
        period = (period+10)%100+10
        h_period = int(duty*period)
        h_t = 0
    if h_t < h_period: s=True
    else: s=False
    print(f'{t:8} {s}')
    h_t = (h_t+1)%period
    t += clock_tick
    sleep(clock_tick/100)


