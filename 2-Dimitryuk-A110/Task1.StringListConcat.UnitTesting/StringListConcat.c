#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "StringListConcat.h"

char* StringListConcat(StringList* stringList)
{
    if (stringList == NULL)
    {
        fprintf(stderr, "An error occurred: Argument null pointer exception\n");
        return NULL;
    }

    size_t _stringLen = 0;
    char* _resultStr = NULL;
    StringList* _listPtr = stringList;

    while (_listPtr != NULL)
    {
        if (_listPtr->Data != NULL)
        {
            _stringLen += strlen(_listPtr->Data);
        }

        _listPtr = _listPtr->Next;
    }

    if (_stringLen == 0)
    {
        fprintf(stderr, "An error occurred: All strings in list are empty\n");
        return NULL;
    }

    _resultStr = (char*)calloc(_stringLen + 1, sizeof(char));
    if (_resultStr == NULL)
    {
        fprintf(stderr, "An error occurred: Failed to allocate memory for concatenated string\n");
        return NULL;
    }

    _listPtr = stringList;
    while (_listPtr != NULL)
    {
        if (_listPtr->Data != NULL)
        {
            strcat(_resultStr, _listPtr->Data);
        }

        _listPtr = _listPtr->Next;
    }

    return _resultStr;
}
