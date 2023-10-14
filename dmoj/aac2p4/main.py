t = int(input())
for x in range(t):
    n = int(input())
    a = [int(xx) for xx in input().split()]
    if n == 1:
        print(a[0])
    a.sort()
    if (n & 1) == 0 and a[0] == a[n - 1]:
        print(-1)
        continue
    print(a[n - 1], end = " ")
    for xx in range(1, n - 1):
        print(a[xx], end = " ")
    print(a[0])
