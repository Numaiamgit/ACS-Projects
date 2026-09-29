


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
global apply_delay

; void apply_delay(struct flight* flights, int nrFlights)
; rdi = struct flight *flights
; rsi = int nrFlights
apply_delay:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r14
    push r15
    ;; DO NOT MODIFY
    ;; Your code starts here
    xor rcx, rcx
    for:
    mov rax, rdi
    mov rdx, rcx
    ; dimensiunea unui struct flight in bytes
    imul rdx, 42
    add rax, rdx

    movzx r8, byte [rax + departingTime.minutes]
    movzx r9, byte [rax + departingTime.hour]
    movzx r10, byte [rax + departingTime.day]
    movzx r11, byte [rax + delayMinutes]
    add r8, r11
    ; 60 de minute intr-o ora
    cmp r8, 60
    jge departing_decalat_ora
    jl dpdo2
    departing_decalat_ora:
    ; scadem 60 de minute si trecem la ora urmatoare
    sub r8, 60
    inc r9
    dpdo2:
    movzx r11, byte [rax + delayHours]
    add r9, r11
    ; 24 de ore intr-o zi
    cmp r9, 24
    jge departing_decalat_zi
    jl dpdo3
    departing_decalat_zi:
    ; scadem 24 de ore si trecem la ziua urmatoare
    sub r9, 24
    inc r10
    dpdo3:

    mov byte [rax + departingTime.minutes], r8b
    mov byte [rax + departingTime.hour], r9b
    mov byte [rax + departingTime.day], r10b

    xor r8, r8
    xor r9, r9
    xor r10, r10
    movzx r8, byte [rax + arrivingTime.minutes]
    movzx r9, byte [rax + arrivingTime.hour]
    movzx r10, byte [rax + arrivingTime.day]
    movzx r11, byte [rax + delayMinutes]
    add r8, r11
    ; 60 de minute intr-o ora
    cmp r8, 60
    jge arriving_decalat_ora
    jl ado2
    arriving_decalat_ora:
    ; scadem 60 de minute si trecem la ora urmatoare
    sub r8, 60
    inc r9
    ado2:
    movzx r11, byte [rax + delayHours]
    add r9, r11
    ; 24 de ore intr-o zi
    cmp r9, 24
    jge arriving_decalat_zi
    jl ado3
    arriving_decalat_zi:
    ; scadem 24 de ore si trecem la ziua urmatoare
    sub r9, 24
    inc r10
    ado3:

    mov byte [rax + arrivingTime.minutes], r8b
    mov byte [rax + arrivingTime.hour], r9b
    mov byte [rax + arrivingTime.day], r10b

    inc rcx
    cmp rcx, rsi
    jl for
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