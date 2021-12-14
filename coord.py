import math

class Coord:
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y

    def rotate(startpoint, angle, distance):
        radangle = angle * math.pi / 180
        angledEndpoint = Coord()
        angledEndpoint.x = startpoint.x + math.cos(radangle) * distance
        angledEndpoint.y = startpoint.y - math.sin(radangle) * distance
        return angledEndpoint