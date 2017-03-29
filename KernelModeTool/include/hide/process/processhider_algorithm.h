#pragma once

#include <ntddk.h>

typedef char BYTE;

typedef enum _SYSTEM_INFORMATION_CLASS
{
    SystemBasicInformation                  = 0x0000,   // SYSTEM_BASIC_INFORMATION         ( Number of processors )
    SystemProcessorInformation              = 0x0001,
    SystemPerformanceInformation            = 0x0002,   // SYSTEM_PERFORMANCE_INFORMATION
    SystemTimeOfDayInformation              = 0x0003,   // SYSTEM_TIMEOFDAY_INFORMATION
    SystemPathInformation                   = 0x0004,
    SystemProcessInformation                = 0x0005,   // SYSTEM_PROCESS_INFORMATION
    SystemCallCountInformation              = 0x0006,
    SystemDeviceInformation                 = 0x0007,
    SystemProcessorPerformanceInformation   = 0x0008,   // SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
    SystemFlagsInformation                  = 0x0009,
    SystemCallTimeInformation               = 0x000A,
    SystemModuleInformation                 = 0x000B,
    SystemLocksInformation                  = 0x000C,
    SystemStackTraceInformation             = 0x000D,
    SystemPagedPoolInformation              = 0x000E,
    SystemNonPagedPoolInformation           = 0x000F,
    SystemHandleInformation                 = 0x0010,
    SystemObjectInformation                 = 0x0011,
    SystemPageFileInformation               = 0x0012,
    SystemVdmInstemulInformation            = 0x0013,
    SystemVdmBopInformation                 = 0x0014,
    SystemFileCacheInformation              = 0x0015,
    SystemPoolTagInformation                = 0x0016,
    SystemInterruptInformation              = 0x0017,
    SystemDpcBehaviorInformation            = 0x0018,
    SystemFullMemoryInformation             = 0x0019,
    SystemLoadGdiDriverInformation          = 0x001A,
    SystemUnloadGdiDriverInformation        = 0x001B,
    SystemTimeAdjustmentInformation         = 0x001C,
    SystemSummaryMemoryInformation          = 0x001D,
    SystemMirrorMemoryInformation           = 0x001E,
    SystemPerformanceTraceInformation       = 0x001F,
    SystemCrashDumpInformation              = 0x0020,
    SystemExceptionInformation              = 0x0021,
    SystemCrashDumpStateInformation         = 0x0022,
    SystemKernelDebuggerInformation         = 0x0023,
    SystemContextSwitchInformation          = 0x0024,
    SystemRegistryQuotaInformation          = 0x0025,
    SystemExtendServiceTableInformation     = 0x0026,
    SystemPrioritySeperation                = 0x0027,
    SystemVerifierAddDriverInformation      = 0x0028,
    SystemVerifierRemoveDriverInformation   = 0x0029,
    SystemProcessorIdleInformation          = 0x002A,
    SystemLegacyDriverInformation           = 0x002B,
    SystemCurrentTimeZoneInformation        = 0x002C,
    SystemLookasideInformation              = 0x002D,
    SystemTimeSlipNotification              = 0x002E,
    SystemSessionCreate                     = 0x002F,
    SystemSessionDetach                     = 0x0030,
    SystemSessionInformation                = 0x0031,
    SystemRangeStartInformation             = 0x0032,
    SystemVerifierInformation               = 0x0033,
    SystemVerifierThunkExtend               = 0x0034,
    SystemSessionProcessInformation         = 0x0035,
    SystemLoadGdiDriverInSystemSpace        = 0x0036,
    SystemNumaProcessorMap                  = 0x0037,
    SystemPrefetcherInformation             = 0x0038,
    SystemExtendedProcessInformation        = 0x0039,
    SystemRecommendedSharedDataAlignment    = 0x003A,
    SystemComPlusPackage                    = 0x003B,
    SystemNumaAvailableMemory               = 0x003C,
    SystemProcessorPowerInformation         = 0x003D,
    SystemEmulationBasicInformation         = 0x003E,
    SystemEmulationProcessorInformation     = 0x003F,
    SystemExtendedHandleInformation         = 0x0040,
    SystemLostDelayedWriteInformation       = 0x0041,
    SystemBigPoolInformation                = 0x0042,
    SystemSessionPoolTagInformation         = 0x0043,
    SystemSessionMappedViewInformation      = 0x0044,
    SystemHotpatchInformation               = 0x0045,
    SystemObjectSecurityMode                = 0x0046,
    SystemWatchdogTimerHandler              = 0x0047,
    SystemWatchdogTimerInformation          = 0x0048,
    SystemLogicalProcessorInformation       = 0x0049,
    SystemWow64SharedInformationObsolete    = 0x004A,
    SystemRegisterFirmwareTableInformationHandler = 0x004B,
    SystemFirmwareTableInformation          = 0x004C,
    SystemModuleInformationEx               = 0x004D,
    SystemVerifierTriageInformation         = 0x004E,
    SystemSuperfetchInformation             = 0x004F,
    SystemMemoryListInformation             = 0x0050, // SYSTEM_MEMORY_LIST_INFORMATION
    SystemFileCacheInformationEx            = 0x0051,
    SystemThreadPriorityClientIdInformation = 0x0052,
    SystemProcessorIdleCycleTimeInformation = 0x0053,
    SystemVerifierCancellationInformation   = 0x0054,
    SystemProcessorPowerInformationEx       = 0x0055,
    SystemRefTraceInformation               = 0x0056,
    SystemSpecialPoolInformation            = 0x0057,
    SystemProcessIdInformation              = 0x0058,
    SystemErrorPortInformation              = 0x0059,
    SystemBootEnvironmentInformation        = 0x005A,
    SystemHypervisorInformation             = 0x005B,
    SystemVerifierInformationEx             = 0x005C,
    SystemTimeZoneInformation               = 0x005D,
    SystemImageFileExecutionOptionsInformation = 0x005E,
    SystemCoverageInformation               = 0x005F,
    SystemPrefetchPatchInformation          = 0x0060,
    SystemVerifierFaultsInformation         = 0x0061,
    SystemSystemPartitionInformation        = 0x0062,
    SystemSystemDiskInformation             = 0x0063,
    SystemProcessorPerformanceDistribution  = 0x0064,
    SystemNumaProximityNodeInformation      = 0x0065,
    SystemDynamicTimeZoneInformation        = 0x0066,
    SystemCodeIntegrityInformation          = 0x0067,
    SystemProcessorMicrocodeUpdateInformation = 0x0068,
    SystemProcessorBrandString              = 0x0069,
    SystemVirtualAddressInformation         = 0x006A,
    SystemLogicalProcessorAndGroupInformation = 0x006B,
    SystemProcessorCycleTimeInformation = 0x006C,
    SystemStoreInformation = 0x006D,
    SystemRegistryAppendString = 0x006E,
    SystemAitSamplingValue = 0x006F,
    SystemVhdBootInformation = 0x0070,
    SystemCpuQuotaInformation = 0x0071,
    SystemNativeBasicInformation = 0x0072,
    SystemErrorPortTimeouts = 0x0073,
    SystemLowPriorityIoInformation = 0x0074,
    SystemBootEntropyInformation = 0x0075,
    SystemVerifierCountersInformation = 0x0076,
    SystemPagedPoolInformationEx = 0x0077,
    SystemSystemPtesInformationEx = 0x0078,
    SystemNodeDistanceInformation = 0x0079,
    SystemAcpiAuditInformation = 0x007A,
    SystemBasicPerformanceInformation = 0x007B,
    SystemQueryPerformanceCounterInformation = 0x007C,
    SystemSessionBigPoolInformation = 0x007D,
    SystemBootGraphicsInformation = 0x007E,
    SystemScrubPhysicalMemoryInformation = 0x007F,
    SystemBadPageInformation = 0x0080,
    SystemProcessorProfileControlArea = 0x0081,
    SystemCombinePhysicalMemoryInformation = 0x0082,
    SystemEntropyInterruptTimingInformation = 0x0083,
    SystemConsoleInformation = 0x0084,
    SystemPlatformBinaryInformation = 0x0085,
    SystemThrottleNotificationInformation = 0x0086,
    SystemHypervisorProcessorCountInformation = 0x0087,
    SystemDeviceDataInformation = 0x0088,
    SystemDeviceDataEnumerationInformation = 0x0089,
    SystemMemoryTopologyInformation = 0x008A,
    SystemMemoryChannelInformation = 0x008B,
    SystemBootLogoInformation = 0x008C,
    SystemProcessorPerformanceInformationEx = 0x008D,
    SystemSpare0 = 0x008E,
    SystemSecureBootPolicyInformation = 0x008F,
    SystemPageFileInformationEx = 0x0090,
    SystemSecureBootInformation = 0x0091,
    SystemEntropyInterruptTimingRawInformation = 0x0092,
    SystemPortableWorkspaceEfiLauncherInformation = 0x0093,
    SystemFullProcessInformation = 0x0094,
    MaxSystemInfoClass = 0x0095
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    BYTE Reserved1[48];
    PVOID Reserved2[3];
    HANDLE UniqueProcessId;
    PVOID Reserved3;
    ULONG HandleCount;
    BYTE Reserved4[4];
    PVOID Reserved5[11];
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER Reserved6[6];
} SYSTEM_PROCESS_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION_DETAILD {
    ULONG NextEntryOffset;
    ULONG NumberOfThreads;
    LARGE_INTEGER SpareLi1;
    LARGE_INTEGER SpareLi2;
    LARGE_INTEGER SpareLi3;
    LARGE_INTEGER CreateTime;
    LARGE_INTEGER UserTime;
    LARGE_INTEGER KernelTime;
    UNICODE_STRING ImageName;
    KPRIORITY BasePriority;
    HANDLE UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
    ULONG HandleCount;
    BYTE Reserved4[4];
    PVOID Reserved5[11];
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivatePageCount;
    LARGE_INTEGER Reserved6[6];
} SYSTEM_PROCESS_INFORMATION_DETAILD, *PSYSTEM_PROCESS_INFORMATION_DETAILD;


typedef struct ProcessHideEntry
{
    size_t process_name_len;
    WCHAR  process_name[24];
} s_ProcessHideEntry;

extern s_ProcessHideEntry processes_to_hide[];

int is_in_processes_to_hide(PUNICODE_STRING process_name);

NTSTATUS Hide(SYSTEM_PROCESS_INFORMATION_DETAILD *SystemInformation);