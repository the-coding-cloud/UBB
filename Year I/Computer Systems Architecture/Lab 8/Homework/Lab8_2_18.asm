;A text file is given. The text contains letters, spaces and points. Read the content of the file, determine the number of words and display the result on the screen. (A word is a sequence of characters separated by space or point)

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf
import printf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "input.txt", 0   ; filename to be read --- in our case "input.txt"
    access_mode db "r", 0         ; file access mode:
                                  ; r - opens a file for reading. The file must exist. 
    file_descriptor dd -1         ; variable to hold the file descriptor
    len equ 100                   ; maximum number of characters to read
    text times len db 0           ; string to hold the text which is read from file
    stop_here dd 0                ; this memory location is exactly after our stored text and it helps us know where to stop the iterations
    format db "%d ",0
    
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

        mov bl, 1       ; We consider the initial character to be a space/period
        mov edi, 0      ; This will be the count for the transitions from space/period to character and vice-versa
        
        read:  
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
            je reading_is_over
            
            mov esi, text ; Here we store the address of the memory location of our text
            
            measure:
                cmp esi, stop_here   ; We check if the current address is the same as the "stop_here" address
                je read              ; If the addresses match, we...stop the comparisons there and do the reading again
                
                lodsb                ; We load the current character
                
                ; When reading less than len characters, the rest of the characters remain from the previously read text, so we need to make sure we don't have any leftover words
                ; Therefore, we change each character to ' ' after loading it and it won't affect the final result in any way
                mov [esi-1], byte ' '
                
                cmp al, 0            ; This is how we realize we haven't read anything from that point and beyond
                je measure
                
                ; We can split our problem into 4 possibilities:
                ; 1. a) The previous character was a letter (bl=0), the current character is a letter
                ;    b) The previous character was a letter (bl=0), the current character is a space/period (we increment edi in this situation)
                ; 2. a) The previous character was a space/period (bl=1), the current character is a letter (we increment edi in this situation)
                ;    b) The previous character was a space/period (bl=1), the current character is a space/period)
                ; At the end, the number of words is equal to (edi+1)/2 (deduced the formula after analyzing all the possible combinations)
                
                cmp bl, 0 ; The prev. character was a letter
                je case_1
                
                cmp bl, 1 ; The prev. character was a space/period
                je case_2
                
                case_1:
                    cmp al, " "
                    je what_to_do_1
                    cmp al, "."
                    je what_to_do_1
                    
                    ; Case 1.a
                    mov bl, 0    ; We set bl to 0 to mark that our current character is a letter, then move to the next character
                    jmp measure
                    
                    ; Case 1.b
                    what_to_do_1:
                        mov bl, 1; We set bl to 1 to mark that our current character is a space/period, then move to the next character
                        inc edi  ; We increment our counter
                        jmp measure
                
                case_2:
                    cmp al, " "
                    je what_to_do_2
                    cmp al, "."
                    je what_to_do_2
                    
                    ; Case 2.a
                    mov bl, 0   ; We set bl to 0 to mark that our current character is a letter, then move to the next character
                    inc edi     ; We increment our counter
                    jmp measure
                     
                    ; Case 2.b
                    what_to_do_2:
                        mov bl, 1 ; We set bl to 1 to mark that our current character is a space/period, then move to the next character
                        jmp measure         

        reading_is_over:
        
        ; We perform our operations on the number of transitions from space/period to characters and vice versa
        inc edi
        mov eax, edi
        mov edx, 0
        mov ecx, 2
        div ecx

        push eax
        push dword format
        call [printf]      
        add esp, 4*2
        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:
        
        ; exit(0)
        push dword 0
        call [exit]