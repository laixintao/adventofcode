def myhash(string):
    cur = 0
    for ch in string:
        value = ord(ch)
        cur += value
        cur = cur * 17
        cur = cur % 256
    return cur

with open("input") as f:
    line = f.read()

inputs = [x.strip() for x in line.split(",")]
result = 0
for i in inputs:
    result += myhash(i)

print(result)

boxes = {i:[] for i in range(256)}

for operation in inputs:
    if "-" in operation:
        name = operation[:-1]
        op = "-"
    else:
        name = operation[:-2]
        op = "="

    relevant_box = myhash(name)
    if op == '-':
        boxes[relevant_box] = [l for l in boxes[relevant_box] if l[0] != name]
    if op == "=":
        in_box = False
        for l in boxes[relevant_box]:
            if l[0] == name:
                l[1] = int(operation[-1])
                in_box = True
                break
        if not in_box:
            boxes[relevant_box].append([name, int(operation[-1])])

result = 0
for k,v in boxes.items():
    box_number = (k+1)
    for i, l in enumerate(v):
        result += box_number * (i+1) * l[1]
print(result)
