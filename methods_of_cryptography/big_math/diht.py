import time


#справа налево
def alg_RL(x, y):
    q = x
    z = x
    for i in range(y.bit_length() - 2, -1, -1):
        q = q ** 2
        if (y >> i) & 1:
            z = z * q

    return z



#слева направо


def alg_LR(x, y):#справа налево
    z = x
    for i in range(y.bit_length() - 2, -1, -1):
        z = z ** 2
        if (y >> i) & 1:
            z *= x 
    return z



x = int(input("Enter x: "))
y = int(input("Enter y: "))



start = time.time_ns()
ans_1 = alg_LR(x, y)
print("Время работы Дихотомического алгоритма: ", (time.time_ns() - start))


start = time.time_ns()
ans_2 = pow(x, y)
print("Время работы стандартной функции: ", time.time_ns() - start)

print("result: ",ans_1)

print(alg_LR(x, y) == x ** y == pow(x, y))
