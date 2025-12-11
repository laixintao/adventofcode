import copy
path = {}
with open("input") as f:
    for line in f:
        start, ends = line.split(":")
        start = start.strip()
        path[start] = [end.strip() for end in ends.split(" ") if end.strip()]


known = {}
def k(current, dac,fft):
    return f"{current}{dac}{fft}"

def find_path(visited, current, dac, fft):
    if current == 'out':
        if  dac and fft:
            print(" ".join(visited))
            return 1
        return 0

    if current in visited:
        return 0

    key = k(current,dac,fft)
    if key in known:
        return known[key]

    ends = path[current]
    count = 0
    new_visited = copy.copy(visited)
    new_visited.append(current)
    if current == 'dac':
        dac = True
    if current == 'fft':
        fft = True
    for end in ends:
        new = find_path(new_visited, end, dac, fft)
        print(f"count {visited} current {current} {count} +={new}: {end}")
        count += new
    known[key] = count
    return count


total =  find_path([], 'svr', False, False)
print(total)
