
bits 32

global start        


extern exit, printf, scanf, fopen, fprintf, fread, fclose
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll  
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
                          
segment data use32 class=data
	mere dd  0      
  
	message  db "Cate mere? ", 0  
	format1  db "%d", 0
    
    file_name_1 db "output.txt", 0 
    write_mode db "w", 0 
    append_mode db "a", 0
    
    file_name_2 db "input.txt", 0
    read_mode db "r", 0
    
    file_descriptor_1 dd -1
    file_descriptor_2 dd -1                  
    format2 db "Ana are %d mere ",0
    
    format3 db "%c", 0
    
    
    len equ 20                   
    text times len db 0    
    
segment code use32 class=code
    start:
       
        ; PART I - READING FROM KEYBOARD
        push dword message 
        call [printf]      
        add esp, 4*1                                          

        push dword mere    
        push dword format1
        call [scanf]      
        add esp, 4 * 2
        
        ; PART II - CREATING OUTPUT FILE
        push dword write_mode    
        push dword file_name_1
        call [fopen]
        add esp, 4*2                

        mov [file_descriptor_1], eax 
        
        cmp eax, 0
        je final
        
        ; PART III - WRITING INTO THE OUTPUT FILE
        push dword [mere]
        push dword format2
        push dword [file_descriptor_1]
        call [fprintf]
        add esp, 4*3
        
        
        
        ; PART IV - OPENING THE INPUT FILE
        push dword read_mode    
        push dword file_name_2
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor_2], eax
        
        cmp eax, 0
        je final
        
        ; PART V - READING FROM THE INPUT FILE
        push dword [file_descriptor_2]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
            
        cmp eax, 0
        je final

        
        ; PART VI - ADDED "si 4 pere"
        push dword text
        push dword [file_descriptor_1]
        call [fprintf]
        add esp, 4*3
        
        mov al, [text+3] ; tried to obtain the 4th character
        sub al, "0" 
        mov bl, al
        mov eax, 0
        mov al, bl
        
        add eax, dword[mere]
        
        
        ; Printed a new line
        mov ebx, 0ah
        
        push ebx
        push format3
        push dword [file_descriptor_1]
        call [fprintf]
        add esp, 4*3
        
        ; Tried to print the result of the addition. The printing works, the result doesn't
        push eax
        push format1
        push dword [file_descriptor_1]
        call [fprintf]
        add esp, 4*3
        
        
        ; Closing the files
        push dword [file_descriptor_1]
        call [fclose]
        add esp, 4
        
        push dword [file_descriptor_2]
        call [fclose]
        add esp, 4
        
        final:
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program