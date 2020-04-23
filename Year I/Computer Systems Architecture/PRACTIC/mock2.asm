bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 

; declare external functions needed by our program
extern exit, fopen, scanf, fprintf, fclose          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "r2.txt", 0
    access_mode db "w", 0
    file_descriptor dd -1
    
    n dd 0
    format db "%x %d --- ", 0
    format_citire db "%d", 0
    

; our code starts here
segment code use32 class=code
    start:
        
        push dword access_mode
        push dword file_name
        call [fopen]
        
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        citire:
            push dword n
            push dword format_citire
            call [scanf]
            
            cmp dword [n], 0
            je aproape_final
            
            popcnt eax, dword [n]
            
            push eax
            push dword [n]
            push dword format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4*4
            
            jmp citire
        
        aproape_final:
            push dword [file_descriptor]
            call  [fclose]
            add esp, 4
        
        final:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
