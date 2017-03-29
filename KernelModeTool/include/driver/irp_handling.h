#pragma once

#include <ntddk.h>

int register_irp_handlers( IN PDRIVER_OBJECT DriverObject);

NTSTATUS DeviceControlRoutine       ( IN PDEVICE_OBJECT fdo, IN PIRP Irp );
NTSTATUS DeviceCloseHandleRoutine   ( IN PDEVICE_OBJECT fdo, IN PIRP Irp );
NTSTATUS DeviceOpenHandleRoutine    ( IN PDEVICE_OBJECT fdo, IN PIRP Irp );

NTSTATUS complete_irp( PIRP Irp, NTSTATUS status, ULONG info);
int call_dispatchers(ULONG controlCode,
                     WCHAR* buf,
                     ULONG inputBufSize,
                     ULONG outputBufSize,
                     ULONG* bytesTxd);

