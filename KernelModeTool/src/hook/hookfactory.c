#include <ntddk.h>

#include "hook/hookfactory.h"
#include "hook/ssdt_utils.h"
#include "dbgutils.h"


int
ssdt_hook_w(s_SSTHook *hook,
            PVOID new_func_ptr,
            WCHAR * org_func_name,
            size_t org_func_name_len)
{
    // Store org_func_name as UNICODE_STRING
    UNICODE_STRING unicode_org_func_name;
    RtlInitUnicodeString(&unicode_org_func_name, org_func_name);

    return ( ssdt_hook_u(hook, new_func_ptr, &unicode_org_func_name) );
}

int
ssdt_hook_u(s_SSTHook *hook,
            PVOID new_func_ptr,
            PUNICODE_STRING org_func_name)
{
    // Create hook struct
    if( !create_hook(hook, new_func_ptr, org_func_name) )
        return ( 0 );

    // Hook SSDT function
    if( !apply_hook(hook) )
        return ( 0 );

    return ( 1 );
}

int
create_hook(s_SSTHook *hook,
            PVOID new_func_ptr,
            PUNICODE_STRING org_func_name)
{
    // Get location of original function in SSDT
    LONG function_index = ssdt_index(org_func_name);

    if ( -1 == function_index )
    {
        DEBUG_PRINT("Couldn't get function index\n");

        hook->org_func = NULL;
        hook->new_func = NULL;

        return ( 0 );
    }

    // Get pointer to original function
    PVOID org_func_ptr = get_sst_function_ptr_by_index(function_index);

    if ( 0 == org_func_ptr )
    {
        DEBUG_PRINT("Couldn't get original function ptr\n");

        hook->org_func = NULL;
        hook->new_func = NULL;

        return ( 0 );
    }

    // Remember original function's location and pointer in hook struct
    // And pointer to new function
    hook->func_index = function_index;
    hook->org_func   = org_func_ptr;
    hook->new_func   = new_func_ptr;

    return ( 1 );
}

int apply_hook(s_SSTHook *hook)
{
    // Catch single processor
    KIRQL oldIrql;
    KeRaiseIrql(HIGH_LEVEL,&oldIrql);

    // Clear write protection
    clear_wp_bit();

    // Change function pointer in SSDT
//    InterlockedExchangePointer(&ServiceTable[hook.Index_SST],hook.newFuncPtr);

    PVOID old_ptr = InterlockedExchangePointer(
                        &(ntoskrnl->ServiceTableBase[hook->func_index]),
                        hook->new_func);

//    ntoskrnl->ServiceTableBase[hook->func_index] = hook->new_func;

    // Reset write protection
    set_wp_bit();

    // Free processor
    KeLowerIrql(oldIrql);

    return ( 1 );
}

int
disclaim_hook(s_SSTHook *hook)
{
    DEBUG_PRINT("Disclaiming hook on %d\n", hook->func_index);

    // Initialize a new s_SSTHook struct, switching original and
    // new function pointers
    s_SSTHook reverse_hook;
    reverse_hook.func_index  = hook->func_index;
    reverse_hook.new_func    = hook->org_func;
    reverse_hook.org_func    = hook->new_func;

    // Apply the reversed hook struct
    return ( apply_hook(&reverse_hook) );
}

void clear_wp_bit()
{
    __asm__(".intel_syntax;"

            "push eax;"
            "mov eax, cr0;"
            "and eax, 0xFFFEFFFF;"
            "mov cr0, eax;"
            "pop eax;"

            ".att_syntax;" );
}

void set_wp_bit()
{
    __asm__( ".intel_syntax;"

             "push eax;"
             "mov eax, cr0;"
             "or eax, not 0xFFFEFFFF;"
             "mov cr0, eax;"
             "pop eax;"

             ".att_syntax;" );
}
