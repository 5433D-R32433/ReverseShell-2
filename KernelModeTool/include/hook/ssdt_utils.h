#pragma once

//#define _PREDEFINED_OFFSETS

#include <ntddk.h>

/* function index lookup methods */

#ifdef _PREDEFINED_OFFSETS
#include "predefined_ssdt_offsets_lookup.h"
#endif // _PREDEFINED_OFFSETS


extern const UCHAR opcode_MovEax;

typedef struct SystemServiceTable
{
    PVOID  *ServiceTableBase;
    PULONG ServiceCounterTableBase;
    ULONG  NumberOfServices;
    PUCHAR ParamTableBase;
} s_SSDT;

typedef struct ServiceDescriptorTable
{
    s_SSDT ntoskrnl;  //SST for ntoskrnl.exe
    s_SSDT win32k;    //SST for win32k.sys
    s_SSDT unused1;
    s_SSDT unused2;
} s_SSDT_Imports;

extern s_SSDT_Imports KeServiceDescriptorTable;
extern s_SSDT  *ntoskrnl;

/**
  * This function initializes the above pointers.
  */
int ssdt_utils_init();

/**
  * Use this function to an index of a function in SSDT.
  * @param[in] func_name - name of function to get the index of.
  * @return On success, matching index is returned.
  *         Otherwise, -1 is returned.
  */
LONG ssdt_index(PUNICODE_STRING func_name);

/**
  * Use this function to get an index of a function in SSDT using
  * 'MOV EAX' method.
  * @param[in] func_name - name of function to get the index of.
  * @return On success, matching index is returned.
  *         Otherwise, -1 is returned.
  */
LONG ssdt_index_moveax(PUNICODE_STRING func_name);

/**
  * Use this function to get a pointer to a function in SSDT that matches
  * a given index.
  * @param[in] index - index inside SSDT
  * @return On success, a valid pointer is returned.
  *         Otherwise, NULL is returned.
  */
PVOID get_sst_function_ptr_by_index(ULONG index);
