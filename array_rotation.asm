INCLUDE Irvine32.inc
.data
	arr word 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 ;declare and initialize word array of size 10
	len = LENGTHOF arr         ;declare and initialize symbolic constant with length of array (10)
	msg1 BYTE "Array before rotation:  ",0 ;declaring/initializing string constants
	msg2 BYTE "Array  after rotation:  ",0
	space BYTE "  ",0

.code
main PROC
	; Print the original array
	mov edx, OFFSET msg1       ;storing msg1 in edx
	call WriteString           ;printing msg1
	
	mov ecx, len			   ;moving length of array into ecx for loop iteration
	mov esi, OFFSET arr        ;moving starting address of arr into esi (esi points to arr[0])

	A_loop:                    ;loop to print initial array
		mov ax, [esi]          ;moving arr[i] into ax
		call WriteDec          ;printing arr[i]
		mov edx, OFFSET space  ;moving space to edx
		call WriteString       ;printing space
		add esi, TYPE arr      ;adding 2 to offset the address to next element every time
	loop A_loop                ;end loop

	call Crlf                  ;printing newline
	call Crlf
	
	; Now perform the left rotation
	mov edx, OFFSET msg2       ;moving msg2 to edx					   
	call WriteString           ;printing msg2
	
	; Save the first element
	mov esi, OFFSET arr        ;point to first element
	mov ax, [esi]              ;save first element in ax
	
	; Rotate left: move each element one position to the left
	mov ecx, len               ;set up loop counter
	dec ecx                    ;we need to do len-1 iterations
	mov esi, OFFSET arr        ;point to first element
	
	rotate_loop:
		mov bx, [esi + TYPE arr]  ;get next element
		mov [esi], bx             ;move it to current position
		add esi, TYPE arr         ;move to next position
	loop rotate_loop
	
	; Put the saved first element at the end
	mov [esi], ax              ;move first element to last position
	
	; Print the rotated array
	mov ecx, len               ;reset loop counter
	mov esi, OFFSET arr        ;point to first element

	B_loop:                    ;loop to print rotated array
		mov ax, [esi]          ;moving arr[i] into ax
		call WriteDec          ;printing arr[i]
		mov edx, OFFSET space  ;moving space to edx
		call WriteString       ;printing space
		add esi, TYPE arr      ;adding 2 to offset the address to next element every time
	loop B_loop                ;end loop

	call Crlf                  ;newline

exit
main endp
end main