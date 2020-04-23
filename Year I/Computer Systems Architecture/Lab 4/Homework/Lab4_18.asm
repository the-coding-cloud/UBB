;Given the word A, compute the doubleword B as follows:
;the bits 0-3 of B have the value 0;
;the bits 4-7 of B are the same as the bits 8-11 of A
;the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;
;the bits 12-15 of B have the value 1
;the bits 16-31 of B are the same as the bits 0-15 of B.

; Observation: bits are numbered from right to left

bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it
import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
        
segment  data use32 class=data ; the data segment where the variables are declared 
     a dw 0111011101010110b
     b dd 0

segment  code use32 class=code ; code segment
start: 

     mov  bx, 0 ; we compute the first half of the result in bx
     
     ; 1. The bits 0-3 are already initialised with 0 (along with all the others), so there is no need
     ; to perform other instructions in order to modify the bits

     
     ; 2. We should now isolate bits 8-11 of A and put them into the result
     mov  ax, [a]               ; ax = 0111011101010110b
     and  ax, 0000111100000000b ; ax = 0000011100000000b
     mov  cl, 4                 ; cl = 4
     ror  ax, cl ; we rotate 4 positions to the right: ax = 0000000001110000b
     or   bx, ax ; we put the bits into the result:    bx = 0000000001110000b
    
    
     ; 3. We invert the bits of A, isolate bits 0-1 of A, then put the 8-9 bits of B into the result
     mov ax, [a]                ; ax = 0111011101010110b
     not ax                     ; we invert the bits of A: ax = 1000100010101001b
     and ax, 0000000000000011b  ; we isolate bits 0-1:     ax = 0000000000000001b
     mov cl, 8                  ; cl = 8
     rol ax, cl ; we rotate 8 positions to the left: ax = 0000000100000000b
     or bx, ax  ; we put the bits into the result:   bx = 0000000101110000b
     
     ; and now we repeat the process above in order to obtain bits 10-11
     mov ax, [a]                ; ax = 0111011101010110b
     not ax                     ; we invert the bits of A: ax = 1000100010101001b
     and ax, 0000000000000011b  ; we isolate bits 0-1:     ax = 0000000000000001b
     mov cl, 10                 ; cl = 10
     rol ax, cl ; we rotate 10 positions to the left: ax = 0000010000000000b
     or bx, ax  ; we put the bits into the result:    bx = 0000010101110000b
     
     
     ; 4. We now set the value of the bits 12-15 to 1
     mov ax, 1111000000000000b ; ax = 1111000000000000b
     or bx, ax                 ; we put the bits into the result: bx = 1111010101110000b
     
     
     ; 5. Now, we need to duplicate bits 0-15 in order to obtain bits 16-31
     mov ax, bx ; we make a copy of bits 0-15: ax = 1111010101110000b
     
     ; We can now put together the whole result
     push ax
     push bx
     pop eax ; We obtain the result in eax: eax = 1111010101110000 1111010101110000b
     
     mov  [b], eax ; We move the result from the register to the result variable
     ; b = 1111010101110000 1111010101110000b

     push dword 0 ;saves on stack the parameter of the function exit
     call [exit] ;function exit is called in order to end the execution of the program	
