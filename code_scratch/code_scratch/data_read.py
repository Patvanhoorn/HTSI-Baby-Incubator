#Modules to import
import time
import keyboard
import serial
import csv
import os

script_dir = os.path.dirname(os.path.abspath(__file__))

# results
results_dir = os.path.join(script_dir, 'results')
os.makedirs(results_dir, exist_ok=True)

#Intialising the connection to the serial port
port_name = 'com3'
baud_rate = 9600
try :
    arduinoData = serial.Serial(port_name,baud_rate)
    if arduinoData.is_open:
        arduinoData.close()
        print("Closing")
        print("Port is closed")
except serial.SerialException:
    print("Unavaliable or cannot be opened")
    exit()
arduinoData = serial.Serial(port_name,baud_rate)
time.sleep(2)
arduinoData.flush()


temperature = []
humidity = []
TempTime = []
HumTime = []
end_read = False

#functions
def readData():
    dataPacket = arduinoData.readline()
    dataPacket = str(dataPacket,'utf-8')
    dataPacket = dataPacket.strip('\r\n')
    datapacket_list  = dataPacket.split()
    if dataPacket.startswith('Temperature'):
        temp_value = float(dataPacket.split(':')[1].strip('°C'))
        temperature.append(temp_value)
    elif dataPacket.startswith('Humidity'):
        humidity_value = float(dataPacket.split(':')[1].strip('%'))
        humidity.append(humidity_value)
    elif dataPacket.startswith('TempTime'):
        temp_time = float(dataPacket.split(':')[1].strip())
        TempTime.append(temp_time/1000)
    elif dataPacket.startswith('HumTime'):
        hum_time = float(dataPacket.split(':')[1].strip())
        HumTime.append(hum_time/1000)


while end_read == False:
    while(arduinoData.inWaiting() == 0):
        pass
    readData()
    if keyboard.is_pressed('t'):
        end_read = True
    
print("Temperature list:", temperature)
print("Humidity list:", humidity)
print("Temp Time list: ", TempTime)
print("Hum Time list: ", HumTime)

data = [list(t) for t in zip(TempTime, temperature, HumTime, humidity)]

csv_file_path = os.path.join(results_dir, 'output.csv')
with open(csv_file_path, 'w', newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['Temp Time', 'Temp Value', 'Hum Time', 'Hum Value'])
    writer.writerows(data)