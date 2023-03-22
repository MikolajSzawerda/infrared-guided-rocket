from time import sleep 
with open('out.txt', 'r') as fh:
    for l in fh:
        freq, time = l.split(' ')
        freq = float(freq)
        time = float(time)
        if freq == -1:
            #pwm.enable = false
            print('pause')
            pass
        else:
            #pwm.frequencie = freq
            print(freq)
            pass
        sleep(time)
