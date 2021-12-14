from coord import Coord

class DrawSVG:
    def __init__(self, filename, height, width):
        self.height = height
        self.width = width
        self.f = open(filename, "w")
        self.center = Coord(width/2, height/2)

        self.f.write("<svg width='" + str(width) + "' height='"+ str(height) +"' xmlns='http://www.w3.org/2000/svg' version='1.1'>")
    
    def circle(self, center : Coord, r, stroke, fill):
        self.f.write("<circle cx='" + str(center.x) + "' cy='" + str(center.y) +"' r='"+str(r)+"' stroke='"+stroke+"' fill='"+fill+"' />")

    def line(self, start : Coord, end : Coord, stroke):
        self.f.write('<line x1="'+ str(start.x) +'" y1="'+str(start.y)+'" x2="'+str(end.x)+'" y2="'+str(end.y)+'" stroke="'+ stroke +'" />')

    def text(self, pos : Coord, content):
        self.f.write('<text x="'+ str(pos.x) + '" y="'+ str(pos.y) +'" text-anchor="middle" dominant-baseline="central">' + content + '</text>')

    def close(self):
        self.f.write("</svg>")
        #script a frissítéshez
        self.f.write("<script>window.onload = function() {setTimeout(function(){location.reload();}, 1000);}</script>")
        self.f.close()