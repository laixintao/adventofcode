arr = []
with open("input", "r") as f:
    for line in f:
        arr.append(line.strip())


def is_adjacent(arr, x, y):
    for i in [0, 1, -1]:
        for j in [0, 1, -1]:
            try:
                char = arr[y + i][x + j]
            except IndexError:
                continue
            if not char.isnumeric() and char != ".":
                return True


result = 0
for y in range(len(arr)):
    line = arr[y]

    numbers = ""
    adjacent = False
    in_number = False
    for x in range(len(line)):
        c = line[x]
        if c.isnumeric():
            in_number = True
            numbers += c
            if is_adjacent(arr, x, y):
                adjacent = True

        # last one, or next char is not number
        if x == len(line) - 1 or not line[x + 1].isnumeric():
            if in_number and adjacent:
                current = int(numbers)
                result += current
            adjacent = False
            in_number = False
            numbers = ""


print(result)

def adjacent_star(arr, x, y):
    for i in [0, 1, -1]:
        for j in [0, 1, -1]:
            try:
                char = arr[y + i][x + j]
            except IndexError:
                continue
            if char == '*':
                yield x + j, y + i

result = 0
stars = {}
for y in range(len(arr)):
    line = arr[y]

    numbers = ""
    adjacent = False
    in_number = False
    for x in range(len(line)):
        c = line[x]
        if c.isnumeric():
            in_number = True
            numbers += c

        # last one, or next char is not number
        if x == len(line) - 1 or not line[x + 1].isnumeric():
            if in_number:
                current = int(numbers)
                stars_set = set()
                for number_index in range(len(numbers)):
                    for row, col in adjacent_star(arr, x-number_index, y):
                        stars_set.add(f"{row}:{col}")
                for s in stars_set:
                    stars.setdefault(s, []).append(current)
            adjacent = False
            in_number = False
            numbers = ""

for pairs in stars.values():
    if len(pairs) == 2:
        result += (pairs[0] * pairs[1])

print(result)
