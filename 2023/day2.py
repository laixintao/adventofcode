# 12 red cubes, 13 green cubes, and 14 blue cubes

# match: Game 1: 10 red, 7 green, 3 blue; 5 blue, 3 red, 10 green; 4 blue, 14 green, 7 red; 1 red, 11 green; 6 blue, 17 green, 15 red; 18 green, 7 red, 5 blue

import re

had_balls = {
    "red": 12,
    "green": 13,
    "blue": 14,
}


def possible(had_balls, game):
    for balls in game.split(","):
        n, ball = balls.strip().split(" ")
        if had_balls.get(ball, 0) < int(n):
            return False

    return True


result = 0
with open("input", "r") as f:
    for line in f:
        m = re.match(r"Game (\d+): (.*)", line)
        number, games = m.groups()
        for game in games.split(";"):
            if not possible(had_balls, game):
                break
        else:
            result += int(number)


print(result)

## 2
result = 0
with open("input", "r") as f:
    for line in f:
        m = re.match(r"Game (\d+): (.*)", line)
        number, games = m.groups()
        min_balls = {}
        for game in games.split(";"):
            for balls in game.split(","):
                n, ball = balls.strip().split(" ")
                min_balls[ball] = max(min_balls.get(ball, 0), int(n))
        power = 1
        for v in min_balls.values():
            power *= v 

        result += power
print(result)
