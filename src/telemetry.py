# import serial.tools.list_ports
# import time

# def find_device(): 
#     for port in serial.tools.list_ports.comports():
#         if port.name == "COM4":
#             return port.name
#     else: 
#         return None

# def connect_arduino(port, baudrate=115200, retries = 3):
#     for attempt in range(retries):
#         try:
#             ser = serial.Serial(port, baudrate, timeout=2)
#             time.sleep(2)
#             ser.reset_input_buffer()

#             print(ser.readline().decode().strip())

#         except serial.SerialException as e:
#             print(f"Attempt {attempt + 1} failed: {e}")
#             time.sleep(1)

#     raise ConnectionError(f"Could not connect to Arduino on {port}")

# port = find_device()
# arduino = connect_arduino(port)
# arduino.close()


import serial
import time

def monitor(port, baudrate=115200):
    """Print timestamped lines from a serial port."""
    ser = serial.Serial(port, baudrate, timeout=0.1)
    print(f"Monitoring {port} at {baudrate} baud (Ctrl+C to stop)")

    try:
        while True:
            line = ser.readline()
            if line:
                ts = time.strftime('%H:%M:%S')
                text = line.decode('utf-8', errors='replace').strip()
                print(f"[{ts}] {text}")
    except KeyboardInterrupt:
        pass
    finally:
        ser.close()

monitor('COM4')