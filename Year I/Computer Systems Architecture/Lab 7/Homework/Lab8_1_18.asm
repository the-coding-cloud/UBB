; The code below will print message ”n=”, then will read from keyboard the value of perameter n.
; Read a decimal number and a hexadecimal number from the keyboard. Display the number of 1's of the sum of the two numbers in binary format.

bits 32

global start        

; declare extern functions used by the programme
extern exit, printf, scanf ; add printf and scanf as extern functions            
import exit msvcrt.dll    
import printf msvcrt.dll    ; tell the assembler that function printf is found in msvcrt.dll library
import scanf msvcrt.dll     ; similar for scanf
                          
segment data use32 class=data
	a dw 0       ; in this variable we will store the decimal value read from the keyboard
    b dw 0       ; in this variable we will store the hexadecimal value read from the keyboard
    
    ; char strings are of type byte
	message1  db "Introduceti un nr (in decimal)", 0      ; char strings for C functions must terminate with 0(value, not char)
    message2  db "Introduceti un nr (in hexadecimal)", 0  ; char strings for C functions must terminate with 0(value, not char)
    
	format_1  db "%d", 0  ; %d <=> decimal number (base 10)
    format_2  db "%x", 0  ; %x <=> hexadecimal number (base 16)
    format_3 db "Numarul este %d", 0 ; %d will be replaced with our result
    
segment code use32 class=code
    start:
       
        ; will call printf(message)
        ; place parameters on stack
        push dword message1 ; ! on the stack we place the address of the string, not its value
        call [printf]       ; call function printf for printing
        add esp, 4*1        ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
                                                   
        ; will call scanf(format_1, a) => will read a number in variable a
        ; place parameters on stack from right to left
        push dword a       ; ! address of a, not value
        push dword format_1
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
                           ; 4 = size of a dword; 2 = no of perameters
                           
        ; will call printf(message) again
        ; place parameters on stack
        push dword message2 ; ! on the stack we place the address of the string, not its value
        call [printf]       ; call function printf for printing
        add esp, 4*1        ; free parameters on the stack; 4 = size of dword; 1 = number of parameters
                                                   
        ; will call scanf(format_2, b) => will read a number in variable b
        ; place parameters on stack from right to left
        push dword b       ; ! address of b, not value
        push dword format_2
        call [scanf]       ; call function scanf for reading
        add esp, 4 * 2     ; free parameters on the stack
                           ; 4 = size of a dword; 2 = no of perameters
        
        mov ax, [a]  ; we move a to ax
        add ax, [b]  ; we add b to ax
        ; we compute everything in ax from the beginning, because we will use div afterwards
        
        cmp ax, 0    ; we want to see if the sum is 0
        jz print_0   ; if the sum is 0, there's no need to execute the next part and we can directly skip to printing 0 on the screen
        
        mov ch, 0    ; here we will store how many 1's appear in the binary representation
        mov cl, 2    ; we will further use this register for repeated divisions by 2
        
        repeta:
            div cl          ; we divide ax by 2 and then analyze the results from the division
            cmp ah, 1       ; we compare the remainder to 1
            jnz next_step   ; if the remainder is not 1, we can directly jump to the next step
            inc ch          ; if the remainder was 1, we increment ch, because we found another 1 in the binary representation
            
            next_step:
            cmp al, 0           ; we want to see if the quotient is 0
            jz print_result     ; if the quotient is 0, we can directly skip to the end
            mov ah, 0           ; if the quotient is not 0, we set ah to 0 so that we can perform further divisions with ax
            jmp repeta          ; we go again to the beginning
            
        
        print_0:
        mov ch, 0   ; if the sum was 0, we just set ch to 0

        print_result:
        mov ebx, 0  ; we will store the final result in ebx because we need to place 32 bits on the stack
        mov bl, ch  ; we move ch to bl
        push ebx    ; we place ebx on the stack
        push dword format_3 ; ! on the stack is placed the address of the string, not its value
        call [printf]       ; call function printf for printing 
        add esp, 4 * 2
        
        ; exit(0)
        push dword 0      ; place on stack parameter for exit
        call [exit]       ; call exit to terminate the program