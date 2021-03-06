#include "stdafx.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <concrt.h>
#include <ppl.h>

class employee
{
	char name_[128];
	unsigned id_;
public:
	employee(char const* name, unsigned id) : id_(id)
	{
		strcpy_s(name_, name);
	}
};

void process_employees()
{
	try {
		auto emp = new employee("David", 123);
		auto emp1 = new employee("David2", 123);
		delete emp1;
		auto p = HeapAlloc(GetProcessHeap(), 0, 100);
		p = HeapReAlloc(GetProcessHeap(), 0, p, 200);
	}
	catch (...) {
		printf("Employee creation failed.\n");
	}
}

DWORD WINAPI Thread(LPVOID)
{
	while (true)
	{
		Sleep(1000);
		process_employees();
	}
	return 0;
}

int main()
{
	for (int i = 0; i < 4; ++i)
	{
		CreateThread(nullptr, 0, Thread, nullptr, 0, nullptr);
	}
	Sleep(INFINITE);
	return 0;
}
