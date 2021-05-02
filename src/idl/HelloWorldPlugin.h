


#ifndef HelloWorldPlugin_1436885939_h
#define HelloWorldPlugin_1436885939_h

#include "HelloWorld.h"




  struct ZHCdrStream;

  #ifndef pres_typePlugin_h
  #include "waitset/pres_typePlugin.h"
  #endif



#ifdef __cplusplus
extern "C" {
#endif

#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)

#undef ZHDDSUSERDllExport
#define ZHDDSUSERDllExport __declspec(dllexport)
#endif
  

#define HelloWorldPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
#define HelloWorldPlugin_return_sample PRESTypePluginDefaultEndpointData_returnSample 
#define HelloWorldPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define HelloWorldPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 
 

#define HelloWorldPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define HelloWorldPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

ZHDDSUSERDllExport extern HelloWorld*
HelloWorldPluginSupport_create_data_ex(ZHBool allocate_pointers);

ZHDDSUSERDllExport extern HelloWorld*
HelloWorldPluginSupport_create_data(void);

ZHDDSUSERDllExport extern ZHBool 
HelloWorldPluginSupport_copy_data(
    HelloWorld *out,
    const HelloWorld *in);

ZHDDSUSERDllExport extern void 
HelloWorldPluginSupport_destroy_data_ex(
    HelloWorld *sample,ZHBool deallocate_pointers);

ZHDDSUSERDllExport extern void 
HelloWorldPluginSupport_destroy_data(
    HelloWorld *sample);

ZHDDSUSERDllExport extern void 
HelloWorldPluginSupport_print_data(
    const HelloWorld *sample,
    const char *desc,
    unsigned int indent);



ZHDDSUSERDllExport extern PRESTypePluginParticipantData 
HelloWorldPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    ZHBool top_level_registration, 
    void *container_plugin_context,
    ZHCdrTypeCode *typeCode);

ZHDDSUSERDllExport extern void 
HelloWorldPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);
    
ZHDDSUSERDllExport extern PRESTypePluginEndpointData 
HelloWorldPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    ZHBool top_level_registration, 
    void *container_plugin_context);

ZHDDSUSERDllExport extern void 
HelloWorldPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *out,
    const HelloWorld *in);


ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const HelloWorld *sample,
    struct ZHCdrStream *stream, 
    ZHBool serialize_encapsulation,
    ZHEncapsulationId encapsulation_id,
    ZHBool serialize_sample, 
    void *endpoint_plugin_qos);

ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *sample, 
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_sample, 
    void *endpoint_plugin_qos);

 
ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld **sample, 
    ZHBool * drop_sample,
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_sample, 
    void *endpoint_plugin_qos);


ZHDDSUSERDllExport extern ZHBool
HelloWorldPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct ZHCdrStream *stream, 
    ZHBool skip_encapsulation,  
    ZHBool skip_sample, 
    void *endpoint_plugin_qos);

ZHDDSUSERDllExport extern unsigned int 
HelloWorldPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int size);

ZHDDSUSERDllExport extern unsigned int 
HelloWorldPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int size);

ZHDDSUSERDllExport extern unsigned int
HelloWorldPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const HelloWorld * sample);

ZHDDSUSERDllExport extern PRESTypePluginKeyKind 
HelloWorldPlugin_get_key_kind(void);

ZHDDSUSERDllExport extern unsigned int 
HelloWorldPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment);

ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const HelloWorld *sample,
    struct ZHCdrStream *stream,
    ZHBool serialize_encapsulation,
    ZHEncapsulationId encapsulation_id,
    ZHBool serialize_key,
    void *endpoint_plugin_qos);

ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld * sample,
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_key,
    void *endpoint_plugin_qos);

 
ZHDDSUSERDllExport extern ZHBool 
HelloWorldPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld ** sample,
    ZHBool * drop_sample,
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_key,
    void *endpoint_plugin_qos);


ZHDDSUSERDllExport extern ZHBool
HelloWorldPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *sample,
    struct ZHCdrStream *stream, 
    ZHBool deserialize_encapsulation,  
    ZHBool deserialize_key, 
    void *endpoint_plugin_qos);

     

ZHDDSUSERDllExport extern struct PRESTypePlugin*
HelloWorldPlugin_new(void);

ZHDDSUSERDllExport extern void
HelloWorldPlugin_delete(struct PRESTypePlugin *);


#if (defined(ZH_WIN32) || defined (ZH_WINCE)) && defined(ZHDDS_USER_DLL_EXPORT)

#undef ZHDDSUSERDllExport
#define ZHDDSUSERDllExport
#endif


#ifdef __cplusplus
}
#endif
        

#endif /* HelloWorldPlugin_1436885939_h */
