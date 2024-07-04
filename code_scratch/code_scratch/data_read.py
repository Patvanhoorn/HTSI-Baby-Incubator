#Modules to import
import time
import serial

#Intialising the connection to the serial port
port_name = 'com5'
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


#functions
def acceleration_list(): #Retrieving IMU acceleromter values
    dataPacket= arduinoData.readline()
    dataPacket = str(dataPacket,'utf-8')
    dataPacket = dataPacket.strip('\r\n')
    datapacket_list  = dataPacket.split()
    a_n = np.float64(datapacket_list)
    return(a_n) #returns it as a list of lenght 3 

def readData():
    dataPacket = arduinoData.readline()

    print(dataPacket)

while True:
    while(arduinoData.inWaiting() == 0):
        pass
    readData()