import re

with open("input") as f:
    data = f.read()

rules_data, parts_data = data.split("\n\n")

rules = {}
for line in rules_data.splitlines():
    m = re.match(r"(.*){(.*)}", line)
    name = m.group(1)
    conditions = m.group(2)

    parsed_conditions = []
    for c in conditions.split(","):
        if ":" in c:
            m = re.match(r"(.)(.)(\d+):(.*)", c)
            attr = m.group(1)
            compare = m.group(2)
            value = m.group(3)
            dest = m.group(4)
            parsed_conditions.append({
                "attr": attr, "compare": compare, "value": int(value), "dest": dest
            })
        else:
            parsed_conditions.append({"compare": "any", "dest": c})
    rules[name] = parsed_conditions


parts = []
for line in parts_data.splitlines():
    m = re.match(r"{x=(\d+),m=(\d+),a=(\d+),s=(\d+)}", line)
    parts.append({
        "x": int(m.group(1)),
        "m": int(m.group(2)),
        "a": int(m.group(3)),
        "s": int(m.group(4)),
    })


def match(part, rule_name):
    if rule_name == "A":
        return True
    if rule_name == "R":
        return False

    rule_seq = rules[rule_name]
    for rule in rule_seq:
        if rule["compare"] == "any":
            return match(part, rule["dest"])
        else:
            my_value = part.get(rule["attr"])
            expect = rule["value"]
            if rule["compare"] == ">":
                matching = my_value > expect
            else:
                matching = my_value < expect
            if not matching:
                continue
            return match(part, rule["dest"])


result = 0
for p in parts:
    if match(p, "in"):
        result += sum(p.values())

print(result)


# ------part2------
def split(r, ranges):
    if r['compare'] == "any":
        return ranges, None

    to_split_value_pairs = ranges[r['attr']]
    split_value = r['value']
    new_matched_ranges = []
    new_non_matched_ranges = []

    for pair in to_split_value_pairs:
        if r['compare'] == "<":
            if pair[1] < split_value:  # all match
                new_matched_ranges.append(pair)
                continue
            if pair[0] >= split_value: # none match
                new_non_matched_ranges.append(pair)
                continue
            matched = (pair[0], split_value-1)
            non_matched = (split_value, pair[1])
            new_matched_ranges.append(matched)
            new_non_matched_ranges.append(non_matched)


        if r['compare'] == ">":
            if pair[0] > split_value:  # all match
                new_matched_ranges.append(pair)
                continue
            if pair[1] <= split_value: # none match
                new_non_matched_ranges.append(pair)
                continue

            matched = (split_value+1, pair[1])
            non_matched = (pair[0], split_value)
            new_matched_ranges.append(matched)
            new_non_matched_ranges.append(non_matched)

    matched_dict = {**ranges}
    matched_dict[r['attr']] = new_matched_ranges

    non_matched_dict = {**ranges}
    non_matched_dict[r['attr']] = new_non_matched_ranges

    return matched_dict, non_matched_dict


def possible_count(rule_name, ranges):
    if rule_name == "R":
        return 0
    if rule_name == "A":
        total = 1
        for key in "xmas":
            range_pairs = ranges[key]
            for pair in range_pairs:
                total *= (pair[1] - pair[0] + 1)
        return total

    rule_list = rules[rule_name]
    count = 0
    for r in rule_list:
        matched, not_matched = split(r, ranges)
        count += possible_count(r["dest"], matched)
        if not_matched:
            ranges = not_matched
    return count


result = possible_count(
    "in",
    {
        "x": [(1, 4000)],
        "m": [(1, 4000)],
        "a": [(1, 4000)],
        "s": [(1, 4000)],
    },
)
print(result)
