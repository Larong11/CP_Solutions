import math
from typing import List, Tuple

MOD = int(1e9 + 7)
eps = 1e-6
SIGNES_AFTER_COMMA = 9

class Field:
    def __init__(self, E: int = 0, t: int = 0, type_: int = 0):
        self.E = E
        self.t = t
        self.type = type_

    def __lt__(self, other):
        if self.t != other.t:
            return self.t < other.t
        else:
            return self.type < other.type

def solve():
    T = int(input())
    fields: List[Field] = []
    for _ in range(T):
        start, finish, e = map(int, input().split())
        fields.append(Field(e, start, 1))
        fields.append(Field(e, finish, 0))

    q, m = map(float, input().split())
    Q = int(input())
    xs: List[Tuple[int, int]] = []
    for i in range(Q):
        t = int(input())
        xs.append((t, i))

    xs.sort()
    fields.sort()

    ans = [0.0] * Q
    t = 0.0
    x = 0.0
    v = 0.0
    a = 0.0
    last = 0

    for i in range(2 * T):
        dt = fields[i].t - t
        newX = x + dt * v + dt * dt * a / 2.0
        while last < len(xs) and xs[last][0] < newX:
            if xs[last][0] == 0:
                ans[xs[last][1]] = 0.0
                last += 1
                continue
            if abs(a) > eps:
                Dt = (-v + math.sqrt(v * v - 2.0 * a * (x - xs[last][0]))) / a
                ans[xs[last][1]] = t + Dt
            else:
                ans[xs[last][1]] = t + (xs[last][0] - x) / v
            last += 1
        t = fields[i].t
        x = newX
        v += a * dt
        a += fields[i].E * (1.0 if fields[i].type == 1 else -1.0) * q / m

    while last < len(xs):
        ans[xs[last][1]] = t + (xs[last][0] - x) / v
        last += 1

    for val in ans:
        print(f"{val:.{SIGNES_AFTER_COMMA}f}")
    print()

if __name__ == "__main__":
    import sys
    input = sys.stdin.readline
    solve()