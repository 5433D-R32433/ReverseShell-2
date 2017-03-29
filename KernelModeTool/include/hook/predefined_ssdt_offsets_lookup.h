#pragma once

#include <ntddk.h>


typedef struct SystemVersion
{
    ULONG majorVersion;
    ULONG minorVersion;
} s_SystemVersion;

typedef struct VersionDependOffset
{
    s_SystemVersion version;
    ULONG offset;

} s_VersionDependOffset;

typedef struct SSTOffset
{
    wchar_t* name;
    s_VersionDependOffset* offsetArray;
    size_t offsetArraySize;

} s_SSTOffset;

#define QUERY_OFFSET_LEN 9
extern s_VersionDependOffset zwQueryDirSSTOffset[QUERY_OFFSET_LEN];

extern s_VersionDependOffset zwQuerySysInfoSSTOffset[QUERY_OFFSET_LEN];

extern s_SSTOffset           sstOffsetArray[2];

/**
  * Use this function to get an index of a function in SSDT using
  * predefined offsets.
  * @param[in] func_name - name of function to get the index of.
  * @param[in] func_name_len - length of func_name in words.
  * @return On success, matching index is returned.
  *         Otherwise, -1 is returned.
  */
LONG ssdt_index_predefined_offset(PUNICODE_STRING func_name);

/**
  * Use this function to get an offsets array for function name.
  * @param[in] func_name - name of function to get offsets array of.
  * @param[out] offsets_array - returned pointer offsets array.
  * @param[out] offsets_array_len - length of offsets_array.
  * @return On success, TRUE is returned.
  *         Otherwise, FALSE is returned.
  */
BOOL ssdt_offsets_array(PUNICODE_STRING func_name,
                        s_VersionDependOffset **offsets_array,
                        size_t *offsets_array_len);

/**
  * Use this function to get an index of a function in SSDT  that matches
  * a windows version using a predefined offsets array.
  * @param[in] offsets_array - offsets array to use.
  * @param[in] offsets_array_len - length of offsets_array.
  * @param[in] windows_version - windows version struct.
  * @return On success, matching index is returned.
  *         Otherwise, -1 is returned.
  */
LONG ssdt_offset_windows_version(s_VersionDependOffset *offsets_array,
                                 size_t offsets_array_len,
                                 RTL_OSVERSIONINFOW windows_version);
