Power	 	proc
		push 	eax
		push	ecx
		
		mov	eax, 1		;������� ���������� ���������� ����������
		
@@Loop:					 
		cmp	ecx, 1		;���� ��������� �������� ����� ���� �� ���� ECX ���,
		jna	@@EndProc	;�� �������.
					;����� ���������� ��������� ����� � �������,
		shl eax, 4		;������� �� 4 �������,
		dec	ecx		;� ����� �������� ���������� ���������� ��������� �����. 
		jmp	@@Loop		;��������� �� ��������� ��������
		
@@EndProc:
		mov	ebx, eax	;��������� ��������� ���������� � �������
		pop	ecx
		pop	eax
		ret
Power		endp