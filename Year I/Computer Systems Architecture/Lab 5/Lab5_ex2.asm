;Se da un sir de caractere format din litere mici.
;Sa se transforme acest sir in sirul literelor mari corespunzator.
bits 32 
global start        
extern exit,printf ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data

segment code use32 class=code
start:
	mov al, -4
    mov bl, 2
    cmp al, bl
    jG et1
    et0:
        mov cl, bl
        jmp iesire
    et1:
        mov cl, al
    iesire:

	; exit(0)
	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program