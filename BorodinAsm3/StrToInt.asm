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
; ���������, �������������� ������� ����������� ������ � ���������� �������� �����
; 
; ����:
;	DS:ESI - ����� ������
; �����:	
;	EAX - ��� ������(2)
;
StrToInt  proc C cstr:dword, numptr:dword, last:dword
		push	edx
		push	ecx

		mov     esi, cstr
        mov		al, byte ptr ds:[esi]
		test	al, al					;���� ��� ������� ����
		jz		@@EmptyStr
		
		call	Convert
		mov edx, numptr
		mov [edx], ebx
@@EndProc:
		pop		ecx
		pop		edx
		ret
		
@@EmptyStr:								; ������ = 2 - ������ ������
		mov		eax, 8000F002h
		jmp		@@EndProc
StrToInt endp
END