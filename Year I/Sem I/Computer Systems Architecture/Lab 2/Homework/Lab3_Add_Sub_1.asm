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
    b dw 1122h
    c dd 11223344h
    d dq 1122334455667788h
    
; the program code will be part of a segment called code
segment code use32 class=code
start:

    ; we need to compute (d+d)-a-b-c=(d+d)-(a+b+c)
    ; firstly, we can compute (a+b+c), then subtract it from (d+d)
    
    mov AX, [c]  ; AX = 3344h
    mov DX, [c+2]; DX = 1122h
    mov CX, [b]  ; CX = 1122h
    mov BX, 0    ; BX = 0000h
    ; BX:CX = 00001122h
    
    add AX, CX   ; AX = AX + CX = 3344h + 1122h = 4466h
    adc DX, BX   ; DX = DX + BX + CF = 1122h + 0000h + 0 = 1122h
    ; DX:AX = b+c
    
    mov CL, [a]  ; CL = 11h  
    mov CH, 0    ; CX = 0011h

    mov BX, 0    ; BX = 0000h
    ; BX:CX = 0000 0011h
    
    add AX, CX   ; AX = AX + CX = 4466h + 0011h = 4477h
    adc DX, BX   ; DX = DX + BX + CF = 1122h + 0000h + 0 = 1122h
    ; DX:AX = a + b + c = 11224477h 
    
    push  DX     ; the high part of the doubleword DX:AX is saved on the stack
	push  AX     ; the low part of the doubleword DX:AX is saved on the stack
	pop  ECX     ; ECX = 11224477h
    
    mov EBX, 0   ; EBX = 00000000h
    ; EBX:ECX = 0000000011224477h
    
    mov EAX, [d]  ; EAX = 55667788h
    mov EDX, [d+4]; EDX = 11223344h
    ; Below, we compute d+d
    add EAX, EAX  ; EAX = EAX + EAX = 55667788h + 55667788h = AACCEF10h
    adc EDX, EDX  ; EDX = EDX + EDX = 11223344h + 11223344h = 22446688h
    
    ; Below, we compute (d+d)-(a+b+c)
    sub EAX, ECX  ; EAX = EAX - ECX = AACCEF10h - 11224477h = 99AAAA99h
    sbb EDX, EBX  ; EDX = EDX - EBX - CF = 22446688h - 00000000h - 0 = 22446688h
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program