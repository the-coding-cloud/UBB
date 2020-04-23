bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    a db 2
    b db 64
    c db 45
    d dw 200
    
; the program code will be part of a segment called code
segment code use32 class=code
start:

;200-[3*(c+b-d/a)-300]

    mov AX, [d]; AX = d = 200
    mov BL, [a]; BL = a = 2
    div BL; AL = AX/BL = 200/2 = 100, AH = AX%BL = 0
    
    mov BL, [c]; BX = c = 45
    mov CL, [b]; CX = b = 64
    add BL, CL; BL = BL + CL = 45 + 64 = 109
    sub BL, AL; BL = BL - AL = 109 - 100 = 9
    mov AL, BL; AL = 9
    mov BL, 3;
    mul BL; AX = AL * BL = 9 * 3 = 27
    sub AX, 300; AX = 27 - 300 = -273
    mov BX, 200; BX = 200
    sub BX, AX; BX = BX - AX = 200 - (-273) = 473 

    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program