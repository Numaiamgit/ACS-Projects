section .text

;; DO NOT MODIFY
global fix_lap_times


fix_lap_times:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    ;; DO NOT MODIFY
    ;; YOUR CODE STARTS HERE
    xor rax, rax
    xor rbx, rbx
    ; initializam numarul de timpi fixati cu 0
    mov dword [r8], 0
    dec rdx
    ; verificam daca primul element este invalid (0 = valid, altceva = invalid)
    cmp byte [rsi + rax], 0
    jne primul
    ; copiem elementul valid din sursa in destinatie
    mov ebx, [rdi + rax*4]
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    inc rax
    for:
    cmp rax, rdx
    je ultim
    ; verificam daca elementul curent este invalid
    cmp byte [rsi + rax], 0
    jne medie
    ; copiem elementul valid
    mov ebx, [rdi + rax*4]
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    ; avansam la urmatorul element
    add rax, 1
    cmp rax, rdx
    jl for
    ; verificam daca ultimul element este invalid
    cmp byte [rsi + rax], 0
    jne ultim
    ; copiem ultimul element valid
    mov ebx, [rdi + rax*4]
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    jmp end
    medie:
    ; luam elementul din stanga (4 bytes inapoi)
    mov ebx, [rdi + rax*4 - 4]
    ; adunam elementul din dreapta (4 bytes inainte)
    add ebx, [rdi + rax*4 + 4]
    ; impartim la 2 pentru medie
    shr ebx, 1
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    inc dword [r8]
    ; avansam la urmatorul element
    add rax, 1
    jmp for
    primul:
    ; primul element invalid se inlocuieste cu urmatorul (4 bytes inainte)
    mov ebx, [rdi + rax*4 + 4]
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    ; avansam la urmatorul element
    add rax, 1
    inc dword [r8]
    jmp for
    ultim:
    ; ultimul element invalid se inlocuieste cu precedentul (4 bytes inapoi)
    mov ebx, [rdi + rax*4 - 4]
    ; fiecare int ocupa 4 bytes
    mov [rcx + rax*4], ebx
    inc dword [r8]
    jmp end
    end:
    ;; YOUR CODE ENDS HERE
    ;; DO NOT MODIFY
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret
    ;; DO NOT MODIFY