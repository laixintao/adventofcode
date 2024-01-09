class Module:
    def __init__(self, name) -> None:
        self.name = name
        self.outputs = []

    def trigger(self, event):
        # print(f"{event._from} -{event.pause}-> {event.to}")
        pass

    def __repr__(self) -> str:
        return self.name
    @property
    def state_unique(self):
        return "1"


class Event:
    def __init__(self, _from, to, pause) -> None:
        self.to = to
        self.pause = pause
        self._from = _from

    def __repr__(self) -> str:
        return f"{self._from} -{self.pause}-> {self.to}"


class FlipFlop(Module):
    def __init__(self, name) -> None:
        self.state = False
        super().__init__(name)

    def trigger(self, event):
        super().trigger(event)
        if event.pause == "high":
            return

        if not self.state:
            self.state = True
            for m in self.outputs:
                yield Event(_from=self, to=m, pause="high")
            return
        if self.state:
            self.state = False
            for m in self.outputs:
                yield Event(_from=self, to=m, pause="low")
    @property
    def state_unique(self):
        return self.state

class Conjunction(Module):
    def __init__(self, name) -> None:
        super().__init__(name)
        self.inputs = {}

    def trigger(self, event):
        super().trigger(event)
        self.inputs[event._from.name] = event.pause
        if all(state == "high" for state in self.inputs.values()):
            for m in self.outputs:
                yield Event(_from=self, to=m, pause="low")
        else:
            for m in self.outputs:
                yield Event(_from=self, to=m, pause="high")

    @property
    def state_unique(self):
        return ",".join((state for state in self.inputs.values()))

class Broadcaster(Module):
    def trigger(self, event):
        super().trigger(event)
        for m in self.outputs:
            yield Event(_from=self, to=m, pause=event.pause)


def push_button(module_dict):
    events = []
    start = Event(_from="button", to=module_dict["broadcaster"], pause="low")
    events.append(start)
    low = 1
    high = 0
    while events:
        e = events.pop(0)
        m = e.to
        new_events = m.trigger(e)
        if not new_events:
            continue
        for new_event in new_events:
            events.append(new_event)
            if new_event.pause == "low":
                low += 1
            else:
                high += 1
            if new_event.to.name == "rx" and new_event.pause == "low":
                print(new_event.pause)
    flipflop_modules = module_dict.values()
    sorted_flipflop_modules = sorted(flipflop_modules, key=lambda m: m.name)
    states = [m.state_unique for m in sorted_flipflop_modules]
    # print(states)
    return states, low, high

def read_data():
    with open("input") as f:
        lines = f.readlines()

    module_dict = {"output": Module("output")}
    for line in lines:
        m = line.split(" ")[0]
        if m == "broadcaster":
            module_dict["broadcaster"] = Broadcaster("broadcaster")
            continue
        if m.startswith("%"):
            name = m[1:]
            module_dict[name] = FlipFlop(name)
        if m.startswith("&"):
            name = m[1:]
            module_dict[name] = Conjunction(name)

    for line in lines:
        name, tails = line.split("->")
        outputs = tails.split(",")
        if name.startswith("broa"):
            name = name.strip()
        else:
            name = name[1:].strip()

        for output in outputs:
            output = output.strip()
            if output not in module_dict:
                module_dict[output] = Module(output)
            module_dict[name].outputs.append(module_dict[output])
            output_module = module_dict[output]
            if isinstance(output_module, Conjunction):
                output_module.inputs[name] = "low"
    return module_dict
    

def part1(module_dict):
    count = 0
    seen_states = {}
    pauses = []

    total_low = total_high = 0
    while True:
        states, low, high = push_button(module_dict)
        print(count, low, high)
        total_low += low
        total_high += high
        pauses.append((low,high))

        seen_states[tuple(states)] = count
        count += 1
        if count == 1000:
            print(total_high * total_low)
            return

def part2(module_dict):
    count = 0

    while True:
        states, low, high = push_button(module_dict)
        print(count)

        count += 1
        
module_dict = read_data()
part1(module_dict)
part2(module_dict)
