HexToChar	proc
		push	dx

		cmp 	al, 9		;Если шестнадцатиричная цифра больше 9, 
		ja	@@Alpha		;то преобразование цифры в символ происходит по алгоритму,
					;написанному после метки @@Alpha
		
		mov	dl, '0'		;иначе получаем код символа
		add	dl, al		;смещением на al позиций относительно кода "0" 	
		jmp	@@EndProcChar
		
@@Alpha:
		mov	dl, 'A' - 10	;для шестнадцатиричных цифр A-F код символа можеть быть получен по
		add	dl, al		;формуле: код символа = 'A' - (Цифра - 10)
				
@@EndProcChar:	
		mov	al, dl
		pop	dx
		ret
HexToChar 	endp
