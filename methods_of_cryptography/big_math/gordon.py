#Метод Гордона
from sympy import isprime
from sympy import randprime
from sympy.ntheory.factor_ import totient
import random

def test_MR(n, t):
    if n > 3:
        r = n -1
        s = 0
        while r % 2 == 0:
            r = r // 2
            s += 1

        while t:
            b = random.randint(2, n - 2)
            y = pow(b, r, n)
            if y != 1 and y !=  n  -1:
                j = 1
                while j < s and y != n - 1:
                    y = pow(y, 2, n)
                    if y == 1:
                        print("Составное!")
                        return 
                    j += 1
                if y != n - 1:
                    print("Составное!")
                    return
            t -= 1

        print("Простое!")

    else:
        print("Число слишком четное!")



def error(n, t):
    return float((totient(n) / (4 * n)) ** t)







def gordon():
    
    s = randprime(10**25, 10**30)
    t = randprime(10**25, 10**30)

    i = random.randint(1, 100)
    r = 2 * i * t + 1

    while not isprime(r):
        i += 1
        r = 2 * i * t + 1
    
    p0 = 2 * (pow(s, r - 2, r)) * s - 1
    j = random.randint(1, 100)
    p = 2 * j * r * s + p0

    while not isprime(p):
        j += 1
        p = 2 * j * r * s + p0
    
    return p
    

g = gordon()

print("Сильное простое: ", g)
