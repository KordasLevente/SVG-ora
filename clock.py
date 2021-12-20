from coord import Coord
from drawsvg import DrawSVG
import time
import ntplib
from time import ctime

#NTP szerver
c= ntplib.NTPClient()
response = c.request('0.hu.pool.ntp.org', version=3)


height = 600
width = 600
r = 100

def drawClock(timeToDisplay):
   d = DrawSVG("clock.html", height, width)
   time = ctime(response.tx_time).split(' ')[3]
   #óralap
   d.circle(d.center, r, "black", "white")

   #rovátkák
   #óra
   for i in range(12):
      d.line(Coord.rotate(d.center, 360/12 * i, r), Coord.rotate(d.center, 360/12 * i, r * 0.9), "blue")
      #számozás
      d.text(Coord.rotate(d.center, 60 - 360/12 * i, r * 0.8), str(i +1))

   #perc/másodperc
   for i in range(60):
      d.line(Coord.rotate(d.center, 360/60 * i, r), Coord.rotate(d.center, 360/60 * i, r * 0.95), "blue")

   #mutatók
   hours = int(time.split(':')[0])
   minutes = int(time.split(':')[1])
   seconds = int(time.split(':')[2])
   
   #óramutató
   #hourdegree = hours * 360/12 + minutes/5 * 360/60
   d.line(d.center, Coord.rotate(d.center, 90 - hours * 360/12, r * 0.5), "red")
   
   #percmutató
   #mindegree = minutes * 360/12 + seconds/5 * 360/60
   d.line(d.center, Coord.rotate(d.center, 90 - minutes* 360/60, r * 0.7), "green")

   #másodpercmutató
   secdegree = seconds* 360/60
   d.line(d.center, Coord.rotate(d.center, 90 - secdegree, r * 0.9), "orange")

   print("Created clock with time: " + time)
   d.close()

while True:
   response = c.request('europe.pool.ntp.org', version=3)
   drawClock(ctime(response.tx_time).split(' ')[3])
   time.sleep(1)