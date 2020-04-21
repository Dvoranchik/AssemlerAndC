.686
.MODEL FLAT, C
.STACK
.DATA
;-----------Local data------------------------------
.CODE
include DigLen.inc
	; ������� ����� � ��������� ������������� � ���������� ������ ��� � ; �����
	;
	; ����: 
	; 		EAX � ����� ��� �������� � ������
	;		
	;�����:
	;		EDX - 0 ��� 1 � ����������� �� �����
	;
IntToStr proc C num:dword, flag:dword, arr:dword, n:dword, last:dword
	mov eax, num
	mov ebx, flag
	mov edi, arr
	mov ecx, n
	push	ecx
@@signIs:
	push eax ;��������� �����
	shr eax, 31;�������� �������� �� 1�� ����
	cmp eax, 0; ��������� 1 ���
	jz @@plus;���� �������������
	pop eax;��������� �����
	neg eax;��������� �� ��������������
	mov edx, 1;���� �����
	jmp @@flag
@@plus:
	pop eax
	mov edx, 0
@@flag:
	push edx
	DigitLen ;���������� ����� �����
	cmp esi, 10
	ja @@invalid_arg
	cmp edi, 0
	jz @@invalid_arg
	;
	; � ����������� �� ���� ������������, ��������� 
	; ������ ������ ��� ������������� �����
	;
	; ����: 
	;	     BL = 0 / �� ���� (� ����������� �� ���� 
	; 		������������)
	;	     EAX � �������� ����� ��� �������� � ������
	;	     EDX = 0 / -1 (� ����������� �� ����� ����� � EAX) 
	; �����:
	;	     ESI � ����� ����� � ���� ������ � ������ �����
	;
@@len_checking:
	cmp     bl, 0   ;��������� ��� ������������
	jnz @@right_align   ;�� 0 - ������
	DigitLen ;���������� ����� �����
	cmp edx, 0
	jnz @@buffer_check
	dec esi
	add esi, ebx ; ���������� � esi �����
	jmp @@buffer_check
@@right_align:
	mov  esi, 11 ; ����������� ������ = 11
	;
	; ��������� ������������ ������� ������
	;
	; ����: 
	; 		ECX � ������ ������
	;		ESI � ����� ������������� ����� � ������ �����
	; �����:
	;		������ / �������� �����������
	;
@@buffer_check:
	push ebx
	mov ebx, 10d ;�������� ��� �����
	cmp ecx, esi ;��������� ���������� �� ����� 
	jb  @@error_message
	;
	; ������� ����� � ��������� ������������� � ���������� ������ ��� � ; �����
	;
	; ����: 
	; 		EAX � ����� ��� �������� � ������
	;		EDI � ����� ��� ������ �����
	;		ESI � ����� ������������� ����� � ������ �����
	; �����:
	;		EDI - ����� ��� ������ �����
	;
@@get_digits:
	xor     edx, edx    ;�������� edx
	div     ebx ;����� �� ����� �����
	or  dl, 30h     ; ������� � �����
	mov     es:[edi+esi], dl ;���������� �����
	dec     esi ;��������� ������� 
	cmp     eax, 0      ;���� ��������� �� � ������ ����� - �������
	jz  @@minus
	loop @@get_digits
@@minus:
	pop ebx;���������� edx
	pop edx;���������� ����
	cmp edx, 0
	jz @@spacing;���� �� �������������
	mov     al, 2Dh;���� �� ������ �����
	mov     es:[edi + esi], al
	dec     esi;��������� �������
	mov     al, 20h ; ���������� ������
@@spacing:
	cmp  esi, 0     ;��������� ������������ �� �����
	jb  @@GoodAndLoop ;������� ���� ��, �� �������
	mov     es:[edi + esi], al ;���������� � ������
	dec     esi ;��������� �������
	mov     al, 20h ; ���������� ������
	loop     @@spacing
@@GoodAndLoop:
	mov eax, 0
	jmp @@EndLoop
@@error_message:
	pop edx
	pop ebx
	mov eax, 8007000Eh;���� ������
	jmp @@EndLoop
@@invalid_arg:
	pop edx
	mov eax, 80070057h;���� ������
@@EndLoop:
	pop ecx
@@EndProc:
	ret
IntToStr endp
END