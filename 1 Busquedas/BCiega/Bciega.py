from random import randint
import os
import sys 
import time
from time import sleep
print(sys.path)

class Node:

    def __init__(self, x, y):

        self.x = x 
        self.y = y
        self.vecinos = []
        self.previous = None
        self. obstaculo = False


    def add_vecinos(self,grid, columnas, filas):

        vecino_x = self.x
        vecino_y = self.y

        ##Vecinos horizontales y verticales
        if vecino_x < columnas - 1:
            self.vecinos.append(grid[vecino_x+1][vecino_y])
        if vecino_x > 0:
            self.vecinos.append(grid[vecino_x-1][vecino_y])
        if vecino_y < filas -1:
            self.vecinos.append(grid[vecino_x][vecino_y +1])
        if vecino_y > 0: 
            self.vecinos.append(grid[vecino_x][vecino_y-1])

        #Vecinos diagonales    
        if vecino_x > 0 and vecino_y > 0:
            self.vecinos.append(grid[vecino_x-1][vecino_y-1])
        if vecino_x < columnas -1 and vecino_y > 0:
            self.vecinos.append(grid[vecino_x+1][vecino_y-1])
        if vecino_x > 0 and vecino_y <filas -1:
            self.vecinos.append(grid[vecino_x-1][vecino_y+1])
        if vecino_x < columnas -1 and vecino_y < filas -1:
            self.vecinos.append(grid[vecino_x+1][vecino_y+1])


        
class BCiego:

    def __init__(self, columnas, filas, start, end):

        self.columnas = columnas
        self.filas = filas
        self.start = start
        self.end = end
        self.obsRatio = False
        self.obsList = False

    @staticmethod
    def clean_open_set(openSet, nodoActual):

        for i in range(len(openSet)):
            if openSet[i] == nodoActual:
                openSet.pop(i)
                break

        return openSet

    @staticmethod
    def crearMalla(columnas, filas):

        grid = []
        for _ in range(columnas):
            grid.append([])
            for _ in range(filas):
                grid[-1].append(0)
        
        return grid

    @staticmethod
    def llenarMallas(grid, columnas, filas, obsRatio = False, obsList = False):

        for i in range(columnas):
            for j in range(filas):
                grid[i][j] = Node(i,j)
                if obsRatio == False:
                    pass
                else:
                    n = randint(0,100)
                    if n < obsRatio: grid[i][j].obstaculo = True
        if obsList == False:
            pass
        else:
            for i in range(len(obsList)):
                grid[obsList[i][0]][obsList[i][1]].obstaculo = True

        return grid

    @staticmethod
    def getVecinos(grid, columnas, filas):
        for i in range(columnas):
            for j in range(filas):
                grid[i][j].add_vecinos(grid, columnas, filas)
        return grid
    
    @staticmethod
    def start_path(openSet, closedSet, nodoActual, end):
        
        nodoActual = openSet[0]
        caminoFinal = []
        if nodoActual == end:
            temp = nodoActual
            while temp.previous:
                caminoFinal.append(temp.previous)
                temp = temp.previous

        openSet = BCiego.clean_open_set(openSet, nodoActual)
        closedSet.append(nodoActual)
        vecinos = nodoActual.vecinos
        for vecino in vecinos:
            if (vecino in closedSet) or (vecino.obstaculo == True):
                continue
            else:
                control_flag = 0
                for k in range(len(openSet)):
                    if vecino.x == openSet[k].x and vecino.y == openSet[k].y:
                        openSet[k].previous = nodoActual
                        control_flag = 1
                if control_flag == 1:
                    pass
                else:
                    vecino.previous = nodoActual
                    openSet.append(vecino)

        return openSet, closedSet, nodoActual, caminoFinal

    def main(self):

        grid = BCiego.crearMalla(self.columnas, self.filas)
        grid = BCiego.llenarMallas(grid, self.columnas, self.filas, obsRatio = 30)
        grid = BCiego.getVecinos(grid, self.columnas, self.filas)
        openSet  = []
        closedSet  = []
        nodoActual = None
        caminoFinal  = []
        openSet.append(grid[self.start[0]][self.start[1]])
        self.end = grid[self.end[0]][self.end[1]]
        while len(openSet) > 0:
            openSet, closedSet, nodoActual, caminoFinal = BCiego.start_path(openSet, closedSet, nodoActual, self.end)
            if len(caminoFinal) > 0:
                break

        return caminoFinal


columnas = 25
filas = 25 
start = [0,0]
end = [15,19]
openSet  = []
closedSet  = []
nodoActual = None
caminoFinal  = []
grid = []


def mostrar(grid_element,color, width,height): 
    if grid_element.obstaculo == True:
            fill("black")
    else:
        fill(color)
    noStroke()
    rect(grid_element.x * width, grid_element.y * height, width-1 , height-1)


def setup():
    global grid
    createCanvas(500, 500)
    background(160)

        
    
flag = False   


def draw():
    
    global grid
    global end
    global openSet
    global closedSet
    global caminoFinal
    global nodoActual
    global flag
    global start

    global columnas 
    global filas 
  
    frameRate(60)
    w = width / columnas
    h = height / filas
    if flag == False:
        
 

        grid = BCiego.crearMalla(columnas, filas)   
        grid = BCiego.llenarMallas(grid, columnas, filas, obsRatio = 30)
        grid = BCiego.getVecinos(grid, columnas, filas)
        start = grid[start[0]][start[1]]
        end = grid[end[0]][end[1]]
        end.obstaculo = False
        start.obstaculo = False

        background(0)
        for i in range(columnas):
            for j in range(filas):
                mostrar(grid[i][j], color(255),w,h)
        stroke(0,0,0)
        line(0, 0, 0, width)
        line(0,0,height, 1)
        openSet.append(start)

        
        flag = True

    if len(openSet) > 0:
        openSet, closedSet, nodoActual, caminoFinal = BCiego.start_path(openSet, closedSet, nodoActual, end)

        mostrar(start, "green", w,h)
        mostrar(end, "red",w,h)
        for i in range(len(openSet)):
            mostrar(openSet[i], "#00ffbf",w,h)

        for i in range(len(closedSet)):
            mostrar(closedSet[i], "#ffa500",w,h)
            mostrar(start, "green", w,h)

        mostrar(nodoActual, "#8a2be2",w,h)

        if len(openSet) == 0:
            print("No way!")
            #noLoop()
    
            frameRate(1)
            columnas = 25
            filas = 25 
            start = [0,0]
            end = [15,19]
            openSet  = []
            closedSet  = []
            nodoActual = None
            caminoFinal  = []
            grid = []
            flag = False
            

        if len(caminoFinal) > 0:
            for i in range(len(caminoFinal)):
                mostrar(caminoFinal[i], "#8a2be2",w,h)
                #mostrar(caminoFinal[i], "red",w,h)
            mostrar(start, "green", w,h)
            mostrar(end, "red",w,h)

            print("Listo")
            frameRate(1)
            columnas = 25
            filas = 25 
            start = [0,0]
            end = [15,19]
            openSet  = []
            closedSet  = []
            nodoActual = None
            caminoFinal  = []
            grid = []
            flag = False
