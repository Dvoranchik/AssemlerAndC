.686
.MODEL FLAT, C
.STACK
.DATA
;-----------Local data------------------------------
.CODE
include SkipSp.inc
include IsNeg.inc
include CheckZ.inc
include Conv.inc
;
; Процедура, осуществляющая перевод содержимого строки в десятичное знаковое число
; 
; Вход:
;	DS:ESI - адрес строки
; Выход:	
;	EAX - код ошибки(2)
;
StrToInt  proc C cstr:dword, numptr:dword, last:dword
		push	edx
		push	ecx

		mov     esi, cstr
        mov		al, byte ptr ds:[esi]
		test	al, al					;Если это нулевой байт
		jz		@@EmptyStr
		
		call	Convert
		mov edx, numptr
		mov [edx], ebx
@@EndProc:
		pop		ecx
		pop		edx
		ret
		
@@EmptyStr:								; Ошибка = 2 - пустая строка
		mov		eax, 8000F002h
		jmp		@@EndProc
StrToInt endp
END