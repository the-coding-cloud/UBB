; A string of doublewords is given. Order in increasing order the string of the high words 
;(most significant) from these doublewords. The low words (least significant) remain unchanged.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    sir DD 12AB5678h, 1256ABCDh, 12344344h
    len EQU ($-sir)/4

; our code starts here
segment code use32 class=code
    start:
        MOV ECX, len
        MOV ESI, sir
        MOV EDI, sir
        CLD
        JECXZ finish
        sort:
            MOV AX, 0
            LODSW
            LODSW
            push ECX
            SUB ECX, 1
            JECXZ finish
            ADD EDI, 4
            MOV EDX, EDI
            sort_2:
                SCASW
                JG swap
                JBE skip_1
                swap:
                    mov BX, [EDI - 2]
                    mov [EDI - 2], AX
                    mov [ESI - 2], BX
                skip_1:
                ADD EDI, 2
            loop sort_2
            pop ECX
            MOV EDI, EDX
        loop sort
        
        finish:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
