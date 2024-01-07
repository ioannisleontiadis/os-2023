import struct

with open("/dev/input/mice", "rb") as f:
    while True:
        data = f.read(3)
        print(struct.unpack('bbb', data))
