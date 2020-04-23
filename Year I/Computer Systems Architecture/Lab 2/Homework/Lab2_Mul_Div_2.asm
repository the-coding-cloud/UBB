bits 32 ;assembling for the 32 bits architecture
global start

; we ask the assembler to give global visibility to the symbol called start 
;(the start label will be the entry point in the program) 
extern exit ; we inform the assembler that the exit symbol is foreign; it exists even if we won't be defining it
import exit msvcrt.dll  ; we specify the external library that defines the symbol
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
        
; f+(c-2)*(3+a)/(d-4)

; our variables are declared here (the segment is called data) 
segment data use32 class=data
    a db 10
    c db 20
    d db 29
    f dw 500

; the program code will be part of a segment called code
segment code use32 class=code
start:

;f+(c-2)*(3+a)/(d-4)

    mov AL, [c] ; AL = c = 20
    sub AL, 2   ; AL = 20 - 2 = 18
    mov BL, 3   ; BL = 3
    add BL, [a] ; BL = BL + a = 3 + 10 = 13
    mul BL      ; AX = AL * BL = 18 * 13 = 234
    
    mov BL, [d] ; BL = 29
    sub BL, 4   ; BL = 25
    
    div BL      ; AL = AX / BL = 9, AH = AX % BL = 9
    cbw         ; AX = AL = 9
    
    mov BX, [f] ; BX = f = 500
    add AX, BX  ; AX = AX + BX = 509

    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program