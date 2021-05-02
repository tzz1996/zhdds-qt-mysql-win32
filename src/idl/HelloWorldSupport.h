

#ifndef HelloWorldSupport_1436885939_h
#define HelloWorldSupport_1436885939_h

#include "HelloWorld.h"



#ifdef __cplusplus
#ifndef zhdds_cpp_h
  #include "zhdds/zhdds_cpp.h"
#endif
#else
#ifndef zhdds_c_h
  #include "zhdds/zhdds_c.h"
#endif
#endif

        

#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)
 
  #undef ZHDDSUSERDllExport
  #define ZHDDSUSERDllExport __declspec(dllexport)

#ifdef __cplusplus
      
  class __declspec(dllimport) DDSTypeSupport;
  class __declspec(dllimport) DDSDataWriter;
  class __declspec(dllimport) DDSDataReader;
#endif

#endif

#ifdef __cplusplus

DDS_TYPESUPPORT_CPP(HelloWorldTypeSupport, HelloWorld);

DDS_DATAWRITER_CPP(HelloWorldDataWriter, HelloWorld);
DDS_DATAREADER_CPP(HelloWorldDataReader, HelloWorldSeq, HelloWorld);


#else

DDS_TYPESUPPORT_C(HelloWorldTypeSupport, HelloWorld);
DDS_DATAWRITER_C(HelloWorldDataWriter, HelloWorld);
DDS_DATAREADER_C(HelloWorldDataReader, HelloWorldSeq, HelloWorld);

#endif

#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)
  
  #undef ZHDDSUSERDllExport
  #define ZHDDSUSERDllExport
#endif



#endif  /* HelloWorldSupport_1436885939_h */
