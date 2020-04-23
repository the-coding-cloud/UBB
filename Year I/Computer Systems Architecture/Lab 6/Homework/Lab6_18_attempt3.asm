; A string of doublewords is given. Order in increasing order the string of the high words (most significant) from these doublewords.
; The low words (least significant) remain unchanged.


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    string DD 12AB5678h, 1256ABCDh, 12344344h
    len EQU ($-string)/4 ; This variable will store the length of the string; the division by 4 occurs because we store a string of dwords
    dest RESD len     ; We reserve a space in the memory for the destination string (we basically reserve the space necessary for a dword times the length of the initial string)
    len_dest DD 0     ; This variable stores the length of the new string of dwords - we initialize it with 0 because we will perform insertion sort

    
; our code starts here
segment code use32 class=code
    start:
    ; The method used in this exercise is Insertion Sort
    ; We sort the dwords using this algorithm, then 
        MOV ECX, len    ; We will have len iterations in the loop
        MOV ESI, string ; We initialize ESI with the address of string
        CLD             ; The comparisons will take place from left to right
        JECXZ finish    ; If the length of the string is 0, we directly jump to the end of the program
        
        ; This is the main loop, where we do the sort
        outer_loop:
            MOV EAX, 0 ; This is how we ensure the high part of the dword is 0, so that the comparisons takes place properly
            LODSW      ; We firstly load the low part of the current dword in AX
            LODSW      ; We now load the high part of the current dword in AX and use it for the comparisons in insertion sort
            push ECX   ; We store the current value of ECX, which we will need later, in the stack, because in the inner loop we need different values of ECX
            MOV ECX, [len_dest] ; We set the value of ECX to the value of the current destination string of dwords length
            JECXZ skip          ; If the length of the destination string is 0, we go directly to the skip label
            
            inner_loop:
            ; Now we properly do the insertion part of the insertion sort
            ; At the offset (ECX-1)*4 is the element to be compared with AX --- multiplication with 4 is required for pointer arithmetic, because we work with dwords (4*byte)
                CMP EAX, [dest+(ECX-1)*4]  ; We compare the words (the high part of the words is ensured to be 0)
                JA skip                    ; If AX is bigger, no more comparisons are needed and we can directly go to the skip label, then insert EAX in the destination string 
                MOV EBX, [dest + (ECX-1)*4]; If AX is smaller, we "shift" the current value in the destination string to the right, in order to "make space" for the element to be inserted
                MOV [dest + ECX*4], EBX    ; We used the EBX register to shift the value
            loop inner_loop
            
            skip:
            MOV [dest+ECX*4], EAX ; We now insert EAX in the destination string - at the moment, the high part of the dwords in the initial string are stored as low parts, so we need to shift it later
            INC dword[len_dest]   ; The destination string has now one more element, so we increase the variable that stores the destination string length
            pop ECX               ; We now restore the previous value of ECX in order to continue the outer loop
        loop outer_loop
        
        
        ; We will now shift the low parts of the dwords in the destination string in order to make them high parts and then move the low parts of the dwords
        ; of the source string in the destination string
        MOV ECX, len    ; We could also use len_dest, because at this point they are both equal
        MOV ESI, string ; We initialize ESI
        MOV EDI, dest   ; We initialize EDI
        
        loop_3:
            LODSW               ; We load the low part of the current dword in the source string in AX
            SHL dword[EDI], 16  ; We shift the low part from the current dword in the destination string to the lift, thus making it a high part now
            STOSW               ; We store the low part of the current dword in the source string as the low part of the current dword in the destination string
            ADD ESI, 2          ; We move to the next dword in the source string
            ADD EDI, 2          ; We move to the next dword in the destination string
        loop loop_3
        
        finish:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
