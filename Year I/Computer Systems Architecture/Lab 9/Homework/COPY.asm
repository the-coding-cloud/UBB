;Read from file numbers.txt a string of numbers (positive and negative). Build two strings using read numbers:
;P – only with positive numbers
;N – only with negative numbers
;Display the strings on the screen.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "numbers.txt", 0   ; filename to be read --- in our case "input.txt"
    access_mode db "r", 0         ; r - opens a file for reading. The file must exist. 
    file_descriptor dd -1         ; variable to hold the file descriptor
    len equ 100                   ; maximum number of characters to read
    text times len db 0           ; string to hold the text which is read from file
    positive times len dw 0
    negative times len dw 0
    format db "%d ",0
    new_line db 0xA,0
    
; our code starts here
segment code use32 class=code
    start:
        ; Call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; Clean-up the stack

        mov [file_descriptor], eax  ; Store the file descriptor returned by fopen

        ; Check if fopen() has successfully opened the file (EAX != 0)
        cmp eax, 0
        je final   ; If the file does not exist or an error occured, we just directly to the end of the code
        
        ; Read the text from file using fread()
        ; After the fread() call, EAX will contain the number of chars we've read 
        ; eax = fread(text, 1, len, file_descriptor)        
        push dword [file_descriptor]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
            
        ; If we haven't read any new element, we jump to the next part
        cmp eax, 0
        je final
        
        mov esi, text
        mov edi, positive
        mov ax, 0
        mov cl, 0
        
        do_positive_numbers:
            mov bl, [esi]
            inc esi
            cmp bl, ' '
            je space_case_pos
            
            cmp bl, '-'
            je set_to_neg_p
            
            cmp bl, 0
            je end_of_positive_numbers
            
            cmp cl, 0
            je compute_pos_number
            
            jmp do_positive_numbers
            
            compute_pos_number:
            mov dx, 10
            mul dx
            sub bl, '0'
            mov bh, 0
            add ax, bx
            jmp do_positive_numbers
            
            set_to_neg_p:
                mov cl, 1
                jmp do_positive_numbers
                
            space_case_pos:
                cmp cl, 0
                jne skip_move_pos_number
        
                mov [edi], ax
                add edi, 2
                
                skip_move_pos_number:
                mov ax, 0
                mov cl, 0
                jmp do_positive_numbers
            
            end_of_positive_numbers:
                cmp cl, 0
                jne skip_move_final_number
        
                mov [edi], ax
                add edi, 2
                skip_move_final_number:
       
        
        mov esi, text
        mov edi, negative
        mov ax, 0
        mov cl, 0
        
        do_negative_numbers:
            mov bl, [esi]
            inc esi  
               
            cmp bl, ' '
            je space_case_neg
            
            cmp bl, '-'
            je set_to_neg_n
            
            cmp bl, 0
            je end_of_negative_numbers
            
            cmp cl, 1
            je compute_neg_number
            
            jmp do_negative_numbers
            
            compute_neg_number:
            mov dx, 10
            mul dx
            sub bl, '0'
            mov bh, 0
            add ax, bx
            jmp do_negative_numbers
            
            set_to_neg_n:
                mov cl, 1
                jmp do_negative_numbers
                
            space_case_neg:
                cmp cl, 0
                je skip_move_neg_number
                
                neg ax
                mov [edi], ax
                add edi, 2
                
                skip_move_neg_number:
                mov ax, 0
                mov cl, 0
                jmp do_negative_numbers
                
            end_of_negative_numbers:
                cmp cl, 0
                je printing
                
                neg ax
                mov [edi], ax
                add edi, 2
        
        printing:
        
        mov esi, positive
        print_pos:
            mov eax, 0
            mov ax, [esi]
            add esi, 2
            
            cmp eax, 0
            je next
            
            push dword eax
            push dword format ; ! on the stack is placed the address of the string, not its value
            call [printf]     ; call function printf for printing 
            add esp, 4 * 2     ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
            
            jmp print_pos
        
        next: 
        
            push dword new_line ; ! on the stack is placed the address of the string, not its value
            call [printf]     ; call function printf for printing 
            add esp, 4    ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
        
        mov esi, negative
        print_neg:
            mov ax, [esi]
            cwde
            add esi, 2
            
            cmp eax, 0
            je final
            
            push dword eax
            push dword format ; ! on the stack is placed the address of the string, not its value
            call [printf]     ; call function printf for printing 
            add esp, 4 * 2     ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
            
            jmp print_neg
        
        final:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
