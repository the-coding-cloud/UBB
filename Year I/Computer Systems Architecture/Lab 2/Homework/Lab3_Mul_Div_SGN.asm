bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    a db 11h
    b db 11h
    c dw 1122h
    e dd 11223344h
    x dq 1122334455667788h
    
; the program code will be part of a segment called code
segment code use32 class=code
start:

    ; We have to compute: (a+b*c+2/c)/(2+a)+e+x; a,b-byte; c-word; e-doubleword; x-qword
    
    ; We firstly compute b*c
    mov AL, [b] ; AL = b
    cbw         ; AX = b
    imul word[c]; DX:AX = b*c = 12342h
    
    mov BX, DX
    mov CX, AX
    ;BX:CX = DX:AX = b*c = 12342h
    
    ; We calculate 2/c and store the result in AX at the end, then add it to BX:CX
    mov AL, 2   ; AL = 2
    cbw         ; AX = 2
    cwd         ; DX:AX = 2
    idiv word[c]; AX = 2/c = 0
    
    cwd         ; DX:AX = 2/c = 0
    
    ; We add the previous results
    add CX, AX  ; CX = CX + AX = 2342h
    adc BX, DX  ; BX = BX + DX + CF = 0001h
    ;BX:CX = b*c + 2/c = 12342h
    
    
    ; We add a to the previously obtained result, after extending the register to match the other operand's size
    mov AL, [a] ; AL = a = 11h
    cbw         ; AX = a = 0011h
    cwd         ; DX:AX = a = 0000 0011h
    
    add CX, AX  ; CX = CX + AX = 2353h
    adc BX, DX  ; BX = BX + DX + CF = 0001h + 0 + 0 = 0001h
    ;BX:CX = b*c + 2/c + a = 0001 2353h
    
    mov AL, [a] ; AL = a = 11h
    add AL, 2   ; AL = a + 2 = 13h
    cbw         ; AX = a + 2 = 0013h
    
    push AX ; we store the value of AX on the stack

    ; We now move the dividend on DX:AX in order to be able to perform the division
    
    mov DX, BX
    mov AX, CX
    ; DX:AX = b*c + 2/c + a = 0001 2353h
    
    pop BX      ; BX = a + 2 = 0013h
    
    idiv BX     ; AX = DX:AX / BX = 0F55h
    
    cwde        ; EAX = (b*c + 2/c + a)/(a + 2) = 00000F55h
    
    add EAX, [e]; EAX = EAX + e = (b*c + 2/c + a)/(a + 2) + e = 11224299h
    cdq         ; EDX:EAX = b*c + 2/c + a)/(a + 2) + e = 00000000 11224299h
    
    mov EBX, [x]; EBX = 55667788h
    mov ECX, [x+4]; ECX = 11223344h
    
    add EAX, EBX ; EAX = EAX + EBX = 6688BA21h
    adc EDX, ECX ; EDX = EDX + ECX = 11223344h
    
    
    
    
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program