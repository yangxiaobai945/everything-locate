
// Everything IPC test
// this tests the lib and the dll.

#include <stdio.h>
#include <tchar.h>
// #include <windows.h>
#define EVERYTHINGUSERAPI
#include "Everything.h"

int _tmain(int argc, TCHAR **argv)
{
	// uw_enable_utf8();
	if (argc == 2)
	{
		Everything_SetSearchW(argv[1]);
		Everything_SetRequestFlags(EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE);
		Everything_SetSort(EVERYTHING_SORT_SIZE_DESCENDING);
		Everything_SetMax(9999);
		Everything_QueryW(TRUE);
		uint32_t mi = Everything_GetNumResults();
		// printf("Result List Request Flags %08x\n",Everything_GetResultListRequestFlags());
		for (uint32_t i = 0; i < mi; i++)
		{
			LARGE_INTEGER size;
			Everything_GetResultSize(i, &size);
			auto filename = Everything_GetResultFileNameW(i);
			auto path = Everything_GetResultPathW(i);
			printf("%S\\%S\n", path, filename);
		}
		Everything_CleanUp();
		return mi > 0 ? 0 : 1;
	}
	else
	{
		fprintf(stderr, "usage: locate <pattern>\n");
		return 1;
	}
}
