#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <string>
#include <tlhelp32.h>
#include <random>
#include <ctime> 
#include <sstream>
#include "md5.hpp"

#define ����������� ZeroMemory
#define ���� main
#define ����� void
#define ������� std::cout
#define �������_����� std::endl;
#define ������ HANDLE
#define ���� decltype(auto)
#define ������� std::string
#define ��������_������� std::filesystem::current_path().string()
#define �������� std::filesystem::recursive_directory_iterator(���)
#define ������������ char*
#define ���� (������������)������.c_str();
#define ���������_���_����� �����.is_directory() || �����.path().extension() != ".dll"
#define ���� if
#define ��� for
#define ��� else
#define ����_�_�������� �����.path().string()
#define ������� system
#define �������_����� exit
#define ��� 10
#define ���_������_���� "pause"
#define ���� empty
#define ������� continue
#define ����� DWORD_PTR
#define ������������ bool
#define ��������_����� while
#define ����� Sleep
#define �_������� setlocale(LC_ALL, "Russian");
#define ������������32 PROCESSENTRY32
#define �������������32�������� CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
#define ���� sizeof
#define ���� dwSize
#define ������32��_������� Process32First
#define �������_���� OpenProcess(PROCESS_ALL_ACCESS, FALSE, �������.th32ProcessID)
#define ��32�_����_��_����� th32ProcessID
#define ��������_��� Process32Next
#define �������_��_228 CloseHandle
#define �������� szExeFile
#define �����_���� long
#define ������ LPVOID
#define �������_����� DWORD
#define ���������_������_�_������� (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary("kernel32"), "LoadLibraryA")
#define �����_������ LPTHREAD_START_ROUTINE
#define ����_�_���� VirtualAllocEx
#define ���� length
#define ��_������� c_str
#define ��������_����� WriteProcessMemory
#define ������_������ CreateRemoteThread(�������, NULL, 0, ����������������, ���������������, 0, &�����)
#define ������ return
#define ����� NULL
#define ��� int
#define ��� true
#define ����� false
#define �� do 
#define �������_����� break
#define �������_��_������ std::stringstream
#define ���_���� std::mt19937
#define ����_������� MAX_PATH
#define ������� seed
#define ����� time
#define ��� str
#define ������� GetModuleFileName
#define ����_����� md5
#define �����_������������ rename
#define ������� ERROR_INVALID_HANDLE
#define ��� MEM_COMMIT
#define ���_�_��� PAGE_EXECUTE_READWRITE
#define ���� TCHAR