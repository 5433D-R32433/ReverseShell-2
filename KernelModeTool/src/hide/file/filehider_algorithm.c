#include <ntddk.h>

#include "hide/file/filehider_algorithm.h"

s_FileHideEntry files_to_hide[] = {
    { 7, L"my_file" },
    { 9, L"my_folder" }
};

int is_in_files_to_hide(WCHAR *name, ULONG name_len)
{
    size_t len;

    for( size_t i = 0; i < sizeof(files_to_hide) / sizeof(files_to_hide[0]); ++i )
    {
        len = min(files_to_hide[i].file_name_len, name_len);

        if ( 0 == wcsncmp(name, files_to_hide[i].file_name, len) )
            return ( 1 );
    }

    return ( 0 );
}
