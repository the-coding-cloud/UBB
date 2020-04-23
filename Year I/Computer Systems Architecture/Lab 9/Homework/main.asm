;Read from file numbers.txt a string of numbers (positive and negative). Build two strings using read numbers:
;P – only with positive numbers
;N – only with negative numbers
;Display the strings on the screen.

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll   
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

extern create_positive_number_string 

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
    
        ; Call fopen() to open the file
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
        
        
        
        ; Here we call our external function - the parameters are the memory addresses of the read text and the beginning of the positive number string
        push dword text
        push dword positive
        call create_positive_number_string
        add esp, 4*2
        
        
        
        mov esi, text       ; Our source address will be the address for the label "text"
        mov edi, negative   ; Our destination address will be the address for the label "negative"
        mov ax, 0           ; We will compute our positive numbers in this register
        mov cl, 0           ; This register will be set to 1 if the current number is negative
        
        do_negative_numbers:
            mov bl, [esi]   ; We take byte by byte and analyze their value
            inc esi         ; We move to the address of the next byte
               
            cmp bl, ' '       ; If we reached a space character, we jump to the specific case
            je space_case_neg
            
            cmp bl, '-'       ; If we reached a minus, we jump to the specific case
            je set_to_neg_n
            
            cmp bl, 0                   ; If the byte is 0, we reached the end of our file and we jump to the next part
            je end_of_negative_numbers
            
            cmp cl, 1                   ; If our current number is known to be negative, we jump to the part where we compute it digit by digit
            je compute_neg_number
            
            jmp do_negative_numbers     ; If the current number is positive, we just go to the start again
            
            compute_neg_number:
            ; ax = ax*10 + current digit
            mov dx, 10
            mul dx                
            sub bl, '0'   ; We find the current digit by subtracting the ASCIIZ code of 0 from the current byte's ASCIIZ code
            mov bh, 0     ; We do an unsigned extension
            add ax, bx    ; We obtain our partial value of the number
            jmp do_negative_numbers ; We go to the beginning
            
            set_to_neg_n:
                mov cl, 1 ; If we encountered a minus, we set cl to 1 so that we know our current number is negative
                jmp do_negative_numbers
                
            space_case_neg:
                cmp cl, 0  ; If the current number is positive, we don't move any value in the negative number string
                je skip_move_neg_number
                
                neg ax         ; We obtained the absolute value in ax so now we negate it, to obtain the corresponding negative value 
                mov [edi], ax  ; We move the value to the string
                add edi, 2     ; We move to the next position
                
                skip_move_neg_number:
                mov ax, 0      ; We reset our values
                mov cl, 0
                jmp do_negative_numbers
                
            end_of_negative_numbers:
                cmp cl, 0       ; If the last number is positive, we skip to printing
                je printing
                
                neg ax         ; We obtained the absolute value in ax so now we negate it, to obtain the corresponding negative value 
                mov [edi], ax  ; We move the value to the string
                add edi, 2     ; We move to the next position
        
        printing:
        
        mov esi, positive
        print_pos:
        ; We print the positive numbers one by one, on the first line
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
        
        ; We print a new line 
            push dword new_line ; ! on the stack is placed the address of the string, not its value
            call [printf]     ; call function printf for printing 
            add esp, 4    ; free parameters on the stack; 4 = size of dword; 2 = number of parameters
        
        mov esi, negative
        print_neg:
        ; We print the negative numbers one by one, on the second line
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
