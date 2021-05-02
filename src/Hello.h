#pragma once
// 宏定义，确保在不同平台下使用相同的函数名称
#ifdef ZH_WIN32
#define ZH_SNPRINTF        _snprintf
#define ZH_STRCASECMP      _stricmp
#define ZH_STRNCASECMP     _strnicmp
#define ZH_STRTOULL        _strtoui64
#define ZH_STRTOUL         strtoul
#define ZH_STRNCMP         strncmp
#else
#define ZH_SNPRINTF        snprintf
#define ZH_STRCASECMP      strcasecmp
#define ZH_STRNCASECMP     strncasecmp
#define ZH_STRTOULL        strtoull
#define ZH_STRTOUL         strtoul
#define ZH_STRNCMP         strncmp
#endif



