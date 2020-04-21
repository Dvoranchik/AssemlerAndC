#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Asm.h"


extern "C" {
	HRESULT IntToStr(int a, bool bAlignLeft, char* szBuffer, unsigned int cBufLen, char** pszNextChar = NULL);
}

void main()
{
	Test_16Right();
	Test_16Left();
	Test_minus1Right();
	Test_minus1Left();
	Test_1322222222Right();
	Test_1322222222Left();
	Test_minus_1322222222Left();
	Test_minus_1322222222Right();
	Test_InvalidArgs_null_arr();
	Test_SmallBuffer();
}

void Test_16Right() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 16_RIGHT\n");
	char* cBUf = new char[12]{ 0 };
	int res = IntToStr(16, 1, cBUf, 12);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_16Left() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 16_LEFT\n");
	char* cBUf = new char[12]{ 0 };
	int res = IntToStr(16, 0, cBUf, 12);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");

}

void Test_minus1Right() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus1_RIGHT\n");
	char* cBUf = new char[12]{ 0 };
	int res = IntToStr(-1, 2, cBUf, 12);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_minus1Left() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus1_LEFT\n");
	char* cBUf = new char[12]{ 0 };
	int res = IntToStr(-1, 0, cBUf, 12);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_1322222222Right() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 1322222222_Right\n");
	char* a;
	char* cBUf = new char[12]{ 0 };
	char** ptr = &a;
	int res = IntToStr(1322222222, 1, cBUf, 12, ptr);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_1322222222Left() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test 1322222222_Left\n");
	char* a;
	char* cBUf = new char[12]{ 0 };
	char** ptr = &a;
	int res = IntToStr(1322222222, 0, cBUf, 12, ptr);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_minus_1322222222Left() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus_1322222222_Left\n");
	char* a;
	char* cBUf = new char[12]{ 0 };
	char** ptr = &a;
	int res = IntToStr(-1322222222, 0, cBUf, 12, ptr);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
	if (res == S_OK) {
		printf("\nTest complete\n");
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}

void Test_minus_1322222222Right() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test minus_1322222222_Right\n");
	char* a;
	char* cBUf = new char[12]{ 0 };
	char** ptr = &a;
	int res = IntToStr(-1322222222, 1, cBUf, 12, ptr);
	for (int i = 0; i < 12; i++)
	{
		printf("%c", cBUf[i]);
	}
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
	int res = IntToStr(1322222222, 2, NULL, 12);
	if (res == E_INVALIDARG) {
		printf("Test complete\n");
		
	}
	else
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}


void Test_SmallBuffer() {
	printf("\n<------------------------TEST------------------------>\n");
	printf("The Test SmallBuffer\n");
	char* a;
	char* cBUf = new char[6]{ 0 };
	char** ptr = &a;
	int res = IntToStr(1322222222, 2, cBUf, 6, ptr);
	if (res == E_OUTOFMEMORY) {
		printf("Test complete\n");
		
	}
	else 
		printf("\nError\n");
	printf("<-------------------------END------------------------->\n");
}
