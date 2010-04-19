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

global board
board = dict()
global score
score = 0

resolution = (320,240)
pygame.font.init()
font = pygame.font.Font(None, 17)


for row in range(0,63):
    for col in range(0,63):
        board[(row,col)] = random.randint(0,1)

def get_cell(ncell):
    global board,score
    if (board.has_key(ncell)):
        if board[ncell]==1:
            score+=1
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
    global board
    for cell in board:
        neighbours = calculateNeighbours(cell)
        #print score
        #print cell
        if board[cell]==1:
            if not score in [2,3]:
                board[cell] = 0
        elif board[cell]==0:
            if score==3:
                board[cell] = 1

pygame.init()
pygame.display.set_caption("jpiiLife - Game of Life")
window = pygame.display.set_mode(resolution)
screen = pygame.display.get_surface()
cycle = 0
while True:
    screen.fill((0,0,0),(0,0,resolution[0],resolution[1]))
    updateCells()
    for x in range(0,resolution[0],10):
        pygame.draw.line(screen,(0,100,0),(x,0),(x,resolution[1]))
    for y in range(0,resolution[1],10):
        pygame.draw.line(screen,(0,100,0),(0,y),(resolution[0],y))
    
    for cell in board:
        x,y = cell
        w,h = 10,10
        if (board[cell]==1):
            screen.fill((0,160,0),(x*w,y*h,w,h))
    
    text = font.render('%s' % cycle, True, (255, 255, 255))
    # Create a rectangle
    textRect = text.get_rect()

    # Center the rectangle
    textRect.centerx = screen.get_rect().centerx
    textRect.centery = screen.get_rect().centery

    # Blit the text
    screen.blit(text, textRect)    
    pygame.display.update()
    pygame.time.delay(int(1000 * 1.0/100))
    events = pygame.event.get()
    for event in events:
        if (event.type == pygame.locals.QUIT or event.type == pygame.locals.KEYDOWN):
            sys.exit(0)
    cycle += 1
