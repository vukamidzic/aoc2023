import strutils
import tables

proc isNum(c: char): bool = c in '0'..'9'

proc part1(filePath: string): int = 
    var sum = 0
    let file = open(filePath)
    while not file.endOfFile():
        let word = file.readLine()
        var 
            l = 0
            r = len(word)-1
        while true:
            if not isNum(word[l]): l += 1
            elif not isNum(word[r]): r -= 1
            else: break
        sum += 10*parseInt($word[l]) + parseInt($word[r])
    return sum

proc part2(filePath: string): int = 
    var sum = 0
    let file = open(filePath)
    while not file.endOfFile():
        var word = file.readLine()
        let mp = {
            "one": '1',
            "two": '2',
            "three": '3',
            "four": '4',
            "five": '5',
            "six": '6',
            "seven": '7',
            "eight": '8',
            "nine": '9'
        }.toTable
        for key, val in mp:
            var idx = word.find(key)
            if idx != -1:
                word[idx+1] = val
            idx = word.rfind(key)
            if idx != -1:
                word[idx+1] = val
        var 
            l = 0
            r = len(word)-1
        while (l <= r):
            if not isNum(word[l]):
                l += 1
            elif not isNum(word[r]):
                r -= 1
            else: break
        sum += 10*parseInt($word[l]) + parseInt($word[r])
    return sum            