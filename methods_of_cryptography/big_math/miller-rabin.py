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



n = 23662702794980672868664545949765991083233364755244809150943
t = 2
print("Число ", n, "при параметре надёжности t = ", t)
test_MR(n, t)
print(round(error(n, t), 5))
print(error(n, t))

n = 75361
t = 100
print("Число ", n, "при параметре надёжности t = ", t)
test_MR(n, t)
print(round(error(n, t), 5))
print(error(n, t))

n =  841157
t = 100
print("Число ", n, "при параметре надёжности t = ", t)
test_MR(n, t)
print(round(error(n, t), 5))
print(error(n, t))
