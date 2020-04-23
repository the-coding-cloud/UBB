bits 32
global start
extern exit,scanf,fopen,fprintf,fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

segment data use32 class=data
    nume_fisier db "r2.txt",0
    descriptor_fisier dd -1
    mod_acces db "w",0
    
    format_citire db "%d",0
    format_scriere db "- %x %d -",0
    numar dd 0
segment code use32 class=code
start:
    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add esp,8
    mov [descriptor_fisier],eax
    cmp eax,0
    je final
    
    loop_citire:
        push dword numar
        push dword format_citire
        call [scanf]
        add esp,8
        cmp dword [numar],0  ; daca numarul citit este 0 , stop
        je stop
        
        ;altfel :
        popcnt eax,[numar]
        
        push dword eax
        push dword [numar]
        push dword format_scriere
        push dword [descriptor_fisier]
        call [fprintf]
        add esp,12
        
        jmp loop_citire
        
    stop:
    push dword [descriptor_fisier]
    call [fclose]
    add esp,4
    
    final:
    push dword 0
    call [exit]