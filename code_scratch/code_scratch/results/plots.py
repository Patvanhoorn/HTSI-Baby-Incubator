import csv
import matplotlib.pyplot as plt
import os
script_dir = os.path.dirname(os.path.abspath(__file__))



def readfile(file_path):
    with open(file_path, 'r') as file:
        # Create a CSV reader object
        reader = csv.reader(file)
    
        # Skip the first row (header row)
        next(reader)
    
        # Extract the first two columns into separate lists
        temptime = []
        tempvalue = []
        for row in reader:
            temptime.append(float(row[0]))
            tempvalue.append(float(row[1]))
    return temptime, tempvalue

plt.figure(figsize=(8, 6))
# Provide the full path to the CSV file
# Call the readfile function to get the data
# Plot the data
file_path = os.path.join(script_dir,"kp = 10, ki = 0, kd = 0;")
column1, column2 = readfile(file_path)
plt.scatter(column1, column2, label= "kp=10,ki=0,kd=0" )
file_path2 = os.path.join(script_dir,"kp = 20, ki = 0, kd = 0;")
column3, column4 = readfile(file_path2)
plt.scatter(column3,column4, label= "kp=20,ki=0,kd=0")


file_path3 = os.path.join(script_dir,"kp = 20v2, ki = 0, kd = 0;")
column5, column6 = readfile(file_path3)
plt.scatter(column5,column6, label= "kp=20v2,ki=0,kd=0")

file_path4 = os.path.join(script_dir,"kp = 50, ki = 0, kd = 0;")
column5, column6 = readfile(file_path4)
plt.scatter(column5,column6, label= "kp=50,ki=0,kd=0")


plt.xlabel('Time')
plt.ylabel('Temp')
plt.xlim(0,1000)
plt.ylim(20,40)
plt.legend()
plt.title('Plot of Temp vs Time')
plt.show()