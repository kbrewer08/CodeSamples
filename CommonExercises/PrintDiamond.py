import sys


def printRow(spaces, stars):
    for i in range(0, spaces):
        sys.stdout.write(' ')
    for j in range(0, stars):
        sys.stdout.write('*')
    print ''
    
def printDiamond(width):
    if width < 3:
        width = 3

    if width % 2 == 0:
        width = width + 1

    for i in range(0, width):
        spaces = abs((width / 2) - i)
        stars  = width - (spaces * 2)
        printRow(spaces, stars)

printDiamond(23)

