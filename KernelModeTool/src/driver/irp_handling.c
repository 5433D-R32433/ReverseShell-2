#include "driver/irp_handling.h"

#include <ntddk.h>

int register_irp_handlers(IN PDRIVER_OBJECT DriverObject)
{
    PDRIVER_DISPATCH *dispatchTable;
    dispatchTable = DriverObject->MajorFunction;

    dispatchTable[IRP_MJ_DEVICE_CONTROL] = (PVOID) DeviceControlRoutine;
    dispatchTable[IRP_MJ_CREATE]         = (PVOID) DeviceOpenHandleRoutine;
    dispatchTable[IRP_MJ_CLOSE]          = (PVOID) DeviceCloseHandleRoutine;

    return ( 1 );
}

// IRP_MJ_CREATE call.
NTSTATUS
DeviceOpenHandleRoutine(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
    return ( complete_irp(Irp, STATUS_SUCCESS, 0) );
}

// IRP_MJ_CLOSE call
NTSTATUS
DeviceCloseHandleRoutine(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
    return ( complete_irp(Irp, STATUS_SUCCESS, 0) );
}

// IRP_MJ_DEVICE_CONTROL call
NTSTATUS
DeviceControlRoutine( IN PDEVICE_OBJECT fdo, IN PIRP Irp )
{
//    NTSTATUS status = STATUS_SUCCESS;
    ULONG bytesTxd =0; // Number of transmitted,received bytes
    PIO_STACK_LOCATION IrpStack=IoGetCurrentIrpStackLocation(Irp);

    // Getting the IOCTL code
    ULONG controlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;

    // Getting the exchange method
    ULONG method = controlCode & 0x03;

    if( METHOD_BUFFERED != method )
        return ( complete_irp(Irp,STATUS_INVALID_PARAMETER,bytesTxd) );

    // input buffer size
    ULONG inputLength = IrpStack->Parameters.DeviceIoControl.InputBufferLength;

    // output buffer size
    ULONG outputLength = IrpStack->Parameters.DeviceIoControl.OutputBufferLength;

    // if there is no buffer generate the error
    if( outputLength < 1 || inputLength < 1)
        return ( complete_irp(Irp,STATUS_INVALID_PARAMETER,bytesTxd) );

    WCHAR *buff = (PWCHAR)Irp->AssociatedIrp.SystemBuffer;

    if( 0 == call_dispatchers(controlCode,buff,inputLength,outputLength,&bytesTxd) )
    {
        size_t len = min(outputLength-1,
                         sizeof("No one dispatcher for this control code"));

        memcpy(buff, "No one dispatcher for this control code", len);

        char* mbStr = (char*)buff;
        mbStr[len] = 0;

        bytesTxd = len + 1;
    }

    return ( complete_irp(Irp,STATUS_SUCCESS,bytesTxd) );
}


NTSTATUS
complete_irp( PIRP Irp, NTSTATUS status, ULONG info)
{
    Irp->IoStatus.Status = status;
    Irp->IoStatus.Information = info;
    IoCompleteRequest(Irp,IO_NO_INCREMENT);

    return ( status );
}

int
call_dispatchers(ULONG controlCode,
                 WCHAR* buf,
                 ULONG inputBufSize,
                 ULONG outputBufSize,
                 ULONG* bytesTxd)
{



    return ( 0 );
}
