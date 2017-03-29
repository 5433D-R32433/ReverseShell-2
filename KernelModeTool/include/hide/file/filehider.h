#pragma once

#include <ntddk.h>


/* NtQueryDirectoryFile function type */
typedef NTSTATUS (*NtQueryDirectoryFile_t)(
    IN HANDLE FileHandle,
    IN HANDLE Event OPTIONAL,
    IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
    IN PVOID ApcContext OPTIONAL,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    OUT PVOID FileInformation,
    IN ULONG FileInformationLength,
    IN FILE_INFORMATION_CLASS FileInformationClass,
    IN BOOLEAN ReturnSingleEntry,
    IN PUNICODE_STRING FileName OPTIONAL,
    IN BOOLEAN RestartScan
);

/*
    Function
*/
int filehider_init();

/*
    Function
*/
int filehider_deinit();

/*
    Function
*/
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
                            IN BOOLEAN RestartScan);
