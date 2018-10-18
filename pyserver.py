import socket
import struct
import time

UDP_IP = "192.168.0.255"
UDP_PORT = 50050

table = [
  ("4550e4", 4, 6.92),  
  ("1", 3, 5.20),
  ("1", 5, 5.20),
  ("1", 2, 3.46),
  ("1", 4, 3.46),
  ("1", 6, 3.46),
  ("1", 1, 1.73),
  ("1", 3, 1.73),
  ("1", 5, 1.73),
  ("1", 7, 1.73),
  ("1", 0, 0),
  ("1", 2, 0),
  ("1", 4, 0),
  ("1", 6, 0),
  ("1", 8, 0)
]
table = [(int(x[0],16),) + x[1:] for x in table]
print(table[0][0])

while True:
  sock = socket.socket(socket.AF_INET, # Internet
                       socket.SOCK_DGRAM) # UDP
  # MESSAGE = b''.join([struct.pack('Qf', *dist) for dist in table])
  MESSAGE = struct.pack('Qff'*len(table), *[item for pair in table for item in pair])
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
  sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
  time.sleep(3)
