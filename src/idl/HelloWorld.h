

#ifndef HelloWorld_1436885939_h
#define HelloWorld_1436885939_h

#ifndef ZHDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef zhdds_cpp_h
            #include "zhdds/zhdds_cpp.h"
        #endif
    #else
        #ifndef zhdds_c_h
            #include "zhdds/zhdds_c.h"
        #endif
    #endif
#else
    #include "zhdds_standalone_type.h"
#endif

             
static const DDS_Long HELLODDS_MAX_PAYLOAD_SIZE = 8192;             
static const DDS_Long HELLODDS_MAX_STRING_SIZE = 64;
#ifdef __cplusplus
extern "C" {
#endif

        
extern const char *HelloWorldTYPENAME;
        

#ifdef __cplusplus
}
#endif

typedef struct HelloWorld
{
    DDS_Long  sampleId;
    DDS_Long  pub_num;
    DDS_Long  pub_stat;
    DDS_Float  temperature;
    DDS_Float  humidity;
    DDS_Long  wind_speed;
    DDS_Long  direction;

} HelloWorld;
    
                            
#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)
  
  #undef ZHDDSUSERDllExport
  #define ZHDDSUSERDllExport __declspec(dllexport)
#endif

    
ZHDDSUSERDllExport DDS_TypeCode* HelloWorld_get_typecode(void); /* Type code */
    

DDS_SEQUENCE(HelloWorldSeq, HelloWorld);
        
ZHDDSUSERDllExport
ZHBool HelloWorld_initialize(
        HelloWorld* self);
        
ZHDDSUSERDllExport
ZHBool HelloWorld_initialize_ex(
        HelloWorld* self,ZHBool allocatePointers);

ZHDDSUSERDllExport
void HelloWorld_finalize(
        HelloWorld* self);
                        
ZHDDSUSERDllExport
void HelloWorld_finalize_ex(
        HelloWorld* self,ZHBool deletePointers);
        
ZHDDSUSERDllExport
ZHBool HelloWorld_copy(
        HelloWorld* dst,
        const HelloWorld* src);

#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)
  
  #undef ZHDDSUSERDllExport
  #define ZHDDSUSERDllExport
#endif



#endif /* HelloWorld_1436885939_h */
