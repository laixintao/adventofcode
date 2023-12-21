import heapq
from collections import defaultdict
with open("input") as f:
    data = [l.strip() for l in f.readlines()]


line0 = data[0]

directions = [
    # up
    (-1, 0),
    # down
    (1, 0),
    # left
    (0, -1),
    #right
    (0, 1),
]

minimal_heat = defaultdict(lambda: float("Inf"))

def move(smallest, biggest, current_heat, current_location, current_direction):
    if current_direction == "v":
        next_direction = [(0,-1), (0,1)]
        vh = "h"
    elif current_direction == "h":
        next_direction = [(-1,0), (1,0)]
        vh = "v"
    
    for direction in next_direction:
        row, col = direction
        for step in range(smallest, biggest+1):
            next_location = (current_location[0] + row * step,  current_location[1] + col * step)
            if next_location[0] < 0 or next_location[0] >= len(data):
                continue
            if next_location[1] < 0 or next_location[1] >= len(line0):
                continue

            next_heat = current_heat
            for ci in range(1,step+1):
                crow = current_location[0] + row * ci
                ccol = current_location[1] + col * ci
                next_heat += int(data[crow][ccol])

            key = (next_location[0],next_location[1],vh)
            if minimal_heat[key] > next_heat:
                minimal_heat[key] = next_heat
                yield next_heat, next_location, vh

possibles = [
    (0, (0,0), "v"),
    (0, (0,0), "h"),
]

heapq.heapify(possibles)

while possibles:
    next_possible = heapq.heappop(possibles)
    # print(len(possibles))
    for n in move(1, 3, *next_possible):
        heapq.heappush(possibles, n)


result = min(minimal_heat[(len(data)-1, len(line0)-1, "v")],
        minimal_heat[(len(data)-1, len(line0)-1, "h")])
print(result)

#============part2

minimal_heat = defaultdict(lambda: float("Inf"))
possibles = [
    (0, (0,0), "v"),
    (0, (0,0), "h"),
]

heapq.heapify(possibles)

while possibles:
    next_possible = heapq.heappop(possibles)
    # print(len(possibles))
    for n in move(4, 10, *next_possible):
        heapq.heappush(possibles, n)


result = min(minimal_heat[(len(data)-1, len(line0)-1, "v")],
        minimal_heat[(len(data)-1, len(line0)-1, "h")])
print(result)
