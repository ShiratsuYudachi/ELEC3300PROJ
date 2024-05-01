import os

path = os.popen('pwd').read().strip()+'/'

is2D = True if input('Is this a 2D file? (y/n): ') == 'y' else False
Xscale = 0.4#10.0
Yscale = 0.4#2.0
Zscale = 1.0

import numpy as np
generatedArray = []

lastG = -1
lastX = 0
lastY = 0
lastZ = 0
lastF = 800

G = -1
X = 0
Y = 0
Z = 0
F = 900

def matchFirstFloat(line) -> str:
    matched = ''
    for char in line:
        if (char.isdigit() or char == '.' or char == '-'):
            matched += char
        else:
            break
    return matched

def parseLine(line):
    global G
    global X
    global Y
    global Z
    global F
    global lastG
    global lastX
    global lastY
    global lastZ
    global lastF

    if ('G' in line):
        lastG = G
        G = float(matchFirstFloat(line.split('G')[-1]))
    if ('X' in line):
        lastX = X
        X = float(matchFirstFloat(line.split('X')[-1])) * Xscale
    if ('Y' in line):
        lastY = Y
        Y = float(matchFirstFloat(line.split('Y')[-1])) * Yscale
    if ('Z' in line):
        lastZ = Z
        Z = float(matchFirstFloat(line.split('Z')[-1])) * Zscale
    if ('F' in line):
        lastF = F
        F = float(matchFirstFloat(line.split('F')[-1]))


with open(path+'scripts/test.gcode', 'r') as f:
    lines = f.readlines()
    for line in lines:
        parseLine(line.strip())
        if (G == 0):
            if (is2D):
                generatedArray.append([lastX, lastY, 3.5, F])
                generatedArray.append([X, Y, 3.5, F])
                generatedArray.append([X, Y, Z, F])
            else:
                generatedArray.append([X, Y, Z, F])
        if (G == 1):
            generatedArray.append([X, Y, Z, F])

def prettyPrint(array):
    for line in array:
        print(line)




carr = str(generatedArray).replace('[', '{').replace(']', '}').replace('},', '},\n')

with open('Core/Inc/gcode.h', 'w') as f:
    f.write(f'int gcodeLegth = {len(generatedArray)};\n const float gcode[{len(generatedArray)}][4] = {carr};')