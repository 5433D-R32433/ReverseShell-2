#include "driver/device_and_slink.h"

#include "dbgutils.h"


#define DEVICE_NAME (PCWSTR)L"\\Device\\HiDriver"
#define SYMBOL_NAME (PCWSTR)L"\\DosDevices\\HiDriver"

UNICODE_STRING g_device_name;
UNICODE_STRING g_symbolic_link;
PDEVICE_OBJECT g_device_object = NULL;

int device_and_slink_install(IN PDRIVER_OBJECT DriverObject)
{
    // Store device name & symbolic link as unicode in UNICODE_STRING structs
    RtlInitUnicodeString(&g_device_name,   DEVICE_NAME);
    RtlInitUnicodeString(&g_symbolic_link, SYMBOL_NAME);

    // Create device & symbolic link

    // https://msdn.microsoft.com/en-us/library/windows/hardware/ff548397(v=vs.85).aspx
    if( !NT_SUCCESS( IoCreateDevice(DriverObject,          // Pointer to Device
                                    0,                     // Additional memory
                                    &g_device_name,  // Device name
                                    FILE_DEVICE_NULL,
                                    0,                     // Device characteristic
                                    FALSE,                 // Not exclusive
                                    &g_device_object) ) )
    {
        return ( 0 );
    }

    // https://msdn.microsoft.com/en-us/library/windows/hardware/ff549043(v=vs.85).aspx
    if( !NT_SUCCESS( IoCreateSymbolicLink(&g_symbolic_link,
                                          &g_device_name) ) )
    {
        return ( 0 );
    }

    return ( 1 );
}

int device_and_slink_remove()
{
    IoDeleteSymbolicLink(&g_symbolic_link);
    IoDeleteDevice(g_device_object);

    return ( 1 );
}
