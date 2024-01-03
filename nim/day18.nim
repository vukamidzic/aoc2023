import strutils
import sequtils
import algorithm
import sugar
import print
import tables

type Pos = (int, int)

proc dist(p1, p2: Pos): int = abs(p2[0]-p1[0]) + abs(p2[1]-p1[1]) 

proc det(p1, p2: Pos): int = p1[0]*p2[1] - p2[0]*p1[1] 

proc area(positions: seq[Pos]): int = 
    let n = len(positions)
    var 
        area = 0
        perim = 0
    for i in 0..n-2:
        area += det(positions[i], positions[i+1])
        perim += dist(positions[i], positions[i+1])
    result = (area + perim) div 2 + 1

proc part1(filepath: string): int = 
    let lines = readFile(filepath).splitLines()
    var 
        positions: seq[Pos] = @[(0,0)]
        index = 0
    for line in lines: 
        let info = line.split(" ")
        let (dir, steps) = (info[0], parseInt(info[1]))
        case dir:
            of "R":
                let new_pos: Pos = (positions[index][0], positions[index][1] + steps)
                positions.add(new_pos)
                index = index + 1
            of "L":
                let new_pos: Pos = (positions[index][0], positions[index][1] - steps)
                positions.add(new_pos)
                index = index + 1
            of "D":
                let new_pos: Pos = (positions[index][0] - steps, positions[index][1])
                positions.add(new_pos)
                index = index + 1
            of "U":
                let new_pos: Pos = (positions[index][0] + steps, positions[index][1])
                positions.add(new_pos)
                index = index + 1
    result = area(positions)

proc part2(filepath: string): int = 
    let lines = readFile(filepath).splitLines()
    let dirs = {
        '0': "R",
        '1': "D",
        '2': "L",
        '3': "U"
    }.toTable 
    var 
        positions: seq[Pos] = @[(0,0)]
        index = 0
    for line in lines:
        var info = line.split(" ")[2]
        removePrefix(info, "(")
        removeSuffix(info, ")")
        let (steps, dir) = (parseHexInt(info[0..len(info)-2]), dirs[info[len(info)-1]])
        case dir:
            of "R":
                let new_pos: Pos = (positions[index][0], positions[index][1] + steps)
                positions.add(new_pos)
                index = index + 1
            of "L":
                let new_pos: Pos = (positions[index][0], positions[index][1] - steps)
                positions.add(new_pos)
                index = index + 1
            of "D":
                let new_pos: Pos = (positions[index][0] - steps, positions[index][1])
                positions.add(new_pos)
                index = index + 1
            of "U":
                let new_pos: Pos = (positions[index][0] + steps, positions[index][1])
                positions.add(new_pos)
                index = index + 1
    result = area(positions)

echo part2("input.txt")