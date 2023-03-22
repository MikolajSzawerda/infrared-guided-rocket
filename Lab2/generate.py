from mido import MidiFile
from collections import namedtuple
import sys

Note = namedtuple('Note', 'freq time')

if __name__ == '__main__':
    file_name = sys.argv[1]

    BPM = int(sys.argv[2])
    qnt = 60/BPM
    mid = MidiFile(file_name, clip=True)
    mid = [x.dict() for x in mid.tracks[1]]
    changes = [(x['type'], x['note'], x['time']) for x in mid if x['type'] in ('note_on', 'note_off')]
    notes = []
    for note in changes:
        time = (note[2]/720)*qnt
        if note[0] == 'note_on':
            if note[2] != 0:
                notes.append(Note(-1, time))
        else:
            freq = 440*pow(2, (note[1]-69)/12)
            notes.append(Note(freq, time))

    with open("out.txt", 'w') as fh:
        for note in notes:
            fh.write(f'{note.freq} {note.time}\n')


