bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    a db 20
    b db 30
    c db 35
    d db 50
    
; the program code will be part of a segment called code
segment code use32 class=code
start:

;d-(a+b)+c

    mov AL, [a]; AL = a = 20
    add AL, [b]; AL = AL + b = 20 + 30 = 50
    mov BL, [d]; BL = 50
    sub BL, AL ; BL = BL - AL = 50 - 50 = 0 
    add BL, [c]; BL = BL + c = 0 + 35 = 35

    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program