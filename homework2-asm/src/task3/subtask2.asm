section .bss
    struc flight
        destination:      resb 32
        departingTime.day:     resb 1
        departingTime.hour:    resb 1
        departingTime.minutes: resb 1
        arrivingTime.day:      resb 1
        arrivingTime.hour:     resb 1
        arrivingTime.minutes:  resb 1
        bag_weight:            resb 2
        delayMinutes:          resb 1
        delayHours:            resb 1
    endstruc

section .text

;; DO NOT MODIFY
global filter_flights

; void filter_flights(struct flight* origFlights, struct flight* finalFlights
;                      int* nrFlights, int min_bag_weight)
; rdi = struct flight *origFlights
; rsi = struct flight *finalFlights
; rdx = int *nrFlights
; rcx = int min_bag_weight
filter_flights:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    ;; DO NOT MODIFY
    ;; Your code starts here
    xor rax, rax
    xor r8, r8
    mov r8, rdi
    mov rax, rdi
    xor r11, r11
    xor rbx, rbx
    xor r9, r9
    for:
    mov r10, rax
    mov r8, r9
    ; dimensiunea unui struct flight in bytes
    imul r8, 42
    add r10, r8
    ; bag_weight este la offset 38 in struct (32+1+1+1+1+1+1=38)
    movzx r8, word [r10 + 38]
    cmp r8, rcx
    jge copiere
    jl continua
    copiere:
    mov r8, r11
    ; dimensiunea unui struct flight in bytes
    imul r8, 42
    mov r10, r9
    ; dimensiunea unui struct flight in bytes
    imul r10, 42
    mov rbx, [rax + r10]
    mov [rsi + r8], rbx
    ; copiem bytes 8-15 din struct
    mov rbx, [rax + r10 + 8]
    ; offset 8 in struct
    mov [rsi + r8 + 8], rbx
    ; copiem bytes 16-23 din struct
    mov rbx, [rax + r10 + 16]
    ; offset 16 in struct
    mov [rsi + r8 + 16], rbx
    ; copiem bytes 24-31 din struct
    mov rbx, [rax + r10 + 24]
    ; offset 24 in struct
    mov [rsi + r8 + 24], rbx
    ; copiem bytes 32-39 din struct
    mov rbx, [rax + r10 + 32]
    ; offset 32 in struct
    mov [rsi + r8 + 32], rbx
    ; copiem ultimii 2 bytes (bag_weight)
    mov bx, word [rax + r10 + 40]
    ; offset 40 in struct
    mov [rsi + r8 + 40], bx
    inc r11

    continua:
    inc r9
    mov r12d, [rdx]
    cmp r9, r12
    jl for
    end:
    mov [rdx], r11
    ;; Your code ends here
    ;; DO NOT MODIFY
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    pop rbp
    ret
    ;; DO NOT MODIFY

    leave
    ret