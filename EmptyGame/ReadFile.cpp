#include <iostream>
#include <windows.h>
#include <stdio.h>

//之前以为fopen是将文件全部加载进内存后再操作，实践之后发现不是这样，它可以一点点向后读取，但是要是太大，直接就seek到文件结尾，还是会异常、崩溃，这时候使用虚拟内存映射来处理：

void createBigFile(int NumberGB = 0)
{
	FILE * p = fopen("d:\\test.dat", "w+");
	for (int i = 0; i < NumberGB; i++)
	{
		fwrite("1\n", 2, 1, p);
	}
	fclose(p);
	p = NULL;
}
void CountBigFile0()
{
	FILE * p = fopen("test.dat", "r");
	__int64 len = 0;
	char a[2] = { 0 };
	for (int i = 0; i < 2992742400; i++)
	{
		fseek(p, i * 1024, SEEK_SET);
		fread(a, 2, 1, p);
		if (a[0] != '1')
			break;
		len = i * 1024;
	}
	printf("%s  %d\n", a, len);
	fclose(p);
	p = NULL;
}
__int64 CountBigFile1(void)
{
	__int64 count = 0;
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	HANDLE hFile = CreateFile(TEXT("d:\\test.dat"), FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return 0;
	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE | SEC_COMMIT, 0, 0, NULL);
	DWORD dwFileHigh;
	__int64 qwFileSize = GetFileSize(hFile, &dwFileHigh);
	qwFileSize += (((__int64)dwFileHigh) << 32);
	CloseHandle(hFile);
	__int64 qwFileOffset = 0;

	while (qwFileSize > 0)
	{
		DWORD dwBytesInblock = sys.dwAllocationGranularity;

		if (qwFileSize < dwBytesInblock)
			dwBytesInblock = qwFileSize;

		PBYTE pbFile = (PBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE | FILE_MAP_READ, (DWORD)qwFileOffset >> 32, (DWORD)(qwFileOffset & 0xffffffff), dwBytesInblock);

		memcpy(pbFile, "12345\n", 6);
		//for(int i = 0 ; i < dwBytesInblock ; i ++)  
		//{  
		//  //doing  
		//  count ++;//记录行数  
		//}  

		//BOOL bRet = ::FlushViewOfFile(pbFile, dwBytesInblock);  
		//if ( bRet == FALSE )  
		//{  
		//  DWORD dwError = GetLastError();  
		//  return FALSE;  
		//}  
		//UnmapViewOfFile(pbFile);  

		qwFileOffset += dwBytesInblock;
		qwFileSize -= dwBytesInblock;
	}
	printf("count = %I64d\n", qwFileSize);
	CloseHandle(hFileMapping); return count;
}