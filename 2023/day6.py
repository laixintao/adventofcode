import re

with open("input", "r") as f:
    data = f.read()

time_line, distance_line = data.splitlines()
times = [int(n) for n in re.findall(r"\b\d+\b", time_line)]
distances = [int(n) for n in re.findall(r"\b\d+\b", distance_line)]

result = 1
for t, d in zip(times, distances):
    methods = 0
    for n in range(t + 1):
        if (t - n) * n > d:
            methods += 1
    result *= methods

print(result)

tim = int("".join([n.strip() for n in re.findall(r"\b\d+\b", time_line)]))
dis = int("".join([n.strip() for n in re.findall(r"\b\d+\b", distance_line)]))

result = 0
# can use binary search
for n in range(tim + 1):
    if (tim - n) * n > dis:
        result += 1

print(result)
