#pragma once

#define SN_NtAcceptConnectPort 0x0000
#define SN_NtAccessCheck 0x0001
#define SN_NtAccessCheckAndAuditAlarm 0x0002
#define SN_NtAccessCheckByType 0x0003
#define SN_NtAccessCheckByTypeAndAuditAlarm 0x0004
#define SN_NtAccessCheckByTypeResultList 0x0005
#define SN_NtAccessCheckByTypeResultListAndAuditAlarm 0x0006
#define SN_NtAccessCheckByTypeResultListAndAuditAlarmByHandle 0x0007
#define SN_NtAddAtom 0x0008
#define SN_NtAddBootEntry 0x0009
#define SN_NtAdjustGroupsToken 0x000a
#define SN_NtAdjustPrivilegesToken 0x000b
#define SN_NtAlertResumeThread 0x000c
#define SN_NtAlertThread 0x000d
#define SN_NtAllocateLocallyUniqueId 0x000e
#define SN_NtAllocateUserPhysicalPages 0x000f
#define SN_NtAllocateUuids 0x0010
#define SN_NtAllocateVirtualMemory 0x0011
#define SN_NtAreMappedFilesTheSame 0x0012
#define SN_NtAssignProcessToJobObject 0x0013
#define SN_NtCallbackReturn 0x0014
#define SN_NtCancelDeviceWakeupRequest 0x0015
#define SN_NtCancelIoFile 0x0016
#define SN_NtCancelTimer 0x0017
#define SN_NtClearEvent 0x0018
#define SN_NtClose 0x0019
#define SN_NtCloseObjectAuditAlarm 0x001a
#define SN_NtCompactKeys 0x001b
#define SN_NtCompareTokens 0x001c
#define SN_NtCompleteConnectPort 0x001d
#define SN_NtCompressKey 0x001e
#define SN_NtConnectPort 0x001f
#define SN_NtContinue 0x0020
#define SN_NtCreateDebugObject 0x0021
#define SN_NtCreateDirectoryObject 0x0022
#define SN_NtCreateEvent 0x0023
#define SN_NtCreateEventPair 0x0024
#define SN_NtCreateFile 0x0025
#define SN_NtCreateIoCompletion 0x0026
#define SN_NtCreateJobObject 0x0027
#define SN_NtCreateJobSet 0x0028
#define SN_NtCreateKey 0x0029
#define SN_NtCreateKeyedEvent 0x0117
#define SN_NtCreateMailslotFile 0x002a
#define SN_NtCreateMutant 0x002b
#define SN_NtCreateNamedPipeFile 0x002c
#define SN_NtCreatePagingFile 0x002d
#define SN_NtCreatePort 0x002e
#define SN_NtCreateProcess 0x002f
#define SN_NtCreateProcessEx 0x0030
#define SN_NtCreateProfile 0x0031
#define SN_NtCreateSection 0x0032
#define SN_NtCreateSemaphore 0x0033
#define SN_NtCreateSymbolicLinkObject 0x0034
#define SN_NtCreateThread 0x0035
#define SN_NtCreateTimer 0x0036
#define SN_NtCreateToken 0x0037
#define SN_NtCreateWaitablePort 0x0038
#define SN_NtDebugActiveProcess 0x0039
#define SN_NtDebugContinue 0x003a
#define SN_NtDelayExecution 0x003b
#define SN_NtDeleteAtom 0x003c
#define SN_NtDeleteBootEntry 0x003d
#define SN_NtDeleteFile 0x003e
#define SN_NtDeleteKey 0x003f
#define SN_NtDeleteObjectAuditAlarm 0x0040
#define SN_NtDeleteValueKey 0x0041
#define SN_NtDeviceIoControlFile 0x0042
#define SN_NtDisplayString 0x0043
#define SN_NtDuplicateObject 0x0044
#define SN_NtDuplicateToken 0x0045
#define SN_NtEnumerateBootEntries 0x0046
#define SN_NtEnumerateKey 0x0047
#define SN_NtEnumerateSystemEnvironmentValuesEx 0x0048
#define SN_NtEnumerateValueKey 0x0049
#define SN_NtExtendSection 0x004a
#define SN_NtFilterToken 0x004b
#define SN_NtFindAtom 0x004c
#define SN_NtFlushBuffersFile 0x004d
#define SN_NtFlushInstructionCache 0x004e
#define SN_NtFlushKey 0x004f
#define SN_NtFlushVirtualMemory 0x0050
#define SN_NtFlushWriteBuffer 0x0051
#define SN_NtFreeUserPhysicalPages 0x0052
#define SN_NtFreeVirtualMemory 0x0053
#define SN_NtFsControlFile 0x0054
#define SN_NtGetContextThread 0x0055
#define SN_NtGetDevicePowerState 0x0056
#define SN_NtGetPlugPlayEvent 0x0057
#define SN_NtGetWriteWatch 0x0058
#define SN_NtImpersonateAnonymousToken 0x0059
#define SN_NtImpersonateClientOfPort 0x005a
#define SN_NtImpersonateThread 0x005b
#define SN_NtInitializeRegistry 0x005c
#define SN_NtInitiatePowerAction 0x005d
#define SN_NtIsProcessInJob 0x005e
#define SN_NtIsSystemResumeAutomatic 0x005f
#define SN_NtListenPort 0x0060
#define SN_NtLoadDriver 0x0061
#define SN_NtLoadKey 0x0062
#define SN_NtLoadKey2 0x0063
#define SN_NtLockFile 0x0064
#define SN_NtLockProductActivationKeys 0x0065
#define SN_NtLockRegistryKey 0x0066
#define SN_NtLockVirtualMemory 0x0067
#define SN_NtMakePermanentObject 0x0068
#define SN_NtMakeTemporaryObject 0x0069
#define SN_NtMapUserPhysicalPages 0x006a
#define SN_NtMapUserPhysicalPagesScatter 0x006b
#define SN_NtMapViewOfSection 0x006c
#define SN_NtModifyBootEntry 0x006d
#define SN_NtNotifyChangeDirectoryFile 0x006e
#define SN_NtNotifyChangeKey 0x006f
#define SN_NtNotifyChangeMultipleKeys 0x0070
#define SN_NtOpenDirectoryObject 0x0071
#define SN_NtOpenEvent 0x0072
#define SN_NtOpenEventPair 0x0073
#define SN_NtOpenFile 0x0074
#define SN_NtOpenIoCompletion 0x0075
#define SN_NtOpenJobObject 0x0076
#define SN_NtOpenKey 0x0077
#define SN_NtOpenKeyedEvent 0x0118
#define SN_NtOpenMutant 0x0078
#define SN_NtOpenObjectAuditAlarm 0x0079
#define SN_NtOpenProcess 0x007a
#define SN_NtOpenProcessToken 0x007b
#define SN_NtOpenProcessTokenEx 0x007c
#define SN_NtOpenSection 0x007d
#define SN_NtOpenSemaphore 0x007e
#define SN_NtOpenSymbolicLinkObject 0x007f
#define SN_NtOpenThread 0x0080
#define SN_NtOpenThreadToken 0x0081
#define SN_NtOpenThreadTokenEx 0x0082
#define SN_NtOpenTimer 0x0083
#define SN_NtPlugPlayControl 0x0084
#define SN_NtPowerInformation 0x0085
#define SN_NtPrivilegeCheck 0x0086
#define SN_NtPrivilegeObjectAuditAlarm 0x0087
#define SN_NtPrivilegedServiceAuditAlarm 0x0088
#define SN_NtProtectVirtualMemory 0x0089
#define SN_NtPulseEvent 0x008a
#define SN_NtQueryAttributesFile 0x008b
#define SN_NtQueryBootEntryOrder 0x008c
#define SN_NtQueryBootOptions 0x008d
#define SN_NtQueryDebugFilterState 0x008e
#define SN_NtQueryDefaultLocale 0x008f
#define SN_NtQueryDefaultUILanguage 0x0090
#define SN_NtQueryDirectoryFile 0x0091
#define SN_NtQueryDirectoryObject 0x0092
#define SN_NtQueryEaFile 0x0093
#define SN_NtQueryEvent 0x0094
#define SN_NtQueryFullAttributesFile 0x0095
#define SN_NtQueryInformationAtom 0x0096
#define SN_NtQueryInformationFile 0x0097
#define SN_NtQueryInformationJobObject 0x0098
#define SN_NtQueryInformationPort 0x0099
#define SN_NtQueryInformationProcess 0x009a
#define SN_NtQueryInformationThread 0x009b
#define SN_NtQueryInformationToken 0x009c
#define SN_NtQueryInstallUILanguage 0x009d
#define SN_NtQueryIntervalProfile 0x009e
#define SN_NtQueryIoCompletion 0x009f
#define SN_NtQueryKey 0x00a0
#define SN_NtQueryMultipleValueKey 0x00a1
#define SN_NtQueryMutant 0x00a2
#define SN_NtQueryObject 0x00a3
#define SN_NtQueryOpenSubKeys 0x00a4
#define SN_NtQueryPerformanceCounter 0x00a5
#define SN_NtQueryPortInformationProcess 0x011b
#define SN_NtQueryQuotaInformationFile 0x00a6
#define SN_NtQuerySection 0x00a7
#define SN_NtQuerySecurityObject 0x00a8
#define SN_NtQuerySemaphore 0x00a9
#define SN_NtQuerySymbolicLinkObject 0x00aa
#define SN_NtQuerySystemEnvironmentValue 0x00ab
#define SN_NtQuerySystemEnvironmentValueEx 0x00ac
#define SN_NtQuerySystemInformation 0x00ad
#define SN_NtQuerySystemTime 0x00ae
#define SN_NtQueryTimer 0x00af
#define SN_NtQueryTimerResolution 0x00b0
#define SN_NtQueryValueKey 0x00b1
#define SN_NtQueryVirtualMemory 0x00b2
#define SN_NtQueryVolumeInformationFile 0x00b3
#define SN_NtQueueApcThread 0x00b4
#define SN_NtRaiseException 0x00b5
#define SN_NtRaiseHardError 0x00b6
#define SN_NtReadFile 0x00b7
#define SN_NtReadFileScatter 0x00b8
#define SN_NtReadRequestData 0x00b9
#define SN_NtReadVirtualMemory 0x00ba
#define SN_NtRegisterThreadTerminatePort 0x00bb
#define SN_NtReleaseKeyedEvent 0x0119
#define SN_NtReleaseMutant 0x00bc
#define SN_NtReleaseSemaphore 0x00bd
#define SN_NtRemoveIoCompletion 0x00be
#define SN_NtRemoveProcessDebug 0x00bf
#define SN_NtRenameKey 0x00c0
#define SN_NtReplaceKey 0x00c1
#define SN_NtReplyPort 0x00c2
#define SN_NtReplyWaitReceivePort 0x00c3
#define SN_NtReplyWaitReceivePortEx 0x00c4
#define SN_NtReplyWaitReplyPort 0x00c5
#define SN_NtRequestDeviceWakeup 0x00c6
#define SN_NtRequestPort 0x00c7
#define SN_NtRequestWaitReplyPort 0x00c8
#define SN_NtRequestWakeupLatency 0x00c9
#define SN_NtResetEvent 0x00ca
#define SN_NtResetWriteWatch 0x00cb
#define SN_NtRestoreKey 0x00cc
#define SN_NtResumeProcess 0x00cd
#define SN_NtResumeThread 0x00ce
#define SN_NtSaveKey 0x00cf
#define SN_NtSaveKeyEx 0x00d0
#define SN_NtSaveMergedKeys 0x00d1
#define SN_NtSecureConnectPort 0x00d2
#define SN_NtSetBootEntryOrder 0x00d3
#define SN_NtSetBootOptions 0x00d4
#define SN_NtSetContextThread 0x00d5
#define SN_NtSetDebugFilterState 0x00d6
#define SN_NtSetDefaultHardErrorPort 0x00d7
#define SN_NtSetDefaultLocale 0x00d8
#define SN_NtSetDefaultUILanguage 0x00d9
#define SN_NtSetEaFile 0x00da
#define SN_NtSetEvent 0x00db
#define SN_NtSetEventBoostPriority 0x00dc
#define SN_NtSetHighEventPair 0x00dd
#define SN_NtSetHighWaitLowEventPair 0x00de
#define SN_NtSetInformationDebugObject 0x00df
#define SN_NtSetInformationFile 0x00e0
#define SN_NtSetInformationJobObject 0x00e1
#define SN_NtSetInformationKey 0x00e2
#define SN_NtSetInformationObject 0x00e3
#define SN_NtSetInformationProcess 0x00e4
#define SN_NtSetInformationThread 0x00e5
#define SN_NtSetInformationToken 0x00e6
#define SN_NtSetIntervalProfile 0x00e7
#define SN_NtSetIoCompletion 0x00e8
#define SN_NtSetLdtEntries 0x00e9
#define SN_NtSetLowEventPair 0x00ea
#define SN_NtSetLowWaitHighEventPair 0x00eb
#define SN_NtSetQuotaInformationFile 0x00ec
#define SN_NtSetSecurityObject 0x00ed
#define SN_NtSetSystemEnvironmentValue 0x00ee
#define SN_NtSetSystemEnvironmentValueEx 0x00ef
#define SN_NtSetSystemInformation 0x00f0
#define SN_NtSetSystemPowerState 0x00f1
#define SN_NtSetSystemTime 0x00f2
#define SN_NtSetThreadExecutionState 0x00f3
#define SN_NtSetTimer 0x00f4
#define SN_NtSetTimerResolution 0x00f5
#define SN_NtSetUuidSeed 0x00f6
#define SN_NtSetValueKey 0x00f7
#define SN_NtSetVolumeInformationFile 0x00f8
#define SN_NtShutdownSystem 0x00f9
#define SN_NtSignalAndWaitForSingleObject 0x00fa
#define SN_NtStartProfile 0x00fb
#define SN_NtStopProfile 0x00fc
#define SN_NtSuspendProcess 0x00fd
#define SN_NtSuspendThread 0x00fe
#define SN_NtSystemDebugControl 0x00ff
#define SN_NtTerminateJobObject 0x0100
#define SN_NtTerminateProcess 0x0101
#define SN_NtTerminateThread 0x0102
#define SN_NtTestAlert 0x0103
#define SN_NtTraceEvent 0x0104
#define SN_NtTranslateFilePath 0x0105
#define SN_NtUnloadDriver 0x0106
#define SN_NtUnloadKey 0x0107
#define SN_NtUnloadKeyEx 0x0108
#define SN_NtUnlockFile 0x0109
#define SN_NtUnlockVirtualMemory 0x010a
#define SN_NtUnmapViewOfSection 0x010b
#define SN_NtVdmControl 0x010c
#define SN_NtWaitForDebugEvent 0x010d
#define SN_NtWaitForKeyedEvent 0x011a
#define SN_NtWaitForMultipleObjects 0x010e
#define SN_NtWaitForSingleObject 0x010f
#define SN_NtWaitHighEventPair 0x0110
#define SN_NtWaitLowEventPair 0x0111
#define SN_NtWriteFile 0x0112
#define SN_NtWriteFileGather 0x0113
#define SN_NtWriteRequestData 0x0114
#define SN_NtWriteVirtualMemory 0x0115
#define SN_NtYieldExecution 0x0116
