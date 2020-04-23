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
    
    mov AL, [b] ; AL = 11h
    mov AH,  0  ; AX = 0011h
    mul word[c] ; DX:AX = b*c = 12342h
    
    mov BX, DX
    mov CX, AX
    ;BX:CX = DX:AX = b*c = 12342h
    
    mov AL, 2   ; AL = 2
    mov AH, 0   ; AX = 2
    mov DX, 0   ; DX:AX = 2
    div word[c] ; AX = 2/c = 0
    
    mov DX, 0   ; DX:AX = 2/c = 0
    
    add CX, AX  ; CX = CX + AX = 2342h
    adc BX, DX  ; BX = BX + DX + CF = 0001h
    ;BX:CX = b*c + 2/c = 00012342h
    
    mov AL, [a] ; AL = a = 11h
    mov AH, 0   ; AX = a = 0011h
    mov DX, 0   ; DX:AX = a = 00000011h
    
    add CX, AX  ; CX = CX + AX
    adc BX, DX  ; BX = BX + DX + CF
    ;BX:CX = b*c + 2/c + a = 00012353h
    
    mov AL, [a] ; AL = a = 11h
    add AL, 2   ; AL = a + 2 = 13h
    mov AH, 0   ; AX = a + 2 = 0013h
    
    push AX     ; we store the value of AX on the stack

    ; We now move the dividend on DX:AX in order to be able to perform the division
    mov DX, BX
    mov AX, CX
    ; DX:AX = b*c + 2/c + a = 00012353h
    
    pop BX ; BX = a + 2 = 0013h
    
    div BX ; AX = DX:AX / BX = 0F55h 
    mov DX, 0 ; DX = 0
    ; DX:AX = (b*c + 2/c + a)/(a + 2) = 00000F55h
    
    push  DX     ; the high part of the doubleword DX:AX is saved on the stack
	push  AX     ; the low part of the doubleword DX:AX is saved on the stack
    pop EAX      ; EAX = (b*c + 2/c + a)/(a + 2) = 00000F55h
    
    add EAX, [e] ; EAX = (b*c + 2/c + a)/(a + 2) + e = 11224299h
    
    mov EDX, 0   ; EDX = 0
    
    mov EBX, [x]; EBX = 55667788h
    mov ECX, [x+4]; ECX = 11223344h
    
    add EAX, EBX ; EAX = EAX + EBX = 6688BA21h
    adc EDX, ECX ; EDX = EDX + ECX = 11223344h
    
    
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program