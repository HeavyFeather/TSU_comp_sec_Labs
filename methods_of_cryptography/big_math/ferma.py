import random
from sympy.ntheory.factor_ import totient


#Функция Эйлера
def error_f(n,t):
    print("Ealer: ", totient(n))
    return float((totient(n)/n))**t

#Тест Ферма
def ferma_test(n, t):
    while t:
        a = random.randint(2, n - 2)
        r = pow(a, n - 1, n)
        t -= 1
    if r != 1:  
        print("[-] Число составное!")
        return
    
    print("[+] Число простое!")


t = 1

n = 6099126388594931945520833493722385030733 # простое
print("Число ", n)
ferma_test(n, t)
print("Вероятность ошибки = ", error_f(n, t))

n = 62745 
print("Число ", n)
ferma_test(n, t)
print("Вероятность ошибки = ", error_f(n, t))

n = 75361
print("Число ", n)
ferma_test(n, t)
print("Вероятность ошибки = ", error_f(n, t))
