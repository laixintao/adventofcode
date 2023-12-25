import re


with open("input") as f:
    data = f.readlines()

current_row = 0
current_col = 0
last_row = 0
last_col = 0
acc = 0

perimeter = 0

for line in data:
    direction, count, color = line.split(" ")
    count = int(count)
    perimeter += count
    if direction == "R":
        current_col += count
    if direction == "L":
        current_col -= count
    if direction == "D":
        current_row += count
    if direction == "U":
        current_row -= count

    acc += last_row * current_col - current_row * last_col
    last_row = current_row
    last_col = current_col

acc += last_row * current_col - current_row * last_col

result = abs(acc/2)  + perimeter /2 + 1
print(result)

with open("input") as f:
    data = f.readlines()

current_row = 0
current_col = 0
last_row = 0
last_col = 0
acc = 0

perimeter = 0

for line in data:
    _, _, color = line.split(" ")
    m = re.match(r'\(#(.{5})(\d)\)', color)
    dis = int(m.group(1), 16)
    direc = m.group(2)
    count = dis
    direction = {"0": "R", "1": "D", "2": "L", "3":"U"}[direc]
    perimeter += count
    if direction == "R":
        current_col += count
    if direction == "L":
        current_col -= count
    if direction == "D":
        current_row += count
    if direction == "U":
        current_row -= count

    acc += last_row * current_col - current_row * last_col
    last_row = current_row
    last_col = current_col

acc += last_row * current_col - current_row * last_col

result = abs(acc/2)  + perimeter /2 + 1
print(result)
