import strutils
import sequtils
import algorithm
import sugar
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

    var positions = getPositions(galaxies)
    return shortestDists(positions)

proc part2(filePath: string): int = 
    const INC = 999_999
    var lines = readFile(filePath).splitLines()
    var 
        galaxies: seq[string] = @[] 
        hor_empty: seq[int] = @[]
        ver_empty: seq[int] = @[]
        i = 0
    for line in lines: 
        galaxies.add(line)
        if not line.contains('#'): hor_empty.add(i)
        i += 1

    var 
        positions = getPositions(galaxies)
        ys: seq[int] = positions.map(p => p[0])
        xs: seq[int] = positions.map(p => p[1])

    for j in 0..len(galaxies[0])-1:
        var vertLine = ""
        for i in 0..len(galaxies)-1: vertLine.add(galaxies[i][j])
        if (not vertLine.contains('#')): ver_empty.add(j)

    print ver_empty

    for i in 0..len(xs)-1:
        let gaps = len(ver_empty.filter(x => xs[i] > x))
        xs[i] += gaps*INC

    for i in 0..len(ys)-1:
        let gaps = len(hor_empty.filter(x => ys[i] > x))
        ys[i] += gaps*INC

    positions = ys.zip(xs)
    return shortestDists(positions)

echo part2("input.txt")

    