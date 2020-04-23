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

    ; We need to compute (d-b)-a-(b-c)

    mov EBX, [d]    ; EBX = 55667788h
    mov ECX, [d+4]  ; ECX = 11223344h
    
    ; 1. We firstly compute d-b
    mov AX, [b]     ; AX = 1122h
    cwde            ; EAX = AX = 00001122h
    cdq             ; EAX = 00001122h, EDX = 00000000h
    sub EBX, EAX    ; EBX = EBX - EAX = 55667788h - 00001122h = 55666666h
    sbb ECX, EDX    ; ECX = ECX - EDX = 11223344h - 00000000h = 11223344h
    
    ; 2. We continue with (d-b)-a
    mov AL, [a]     ; AL = 11h
    cbw             ; AX = 0011h
    cwde            ; EAX = 00000011h
    cdq             ; EAX = 00000011h, EDX = 00000000h
    sub EBX, EAX    ; EBX = EBX - EAX = 55666666h - 00000011h = 55666655h
    sbb ECX, EDX    ; ECX = ECX - EDX - CF = 11223344h - 00000000h - CF = 11223344h

    ; 3. Now we calculate (b-c)
    mov AX, [b]     ; AX = 1122h
    cwde            ; EAX = AX = 00001122h
    mov EDX, [c]    ; EDX = 11223344h
    sub EAX, EDX    ; EAX = EAX - EDX = 00001122h - 11223344h = EEDDDDDEh
    cdq             ; EAX = EEDDDDDEh, EDX = FFFFFFFFh
    
    ; 4. We subtract (b-c) from ((d-b)-a)
    sub EBX, EAX    ; EBX = EBX - EAX = 55666655h - EEDDDDDEh = 66888877h
    sbb ECX, EDX    ; ECX = ECX - EDX = 11223344h - FFFFFFFFh = 11223344h
    
    
    ; call exit(0) ), 0 represents status code: SUCCESS
    push dword 0 ; saves on stack the parameter of the function exit
    call [exit] ; function exit is called in order to end the execution of the program