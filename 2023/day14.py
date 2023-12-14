import copy
with open("input") as f:
    data = [list(line.strip()) for line in f.readlines()]

line0 = data[0]
total_col = len(line0)


def weight(col_i, data):
    result = 0
    all_rocks = [line[col_i] for line in data]
    current_weight = len(all_rocks)

    for idx, char in enumerate(all_rocks):
        if char == "O":
            result += current_weight
            current_weight -= 1
        elif char == ".":
            pass
        elif char == "#":
            current_weight = len(all_rocks) - idx - 1
    return result


result = 0
for col_i in range(total_col):
    result += weight(col_i, data)
print(result)


def cycle_north(data):
    for col_i in range(total_col):
        last_dot = None
        for row_i in range(len(data)):
            char = data[row_i][col_i]
            if char == ".":
                if last_dot is None:
                    last_dot = row_i
            if char == "O":
                if last_dot is not None:
                    data[last_dot][col_i] = "O"
                    data[row_i][col_i] = "."
                    last_dot += 1
            if char == "#":
                last_dot = None
    return data


def cycle_west(data):
    for row_i in range(len(data)):
        last_dot = None
        for col_i in range(len(line0)):
            char = data[row_i][col_i]
            if char == ".":
                if last_dot is None:
                    last_dot = col_i
            if char == "O":
                if last_dot is not None:
                    data[row_i][last_dot] = "O"
                    data[row_i][col_i] = "."
                    last_dot += 1
            if char == "#":
                last_dot = None
    return data


def cycle_south(data):
    for col_i in range(total_col):
        last_dot = None
        for row_i in range(len(data) - 1, -1, -1):
            char = data[row_i][col_i]
            if char == ".":
                if last_dot is None:
                    last_dot = row_i
            if char == "O":
                if last_dot is not None:
                    data[last_dot][col_i] = "O"
                    data[row_i][col_i] = "."
                    last_dot -= 1
            if char == "#":
                last_dot = None
    return data


def cycle_east(data):
    for row_i in range(len(data)):
        last_dot = None
        for col_i in range(len(line0) - 1, -1, -1):
            char = data[row_i][col_i]
            if char == ".":
                if last_dot is None:
                    last_dot = col_i
            if char == "O":
                if last_dot is not None:
                    data[row_i][last_dot] = "O"
                    data[row_i][col_i] = "."
                    last_dot -= 1
            if char == "#":
                last_dot = None
    return data


def cycle(data):
    data1 = cycle_north(data)
    # for line in data1:
    #     print("".join(line))
    # print("*" * 10)
    data1 = cycle_west(data)
    # for line in data1:
    #     print("".join(line))
    # print("*" * 10)
    data1 = cycle_south(data)
    # for line in data1:
    #     print("".join(line))
    # print("*" * 10)
    data1 = cycle_east(data)
    # for line in data1:
    #     print("".join(line))
    
    # print("----------------")
    return data1


def get_identical_cycle(data):
    count = 0
    cache = {}

    while 1:
        last = "".join("".join(line) for line in data)
        if last not in cache:
            cache[last] = count
        else:
            loop_count = count - cache[last]
            print(f"{cache[last]=}, {count=}, {loop_count=}")
            cache[last] = count
            identical_count = ((1000000000-cache[last]) % loop_count) + count
            return identical_count
        count += 1
        data = cycle(data)



with open("input") as f:
    data = [list(line.strip()) for line in f.readlines()]
identical_count = get_identical_cycle(data)

with open("input") as f:
    data = [list(line.strip()) for line in f.readlines()]
print(f"{identical_count=}")
for c in range(identical_count):
    print(f"cycle for count={c}")
    data = cycle(data)
    for line in data:
        print("".join(line))

result = 0
total_row = len(data)
for index, row in enumerate(data):
    row_count  = 0
    for col in row:
        if col == 'O':
            score =  (total_row - index )
            row_count += score
    result += row_count
    print("".join(row), row_count)
print(result)
