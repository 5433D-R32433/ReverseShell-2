#pragma once

#include <ntddk.h>


extern UNICODE_STRING g_device_name;
extern UNICODE_STRING g_symbolic_link;
extern PDEVICE_OBJECT g_device_object;

/**
  *
  */
int device_and_slink_install(IN PDRIVER_OBJECT DriverObject);

/**
  *
  */
int device_and_slink_remove();
