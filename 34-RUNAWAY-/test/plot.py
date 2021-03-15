import sys
import matplotlib.pyplot as plt
import numpy as np

def plot_line():
    a = 1.0
    b = 0.5
    c = 2.0
    x = np.array(range(10))
    y = (c - a * x) / b
    mylabel = '%f * x + %f * y = %f' % (a, b, c)
    plt.plot(x,y,'go-',label=mylabel)
    plt.title('My first Plot with Python')
    plt.legend()
    plt.grid(alpha=.4,linestyle='--')
    plt.xlim(-5, 15)
    plt.ylim(-15, 5)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

def import_data():
    filepath = 'c:/Users/Xeno/OneDrive/SourceCode/spoj/RUNAWAY/test/example_points.csv'
    # filepath = 'C:\\Users\\Xeno\\OneDrive\\SourceCode\\spoj\\RUNAWAY\\test\\example_points.csv'
    data = np.loadtxt(filepath, delimiter=',', skiprows=1)
    print(data)

def plot_bisection():
    x1 = 1
    y1 = 1
    x2 = 3
    y2 = 2
    dx = x2 - x1
    dy = y2 - y1
    c = x1 * dx + y1 * dy + (dx*dx + dy*dy)*0.5
    adx = dx if dx > 0 else -dx
    ady = dy if dy > 0 else -dy
    a = None
    b = None
    if adx > ady:
        a = 1.0
        b = dy / dx
        c /= dx
    else:
        a = dx / dy
        b = 1.0
        c /= dy
    # print([a, b, c])
    x = np.array(range(10))
    # y = (c - a * x) / b
    y = (b * x + c) / a
    mylabel = '%f * x + %f * y = %f' % (a, b, c)
    plt.plot(x,y,'go-',label=mylabel)
    plt.plot([x1, x2], [y1, y2], 'ro',label='Point')
    plt.title('My first Plot with Python')
    plt.legend()
    plt.grid(alpha=.4,linestyle='--')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

def plot_parabola():
    x1 = 0
    y1 = 0
    x2 = 5
    y2 = 6
    # y2 = 3.7
    py = 11
    n = 20
    d = (x2 - x1) / (n * 2)
    dx = x2 - x1
    dy = y2 - y1
    c = x1 * dx + y1 * dy + (dx*dx + dy*dy)*0.5
    adx = dx if dx > 0 else -dx
    ady = dy if dy > 0 else -dy
    a = None
    b = None
    if adx > ady:
        a = 1.0
        b = dy / dx
        c /= dx
    else:
        a = dx / dy
        b = 1.0
        c /= dy
    data = np.empty([n * 4 + 1, 5], dtype = float)
    for i in range(n * 4 + 1):
        data[i, 0] = x1 - n * d + i * d
    data[:, 1] = - (data[:, 0] - x1) ** 2 / (2 * (py - y1)) + (y1 + py) / 2
    data[:, 2] = - (data[:, 0] - x2) ** 2 / (2 * (py - y2)) + (y2 + py) / 2
    data[:, 3] = (c - a * data[:, 0]) / b
    data[:, 4] = b * (data[:, 0] - x1) / a + y1
    limit_height = 2 * (x2 - x1)
    l_idx = 0
    h_idx = n * 4
    while l_idx < n * 4 and data[l_idx, 3] > py:
        l_idx += 1
    while l_idx < n * 4 and data[l_idx, 3] < (y1 + y2) / 2 - limit_height:
        l_idx += 1
    if l_idx > 0:
        l_idx -= 1
    while h_idx > 0 and data[h_idx, 3] > py:
        h_idx -= 1
    while h_idx > 0 and data[h_idx, 3] < (y1 + y2) / 2 - limit_height:
        h_idx -= 1
    if h_idx < n * 4:
        h_idx += 1
    # print(data)
    plt.plot(data[:, 0], data[:, 1], 'b-')
    plt.plot(data[:, 0], data[:, 2], 'b-')
    plt.plot(data[l_idx:h_idx, 0], data[l_idx:h_idx, 3], 'b-')
    plt.plot(data[:, 0], data[:, 4], 'b-')
    plt.plot([x1, x2], [y1, y2], 'ro')
    plt.plot([data[0, 0], data[n * 4, 0]], [py, py], 'g-')
    plt.gca().set_aspect('equal', adjustable='box')
    title = 'a=%.2f,b=%.2f,c=%.2f' % (a, b, c)
    plt.title(title)
    plt.show()

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __repr__(self):
        return ("(%f,%f)" % (self.x, self.y))
    def __str__(self):
        return self.__repr__()

class HalfEdge:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2
        dx = p2.x - p1.x
        dy = p2.y - p1.y
        self.c = p1.x * dx + p1.y * dy + (dx * dx + dy * dy) / 2
        adx = dx if dx > 0 else -dx
        ady = dy if dy > 0 else -dy
        self.a = None
        self.b = None
        if adx > ady:
            self.a = 1.0
            self.b = dy / dx
            self.c /= dx
        else:
            self.a = dx / dy
            self.b = 1.0
            self.c /= dy
    def __repr__(self):
        return ("(%s,%s,%f,%f,%f)" % (self.p1, self.p2, self.a, self.b, self.c))
    def __str__(self):
        return self.__repr__()

def get_line(he, x_points):
    n = x_points.shape[0]
    line = np.empty([n, 2], dtype = float)
    line[:, 0] = x_points
    line[:, 1] = (he.c - he.a * line[:, 0]) / he.b
    return line

def get_scan_y(he1, he2):
    d = he1.a * he2.b - he1.b * he2.a

def display_vector_event():
    p1 = Point(0, 0)
    p2 = Point(5, 1)
    p3 = Point(8, 3)
    he1 = HalfEdge(p1, p2)
    he2 = HalfEdge(p2, p3)
    # print(he1)
    # print(he2)
    w = 2 * (p3.x - p1.x)
    x_min = p1.x - (p2.x - p1.x) / 2
    n = 25
    d = w / n
    x_points = np.empty([n + 1], dtype = float)
    for i in range(n + 1):
        x_points[i] = x_min + d * i
    # print(x_points.shape[0])
    l1 = get_line(he1, x_points)
    l2 = get_line(he2, x_points)
    y_scan_line = get_scan_y(he1, he2)
    plt.plot(l1[:, 0], l1[:, 1], 'b-')
    plt.plot(l2[:, 0], l2[:, 1], 'b-')
    plt.plot([p1.x, p2.x, p3.x], [p1.y, p2.y, p3.y], 'ro')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

def main():
    # plot_line()
    # import_data()
    # plot_bisection()
    # plot_parabola()
    display_vector_event()

if __name__ == '__main__':
    main()
    sys.exit(0)