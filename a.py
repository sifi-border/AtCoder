import math
t, a, b = map(int, input().split())
c = a*b//math.gcd(a, b)
print((t + a - 1) // a + (t + b - 1) // b - (t + c - 1)//c)
