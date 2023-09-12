def recursion_test(f, r):
    r2 = float(f) / r
    r3 = (r2 + r) / 2
    r4 = r3 - r
    if r3 < r:
        r4 = -r4
    if r4 < 0.000001:
        return r3
    else:
        return recursion_test(f, r3)

def gcd(a, b):
    r = a % b
    r2 = b
    while r != 0:
        temp = r
        r = r2 % r
        r2 = temp
    return r2

def search_for_solution(a, b, c):
    h = a
    l = b
    if a < b:
        l = a
        h = b
    # Initial state: (l, h) = (0, m)
    r1 = 0
    m = 0 # m is remained water in b
    while ((c - m) % l) != 0:
        n = (h - m) // l
        m = l - ((h - m) % l)
        if m == l:
            r1 = -1
            break
        r1 += 2 * (n + 1) + 2
    if r1 != -1:
        if c == m:
            r1 -= 2 # The remaining water in b has been availabe 2 steps before in a
        else:
            nc = (c - m) // l
            r1 += 2 * nc
    # Initial state: (h, l) = (h - m, 0)
    r2 = 1 # To meet the initial state
    m = 0 # m is lost water from a
    while ((h - m - c) % l) != 0:
        n = (h - m) // l
        m = l - ((h - m) % l)
        if m == l:
            r2 = -1
            break
        r2 += 2 * (n + 1) + 2
    if r2 != -1:
        nc = (h - m - c) // l
        r2 += 2 * nc - 1 # -1: We don't need to empty b
    if r1 != -1 and r1 < r2:
        return r1
    else:
        return r2

def find_solution(a, b, c):
    if a < c and b < c:
        return -1
    if a == c or b == c:
        return 1
    if c % gcd(a, b) != 0:
        return -1
    return search_for_solution(a, b, c)

t = int(input(''))
for i in range(t):
    a = int(input(''))
    b = int(input(''))
    c = int(input(''))
    r = find_solution(a, b, c);
    print(r)