bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    a dw 127
    b dw 200
    c dw 400
    d dw 3
    
; the program code will be part of a segment called code
segment code use32 class=code
start:

;b+a-(4-d+2)+c+(a-b)

    mov AX, 4; AX = 4
    mov BX, [d]; BX = 5
    sub AX, BX; AX = AX - BX = 4 - 3 = 1
    add AX, 2; AX = AX + 2 = 1 + 2 = 3
    
    mov BX, [b]; BX = b = 200
    mov CX, [a]; CX = a = 127
    add BX, CX; BX = BX + CX = 200 + 127 = 327
    sub BX, AX; BX = BX - AC = 327 - 3 = 324
    mov AX, [c]; AX = 400
    add BX, AX; BX = BX + AX = 324 + 400 = 724
    
    mov AX, [a]; AX = a = 127
    mov CX, [b]; CX = b = 200
    sub AX, CX; AX = AX - CX = 127 - 200 = -73
    
    add BX, AX; BX = BX + AX = 724 + (-73) = 653

    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program