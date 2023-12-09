import re

with open("input", "r") as f:
    data = f.read()

data = data.split("\n\n")

seeds = [int(r) for r in re.findall(r"\b(\d+)\b", data[0])]


def match_one(current, match):
    for map_line in match.splitlines()[1:]:
        dst, src, length = [int(n) for n in map_line.split(" ")]
        if src <= current < src + length:
            return current - src + dst
    return current


last_matched = seeds
for match in data[1:]:
    last_matched = [match_one(s, match) for s in last_matched]

result = min(last_matched)
print(result)


def match_range(seed_pair, match):
    seed_start, seed_end = seed_pair
    after_match = []
    for map_line in match.splitlines()[1:]:
        dst, src, length = [int(n) for n in map_line.split(" ")]
        # no overlap
        if seed_start >= src + length or seed_end <= src:
            continue

        # overlap
        overlap_start = max(seed_start, src)
        overlap_end = min(seed_end, src + length)

        after_match.append((overlap_start - src + dst, overlap_end - src + dst))

        if overlap_start > seed_start:
            non_overlap = (seed_start, overlap_start)
            after_match.extend(match_range(non_overlap, match))

        if overlap_end < seed_end:
            non_overlap = (overlap_end, seed_end)
            after_match.extend(match_range(non_overlap, match))

        return after_match

    return [seed_pair]


# [start,end)
seed_pairs = [(seeds[i], seeds[i] + seeds[i + 1]) for i in range(0, len(seeds), 2)]
for match in data[1:]:
    matched = []
    for seed_pair in seed_pairs:
        matched.extend(match_range(seed_pair, match))
    seed_pairs = matched


result = min(x[0] for x in seed_pairs)
print(result)
