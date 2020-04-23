bits 32
global _MergeStrings

segment data public data use32
	sir3 dd 0		; We will compute our string here

segment code public code use32


_MergeStrings:

push ebp
mov ebp, esp

pushad    ; At the end of the assembly "function", we need to leave the registers unchanged

	; This is the first part of the merge - we place the characters from the first source string in the destination string, leaving an "empty" byte between them
		mov ecx,[ebp+8]   ; This is the length of the first string
		mov esi,[ebp+12]  ; This is the address of the first string
		mov edi, sir3	  ; This is the address of the destination string
		
		repeat1:
			movsb		; We move the current byte from the source string to the destination string and both esi and edi are incremented
			inc edi		; Now we leave the "empty place"
			loop repeat1

	; This is the second part of the merge - we do the same with the remaining characters
		mov ecx, [ebp+16] ; This is the length of the second string
		mov esi, [ebp+20] ; This is the address of the second string
		mov edi, sir3	  ; This is the address of the destination string
		inc edi			  ; Now we start doing the same thing, but from the odd position
		
		repeat2:
			movsb		; We move the current byte from the source string to the destination string and both esi and edi are incremented
			inc edi		; Now we skype the already-filled byte
			loop repeat2

popad	  ; We did all we needed to do and now we should restore the registers so that nothing bad happens to our program

mov eax, sir3  ; This is how we return the address of our string to the caller program

mov esp, ebp
pop ebp

ret