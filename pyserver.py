import socket
import struct
import time

UDP_IP = "10.0.1.255"
UDP_PORT = 50050

table = [
  (0, 4, 6.92),
  (1, 3, 5.20),
  (2, 5, 5.20),
  (3, 2, 3.46),
  (4, 4, 3.46),
  (5, 6, 3.46),
  (6, 1, 1.73),
  (7, 3, 1.73),
  (8, 5, 1.73),
  (9, 7, 1.73),
  (10, 0, 0),
  (11, 2, 0),
  (12, 4, 0),
  (13, 6, 0),
  (14, 8, 0)
]

while True:
  sock = socket.socket(socket.AF_INET, # Internet
                       socket.SOCK_DGRAM) # UDP
  # MESSAGE = b''.join([struct.pack('Qf', *dist) for dist in table])
  MESSAGE = struct.pack('Qff'*len(table), *[item for pair in table for item in pair])
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
  sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
  time.sleep(3)
