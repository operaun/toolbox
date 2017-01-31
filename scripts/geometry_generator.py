#!/usr/bin/env python3
import sys; sys.dont_write_bytecode = True
import random
import math

MinXinKr = 869000
MaxXinKr = 1186000
MinYinKr = 1593000
MaxYinKr = 2035600

class WktGeometryGenerator:
    def __init__(self):
        self.nearX = 0
        self.nearY = 0

    def createPoint(self):
        return "POINT(" + self.__getRawPoint__() + ")"

    def createPointNear(self):
        return "POINT(" + self.__getRawPointNear__() + ")"

    def createLinestring(self):
        return # TODO(Jongmin): not completed method
        return "LINESTRING(%s, %s)" % (self.__getPoint__(), self.__getPoint__())

    def createPolygon(self):
        return # TODO(Jongmin): not completed method
        return "POLYGON(%s, %s)" % (self.__getPoint__(), self.__getPoint__())

    def __getPoint__(self):
        return "(%s)" % self.__getRawPoint__()

    def __getRawPoint__(self):
        return "%s %s" % (self.__getRandomX__(), self.__getRandomY__())

    def __getRawPointNear__(self):
        if self.nearX == 0 and self.nearY == 0:
            self.nearX = random.randrange(MinXinKr, MaxXinKr)
            self.nearY = random.randrange(MinYinKr, MaxYinKr)
        self.nearX = random.randrange(self.nearX-1000, self.nearX+1000)
        self.nearY = random.randrange(self.nearY-1000, self.nearY+1000)
        return "%s %s" % (self.nearX, self.nearY)

    def __getRandomX__(self):
        return random.randrange(MinXinKr, MaxXinKr)

    def __getRandomY__(self):
        return random.randrange(MinYinKr, MaxYinKr)

if __name__ == '__main__':
    wktGeometryGenerator = WktGeometryGenerator()
    print(wktGeometryGenerator.createPoint())
    print(wktGeometryGenerator.createLinestring())
    for i in range(100):
        print(wktGeometryGenerator.createPointNear())
