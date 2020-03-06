#Nancy Mazariegos
#Laboratorio 6 RaspberryPi
from Adafruit_IO import *
import random
#Codigo Obtenido del Tutorial de Adafruit
ADAFRUIT_IO_USERNAME = "NancyM20"
ADAFRUIT_IO_KEY = "aio_HdGw57ohvqLy3IzNcBmxUujTe3Xy"
aio = Client(ADAFRUIT_IO_USERNAME,ADAFRUIT_IO_KEY)

#Valores aleatorios de 0-1000, obtenido del ejemplo de clase
sensor_1=random.randint(0,100)
sensor_2=random.randint(0,100)
sensor_3=random.randint(0,100)
sensor_4=random.randint(0,100)

#Envio de valores a la raspberry
aio.send("sensor1", sensor_1)
aio.send("sensor2", sensor_2)
aio.send("sensor3", sensor_3)
aio.send("sensor4", sensor_4)
