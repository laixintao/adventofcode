with open("input") as f:
    data = [i.strip() for i in f.readlines()]


cache = {}


def debug_func(func):
    def wrapper(springs, stats):
        key = ",".join(springs) + "+" + ",".join(str(i) for i in stats)
        if key in cache:
            return cache[key]
        return_value = func(springs, stats)
        # print(f"{springs} \t {stats} \t {return_value=}")
        cache[key] = return_value
        return return_value

    return wrapper


@debug_func
def count_arrangements(springs, stats):
    springs = springs.strip(".")
    if not springs:
        if len(stats) > 0:
            return 0
        else:
            return 1
    if len(stats) == 0:
        if "#" in springs:
            return 0
        else:
            return 1

    if springs[0] == "?":
        return count_arrangements(springs[1:], stats) + count_arrangements(
            "#" + springs[1:], stats
        )
    if springs[0] == "#":
        continues_spring = 0
        for index in range(len(springs)):
            if springs[index] == "#":
                continues_spring += 1
            else:
                break
        if continues_spring < len(springs):
            non_spring = springs[continues_spring]
            if non_spring == ".":
                if stats[0] == continues_spring:
                    return count_arrangements(springs[continues_spring:], stats[1:])
                else:
                    return 0
            if non_spring == "?":
                if stats[0] < continues_spring:
                    return 0
                elif stats[0] == continues_spring:
                    return count_arrangements(
                        springs[continues_spring + 1 :], stats[1:]
                    )
                else:
                    return count_arrangements(
                        springs[:continues_spring]
                        + "."
                        + springs[continues_spring + 1 :],
                        stats,
                    ) + count_arrangements(
                        springs[:continues_spring]
                        + "#"
                        + springs[continues_spring + 1 :],
                        stats,
                    )
        else:
            if len(stats) == 1 and continues_spring == stats[0]:
                return 1
            return 0


result = 0
for line in data:
    springs, stats = line.split(" ")
    stats = [int(n) for n in stats.split(",")]

    arr = count_arrangements(springs, stats)
    print("==> ", line, "-- ", arr)
    result += arr

print(result)
result = 0

for line in data:
    springs, stats = line.split(" ")
    stats = [int(n) for n in stats.split(",")]
    stats = stats * 5
    springs = '?'.join([springs] * 5)

    arr = count_arrangements(springs, stats)
    print("==> ", line, "-- ", arr)
    result += arr

print(result)
