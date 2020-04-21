.686
.MODEL FLAT, C
.STACK
.DATA
;-----------Local data------------------------------
.CODE
include DigLen.inc
	; Перевод числа в строковое представление и дальнейшая запись его в ; буфер
	;
	; Вход: 
	; 		EAX – число для перевода в строку
	;		
	;Выход:
	;		EDX - 0 или 1 в зависимости от знака
	;
IntToStr proc C num:dword, flag:dword, arr:dword, n:dword, last:dword
	mov eax, num
	mov ebx, flag
	mov edi, arr
	mov ecx, n
	push	ecx
@@signIs:
	push eax ;сохраняем число
	shr eax, 31;побитово сдвигаем до 1го бита
	cmp eax, 0; проверяем 1 бит
	jz @@plus;если положительное
	pop eax;возращаем число
	neg eax;переводим из отрицательного
	mov edx, 1;флаг знака
	jmp @@flag
@@plus:
	pop eax
	mov edx, 0
@@flag:
	push edx
	DigitLen ;определяем длину числа
	cmp esi, 10
	ja @@invalid_arg
	cmp edi, 0
	jz @@invalid_arg
	;
	; В зависимости от типа выравнивания, вычисляет 
	; размер буфера для записываемого числа
	;
	; Вход: 
	;	     BL = 0 / не ноль (В зависимости от типа 
	; 		выравнивания)
	;	     EAX – исходное число для перевода в строку
	;	     EDX = 0 / -1 (В зависимости от знака числа в EAX) 
	; Выход:
	;	     ESI – длина числа в виде строки с учетом знака
	;
@@len_checking:
	cmp     bl, 0   ;проверяем тип выравнивания
	jnz @@right_align   ;не 0 - правое
	DigitLen ;определяем длину числа
	cmp edx, 0
	jnz @@buffer_check
	dec esi
	add esi, ebx ; записываем в esi длину
	jmp @@buffer_check
@@right_align:
	mov  esi, 11 ; необходимый размер = 11
	;
	; Проверяет корректность размера буфера
	;
	; Вход: 
	; 		ECX – размер буфера
	;		ESI – длина записываемого числа с учетом знака
	; Выход:
	;		Ошибка / успешное продолжение
	;
@@buffer_check:
	push ebx
	mov ebx, 10d ;делитель для числа
	cmp ecx, esi ;проверяем достаточно ли места 
	jb  @@error_message
	;
	; Перевод числа в строковое представление и дальнейшая запись его в ; буфер
	;
	; Вход: 
	; 		EAX – число для перевода в строку
	;		EDI – буфер для записи числа
	;		ESI – длина записываемого числа с учетом знака
	; Выход:
	;		EDI - буфер для записи числа
	;
@@get_digits:
	xor     edx, edx    ;обнуляем edx
	div     ebx ;делим на длину слова
	or  dl, 30h     ; остаток в букву
	mov     es:[edi+esi], dl ;записываем букву
	dec     esi ;уменьщаем счетчик 
	cmp     eax, 0      ;если закончили то в пустые места - пробелы
	jz  @@minus
	loop @@get_digits
@@minus:
	pop ebx;возвращаем edx
	pop edx;возвращаем флаг
	cmp edx, 0
	jz @@spacing;если не отрицательное
	mov     al, 2Dh;если да ставим минус
	mov     es:[edi + esi], al
	dec     esi;уменьщаем счетчик
	mov     al, 20h ; записываем пробел
@@spacing:
	cmp  esi, 0     ;проверяем отрицательно ли число
	jb  @@GoodAndLoop ;переход если да, то выходим
	mov     es:[edi + esi], al ;записываем в строку
	dec     esi ;уменьшаем счетчик
	mov     al, 20h ; записываем пробел
	loop     @@spacing
@@GoodAndLoop:
	mov eax, 0
	jmp @@EndLoop
@@error_message:
	pop edx
	pop ebx
	mov eax, 8007000Eh;флаг ошибки
	jmp @@EndLoop
@@invalid_arg:
	pop edx
	mov eax, 80070057h;флаг ошибки
@@EndLoop:
	pop ecx
@@EndProc:
	ret
IntToStr endp
END