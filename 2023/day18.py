with open("input") as f:
    data = f.readlines()

right_most = 0
down_most = 0
current_row = 0
current_col = 0
points = []

for line in data:
    direction, count, color = line.split(" ")
    count = int(count)
    if direction == "R":
        for i in range(1, count + 1):
            points.append((current_row, current_col + i, color))
        current_col += count
        right_most = max(right_most, current_col)
    if direction == "L":
        for i in range(1, count + 1):
            points.append((current_row, current_col - i, color))
        current_col -= count
    if direction == "D":
        for i in range(1, count + 1):
            points.append((current_row + i, current_col, color))
        current_row += count
        down_most = max(down_most, current_row)
    if direction == "U":
        for i in range(1, count + 1):
            points.append((current_row - i, current_col, color))
        current_row -= count

rect = [[False] * (right_most + 1) for _ in range(down_most + 1)]
for p in points:
    row, col, _ = p
    rect[row][col] = True


def inside(r, c, rect):
    if rect[row_i][col_i]:
        return True
    total_row = len(rect)
    total_cross = 0
    edge_connect_right = edge_connect_left = 0
    # left most or right most
    if c == 0 or c == len(rect[r]) - 1:
        return False

    for line_i in range(r + 1, total_row):
        if not rect[line_i][c]:
            continue
        left = rect[line_i][c - 1]
        right = rect[line_i][c + 1]
        if left and right:
            total_cross += 1
            continue
        elif left and not right:
            edge_connect_left += 1
            continue
        elif not left and right:
            edge_connect_right += 1
            continue
    total_cross = total_cross + min(edge_connect_left, edge_connect_right)
    return total_cross % 2 == 1


for row_i in range(len(rect)):
    row = rect[row_i]
    for col_i in range(len(row)):
        if inside(row_i, col_i, rect):
            rect[row_i][col_i] = True

for row in rect:
    for c in row:
        if c:
            print("#", end="")
        else:
            print(".", end="")
    print()

result = sum(sum(row) for row in rect)
print(result)
print(list(sum(row) for row in rect))
