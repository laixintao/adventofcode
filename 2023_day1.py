import re


with open("input_day1.txt", "r") as f:
    result = 0
    for line in f:
        first = re.match(r"[^\d]*(\d)", line).group(1)
        last = re.match(r".*(\d)(?!.*\d)", line).group(1)
        result += int(first + last)
    print(result)

words = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four":"4", 
    "five": "5", 
    "six":"6",
    "seven": "7" , 
    "eight": "8", 
    "nine": "9"
}
re_words = "|".join(words.keys())
nonmatch_re_words = "|".join([f"(?!{k})" for k in words.keys()])


def overlap_find(matcher, line):
    result = []
    for start in range(len(line)-1):
        text = line[start:]
        m = re.search(matcher, text)
        if m:
            result.append(m.group())

    return result



with open("input_day1.txt", "r") as f:
    result = 0
    for line in f:
        matcher = rf"(\d|one|two|three|four|five|six|seven|eight|nine)"
        groups = overlap_find(matcher, line)
        first = groups[0]
        if first in words:
            first = words[first]

        last = groups[-1]
        if last in words:
            last = words[last]

        result += int(first + last)
    print(result)
