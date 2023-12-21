import time

def fast_squaring(n):
    k = len(n)
    x = [int(i) for i in n] 
    x.reverse() 
    y = [0 for i in range (2 * k)] 

    for i in range(k): # 2
        uv = y[2 * i] + x[i] * x[i] # 2.1
        c = 0
        u = uv // 10
        v = uv % 10
        y[2 * i] = v
        for j in range(i + 1, k): # 2.2
            cuv = y[i + j] + 2 * x[i] * x[j] + c*10 + u
            c = cuv // 100
            v = cuv % 10
            u = (cuv - c * 100) // 10
            y[i + j] = v
        if c != 0: # 2.3
            y[i + k + 1] += c #c
        y[i + k] += u
    
    return int(''.join([str(i) for i in reversed(y)]))


#------------------------------------------------------------
n = input('Введите число: ')

start = time.time_ns()
ans_1 = fast_squaring(n)
print("Время выполнения в наносекундах")
print("Время выполнения алгоритма: ", (time.time_ns() - start) )

#------------------------------------------------------------
start = time.time_ns()
ans_2 = pow(int(n), 2)

print("Время выполнения 'pow': ", (time.time_ns() - start))

#------------------------------------------------------------
start = time.time_ns()
ans_3 = int(n) * int(n)

print("Время выполнения 'i*i': ", (time.time_ns() - start))

#------------------------------------------------------------
print(ans_1)
print(ans_2)
print(ans_3)
print(ans_1 == ans_2 == ans_3)
