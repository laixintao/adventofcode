with open("input", "r") as f:
    lines = f.readlines()

hands = [(c.strip().split(" ")) for c in lines]


def get_kind(hand):
    d = {}
    for h in hand:
        d.setdefault(h, 0)
        d[h] += 1
    most = max(d.values())
    kinds = len(d.keys())
    if most == 5:
        return 10
    if most == 4:
        return 9
    if most == 3:
        if kinds == 2:
            return 8
        else:
            return 7
    if most == 2:
        # 2 pairs
        if kinds == 3:
            return 6
        else:
            return 5
    return 1


numbers = {"A": 20, "K": 19, "Q": 18, "J": 17, "T": 16}


def hand_power(hand_line):
    hand = hand_line[0]

    kind = get_kind(hand)
    keys = [kind]
    for a in hand:
        keys.append(numbers.get(a) or int(a))
    return keys


result = 0
for index, hand in enumerate(sorted(hands, key=hand_power)):
    result += (index + 1) * int(hand[1])

print(result)


def get_kind_J(hand):
    d = {}
    count_j = 0
    for h in hand:
        if h == "J":
            count_j += 1
            continue
        d.setdefault(h, 0)
        d[h] += 1

    if count_j == 5:
        return 10
    if count_j:
        most = max(d.values())
        for h in hand:
            if h != "J" and d[h] == most:
                d[h] += count_j

    most = max(d.values())
    kinds = len(d.keys())
    if most == 5:
        return 10
    if most == 4:
        return 9
    if most == 3:
        if kinds == 2:
            return 8
        else:
            return 7
    if most == 2:
        # 2 pairs
        if kinds == 3:
            return 6
        else:
            return 5
    return 1


numbers = {"A": 20, "K": 19, "Q": 18, "J": 17, "T": 16, "J": 1}


def hand_power_J(hand_line):
    hand = hand_line[0]

    kind = get_kind_J(hand)
    keys = [kind]
    for a in hand:
        keys.append(numbers.get(a) or int(a))
    return keys


result = 0
for index, hand in enumerate(sorted(hands, key=hand_power_J)):
    result += (index + 1) * int(hand[1])
print(result)
