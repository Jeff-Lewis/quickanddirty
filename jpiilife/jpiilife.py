#!/usr/bin/python
###########################################################################################
# Author: 
#     Juhapekka Piiroinen
# Email:
#     juhapekka.piiroinen@gmail.com
# License: 
#     GNU/GPLv3
#
# Description:
#     A quick-and-dirty game of life
#
############################################################################################
# (C) 2010 Juhapekka Piiroinen
############################################################################################
import pygame,pygame.locals,sys,random
import getopt

global board,resolution,cellsize,framelimit,boardscore
board = dict()
boardscore = dict()
global score
score = 0
resolution = (320,240)
cellsize = 1
framelimit = 100
life = -1


def usage():
    print "USAGE: jpiilife.py --width=320 --height=240 --cell=10 --framelimit=100 --life=10"

if len(sys.argv)<2:
    usage()
    sys.exit(2)
    
try:
    optlist,args = getopt.getopt(sys.argv[1:],None,["width=","height=","cell=","framelimit=","life="])
except getopt.GetoptError, err:
    print str(err)
    usage()
    sys.exit(2)

newresolution = {resolution[0]:"", resolution[1]:""}
for o,a in optlist:
    if o=="--width":
        newresolution['width'] = int(a)
    elif o=="--height":
        newresolution['height'] = int(a)
    elif o=="--cell":
        cellsize = int(a)
    elif o=="--framelimit":
        framelimit = int(a)
    elif o=="--life":
        life = int(a)
resolution = (newresolution['width'],newresolution['height'])

pygame.font.init()
font = pygame.font.Font(None, 17)


def reset_board():
    global resolution,cellsize,board,life
    lifeleft = life
    for row in range(0,resolution[0]/cellsize):
        for col in range(0,resolution[1]/cellsize):
            board[(row,col)] = 0
            
    for row in range(0,resolution[0]/cellsize):
        for col in range(0,resolution[1]/cellsize):
            board[(row,col)] = random.randint(0,1)
            lifeleft -= board[(row,col)]
            if lifeleft==0:
                return
                

def get_cell(ncell):
    global board,score
    if (board.has_key(ncell)):
        if board[ncell]==1:
            score += 1
        return board[ncell]
    else:
        return 0

def calculateNeighbours(cell):
    global board,score
    neighbours = dict()
    score = 0
    # 000
    # 0-0
    # x00
    ncell = (cell[0]-1,cell[1]-1)
    neighbours[ncell] = get_cell(ncell)
    # 000
    # 0-0
    # 0x0
    ncell = (cell[0],cell[1]-1)
    neighbours[ncell] = get_cell(ncell)
    # 000
    # 0-0
    # 00x
    ncell = (cell[0]+1,cell[1]-1)
    neighbours[ncell] = get_cell(ncell)
    # 000
    # 0-x
    # 000
    ncell = (cell[0]+1,cell[1])
    neighbours[ncell] = get_cell(ncell)
    # 00x
    # 0-0
    # 000
    ncell = (cell[0]+1,cell[1]+1)
    neighbours[ncell] = get_cell(ncell)
    # 0x0
    # 0-0
    # 000
    ncell = (cell[0],cell[1]+1)
    neighbours[ncell] = get_cell(ncell)
    # x00
    # 0-0
    # 000
    ncell = (cell[0]-1,cell[1]+1)
    neighbours[ncell] = get_cell(ncell)
    # 000
    # x-0
    # 000
    ncell = (cell[0]-1,cell[1])
    neighbours[ncell] = get_cell(ncell)
    return neighbours

def updateCells():
    global board,score,boardscore
    updateCount = 0
    for cell in board:
        neighbours = calculateNeighbours(cell)
        boardscore[cell] = score
        if board[cell]>0:
            if not boardscore[cell] in [2,3]:
                board[cell] = 0
                updateCount+=1
        elif board[cell]==0:
            if boardscore[cell]==3:
                board[cell] = 1
                updateCount+=1
    return updateCount

pygame.init()
pygame.display.set_caption("jpiiLife - Game of Life")
window = pygame.display.set_mode(resolution)
screen = pygame.display.get_surface()
cycle = 0
updateCount = 1
reset_board()

while True:
    if (updateCount>0):
        updateCount = updateCells()

    screen.fill((0,0,0),(0,0,resolution[0],resolution[1]))

    for x in range(0,resolution[0],cellsize):
        pygame.draw.line(screen,(0,100,0),(x,0),(x,resolution[1]))
    for y in range(0,resolution[1],cellsize):
        pygame.draw.line(screen,(0,100,0),(0,y),(resolution[0],y))
    
    for cell in board:
        x,y = cell
        w,h = cellsize,cellsize
        if (board[cell]==1):
            scoreb = boardscore[cell]
            color = (0,160,0)
            if (scoreb==2):
                color = (0,190,0)
            elif (scoreb==3):
                color = (0,140,0)
            screen.fill(color,(x*w,y*h,w,h))
    
    text = font.render('%s' % cycle, True, (255, 255, 255))
    # Create a rectangle
    textRect = text.get_rect()

    # Center the rectangle
    textRect.centerx = screen.get_rect().centerx
    textRect.centery = screen.get_rect().centery

    # Blit the text
    screen.blit(text, textRect)    
    pygame.display.update()
    pygame.time.delay(int(1000 * 1.0/framelimit))
    events = pygame.event.get()
    for event in events:
        if (event.type == pygame.locals.QUIT):
            sys.exit(0)
        if (event.type == pygame.locals.KEYUP):
            reset_board()
            updateCount = 1
            cycle = 0
    if updateCount>0:
        cycle += 1
