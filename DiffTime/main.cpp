#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <locale.h>

int main()
{
	{
		char szFileName[MAX_PATH] = { "C:\\file\\path\\file.txt"};
		DWORD attr = GetFileAttributes(szFileName);

		HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, 0, OPEN_ALWAYS,
			(attr & FILE_ATTRIBUTE_DIRECTORY) ? FILE_FLAG_BACKUP_SEMANTICS : FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE) {
			return 0;
		}

		FILETIME CreationTime;
		FILETIME AccessTime;
		FILETIME WriteTime;
		FILETIME localTime;
		SYSTEMTIME systemTime;

		// 現在のファイルの日時を取得表示
		GetFileTime(hFile, &CreationTime, &AccessTime, &WriteTime);

		// UTC→ローカルタイム
		FileTimeToLocalFileTime(&CreationTime, &localTime);
		// FILETIMEをSYSTEMTIMEに変換
		FileTimeToSystemTime(&localTime, &systemTime);
		printf("作成時間 : ");
		printf_s("%i/%0.2i/%0.2i %0.2i:%0.2i:%0.2i\n", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);

		// UTC→ローカルタイム
		FileTimeToLocalFileTime(&AccessTime, &localTime);
		// FILETIMEをSYSTEMTIMEに変換
		FileTimeToSystemTime(&localTime, &systemTime);
		printf("アクセス時間 : ");
		printf_s("%i/%0.2i/%0.2i %0.2i:%0.2i:%0.2i\n", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);

		// UTC→ローカルタイム
		FileTimeToLocalFileTime(&WriteTime, &localTime);
		// FILETIMEをSYSTEMTIMEに変換
		FileTimeToSystemTime(&localTime, &systemTime);
		printf("書き込み時間 : ");
		printf_s("%i/%0.2i/%0.2i %0.2i:%0.2i:%0.2i\n", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);

		CloseHandle(hFile);

		SYSTEMTIME nowSysTime;
		FILETIME nowFileTime;
		GetSystemTime(&nowSysTime);
		SystemTimeToFileTime(&nowSysTime, &nowFileTime);

		// int64にキャスト
		__int64* nTime1 = (__int64*)&CreationTime;
		__int64* nTime2 = (__int64*)&nowFileTime;

		// 経過秒
		__int64 nDiffSec = (*nTime2 - *nTime1) / 10000 / 1000;

		// 経過分
		__int64 nDiffMinute = nDiffSec / 60;

		// 経過時間
		__int64 nDiffHour = nDiffSec / 60 / 60;

		// 経過日数
		__int64 nDiffDay = nDiffSec / 60 / 60 / 24;
	}

	{
		// ファイル検索
		char szFileName[MAX_PATH] = { "D:\\src\\CPP\\TestTime\\*" };
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;
		hFind = FindFirstFile(szFileName, &win32fd);
		if (hFind == INVALID_HANDLE_VALUE) {
			return 0;
		}

		do {
			if ((win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
				printf_s("%s\n", win32fd.cFileName);
			}
		} while (FindNextFile(hFind, &win32fd));

		FindClose(hFind);
	}

	return 0;
}
