with open("input") as f:
    lines = f.readlines()


def extrapolate(numbers):
    next_level_numbers = []
    for index in range(len(numbers) - 1):
        next_level_numbers.append(numbers[index + 1] - numbers[index])

    if all([n == 0 for n in next_level_numbers]):
        return numbers[-1] + next_level_numbers[-1]
    else:
        add = extrapolate(next_level_numbers)
        return numbers[-1] + add


result = 0
for line in lines:
    numbers = [int(n) for n in line.split(" ")]
    x = extrapolate(numbers)
    result += x
print(result)


def extrapolate_forward(numbers):
    next_level_numbers = []
    for index in range(len(numbers) - 1):
        next_level_numbers.append(numbers[index + 1] - numbers[index])

    if all([n == 0 for n in next_level_numbers]):
        return numbers[0] - next_level_numbers[0]
    else:
        add = extrapolate_forward(next_level_numbers)
        return numbers[0] - add


result = 0
for line in lines:
    numbers = [int(n) for n in line.split(" ")]
    x = extrapolate_forward(numbers)
    result += x

print(result)
