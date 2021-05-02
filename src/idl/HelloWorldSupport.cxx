


#include "HelloWorldSupport.h"
#include "HelloWorldPlugin.h"



#ifdef __cplusplus  
    #ifndef dds_c_log_impl_h              
         #include "zhdds_c/dds_c_log_impl.h"                                
    #endif        
#endif        




#define TTYPENAME   HelloWorldTYPENAME

#define TDataWriter HelloWorldDataWriter
#define TData       HelloWorld


#ifdef __cplusplus
#include "zhdds_cpp/generic/dds_cpp_data_TDataWriter.gen"
#else
#include "zhdds_c/generic/dds_c_data_TDataWriter.gen"
#endif


#undef TDataWriter
#undef TData

#undef TTYPENAME


#define TTYPENAME   HelloWorldTYPENAME

#define TDataReader HelloWorldDataReader
#define TDataSeq    HelloWorldSeq
#define TData       HelloWorld


#ifdef __cplusplus
#include "zhdds_cpp/generic/dds_cpp_data_TDataReader.gen"
#else
#include "zhdds_c/generic/dds_c_data_TDataReader.gen"
#endif


#undef TDataReader
#undef TDataSeq
#undef TData

#undef TTYPENAME

#define TTYPENAME    HelloWorldTYPENAME
#define TPlugin_new  HelloWorldPlugin_new
#define TPlugin_delete  HelloWorldPlugin_delete

#define TTypeSupport HelloWorldTypeSupport
#define TData        HelloWorld
#define TDataReader  HelloWorldDataReader
#define TDataWriter  HelloWorldDataWriter
#ifdef __cplusplus



#include "zhdds_cpp/generic/dds_cpp_data_TTypeSupport.gen"



#else
#include "zhdds_c/generic/dds_c_data_TTypeSupport.gen"
#endif
#undef TTypeSupport
#undef TData
#undef TDataReader
#undef TDataWriter

#undef TTYPENAME
#undef TPlugin_new
#undef TPlugin_delete


