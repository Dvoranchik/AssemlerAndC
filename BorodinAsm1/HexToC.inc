HexToChar	proc
		push	dx

		cmp 	al, 9		;���� ����������������� ����� ������ 9, 
		ja	@@Alpha		;�� �������������� ����� � ������ ���������� �� ���������,
					;����������� ����� ����� @@Alpha
		
		mov	dl, '0'		;����� �������� ��� �������
		add	dl, al		;��������� �� al ������� ������������ ���� "0" 	
		jmp	@@EndProcChar
		
@@Alpha:
		mov	dl, 'A' - 10	;��� ����������������� ���� A-F ��� ������� ������ ���� ������� ��
		add	dl, al		;�������: ��� ������� = 'A' - (����� - 10)
				
@@EndProcChar:	
		mov	al, dl
		pop	dx
		ret
HexToChar 	endp
