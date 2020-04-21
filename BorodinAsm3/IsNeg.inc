;
; Проверка числа на отрицательность
;
; Вход: AL - символ в начале числа
; Выход: EBX = -1 / 1 (отриц./полож.)
;
IsNegative proc
			cmp		al, '-'  ;сравниваем с минусом
			je 		@@Negative
			ret
			
@@Negative:
			mov		ebx, -1 ;помещаем -1
			lodsb			  ;берем следующий символ
			ret
		
IsNegative endp 
