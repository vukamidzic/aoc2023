import strutils
import sequtils
import std/algorithm
import sugar
import print

proc makeMatrixPart1(nums: seq[int]): seq[seq[int]] = 
    var 
        curr = nums
        offset = 0
    var matrix: seq[seq[int]] = @[curr]
    while curr.any(elem => elem != 0):
        var t = newSeq[int](len(curr))
        for i in 1..len(curr)-2-offset:
            t[i-1] = curr[i] - curr[i-1]
        matrix.add(t)
        curr = t
        offset = offset + 1
    return matrix

proc makeMatrixPart2(nums: seq[int]): seq[seq[int]] = 
    var 
        curr = nums
        offset = 0
    var matrix: seq[seq[int]] = @[curr]
    while curr.any(elem => elem != 0):
        var t = newSeq[int](len(curr))
        for i in 1..len(curr)-2-offset:
            t[i-1] = curr[i-1] - curr[i]
        matrix.add(t)
        curr = t
        offset = offset + 1
    return matrix

proc findNextElemPart1(matrix: var seq[seq[int]]): int = 
    var 
        n = len(matrix)
        i = n-1
        j = (len(matrix[0])-1)-n+1
    while i > 0 and j < len(matrix[0])-1:
        matrix[i-1][j+1] = matrix[i-1][j] + matrix[i][j]
        i = i - 1
        j = j + 1
    return matrix[i][j]

proc findNextElemPart2(matrix: var seq[seq[int]]): int = 
    var 
        n = len(matrix)
        i = n-1
        j = (len(matrix[0])-1)-n+1
    while i > 0 and j < len(matrix[0])-1:
        matrix[i-1][j+1] = matrix[i-1][j] - matrix[i][j]
        i = i - 1
        j = j + 1
    return matrix[i][j]

proc part1(filePath: string): int = 
    var seqs = readFile(filePath)
                    .splitLines()
                    .map(s => s.split(' ').map(x => parseInt(x)))
    seqs = seqs.map(s => (var t = s; t.add(0); t))
    for sequence in seqs:
        var matrix = makeMatrixPart1(sequence)
        result += findNextElemPart1(matrix)

proc part2(filePath: string): int = 
    var seqs = readFile(filePath)
                    .splitLines()
                    .map(s => s.split(' ').map(x => parseInt(x)))
    seqs = seqs.map(s => s.reversed()).map(s => (var t = s; t.add(0); t))
    for sequence in seqs:
        var matrix = makeMatrixPart2(sequence)
        result += findNextElemPart2(matrix)