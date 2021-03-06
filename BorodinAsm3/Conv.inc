;
; ���������, �������������� ������� ����������� ������ � ���������� �������� �����
; 
; ����:
;	DS:ESI - ����� ������
; �����:	
;	EAX - ��� ������ (2, 4)	
;
Convert proc
			xor		eax, eax				; �������� AX
			xor		edx, edx				; �������� DX
		
			call	SkipSpace				; ������� ��������
		
			mov		ebx, 1					; EBX = 1 ������������� �����
			call 	IsNegative
		
			call	CheckZero				; �������� �� '-0' � 0
			cmp		ebx, 2					; ���� -0, �� EBX == 2
			je		@@InvalidSymb			; ����� ������ ������ ������������� �������
		
			cmp		ebx, 3					; ���� ������ ������ '+0'
			je		@@Zero
		
			cmp		al, '0'					; �������� �� ������������ ������� �������
			jb		@@InvalidSymb			; �������� ��� ������ = 0-9
			cmp		al, '9'
			jg		@@InvalidSymb 
			
			cmp		al, '0'
			dec		esi
		
@@ExtractSymbol:
			mov		al, byte ptr ds:[esi]		; ����� ��������� ������

			jmp		@@IsStop				;  �������� �� ��������� ��������
			jmp		@@IsCorrect				; ��������, ��������� �� ��������� ������
@@Extract:		
			cmp		ebx, -1
			je		@@ExtractNeg
		
@@ExtractPos:
			sub		al, '0' 				; �������� �����
			imul	edx, 10
			jo		@@Overflow				;�������� �� ������������
			add		edx, eax
			jo		@@Overflow				;�������� �� ������������
			inc		esi
			jmp		@@ExtractSymbol

@@ExtractNeg:
			sub 	al, '0'
			imul	edx, 10
			jo		@@Overflow				;�������� �� ������������
			sub		edx, eax
			jo		@@Overflow
			inc		esi
			jmp		@@ExtractSymbol
		
@@StopExtract:
			mov		ebx, edx				; ��������� �������� � EBX
								
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
			mov		eax, 8000F001h						; ������������� ��� ������ = 4 - ������������
			jmp 	@@EndProc
		
@@IsCorrect:								; ��������, �� �� ��� ������ ����
			cmp		al, '0'						; ������ '0'-'9'
			jb		@@InvalidSymb				; ���� ���, �� ������������ ������
			cmp		al, '9'
			jg		@@InvalidSymb 
			jmp		@@Extract
		
@@InvalidSymb:		
			mov		eax, 8000F000h						; ��� ������ = 3 - ������������ ������
			jmp		@@EndProc
		
@@Zero:										; ��������� �������� - ������� ������ = '0'
			inc		esi
			mov		al, byte ptr ds:[esi]		; ����� ��������� ������
		
			mov		edx, 0						; �������� ������� �������� = 0
			cmp		al, ','						; �������� �� ������ ����� ����
			je		@@StopExtract				; -����, ������ ��������, �� �������, � EDX = 0
			cmp		al, ' '						; -����, ������ �� ��������, ������ ������������ �������
			je		@@StopExtract
			cmp		al, 10
			je		@@StopExtract
			cmp		al, 0
			je		@@StopExtract
			cmp		al, 13
			je		@@StopExtract
											;-����, ������ �� ��������, ������ ������������ �������
			jmp		@@InvalidSymb
	
@@EndProc:
			ret	
		
Convert endp 
