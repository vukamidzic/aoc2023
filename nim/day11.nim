import strutils
import print

type Position = (int, int)

proc getPositions(galaxies: seq[string]): seq[Position] = 
    result = @[]
    for i in 0..len(galaxies)-1:
        for j in 0..len(galaxies[0])-1:
            if galaxies[i][j] == '#': result.add((i, j))

proc shortestDists(positions: seq[Position]): int = 
    for i in 0..len(positions)-1:
        for j in i+1..len(positions)-1:
            result += abs(positions[i][0] - positions[j][0]) + abs(positions[i][1] - positions[j][1])                 

proc part1(filePath: string): int = 
    var lines = readFile(filePath).splitLines()
    var galaxies: seq[string] = @[] 
    for line in lines:
        galaxies.add(line)
        if not line.contains('#'): galaxies.add(line)

    var toEvade: seq[int] = @[]
    for j in 0..len(galaxies[0]):
        var vertLine = ""
        for i in 0..len(galaxies)-1: vertLine.add(galaxies[i][j])
        if (not vertLine.contains('#')) and (not toEvade.contains(j)):
            for i in 0..len(galaxies)-1:
                let tmp = galaxies[i].substr(j+1, len(galaxies[0])-1)
                galaxies[i] = galaxies[i].substr(0,j)
                galaxies[i].add('.')
                galaxies[i].add(tmp)
            toEvade.add(j + 1)
    echo toEvade

    var positions = getPositions(galaxies)
    return shortestDists(positions)