#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Asm.h"


extern "C" {
	HRESULT StrToInt(char* szStr, int* pi, char** pszNextChar = NULL);
}

void main()
{
	Test_16();
	Test_16776();
	Test_minus1();
	Test_____minus1();
	Test_132222222();
	Test_____22____();
	Test_minus____330____();
	Test_minus____33____();
	Test_InvalidArgs_null_arr();
	Test_Overflow();
	Test_BadSym1();
	Test_BadSym2();
}

void Test_16() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 16\n");
	char* str = "16";
	int* a = new int;
	int res = StrToInt(str, a);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_16776() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 16776\n");
	char* str = "16776";
	int* a = new int;
	int res = StrToInt(str, a);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");

}

void Test_minus1() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus1\n");
	char* str = "-1";
	int* a = new int;
	int res = StrToInt(str, a);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_____minus1() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test ___minus1\n");
	char* str = "    -1";
	int* a = new int;
	int res = StrToInt(str, a);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_132222222() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 1322222222\n");
	char* b;
	char* str = "132222222";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_____22____() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test ____22____\n");
	char* b;
	char* str = "    22    ";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_minus____330____() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus____330____\n");
	char* b;
	char* str = "    -330    ";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_minus____33____() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus____33____\n");
	char* b;
	char* str = "    -33    ";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	printf("%d", *a);
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_InvalidArgs_null_arr() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test InvalidArgs_null_arr\n");
	int* a = new int;
	int res = StrToInt("", a);
	if (res == E_EMPTYSTRING) {
		printf("Test complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}


void Test_Overflow() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test Overflow\n");
	char* b;
	char* str = "2147483648";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	if (res == E_OUTOFBOUND) {
		printf("Test complete\n");
	}
	else 
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}


void Test_BadSym1() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test BadSymbol1\n");
	char* b;
	char* str = "ab";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	if (res == E_BADFORMAT) {
		printf("Test complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_BadSym2() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test BadSymbol2\n");
	char* b;
	char* str = "--88";
	int* a = new int;
	char** ptr = &b;
	int res = StrToInt(str, a, ptr);
	if (res == E_BADFORMAT) {
		printf("Test complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}