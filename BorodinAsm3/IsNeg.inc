;
; �������� ����� �� ���������������
;
; ����: AL - ������ � ������ �����
; �����: EBX = -1 / 1 (�����./�����.)
;
IsNegative proc
			cmp		al, '-'  ;���������� � �������
			je 		@@Negative
			ret
			
@@Negative:
			mov		ebx, -1 ;�������� -1
			lodsb			  ;����� ��������� ������
			ret
		
IsNegative endp 
