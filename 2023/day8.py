from collections import defaultdict
import math
import re

with open("input") as f:
    lines = f.readlines()

instructions = lines[0].strip()
map_data = {}

for line in lines[2:]:
    m = re.match(r"(\w+) = \((\w+), (\w+)\)", line)
    c, l, r = m.groups()
    map_data[c] = (l, r)


def walk():
    node = "AAA"
    count = 0
    while 1:
        for move in instructions:
            if move == "L":
                index = 0
            else:
                index = 1
            node = map_data[node][index]
            count += 1
            if node == "ZZZ":
                return count


result = walk()
print(result)


def find_loop_count(node):
    count = 0
    start_count = None
    while 1:
        for move in instructions:
            if move == "L":
                index = 0
            else:
                index = 1

            node = map_data[node][index]
            count += 1
            if node[-1] == "Z":
                if not start_count:
                    start_count = count
                else:
                    return count - start_count, node


def gohst_walk():
    nodes = [n for n in map_data.keys() if n.endswith("A")]
    loops = []
    for node in nodes:
        count, end = find_loop_count(node)
        print(f"{node} will end at {end} every {count} moves")
        loops.append(count)

    lcm = 1
    for num in loops:
        lcm = lcm * num // math.gcd(lcm, num)

    return lcm


result = gohst_walk()
print(result)
