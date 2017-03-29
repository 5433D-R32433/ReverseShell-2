#include <ntddk.h>

#include "hook/ssdt_utils.h"
#include "dbgutils.h"


const UCHAR opcode_MovEax = 0xB8;

__declspec(dllimport) s_SSDT_Imports KeServiceDescriptorTable;
s_SSDT *ntoskrnl;

int ssdt_utils_init()
{
    ntoskrnl = &(KeServiceDescriptorTable.ntoskrnl);

    return ( 1 );
}

LONG
ssdt_index(PUNICODE_STRING func_name)
{
    LONG index;

    if ( -1 != (index = ssdt_index_moveax(func_name)) )
        return ( index );

#ifdef _PREDEFINED_OFFSETS
    if ( -1 != (index = ssdt_index_predefined_offset(func_name)) )
        return ( index );
#endif // _PREDEFINED_OFFSETS

    return ( -1 );
}

LONG
ssdt_index_moveax(PUNICODE_STRING func_name)
{
    // Get function ptr
    PVOID func = MmGetSystemRoutineAddress(func_name);

    // If failed to get pointer then return error code
    if ( NULL == func )
        return ( -1 );

    // Look for "mov eax, index", if failed then return error code
    // Starts from Vista DriverVerifier can substitute ntoskrnl code.
    if( *( (PUCHAR)func ) != opcode_MovEax )
        return ( -1 );

    // Skip "mov eax, index" and get index.
    return ( *(PULONG)((PUCHAR) func + 1) );
}

PVOID get_sst_function_ptr_by_index(ULONG index)
{
    if ( 0 <= index && index <= ntoskrnl->NumberOfServices )
        return ( ntoskrnl->ServiceTableBase[index] );

    return ( NULL );
}
