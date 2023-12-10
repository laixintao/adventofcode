with open("input") as f:
    data = [x.strip() for x in f.readlines()]


def get_start(data):
    for y in range(len(data)):
        line = data[y]
        for x in range(len(line)):
            if data[y][x] == "S":
                return x, y


start_x, start_y = (111, 41)
print(f"{start_x=}, {start_y=}")


direction = {
    "left": (-1, 0),
    "right": (1, 0),
    "up": (0, -1),
    "down": (0, 1),
}

pipe = {
    # pipe, and how do we get there?
    ("|", "down"): "down",
    ("|", "up"): "up",
    ("-", "left"): "left",
    ("-", "right"): "right",
    ("J", "right"): "up",
    ("J", "down"): "left",
    ("7", "right"): "down",
    ("7", "up"): "left",
    ("F", "up"): "right",
    ("F", "left"): "down",
    ("L", "down"): "right",
    ("L", "left"): "up",
}

count = 1
track = []
# initial direction
# if input changed, this need to change
last_move = "left"
cur_x = start_x + direction[last_move][0]
cur_y = start_y + direction[last_move][1]
track.append((cur_x, cur_y))
while cur_x != start_x or cur_y != start_y:
    cur_pipe = data[cur_y][cur_x]
    next_dir = pipe[(cur_pipe, last_move)]
    count += 1
    cur_x += direction[next_dir][0]
    cur_y += direction[next_dir][1]
    last_move = next_dir
    track.append((cur_x, cur_y))
    print(f"{count=} {cur_x=}, {cur_y=}, {last_move=} {cur_pipe=}")

result = int(count / 2)
print(result)

tiles = 0
max_y = len(data)


def inside(x, y, track):
    cross = 0
    connect_left = 0
    connect_right = 0
    for yy in range(y + 1, max_y):
        if (x, yy) in track:
            char = data[yy][x]
            if char == "-":
                cross += 1
            if char in ["J", "7"]:
                connect_left += 1
            if char in ["F", "L"]:
                connect_right += 1

    cross += min(connect_left, connect_right)
    return cross % 2


for y in range(len(data)):
    print(f"line = {y}")
    for x in range(len(data[y])):
        if (x, y) in track:
            continue
        if inside(x, y, track):
            print(x, y)
            tiles += 1

print(tiles)
