with open("input") as f:
    data = [line.strip() for line in f.readlines()]


galaxies = []

for row_index in range(len(data)):
    line = data[row_index]
    line_none = True
    for col_index in range(len(line)):
        if line[col_index] == "#":
            galaxies.append((row_index, col_index))
            line_none = False
expand_rows = set(i for i in range(len(data)))
expand_cols = set(i for i in range(len(data[0])))

for g in galaxies:
    expand_rows -= set([g[0]])
    expand_cols -= set([g[1]])

print(galaxies)
print(expand_rows)
print(expand_cols)

result = 0
for i in range(len(galaxies)):
    for j in range(i+1, len(galaxies)):
        start = galaxies[i]
        end = galaxies[j]

        row_start = min(start[0], end[0])
        row_end = max(start[0], end[0])
        steps = row_end - row_start
        for step in range(row_start, row_end):
            if step in expand_rows:
                result += 2
            else:
                result += 1

        col_start = min(start[1], end[1])
        col_end = max(start[1], end[1])
        steps = col_end - col_start
        for step in range(col_start, col_end):
            if step in expand_cols:
                result += 2
            else:
                result += 1

print(result)

result = 0
for i in range(len(galaxies)):
    for j in range(i+1, len(galaxies)):
        start = galaxies[i]
        end = galaxies[j]

        row_start = min(start[0], end[0])
        row_end = max(start[0], end[0])
        steps = row_end - row_start
        for step in range(row_start, row_end):
            if step in expand_rows:
                result += 1000000
            else:
                result += 1

        col_start = min(start[1], end[1])
        col_end = max(start[1], end[1])
        steps = col_end - col_start
        for step in range(col_start, col_end):
            if step in expand_cols:
                result += 1000000
            else:
                result += 1

print(result)
