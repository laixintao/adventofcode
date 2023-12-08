import re
from collections import defaultdict

result = 0


def winning(line):
    m = re.match(r"Card\s+\d+: (.*)", line)
    numbers = m.group(1)
    winning_number, my_number = numbers.split("|")
    winning_numbers = [int(n) for n in winning_number.split(" ") if n.strip()]
    my_numbers = [int(n) for n in my_number.split(" ") if n.strip()]

    hit = 0
    for n in my_numbers:
        if n in winning_numbers:
            hit += 1
    return hit


with open("input", "r") as f:
    for line in f:
        hit = winning(line)
        if hit > 0:
            result += 2 ** (hit - 1)

print(result)

card_count = defaultdict(int)

with open("input", "r") as f:
    for index, line in enumerate(f):
        card_count[index] += 1

        hit = winning(line)
        if hit > 0:
            for i in range(1, hit + 1):
                card_count[index+i] += card_count[index]

result = sum(card_count.values())
print(result)
