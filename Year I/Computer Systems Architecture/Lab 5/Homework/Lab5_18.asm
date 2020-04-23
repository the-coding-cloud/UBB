; Two byte strings A and B are given. Obtain the string R that contains only the odd positive elements of the two strings.

bits 32 
global start        
extern exit ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll ; exit is a function that ends the calling process. It is defined in msvcrt.dll
; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data

	a db 1, 2, -3, 4, 5
	len_a equ $-a ; This is the length of the byte string a
    b db 1, 2, -3, 4, 7 
	len_b equ $-b ; This is the length of the byte string b
	r times len_a+len_b db 0 ; We initialize the destination string with the sum of the two previous lengths (in case all the numbers from a and b are odd and positive)

segment code use32 class=code
start:
	mov ecx, len_a  ; We move the length of a in ecx in order to perform the loop "ecx" times --- ecx = 5
	mov esi, 0      ; We start from the beggining of the string --- esi = 0
    mov edi, 0      ; We start putting the requested numbers from the beginning of the destination string --- edi = 0
	jecxz Skip_to_b ; If ecx is 0, we just go to the part where we check the numbers in string b
    
	Check_sign_a:
		mov al, [a+esi]   ; We move the first byte into al in order to do all the calculations that we need - for the first iteration, al = 01
        cmp al, 0         ; Here, we do the fictional subtraction in order to check if the value in al is greater or not than 0 - for the first iteration, the result is 1
        jg Check_parity_a ; If al is greater than 0 (therefore, positive), we can jump to the next part, where we check the parity of the number
        jmp Do_nothing_a  ; If we reach this instruction, our number is not positive, so we skip to the end of this iteration
        
        Check_parity_a:
            mov ah, 0     ; We will perform an unsigned division and we need to divide a word to a byte, therefore we need to extend al - for the first iteration, ah = 0001
            mov bl, 2     ; This will be our divisor. We divide by 2 to see if the remainder is different or not from 0
            div bl        ; We perform the division and the remainder is stored in ax. For the first iteration, ax = 01
            cmp ah, 0     ; We do the fictional subtraction in order to check if the remainder is 0 or not
            jnz Move_a    ; If the remainder is not 0, therefore the initial number is odd, we go to the part where we move our positive, odd number into the destination string
            jmp Do_nothing_a ; If we reach this instruction, our number is not odd, so we skip to the end of this iteration
    
        Move_a:
            mov al, [a+esi] ; We lost the number when we performed the division, so we move it once again in al
            mov [r+edi], al ; We move the number into our destination string
            inc edi         ; We increase the index in the destination string
            
        Do_nothing_a:
        
        inc esi ; We increase the index in the source string
        
	loop Check_sign_a ; We do it all over again until ecx becomes 0 - after the first iteration, ecx = 4
    
    ; We perform exactly the same operations on string b 
    
    Skip_to_b:
    mov ecx, len_b
    mov esi, 0
    
    Check_sign_b:
		mov al, [b+esi]
        cmp al, 0
        jg Check_parity_b
        jmp Do_nothing_b
        
        Check_parity_b:
            mov ah, 0
            mov bl, 2
            div bl
            cmp ah, 0
            jnp Move_b
            jmp Do_nothing_b
    
        Move_b:
            mov al, [b+esi]
            mov [r+edi], al    
            inc edi
        
        Do_nothing_b:
        
        inc esi
        
	loop Check_sign_b
    
	Do_nothing:
    ; We finish the program here

	; exit(0)
	push dword 0 ; push the parameter for exit onto the stack
	call [exit] ; call exit to terminate the program