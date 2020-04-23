bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, fopen, fread, fclose, printf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import scanf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

import fclose msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    access_mode db "r", 0
    file_name times 100 db 0
    N db 0
   
    file_descriptor dd -1
    
    text times 100 db 0
    
    format_filename db "%s", 0
    format db "%d", 0

; our code starts here
segment code use32 class=code
    start:
        
        ; citire nume fisier
        push dword file_name
        push dword format_filename
        call [scanf]     
        add esp, 4*2
        
        ; citire index bit cu validare
        validare:
        
        push dword N
        push dword format
        call [scanf]     
        add esp, 4*2
        
        mov al, byte[N]
        cmp al, 0
        jl validare
        
        cmp al, 7
        jg validare
        
        ; deschidere fisier
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax       
      
        cmp eax, 0
        je final
        
        ; citire din fisier (max 100 caractere)
        push dword [file_descriptor]
        push dword 100
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        ; adresa stringului de prelucrat
        mov esi, text
        
        ; il folosim drept contor in loc de ecx pentru loop, pentru ca avem nevoie de cl la shiftari si se va modifica
        mov edi, eax
        
        ; aici retinem suma bitilor
        mov edx, 0
        
        ; asta va fi masca noastra pentru a prelua al N-lea bit
        mov bl, 10000000b
        mov bh, byte[N]
        mov cl, bh
        shr bl, cl
        
        ; cu atatea pozitii vom shifta al N-lea bit ca sa il putem aduna la suma la final
        mov ah, byte[N]
        sub ah, 7
        neg ah
        mov cl, ah
        
        repeta:
            lodsb
            and al, bl          
            shr al, cl
            cmp al, 0
            je skip
            
            inc edx
            
            skip:
            dec edi
            cmp edi, 0
            jne repeta
        
        afisare:
        
        push edx
        push dword format
        call [printf]
        add esp, 4*2
        
        ;push dword text
        ;push dword format_filename
        ;call [printf]
        ;add esp, 4*2
        
        push dword[file_descriptor]
        call [fclose]
        add esp, 4
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
