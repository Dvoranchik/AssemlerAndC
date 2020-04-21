;
; Процедура, осуществляющая перевод содержимого строки в десятичное знаковое число
; 
; Вход:
;	DS:ESI - адрес строки
; Выход:	
;	EAX - код ошибки (2, 4)	
;
Convert proc
			xor		eax, eax				; Обнуляем AX
			xor		edx, edx				; Обнуляем DX
		
			call	SkipSpace				; Пропуск пробелов
		
			mov		ebx, 1					; EBX = 1 Положительное число
			call 	IsNegative
		
			call	CheckZero				; Проверка на '-0' и 0
			cmp		ebx, 2					; если -0, то EBX == 2
			je		@@InvalidSymb			; Тогда выдаем ошибку некорректного символа
		
			cmp		ebx, 3					; Если первый разряд '+0'
			je		@@Zero
		
			cmp		al, '0'					; Проверка на корректность первого символа
			jb		@@InvalidSymb			; Проверка что символ = 0-9
			cmp		al, '9'
			jg		@@InvalidSymb 
			
			cmp		al, '0'
			dec		esi
		
@@ExtractSymbol:
			mov		al, byte ptr ds:[esi]		; Берем очередной символ

			jmp		@@IsStop				;  Проверка на остановку подсчету
			jmp		@@IsCorrect				; Проверка, корректен ли очередной символ
@@Extract:		
			cmp		ebx, -1
			je		@@ExtractNeg
		
@@ExtractPos:
			sub		al, '0' 				; Получаем число
			imul	edx, 10
			jo		@@Overflow				;проверка не переполнение
			add		edx, eax
			jo		@@Overflow				;проверка не переполнение
			inc		esi
			jmp		@@ExtractSymbol

@@ExtractNeg:
			sub 	al, '0'
			imul	edx, 10
			jo		@@Overflow				;проверка не переполнение
			sub		edx, eax
			jo		@@Overflow
			inc		esi
			jmp		@@ExtractSymbol
		
@@StopExtract:
			mov		ebx, edx				; Сохраняем значение в EBX
								
			mov		eax, 0
			jmp		@@EndProc

@@IsStop:
			cmp		al, ','
			je		@@StopExtract
			cmp		al, ' '
			je		@@StopExtract
			cmp		al, 10			;\n
			je		@@StopExtract
			cmp		al, 0			; \0
			je		@@StopExtract	
			cmp		al, 13			; \r
			je		@@StopExtract
			jmp		@@Extract

@@Overflow:
			mov		eax, 8000F001h						; Устанавливаем код ошибки = 4 - переполнение
			jmp 	@@EndProc
		
@@IsCorrect:								; Проверка, на то что символ есть
			cmp		al, '0'						; символ '0'-'9'
			jb		@@InvalidSymb				; Если нет, то некорректный символ
			cmp		al, '9'
			jg		@@InvalidSymb 
			jmp		@@Extract
		
@@InvalidSymb:		
			mov		eax, 8000F000h						; Код ошибки = 3 - Некорректный символ
			jmp		@@EndProc
		
@@Zero:										; Обработка ситуации - старший разряд = '0'
			inc		esi
			mov		al, byte ptr ds:[esi]		; Берем очередной символ
		
			mov		edx, 0						; Помещаем текущее значение = 0
			cmp		al, ','						; Проверка на символ после нуля
			je		@@StopExtract				; -если, символ Останова, то выходим, с EDX = 0
			cmp		al, ' '						; -если, символ не останова, ошибка Корректности символа
			je		@@StopExtract
			cmp		al, 10
			je		@@StopExtract
			cmp		al, 0
			je		@@StopExtract
			cmp		al, 13
			je		@@StopExtract
											;-если, символ не останова, ошибка Корректности символа
			jmp		@@InvalidSymb
	
@@EndProc:
			ret	
		
Convert endp 
