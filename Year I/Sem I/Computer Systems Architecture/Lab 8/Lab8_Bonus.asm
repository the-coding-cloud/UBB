bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf, fopen, fprintf, fclose         
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
                          
segment data use32 class=data
	x dd 0       
    y dw 0, 0       
    z db 0, 0, 0, 0
    ; char strings are of type byte
	message1  db "x=", 0   
    message2  db "y=", 0
    message3  db "z=", 0 
    
	format_1  db "%d", 0
    text      db "Rezultatul este:", 0
   
segment code use32 class=code
    start:              
        
        push dword message1
        call [printf]       
        add esp, 4*1 
                                                   
        push dword x      
        push dword format_1
        call [scanf]    
        add esp, 4 * 2    
                           
        push dword message2 
        call [printf]       
        add esp, 4*1        
                                                  
        push dword y      
        push dword format_1
        call [scanf]       
        add esp, 4 * 2    
                           

        push dword message3 
        call [printf]       
        add esp, 4*1        
        
        push dword z     
        push dword format_1
        call [scanf]       
        add esp, 4 * 2    
        
        mov ax, [x]
        mov dx, [x+2]
        mov ebx, [y]
        idiv bx
        
        mov bx, ax
        mov al, [z]
        cbw
        
        add ax, bx
        
        mov ch, 2
        idiv ch
        
        cbw
        cwde
        
        push eax   
        push dword format_1
        call [printf] 
        add esp, 4 * 2
               
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program