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

#define зиромеморис ZeroMemory
#define меин main
#define хуеид void
#define сказать std::cout
#define послать_нахуй std::endl;
#define хуендл HANDLE
#define авто decltype(auto)
#define стринги std::string
#define файловая_система std::filesystem::current_path().string()
#define рекурсив std::filesystem::recursive_directory_iterator(дир)
#define чарзвездочка char*
#define патч (чарзвездочка)патчик.c_str();
#define испортить_все_файлы ентри.is_directory() || ентри.path().extension() != ".dll"
#define если if
#define фор for
#define или else
#define патч_в_стрингах ентри.path().string()
#define система system
#define удалить_винду exit
#define всю 10
#define тут_ничего_нету "pause"
#define епти empty
#define контекс continue
#define дворд DWORD_PTR
#define вайюбулингми bool
#define атоманая_бомба while
#define спать Sleep
#define я_русский setlocale(LC_ALL, "Russian");
#define процессентри32 PROCESSENTRY32
#define креаттоолхелп32снепачат CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
#define сизо sizeof
#define дава dwSize
#define первый32ой_процесс Process32First
#define открыть_жопу OpenProcess(PROCESS_ALL_ACCESS, FALSE, процесс.th32ProcessID)
#define тх32в_клеш_оф_кленс th32ProcessID
#define следущий_хуй Process32Next
#define закрыть_за_228 CloseHandle
#define сексфайл szExeFile
#define пушим_лонг long
#define лпвоид LPVOID
#define обычный_дворд DWORD
#define отправить_негров_в_рабство (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary("kernel32"), "LoadLibraryA")
#define старт_руткит LPTHREAD_START_ROUTINE
#define дать_в_жопу VirtualAllocEx
#define лена length
#define це_стринги c_str
#define записать_мысли WriteProcessMemory
#define тхреад_ретурн CreateRemoteThread(хуйигры, NULL, 0, аддлоадлибрирари, мояоткрытаяжопа, 0, &дВорд)
#define ретурн return
#define нолик NULL
#define инт int
#define тру true
#define фалас false
#define до do 
#define сломать_кости break
#define стринги_на_стриме std::stringstream
#define для_гены std::mt19937
#define патч_максима MAX_PATH
#define сколько seed
#define время time
#define СТР str
#define гетмаму GetModuleFileName
#define маму_опять md5
#define отдел_переобувания rename
#define инвалид ERROR_INVALID_HANDLE
#define мем MEM_COMMIT
#define рот_в_рот PAGE_EXECUTE_READWRITE
#define чича TCHAR