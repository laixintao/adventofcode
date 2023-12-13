with open("input") as f:
    data = f.read()

squares = data.split("\n\n")
result = 0


def is_col_mirror(col_index, lines, line0):
    for j in range(col_index + 1):
        this_col = j
        reflect_col = (col_index - j) + 1 + col_index
        if reflect_col >= len(line0):
            continue

        for line in lines:
            if line[this_col] != line[reflect_col]:
                return False
    return True


def find_col_mirror(square):
    lines = square.split("\n")
    line0 = lines[0]
    for col_index in range(len(line0) - 1):
        if is_col_mirror(col_index, lines, line0):
            return col_index


def is_row_mirror(row_index, lines):
    for j in range(row_index + 1):
        this_row = j
        reflect_row = (row_index - j) + 1 + row_index
        if reflect_row >= len(lines):
            continue
        if lines[this_row] != lines[reflect_row]:
            return False
    return True


def find_row_mirror(square):
    lines = square.split("\n")
    for row_index in range(len(lines) - 1):
        print(f"{row_index=}")
        if is_row_mirror(row_index, lines):
            return row_index


for square in squares:
    print("=" * 10)
    print(square)
    col = find_col_mirror(square)
    if col is not None:
        col += 1
        print("col -> ", col)
        result += col
        continue
    row = find_row_mirror(square)
    if row is not None:
        row += 1
        print("row -> ", row)
        result += 100 * row
print(result)

result = 0


def is_col_mirror2(col_index, lines, line0):
    diff_count = 0
    for j in range(col_index + 1):
        this_col = j
        reflect_col = (col_index - j) + 1 + col_index
        if reflect_col >= len(line0):
            continue

        for line in lines:
            if line[this_col] != line[reflect_col]:
                diff_count += 1
                if diff_count > 1:
                    return False
    if diff_count == 1:
        return True
    else:
        return False


def find_col_mirror2(square):
    lines = square.split("\n")
    line0 = lines[0]
    for col_index in range(len(line0) - 1):
        if is_col_mirror2(col_index, lines, line0):
            return col_index


def is_row_mirror2(row_index, lines):
    diff_count = 0
    for j in range(row_index + 1):
        this_row = j
        reflect_row = (row_index - j) + 1 + row_index
        if reflect_row >= len(lines):
            continue
        for a,b in zip(lines[this_row], lines[reflect_row]):
            if a!=b:
                diff_count += 1
                if diff_count > 1:
                    return False

    if diff_count == 1:
        return True
    else:
        return False


def find_row_mirror2(square):
    lines = square.split("\n")
    for row_index in range(len(lines) - 1):
        print(f"{row_index=}")
        if is_row_mirror2(row_index, lines):
            return row_index


for square in squares:
    print("=" * 10)
    print(square)
    col = find_col_mirror2(square)
    if col is not None:
        col += 1
        print("col -> ", col)
        result += col
        continue
    row = find_row_mirror2(square)
    if row is not None:
        row += 1
        print("row -> ", row)
        result += 100 * row

print(result)
