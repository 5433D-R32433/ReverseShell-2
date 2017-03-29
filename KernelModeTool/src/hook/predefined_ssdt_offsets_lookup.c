#include "hook/predefined_ssdt_offsets_lookup.h"


/**
  * This array matches a Windows version to a zwQueryDirectoryFile offset in SST
  * Offset 0 means offset unknown
  */
s_VersionDependOffset zwQueryDirSSTOffset[QUERY_OFFSET_LEN] =
{
    {{5,0},     0x7D}, // 2k
    {{5,1},     0x91}, // XP
    {{5,2},     0x97}, // 2k3
    {{6,0},     0xDA}, // Vista,2k8
    {{6,1},     0xE0},  // Win7
    {{6,2},     0}, // Server 2012
    {{6,2},     0}, // 8
    {{6,3},     0xbe}, // 8.1, Server 2012 R2
    {{10, 0},   0}, // 10, Server 2016
};

/**
  * This array matches a Windows version to a zwQuerySysInformation offset in SST
  * Offset 0 means offset unknown
  */
s_VersionDependOffset zwQuerySysInfoSSTOffset[QUERY_OFFSET_LEN] =
{
    {{5,0},     0x97}, // 2000
    {{5,1},     0xAD}, // XP
    {{5,2},     0xB5}, // XP 64b, Server 2003
    {{6,0},     0xF8}, // Vista, Server 2008
    {{6,1},     0x106}, // Win7
    {{6,2},     0}, // Server 2012
    {{6,2},     0}, // 8
    {{6,3},     0x98}, // 8.1, Server 2012 R2
    {{10, 0},   0}, // 10, Server 2016
};

struct SSTOffset sstOffsetArray[2] =
{
    {
        L"ZwQueryDirectoryFile",
        zwQueryDirSSTOffset,
        sizeof(zwQueryDirSSTOffset) / sizeof(s_VersionDependOffset)
    },
    {
        L"ZwQuerySystemInformation",
        zwQuerySysInfoSSTOffset,
        sizeof(zwQuerySysInfoSSTOffset) / sizeof(s_VersionDependOffset)
    }
};

LONG
ssdt_index_predefined_offset(PUNICODE_STRING func_name)
{
    // get version dependent offsets array by func name
    s_VersionDependOffset *offsets_array;
    size_t offsets_array_len;

    if ( !ssdt_offsets_array(func_name, &offsets_array, &offsets_array_len) )
        return ( -1 );

    // Get windows version
    RTL_OSVERSIONINFOW  windows_version =
    { .dwOSVersionInfoSize = sizeof(RTL_OSVERSIONINFOW) };

    if( !NT_SUCCESS( RtlGetVersion(&windows_version) ) )
        return ( -1 );

    // Get function index by windows version and offsets array
    return ( ssdt_offset_windows_version(offsets_array,
                                         offsets_array_len,
                                         windows_version)
           );
}

BOOL
ssdt_offsets_array(PUNICODE_STRING func_name,
                   s_VersionDependOffset **offsets_array,
                   size_t *offsets_array_len)
{
    size_t func_name_len = func_name->Length / 2;

    // For each function name in offsets array
    for( size_t i = 0; i < 2; ++i )
    {
        // Ignore if names lengths dont match
        if( func_name_len != wcslen(sstOffsetArray[i].name) )
            continue;

        // Ignore if names are not equal
        if( 0 != wcsncmp(sstOffsetArray[i].name, func_name->Buffer, func_name_len) )
            continue;

        // Return offsets array
        *offsets_array     = sstOffsetArray[i].offsetArray;
        *offsets_array_len = sstOffsetArray[i].offsetArraySize;

        return ( TRUE );

    }

    return ( FALSE );
}

LONG
ssdt_offset_windows_version(s_VersionDependOffset *offsets_array,
                            size_t offsets_array_len,
                            RTL_OSVERSIONINFOW windows_version)
{
    for( size_t i = 0; i < offsets_array_len ; ++i)
    {
        if( offsets_array[i].version.majorVersion != windows_version.dwMajorVersion )
            continue;

        if( offsets_array[i].version.minorVersion != windows_version.dwMinorVersion )
            continue;

        return ( offsets_array[i].offset );
    }

    return ( -1 );
}
