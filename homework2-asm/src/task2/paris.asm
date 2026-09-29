section .text

;; DO NOT MODIFY
global solve_labyrinth

solve_labyrinth:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15

    mov     r12, rdi
    mov     r13, rsi
    mov     r14, rdx
    mov     r15, rcx
    mov     rbx, r8
    ;; DO NOT MODIFY
    ;; YOUR CODE STARTS HERE
    xor rax, rax
    xor r9, r9

    for2:
    mov r11, r14
    dec r11
    cmp rax, r11
    je end
    mov r11, r15
    dec r11
    cmp r9, r11
    je end

    ; fiecare pointer de rand ocupa 8 bytes
    mov r10, [rbx + rax*8]
    ; 0x31 = caracterul '1', marcam celula ca vizitata
    mov byte [r10 + r9], 0x31

    ; verificam daca suntem pe coloana 0 (fara stanga)
    cmp r9, 0
    je check_sus
    ; 0x30 = caracterul '0', celula libera
    cmp byte [r10 + r9 - 1], 0x30
    je stanga

    check_sus:
    ; verificam daca suntem pe randul 0 (fara sus)
    cmp rax, 0
    je check_dreapta
    mov r11, rax
    dec r11
    ; fiecare pointer de rand ocupa 8 bytes
    mov r11, [rbx + r11*8]
    ; 0x30 = caracterul '0', celula libera
    cmp byte [r11 + r9], 0x30
    je sus

    check_dreapta:
    mov r11, r9
    inc r11
    cmp r11, r15
    jge check_jos
    ; fiecare pointer de rand ocupa 8 bytes
    mov r10, [rbx + rax*8]
    ; 0x30 = caracterul '0', celula libera
    cmp byte [r10 + r9 + 1], 0x30
    je dreapta

    check_jos:
    mov r11, rax
    inc r11
    cmp r11, r14
    jge end
    ; fiecare pointer de rand ocupa 8 bytes
    mov r11, [rbx + r11*8]
    ; 0x30 = caracterul '0', celula libera
    cmp byte [r11 + r9], 0x30
    je jos
    jmp end

    dreapta:
    inc r9
    jmp for2
    sus:
    dec rax
    jmp for2
    stanga:
    dec r9
    jmp for2
    jos:
    inc rax
    jmp for2

    end:
    mov [r12], eax
    mov [r13], r9d

    ;; YOUR CODE ENDS HERE
    ;; DO NOT MODIFY
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    pop     rbp
    ret
    ;; DO NOT MODIFY