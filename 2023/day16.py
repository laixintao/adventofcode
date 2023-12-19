with open("input") as f:
    data = [l.strip() for l in f.readlines()]

line0 = data[0]
guide = {"up": (-1, 0), "down": (1, 0), "left": (0, -1), "right": (0, 1)}


def move(energized, row, col, direction):
    "from row,col to yield  to next"
    if row < 0 or row >= len(data):
        return
    if col < 0 or col >= len(line0):
        return
    cur = data[row][col]
    energized[row][col] = True
    if cur == ".":
        row += guide[direction][0]
        col += guide[direction][1]
        yield (row, col, direction)

    if cur == "|":
        if direction == "up" or direction == "down":
            nrow = guide[direction][0] + row
            ncol = guide[direction][1] + col
            yield (nrow, ncol, direction)
        else:
            direction = "up"
            nrow = guide[direction][0] + row
            ncol = guide[direction][1] + col
            yield (nrow, ncol, direction)

            direction = "down"
            nrow = guide[direction][0] + row
            ncol = guide[direction][1] + col
            yield (nrow, ncol, direction)
    if cur == "-":
        if direction == "left" or direction == "right":
            row += guide[direction][0]
            col += guide[direction][1]
            yield (row, col, direction)
        else:
            direction = "left"
            nrow = guide[direction][0] + row
            ncol = guide[direction][1] + col
            yield (nrow, ncol, direction)

            direction = "right"
            row += guide[direction][0]
            col += guide[direction][1]
            yield (row, col, direction)
    if cur == "\\":
        direction = {"right": "down", "left": "up", "down": "right", "up": "left"}[
            direction
        ]
        row += guide[direction][0]
        col += guide[direction][1]
        yield (row, col, direction)
    if cur == "/":
        direction = {"right": "up", "left": "down", "down": "left", "up": "right"}[
            direction
        ]
        row += guide[direction][0]
        col += guide[direction][1]
        yield (row, col, direction)


def get_energized(start):
    steps = [start]
    walked = set()

    energized = [[False] * len(line0) for _ in data]

    while steps:
        step = steps.pop()
        for next_step in move(energized, *step):
            if next_step and next_step not in walked:
                steps.append(next_step)
                walked.add(next_step)

    result = 0
    for line in energized:
        for x in line:
            if x == True:
                result += 1

    return result


result = get_energized((0, 0, "right"))
print(result)

possiblities = []
for _row in range(len(data)):
    t = get_energized((_row, 0, "right"))
    possiblities.append(t)
    t = get_energized((_row, len(line0) - 1, "left"))
    possiblities.append(t)

for _col in range(len(line0)):
    t = get_energized((0, _col, "down"))
    possiblities.append(t)
    t = get_energized((len(data) - 1, _col, "up"))
    possiblities.append(t)

print(max(possiblities))
