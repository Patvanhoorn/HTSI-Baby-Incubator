#Modules to import
import time
import keyboard
import serial

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
end_read = False

#functions
def readData():
    dataPacket = arduinoData.readline()
    dataPacket = str(dataPacket,'utf-8')
    dataPacket = dataPacket.strip('\r\n')
    datapacket_list  = dataPacket.split()
    print(dataPacket)
    if dataPacket.startswith('Temperature'):
        temp_value = float(dataPacket.split(':')[1].strip('C'))
        temperature.append(temp_value)
    elif dataPacket.startswith('Humidity'):
        humidity_value = float(dataPacket.split(':')[1].strip('%'))
        humidity.append(humidity_value)



while end_read == False:
    while(arduinoData.inWaiting() == 0):
        pass
    readData()
    if keyboard.is_pressed('t'):
        end_read = True
    
print("Temperature list:", temperature)
print("Humidity list:", humidity)