bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global create_positive_number_string       

segment data use32 class=data

; our code starts here
segment code use32 class=code
    create_positive_number_string:
    
    ; The process is similar to computing negative numbers in the main module
    
        mov esi, [esp+8] ; We take the values from the stack - this one is the address for the label "text"
        mov edi, [esp+4] ; - this one is the address for the label "positive"
        mov ax, 0        ; The initial values are the same
        mov cl, 0
        
        do_positive_numbers:
            mov bl, [esi]
            inc esi
            
            ; We compare the current byte to the space character, "-" or do the things we want to do if it is a digit
            
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
                
        ret 8
