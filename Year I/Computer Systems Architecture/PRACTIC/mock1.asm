bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf        ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "r1.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    
    len equ 100
    mesaj times len db 0
    decodat times len db 0
    format db "%s", 0

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
        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword mesaj
        call [fread]
        
        mov esi, mesaj
        mov edi, decodat
        
        repeta:
            mov al, [esi]
            cmp al, 0
            je afisare
            
            movsb
            cmp al, "y"
            je do_y
            
            cmp al, "z"
            je do_z
            
            cmp al, " "
            je skip 
            
            cmp al, "."
            je skip
            
            cmp al, ","
            je skip
            
            sub byte[edi-1], 2
            jmp skip
            
            do_y:
            mov byte[edi-1], "a"
            jmp skip
            
            do_z:
            mov byte[edi-1], "b"
            jmp skip
            
            skip:
            
            jmp repeta
            
        afisare:
        
        push dword decodat
        push dword format
        call [printf]
        add esp, 4*2
        
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
