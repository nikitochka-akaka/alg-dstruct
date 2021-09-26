#pragma once

struct List
{
    struct List* Next;
    char* Data;
};

typedef struct List StringList;

/// StringListConcat — concatenate strings from list
///
/// \param stringList — pointer to first element of list
/// \return             pointer to concatenated string
char* StringListConcat(StringList* stringList);
