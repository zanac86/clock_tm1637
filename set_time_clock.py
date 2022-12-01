import sys
import datetime
import serial
import serial.tools.list_ports
import time


ports = serial.tools.list_ports.comports()

if len(ports) == 0:
    print("No serial ports found")
    sys.exit(0)

for port, desc, hwid in sorted(ports):
    print(f"{port}: {desc} [{hwid}]")

if len(ports) > 1:
    print("Too many serial ports found")
    sys.exit(0)

ser = serial.Serial(ports[0].device, 115200, timeout=1, parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS)

# arduino reset by ch340 when open port
# need delay after open before send time
time.sleep(5)

d = datetime.datetime.now()
#timedelta(seconds=24)
# brightness 0..7 at end before $
s = d.strftime("$%y%m%d%H%M%S4$")
print(s)
ser.write(s.encode())
