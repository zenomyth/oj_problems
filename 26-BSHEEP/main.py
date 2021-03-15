import sys
import functools
import math
# import matplotlib.pyplot as plt
# import numpy as np

class Point:
    def __init__(self, x, y, n):
        self.x = x
        self.y = y
        self.n = n
    def __repr__(self):
        return ("(%d,%d,%d)" % (self.x, self.y, self.n))
    def __str__(self):
        return self.__repr__()

def pred3(x, y, m):
    return (x % m) - (y % m)

def sort_test():
    l = [5,3,2,6,9,1,7,8]
    print(l)
    l.sort(key = functools.cmp_to_key(lambda x, y: pred3(x, y, 3)))
    print(l)
    l.sort(key = functools.cmp_to_key(lambda x, y: pred3(x, y, 4)))
    print(l)

def coordinate_less_than(a, b):
    if a.x == b.x and a.y == b.y:
        return a.n - b.n
    return a.x - b.x if a.y == b.y else a.y - b.y

def angle_less_than(a, b, m):
    if a.x == b.x and a.y == b.y:
        return a.n - b.n
    ax = a.x - m.x
    ay = a.y - m.y
    bx = b.x - m.x
    by = b.y - m.y
    if ax == 0 and ay == 0:
        return -1
    if bx == 0 and by == 0:
        return 1
    sax = 1 if ax > 0 else -1
    sbx = 1 if bx > 0 else -1
    cosa = sax * ax * ax * (bx * bx + by * by)
    cosb = sbx * bx * bx * (ax * ax + ay * ay)
    return ax - bx if cosa == cosb else cosb - cosa

# Cross product from P1P2 to P1P3: (x2 - x1)(y3 - y1) - (y2 - y1)(x3 - x1)
def cross_product(p1, p2, p3):
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)

def dist(p1, p2):
    return math.sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y))

def graham_scan(points):
    # print(points)
    m = min(points, key = functools.cmp_to_key(coordinate_less_than))
    # print(m)
    points_sorted = sorted(points, key = functools.cmp_to_key(lambda a, b: angle_less_than(a, b, m)))
    # print(points_sorted)
    points_nodup = []
    points_nodup.append(points_sorted[0])
    for i in range(1, len(points_sorted)):
        if points_sorted[i].x == points_sorted[i - 1].x and points_sorted[i].y == points_sorted[i - 1].y:
            continue
        points_nodup.append(points_sorted[i])
    # print(points_nodup)
    ch = [] # Convex hull
    ch.append(points_nodup[0])
    if len(points_nodup) >= 2:
        ch.append(points_nodup[1])
        for i in range(2, len(points_nodup)):
            cp = cross_product(ch[len(ch) - 2], ch[len(ch) - 1], points_nodup[i])
            while cp <= 0:
                ch.pop()
                if len(ch) < 2:
                    break
                cp = cross_product(ch[len(ch) - 2], ch[len(ch) - 1], points_nodup[i])
            ch.append(points_nodup[i])
    # print(ch)
    fence_len = 0
    for i in range(len(ch) - 1):
        fence_len += dist(ch[i], ch[i + 1])
    fence_len += dist(ch[len(ch) - 1], ch[0])
    print('%.2f' % fence_len)
    for i in range(len(ch) - 1):
        print(ch[i].n, end = ' ')
    print(ch[len(ch) - 1].n)
    print()

    # input_np = np.empty([len(points), 2], dtype = float)
    # for i in range(len(points)):
        # input_np[i, 0] = int(points[i].x)
        # input_np[i, 1] = int(points[i].y)
    # ch_np = np.empty([len(ch) + 1, 2], dtype = float)
    # for i in range(len(ch)):
        # ch_np[i, 0] = int(ch[i].x)
        # ch_np[i, 1] = int(ch[i].y)
    # ch_np[len(ch), 0] = ch_np[0, 0]
    # ch_np[len(ch), 1] = ch_np[0, 1]
    # plt.plot(input_np[:, 0], input_np[:, 1], 'go', label = 'input')
    # plt.plot(ch_np[:, 0], ch_np[:, 1], 'm--', label = 'output')
    # plt.legend()
    # plt.show()

def main():
    t = int(input(''))
    for i in range(t):
        input('')
        n = int(input(''))
        points = []
        for j in range(n):
            line = input('').split()
            points.append(Point(int(line[0]), int(line[1]), j + 1))
        graham_scan(points)
        # break
    return

if __name__ == '__main__':
    main()
    # sort_test()
    # min_test()
    sys.exit(0)