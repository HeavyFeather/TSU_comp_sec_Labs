%macro output 2
mov eax, 4
mov ebx, 1
mov ecx, %1
mov edx, %2
int 0x80
%endmacro

section .text

global _start

_start:
    mov eax,3 ;  номер syscall-а read()
    xor ebx, ebx     ; fd = 0 = STDIN
    mov ecx, count     ; адрес буфера под вводимую строку
    mov edx,1 ; максимальная длина вводимой строки
    int 0x80

    ; положили ввод в переменные столбца и строки
    mov eax, [count]
    sub eax, '0'
    mov [n], eax
    mov [m], eax

    mov eax, [count]
    mov ebx, [count]
    mul ebx
    mov [count], eax

    xor eax, eax
    xor ebx, ebx
    xor edx,edx

    output space, 2
    ; создание матрицы
	mov esi, matrix ;записываем начало матрицы
    mov edi, 0 ;смещение
    mov ebp, [count] ;длина массива

    mov ebx, 0 ; i
    mov ecx, 0 ; j

    mov eax, [n]; инициализируем побочный pos
    dec eax
    mov [p_pos], eax

    L1: ; loop L1
    mov eax, [g_pos] ; поставили текущие pos к pos для строки
    mov [curr_g], eax

    mov edx, [p_pos]
    mov [curr_p], edx

    cmp ebx, [m] ; while i<m
    jge exit
    mov ecx, 0 ; j = 0

    L2:
    cmp ecx, [n] ; while j<n
    jge exitL2

    mov eax, [esi+4*edi]
    mov eax, 0
    mov [esi+4*edi], eax

    xor eax, eax
    xor edx, edx
    mov eax, [curr_g]
    mov edx, [curr_p]
    cmp eax, 0
    jne A ; условие пропуска

    mov eax, [diag]
    mov [esi+4*edi], eax

    A:
    cmp edx, 0
    jne B

    mov eax, [diag]
    mov [esi+4*edi], eax
    B:
    ;-- output elem matrix
    xor eax, eax
    xor edx, edx

    mov eax, [esi + 4 * edi] ;текущий элемент массива
    ; -- подсчёт нулей
    cmp eax, 0 ;jump if no equal to 0
    jne D

    push edx
    mov edx, [zeroes] ; zeroes++
    inc edx
    mov [zeroes], edx
    pop edx

    D:
    ; -- конец подсчёта нулей
    add eax, dword 48 ; перевод числа в символ
    mov [N], eax ; Записываем в переменную значение eax


    push ecx
    push ebx

    mov eax, 4
    mov ebx, 1
    mov ecx, N
    mov edx, 1
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, space
    mov edx, 1
    int 0x80

    pop ebx
    pop ecx
    ;-- end of output elem matrix
    inc ecx ; j++

    mov eax, [curr_g]
    dec eax ;уменьшаем pos
    mov [curr_g], eax

    mov edx, [curr_p]
    dec edx
    mov [curr_p], edx


    add esi, 4 ; next column
    jmp L2

    exitL2:

    add edi, [n] ;next string
    inc ebx ; i++

    mov eax, [diag]; инкрементируем значение для вставки
    inc eax
    mov [diag], eax

    mov eax, [g_pos]; инкрементируем главный pos
    inc eax
    mov [g_pos], eax

    mov edx, [p_pos]; декрементируем побочный pos
    dec edx
    mov [p_pos], edx

    push ecx
    push ebx
    output nextLine,1
    pop ebx
    pop ecx

    jmp L1

    exit: ; -- выход из цикла создания и вывода матрицы (и подсчёта нулей)

    xor esi, esi


    mov eax, [n] ; finding count of not zeroes
    mov ebx, [m]
    mul ebx
    sub eax, [zeroes]
    mov [nozeroes], eax

    ; perform relation --------------
    finit ; expression
    fld DWORD [nozeroes] ; x
    fld DWORD [zeroes]
    fdiv


	mov esi, [signs] ; signs after dot
    call outNu ; call procedure to output
    output nextLine,1
    jmp end

	printNum: ; output numbers from stek procedure

    mov ecx, 10 ; 10
    xor ebx, ebx
    xor edx, edx
    toStek: ; push numbers to stek
    div ecx ; /10
    add edx, dword 48 ; +'0'
    push edx ; push char value to stek
    xor edx, edx

    inc ebx ; iterator
    cmp eax, 0
    jnz toStek

    mov [temp], ebx ;temp = count

    fromStek:
    pop eax ; pop number from stek
    mov [var], eax ; n = number

    output var, 1 ; output number

    dec dword [temp] ; dec iterator
    cmp [temp], dword 0
    jnz fromStek

    ret

    printFrac: ; output float part of the value

    FloatPart: ; loop
    fld DWORD [currentFrac] ; currentFrac
    fld DWORD [one] ; 0.0001
    faddp ; +
    fmul DWORD [ten] ; *10

    fstp DWORD [currentTmp] ; currentTmp = fracPart*10

    fld1 ; 1
    fld DWORD [currentTmp] ; currentTmp
    fprem ; /1
    fst DWORD [currentFrac] ; Frac
    fld DWORD [currentTmp] ; Tmp

    fsubr ; Tmp - Frac = Int

    fistp DWORD [currentInt] ; Int

    mov ecx, [currentInt] ; ecx = currentInt
    add ecx, '0'
    mov [currentInt], ecx ; int

    output currentInt, 1 ; output

    dec esi ; iterator
    cmp esi, 0
    jne FloatPart

    ret

    outNu: ; main func for printing

    fstp DWORD [currentTmp] ; currentTmp

    fld1 ; 1
    fld DWORD [currentTmp] ; currentTmp
    fprem ; currentTmp/1
    fst DWORD [currentFrac] ; FracPart
    fld DWORD [currentTmp] ; TmpPart

    fsubr ; -

    fistp DWORD [currentInt] ; currentInt

    mov eax, [currentInt] ; print current integer
    call printNum

    output dot, 1 ; output dot

    call printFrac ; call print fracPart

    ret

    output nextLine, 1 ; output the next line

    end:
    mov     eax, 1
    int     0x80


section .bss
    matrix resd 100
section .data

    ;const
    one dd 0.000001 ; 0.0001
    ten dd 10.0 ; 10

    ;vars
    currentInt dd 0.0
    currentFrac dd 0.0
    currentTmp dd 0.0
    zeroes dd 0
    nozeroes dd 0

    signs dd 5 ; signs after dot

    temp dd 0 ; temp for printing numbers
    var dd 0 ; variable for print
    dot db  "."
    diag dd 1 ;число для вставки в диагональ
    g_pos dd 0; главный pos растёт с нуля каждый раз, когда переходим к новой строке (его возьмёт eax в каждой строке он инкрементирует)
    p_pos dd 0; побочный pos декрементирует с позиции n-1 (его возьмёт edx)
    curr_g dd 0
    curr_p dd 0
    m dd 0 ;количество строк
    n dd 0 ;кол-во столбцов
    buff dd 0
    count dd 5
    MAX_LEN dd 1
    space db '   '
    len_space equ $-space
    N dd 0
    i dd 0
    nextLine db 0xD ; next line
