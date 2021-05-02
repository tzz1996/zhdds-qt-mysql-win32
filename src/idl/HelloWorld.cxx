

#ifndef ZHDDS_STANDALONE_TYPE
    #ifdef __cplusplus
        #ifndef zhdds_cpp_h
            #include "zhdds/zhdds_cpp.h"
        #endif
        #ifndef dds_c_log_impl_h              
            #include "zhdds_c/dds_c_log_impl.h"                                
        #endif        
    #else
        #ifndef zhdds_c_h
            #include "zhdds/zhdds_c.h"
        #endif
    #endif
    
    #ifndef cdr_type_h
        #include "serialize/cdr_type.h"
    #endif    

    #ifndef osapi_heap_h
        #include "sys_api/osapi_heap.h" 
    #endif
#else
    #include "zhdds_standalone_type.h"
#endif



#include "HelloWorld.h"

/* ========================================================================= */
const char *HelloWorldTYPENAME = "HelloWorld";

DDS_TypeCode* HelloWorld_get_typecode()
{
    static ZHBool is_initialized = ZH_FALSE;


    static DDS_TypeCode_Member HelloWorld_g_tc_members[7]=
    {
        {
            (char *)"sampleId",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"pub_num",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"pub_stat",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"temperature",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"humidity",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"wind_speed",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        },
        {
            (char *)"direction",
            {
                0,
                DDS_BOOLEAN_FALSE,
                -1,
                NULL
            },
            0, 
            0, 
            0, 
            NULL, 
            DDS_BOOLEAN_FALSE, 
            DDS_PRIVATE_MEMBER,
            0,
            NULL
        }
    };

    static DDS_TypeCode HelloWorld_g_tc =
    {{
        DDS_TK_STRUCT,
        DDS_BOOLEAN_FALSE, 
        -1,
        (char *)"HelloWorld", 
        NULL, 
        0, 
        0, 
        NULL, 
        7, 
        HelloWorld_g_tc_members, 
        DDS_VM_NONE 
    }}; /* Type code for HelloWorld*/

    if (is_initialized) {
        return &HelloWorld_g_tc;
    }


    HelloWorld_g_tc_members[0]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_long;
    HelloWorld_g_tc_members[1]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_long;
    HelloWorld_g_tc_members[2]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_long;
    HelloWorld_g_tc_members[3]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_float;
    HelloWorld_g_tc_members[4]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_float;
    HelloWorld_g_tc_members[5]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_long;
    HelloWorld_g_tc_members[6]._representation._typeCode = (ZHCdrTypeCode *)&DDS_g_tc_long;

    is_initialized = ZH_TRUE;

    return &HelloWorld_g_tc;
}


ZHBool HelloWorld_initialize(
    HelloWorld* sample) {
  return HelloWorld_initialize_ex(sample,ZH_TRUE);
}
        
ZHBool HelloWorld_initialize_ex(
    HelloWorld* sample,ZHBool allocatePointers)
{

    if (!ZHCdrType_initLong(&sample->sampleId)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initLong(&sample->pub_num)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initLong(&sample->pub_stat)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initFloat(&sample->temperature)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initFloat(&sample->humidity)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initLong(&sample->wind_speed)) {
        return ZH_FALSE;
    }                
            
    if (!ZHCdrType_initLong(&sample->direction)) {
        return ZH_FALSE;
    }                
            

    return ZH_TRUE;
}

void HelloWorld_finalize(
    HelloWorld* sample)
{
    HelloWorld_finalize_ex(sample,ZH_TRUE);
}
        
void HelloWorld_finalize_ex(
    HelloWorld* sample,ZHBool deletePointers)
{        

}

ZHBool HelloWorld_copy(
    HelloWorld* dst,
    const HelloWorld* src)
{        

    if (!ZHCdrType_copyLong(
        &dst->sampleId, &src->sampleId)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyLong(
        &dst->pub_num, &src->pub_num)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyLong(
        &dst->pub_stat, &src->pub_stat)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyFloat(
        &dst->temperature, &src->temperature)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyFloat(
        &dst->humidity, &src->humidity)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyLong(
        &dst->wind_speed, &src->wind_speed)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrType_copyLong(
        &dst->direction, &src->direction)) {
        return ZH_FALSE;
    }
            

    return ZH_TRUE;
}


/**
 * <<IMPLEMENTATION>>
 *
 * Defines:  TSeq, T
 *
 */
#define T HelloWorld
#define TSeq HelloWorldSeq
#define T_initialize_ex HelloWorld_initialize_ex
#define T_finalize_ex   HelloWorld_finalize_ex
#define T_copy       HelloWorld_copy

#ifndef ZHDDS_STANDALONE_TYPE
#include "zhdds_c/generic/dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "zhdds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#endif
#else
#include "dds_c_sequence_TSeq.gen"
#ifdef __cplusplus
#include "dds_cpp_sequence_TSeq.gen"
#endif
#endif

#undef T_copy
#undef T_finalize_ex
#undef T_initialize_ex
#undef TSeq
#undef T

