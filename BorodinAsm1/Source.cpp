#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Asm.h"


extern "C"
{
	void sayHello();
}

extern "C" {
	HRESULT HexToStr(unsigned int a, char* szBuffer, unsigned int cBufLen, char** pszNextChar = NULL);
}

void main()
{
	Test_16();
	Test_20657();
	Test_InvalidArgs();
	Test_minus1();
	Test_SmallBuffer();
}

void Test_16() {
	printf("The Test 16\n");
	char* cBUf = new char[8];
	int res = HexToStr(16, cBUf, 15);
	for (int i = 0; i < 8; i++)
	{
		printf("%c", cBUf[i]);
	}
	delete[] cBUf;
	if (res == S_OK) {
		printf("\nTest complete\n\n");
		return;
	}
	printf("\nError\n");
	
}

void Test_minus1() {
	printf("The Test minus1\n");
	char* a;
	char* cBUf = new char[8];
	char** ptr = &a;
	int res = HexToStr(-1, cBUf, 8, ptr);
	for (int i = 0; i < 8; i++)
	{
		printf("%c", cBUf[i]);
	}
	delete[] cBUf;
	if (res == S_OK) {
		printf("\nTest complete\n\n");
		return;
	}
	printf("Error\n");
}

void Test_20657() {
	printf("The Test 20657\n");
	char* a;
	char* cBUf = new char[8];
	char** ptr = &a;
	int res = HexToStr(14, cBUf, 8, ptr);
	for (int i = 0; i < 8; i++)
	{
		printf("%c", cBUf[i]);
	}
	delete[] cBUf;
	if (res == S_OK) {
		printf("\nTest complete\n\n");
		return;
	}
	printf("Error\n");
}

void Test_InvalidArgs() {
	printf("The Test InvalidArgs\n");
	int res = HexToStr(14, NULL, 8);
	if (res == E_INVALIDARG) {
		printf("Test complete\n\n");
		return;
	}
	printf("Error\n");
}

void Test_SmallBuffer() {
	printf("The Test SmallBuffer\n");
	char* a;
	char* cBUf = new char[8];
	char** ptr = &a;
	int res = HexToStr(20657, cBUf, 5, ptr);
	for (int i = 0; i < 8; i++)
	{
		printf("%c", cBUf[i]);
	}
	delete[] cBUf;
	if (res == E_OUTOFMEMORY) {
		printf("\nTest complete\n\n");
		return;
	}
	printf("\nError\n");
}


extern "C"
void* readName()
{
	char* name = (char*)calloc(1, 255);
	scanf("%s", name);
	while (getchar() != '\n');
	return name;
}