.686

.MODEL FLAT, C

.STACK
.DATA

;-----------Local data------------------------------
Data DB 0h
.CODE
    include Power.inc
    include HexToC.inc
    

HexToStr proc ;C num:dword, arr:dword, n:dword, last:dword

        push ebp           ; ������: ���������� EBP
        mov ebp, esp       ; ������: ������������� EBP


        push    ebx
        push    ecx
        push    edx


        mov eax, [ebp+8]   ; ������ � ��������� 4
        mov edi, [ebp+12] ; ������ � ��������� 3
        mov ecx, [ebp+16] ; ������ � ��������� 2

       ; mov eax, num
       ; mov ecx, n
       ; mov edi, arr

        cmp     ecx, 8      ;???? ?????? ?????? ?????? 8,
        jb  @@BufferTooSmall

        cmp edi, 0
        je @@InvalidArgs
                    ;?? ??????? ?? ???????
        
        mov     ecx, 8      

@@ExctractHexLoop:
                    ;???? ????????????????? ?????????
                    ;???????? ?????, ??????? ?? ????????
        mov     ebx, 16 
        call    Power       ;???????? 16 ? ??????? ??????????? ???????
        
		mov	edx, 0		;� ����� �� ���� ���������� �����
		div	ebx		;EAX = �������(���������� ������)
					;EDX = �������(���������� ����� �����)

        call    HexToChar   ;????????? ?????????? ?????? ? ??????
        
        mov es:[edi], al    ;?????????? ??? ? ??????
        inc     edi     ;? ????????? ? ?????????? ??????? ? ??????

        mov     eax, edx    ;????? ????????? ?????????? ?????,

        loop    @@ExctractHexLoop   ;? ?????????? ????????? ?????

        push eax
        mov eax, [ebp+20]
        cmp eax, 0
        pop eax
        je @@EndLoop
        inc edi
        mov [ebp+20], edi
 

@@EndLoop:              ;????? ??? ??????
        mov eax, 0
        jmp @@EndProcHex
        
@@BufferTooSmall:           ;????? ? ??????? "????? ??????? ???"
        mov     eax, 8007000Eh
        jmp @@EndProcHex

@@InvalidArgs:
        mov     eax, 80070057h


        @@EndProcHex:
        pop     edx
        pop ecx
        pop ebx

        pop ebp
        ret

HexToStr endp
end 