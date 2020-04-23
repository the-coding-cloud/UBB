	; Write a program in the assembly language that computes the following arithmetic expression, considering the following data types for the variables:
; a - byte, b - word
; (b / a * 2 + 10) * b - b * 15;
; ex. 1: a = 10; b = 40; Result: (40 / 10 * 2 + 10) * 40 - 40 * 15 = 18 * 40 - 1600 = 720 - 600 = 120
; ex. 2: a = 100; b = 50; Result: (50 / 100 * 2 + 10) * 50 - 50 * 15 = 12 * 50 - 750 = 600 - 750 = - 150
bits 32 ;assembling for the 32 bits architecture
; the start label will be the entry point in the program
global  start 

extern  exit ; we inform the assembler that the exit symbol is foreign, i.e. it exists even if we won't be defining it

import  exit msvcrt.dll; exit is a function that ends the process, it is defined in msvcrt.dll
        ; msvcrt.dll contains exit, printf and all the other important C-runtime functions
segment  data use32 class=data ; the data segment where the variables are declared 
	a  db 10
	b  dw 40
segment  code use32 class=code ; code segment
start: 
	mov  AX, [b] ;AX = b
	div  BYTE [a] ;AL = AX / a = b / a and AH = AX % a = b % a
	
	mov  AH, 2 ;AH = 2
	mul  AH ;AX = AL * AH = b / a * 2	
	
	add  AX, 10 ;AX = AX + b = b / a * 2 + 10
	
	mul  word [b] ;DX:AX = AX * b = (b / a * 2 + 10) * b
	
	push  DX ;the high part of the doubleword DX:AX is saved on the stack
	push  AX ;the low part of the doubleword DX:AX is saved on the stack
	pop  EBX ;EBX = DX:AX = (b / a * 2 + 10) * b
	
	mov  AX, [b] ;AX = b
	mov  DX, 15 ;DX = 15
	mul  DX ;DX:AX = b * 15
	
	push  DX ;the high part of the doubleword DX:AX is saved on the stack
	push  AX ;the low part of the doubleword DX:AX is saved on the stack
	pop  EAX ;EAX = DX:AX = b * 15
	
	sub  EBX, EAX ;EBX = EBX - EAX = (b / a * 2 + 10) * b - b * 15
	
	push   dword 0 ;saves on stack the parameter of the function exit
	call   [exit] ; function exit is called in order to end the execution of the program