import strutils
import sugar
import sequtils
import tables

proc stripData(data: string): seq[string] = 
    data.split(';')
        .map(s => s.strip(true, false))

proc part1(filePath: string): int = 
    let lines = readFile(filePath).splitLines()
    var 
        sum = 0
        gameNum = 1
    for line in lines:
        var data = line.split(':')
        let rounds = stripData(data[1].strip(true, false))
        var possible = true
        for round in rounds:
            let curr = round.split(',').map(s => s.strip(true, false))
            for balls in curr:
                let 
                    info = balls.split(' ')
                    color = info[1]
                    n = parseInt(info[0])
                case color:
                    of "red": 
                        if n > 12: possible = false
                    of "blue":
                        if n > 14: possible = false
                    of "green": 
                        if n > 13: possible = false
        if possible: sum += gameNum
        gameNum += 1 
    return sum

proc part2(filePath: string): int = 
    let lines = readFile(filePath).splitLines()
    var 
        sum = 0
    for line in lines:
        var data = line.split(':')
        let rounds = stripData(data[1].strip(true, false))
        var 
            maxRed = 0
            maxGreen = 0
            maxBlue = 0
        for round in rounds:
            let curr = round.split(',').map(s => s.strip(true, false))
            for balls in curr:
                let 
                    info = balls.split(' ')
                    color = info[1]
                    n = parseInt(info[0])
                case color:
                    of "red": 
                        if n > maxRed: maxRed = n
                    of "blue":
                        if n > maxBlue: maxBlue = n
                    of "green": 
                        if n > maxGreen: maxGreen = n
        sum += maxRed*maxGreen*maxBlue
    return sum

echo part2("input.txt")
