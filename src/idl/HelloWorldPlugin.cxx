

#include <string.h>

#ifdef __cplusplus
#ifndef zhdds_cpp_h
  #include "zhdds/zhdds_cpp.h"
#endif
#else
#ifndef zhdds_c_h
  #include "zhdds/zhdds_c.h"
#endif
#endif

#ifndef osapi_type_h
  #include "sys_api/osapi_type.h"
#endif
#ifndef osapi_heap_h
  #include "sys_api/osapi_heap.h"
#endif

#ifndef osapi_utility_h
  #include "sys_api/osapi_utility.h"
#endif

#ifndef cdr_type_h
  #include "serialize/cdr_type.h"
#endif

#ifndef cdr_encapsulation_h
  #include "serialize/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
  #include "serialize/cdr_stream.h"
#endif

#ifndef pres_typePlugin_h
  #include "waitset/pres_typePlugin.h"
#endif



#include "HelloWorldPlugin.h"

HelloWorld *
HelloWorldPluginSupport_create_data_ex(ZHBool allocate_pointers){
    HelloWorld *sample = NULL;

    ZHOsapiHeap_allocateStructure(
        &sample, HelloWorld);

    if(sample != NULL) {
        if (!HelloWorld_initialize_ex(sample,allocate_pointers)) {
            ZHOsapiHeap_freeStructure(&sample);
            return NULL;
        }
    }
    return sample; 
}

HelloWorld *
HelloWorldPluginSupport_create_data(void)
{
    return HelloWorldPluginSupport_create_data_ex(ZH_TRUE);
}

void 
HelloWorldPluginSupport_destroy_data_ex(
    HelloWorld *sample,ZHBool deallocate_pointers) {

    HelloWorld_finalize_ex(sample,deallocate_pointers);

    ZHOsapiHeap_freeStructure(sample);
}

void 
HelloWorldPluginSupport_destroy_data(
    HelloWorld *sample) {

    HelloWorldPluginSupport_destroy_data_ex(sample,ZH_TRUE);

}

ZHBool 
HelloWorldPluginSupport_copy_data(
    HelloWorld *dst,
    const HelloWorld *src)
{
    return HelloWorld_copy(dst,src);
}

void 
HelloWorldPluginSupport_print_data(
    const HelloWorld *sample,
    const char *desc,
    unsigned int indent_level)
{


    ZHCdrType_printIndent(indent_level);

    if (desc != NULL) {
      ZHLog_debug("%s:\n", desc);
    } else {
      ZHLog_debug("\n");
    }

    if (sample == NULL) {
      ZHLog_debug("NULL\n");
      return;
    }


    ZHCdrType_printLong(
        &sample->sampleId, "sampleId", indent_level + 1);
            
    ZHCdrType_printLong(
        &sample->pub_num, "pub_num", indent_level + 1);
            
    ZHCdrType_printLong(
        &sample->pub_stat, "pub_stat", indent_level + 1);
            
    ZHCdrType_printFloat(
        &sample->temperature, "temperature", indent_level + 1);
            
    ZHCdrType_printFloat(
        &sample->humidity, "humidity", indent_level + 1);
            
    ZHCdrType_printLong(
        &sample->wind_speed, "wind_speed", indent_level + 1);
            
    ZHCdrType_printLong(
        &sample->direction, "direction", indent_level + 1);
            

}



PRESTypePluginParticipantData 
HelloWorldPlugin_on_participant_attached(
    void *registration_data,
    const struct PRESTypePluginParticipantInfo *participant_info,
    ZHBool top_level_registration,
    void *container_plugin_context,
    ZHCdrTypeCode *type_code)
{

    return PRESTypePluginDefaultParticipantData_new(participant_info);

}

void 
HelloWorldPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data)
{

  PRESTypePluginDefaultParticipantData_delete(participant_data);
}

PRESTypePluginEndpointData
HelloWorldPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    ZHBool top_level_registration, 
    void *containerPluginContext)
{
    PRESTypePluginEndpointData epd = NULL;

    epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            (PRESTypePluginDefaultEndpointDataCreateSampleFunction)
            HelloWorldPluginSupport_create_data,
            (PRESTypePluginDefaultEndpointDataDestroySampleFunction)
            HelloWorldPluginSupport_destroy_data,
            NULL, NULL);

    if (epd == NULL) {
        return NULL;
    }

    
    if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
        if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
            (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                HelloWorldPlugin_get_serialized_sample_max_size, epd,
            (PRESTypePluginGetSerializedSampleSizeFunction)
            HelloWorldPlugin_get_serialized_sample_size,
            epd) == ZH_FALSE) {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }
    }
    


    return epd;    
}

void 
HelloWorldPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data)
{  

    PRESTypePluginDefaultEndpointData_delete(endpoint_data);
}

ZHBool 
HelloWorldPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *dst,
    const HelloWorld *src)
{
    return HelloWorldPluginSupport_copy_data(dst,src);
}

ZHBool 
HelloWorldPlugin_serialize(
    PRESTypePluginEndpointData endpoint_data,
    const HelloWorld *sample, 
    struct ZHCdrStream *stream,    
    ZHBool serialize_encapsulation,
    ZHEncapsulationId encapsulation_id,
    ZHBool serialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


  if(serialize_encapsulation) {

    if (!ZHCdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
        return ZH_FALSE;
    }

    position = ZHCdrStream_resetAlignment(stream);

  }


  if(serialize_sample) {

    if (!ZHCdrStream_serializeLong(
        stream, &sample->sampleId)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeLong(
        stream, &sample->pub_num)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeLong(
        stream, &sample->pub_stat)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeFloat(
        stream, &sample->temperature)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeFloat(
        stream, &sample->humidity)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeLong(
        stream, &sample->wind_speed)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_serializeLong(
        stream, &sample->direction)) {
        return ZH_FALSE;
    }
            
  }


  if(serialize_encapsulation) {
    ZHCdrStream_restoreAlignment(stream,position);
  }


  return ZH_TRUE;
}

ZHBool 
HelloWorldPlugin_deserialize_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *sample,
    struct ZHCdrStream *stream,   
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {

        if (!ZHCdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return ZH_FALSE;
        }

        position = ZHCdrStream_resetAlignment(stream);

    }
    

    if(deserialize_sample) {

    if (!ZHCdrStream_deserializeLong(
        stream, &sample->sampleId)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeLong(
        stream, &sample->pub_num)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeLong(
        stream, &sample->pub_stat)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeFloat(
        stream, &sample->temperature)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeFloat(
        stream, &sample->humidity)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeLong(
        stream, &sample->wind_speed)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_deserializeLong(
        stream, &sample->direction)) {
        return ZH_FALSE;
    }
            
    }


    if(deserialize_encapsulation) {
        ZHCdrStream_restoreAlignment(stream,position);
    }


    return ZH_TRUE;
}

 
ZHBool 
HelloWorldPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld **sample,
    ZHBool * drop_sample,
    struct ZHCdrStream *stream,   
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_sample, 
    void *endpoint_plugin_qos)
{

    return HelloWorldPlugin_deserialize_sample( 
        endpoint_data, (sample != NULL)?*sample:NULL,
        stream, deserialize_encapsulation, deserialize_sample, 
        endpoint_plugin_qos);
 
}


ZHBool HelloWorldPlugin_skip(
    PRESTypePluginEndpointData endpoint_data,
    struct ZHCdrStream *stream,   
    ZHBool skip_encapsulation,
    ZHBool skip_sample, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(skip_encapsulation) {
        if (!ZHCdrStream_skipEncapsulation(stream)) {
            return ZH_FALSE;
        }


        position = ZHCdrStream_resetAlignment(stream);

    }

    if (skip_sample) {

    if (!ZHCdrStream_skipLong(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipLong(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipLong(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipFloat(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipFloat(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipLong(stream)) {
        return ZH_FALSE;
    }
            
    if (!ZHCdrStream_skipLong(stream)) {
        return ZH_FALSE;
    }
            
    }


    if(skip_encapsulation) {
        ZHCdrStream_restoreAlignment(stream,position);
    }


    return ZH_TRUE;
}

unsigned int 
HelloWorldPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        if (!ZHCdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        ZHCdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

unsigned int 
HelloWorldPlugin_get_serialized_sample_min_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        if (!ZHCdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        ZHCdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment +=  ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

unsigned int
HelloWorldPlugin_get_serialized_sample_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment,
    const HelloWorld * sample) 
{

    unsigned int initial_alignment = current_alignment;

    unsigned int encapsulation_size = current_alignment;


    if (include_encapsulation) {

        if (!ZHCdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }

        ZHCdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }


    current_alignment += ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getFloatMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    current_alignment += ZHCdrType_getLongMaxSizeSerialized(
        current_alignment);
            
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

/* --------------------------------------------------------------------------------------
    Key Management functions:
 * -------------------------------------------------------------------------------------- */

PRESTypePluginKeyKind 
HelloWorldPlugin_get_key_kind(void)
{

    return PRES_TYPEPLUGIN_NO_KEY;
     
}

ZHBool 
HelloWorldPlugin_serialize_key(
    PRESTypePluginEndpointData endpoint_data,
    const HelloWorld *sample, 
    struct ZHCdrStream *stream,    
    ZHBool serialize_encapsulation,
    ZHEncapsulationId encapsulation_id,
    ZHBool serialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(serialize_encapsulation) {
        if (!ZHCdrStream_serializeAndSetCdrEncapsulation(stream, encapsulation_id)) {
            return ZH_FALSE;
        }


        position = ZHCdrStream_resetAlignment(stream);

    }

    if(serialize_key) {

        if (!HelloWorldPlugin_serialize(
                endpoint_data,
                sample,
                stream,
                ZH_FALSE, encapsulation_id,
                ZH_TRUE,
                endpoint_plugin_qos)) {
            return ZH_FALSE;
        }
    
    }


    if(serialize_encapsulation) {
        ZHCdrStream_restoreAlignment(stream,position);
    }


    return ZH_TRUE;
}

ZHBool HelloWorldPlugin_deserialize_key_sample(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *sample, 
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_key,
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        /* Deserialize encapsulation */
        if (!ZHCdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return ZH_FALSE;  
        }


        position = ZHCdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!HelloWorldPlugin_deserialize_sample(
                endpoint_data, sample, stream,
                ZH_FALSE, ZH_TRUE, 
                endpoint_plugin_qos)) {
            return ZH_FALSE;
        }
    
    }


    if(deserialize_encapsulation) {
        ZHCdrStream_restoreAlignment(stream,position);
    }


    return ZH_TRUE;
}

 
ZHBool HelloWorldPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld **sample, 
    ZHBool * drop_sample,
    struct ZHCdrStream *stream,
    ZHBool deserialize_encapsulation,
    ZHBool deserialize_key,
    void *endpoint_plugin_qos)
{
    return HelloWorldPlugin_deserialize_key_sample(
        endpoint_data, (sample != NULL)?*sample:NULL, stream,
        deserialize_encapsulation, deserialize_key, endpoint_plugin_qos);
}


unsigned int
HelloWorldPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    ZHBool include_encapsulation,
    ZHEncapsulationId encapsulation_id,
    unsigned int current_alignment)
{

    unsigned int encapsulation_size = current_alignment;


    unsigned int initial_alignment = current_alignment;

    if (include_encapsulation) {
        if (!ZHCdrEncapsulation_validEncapsulationId(encapsulation_id)) {
            return 1;
        }


        ZHCdrStream_getEncapsulationSize(encapsulation_size);
        encapsulation_size -= current_alignment;
        current_alignment = 0;
        initial_alignment = 0;

    }
        

    current_alignment += HelloWorldPlugin_get_serialized_sample_max_size(
        endpoint_data,ZH_FALSE, encapsulation_id, current_alignment);
    
    if (include_encapsulation) {
        current_alignment += encapsulation_size;
    }

    return current_alignment - initial_alignment;
}

ZHBool 
HelloWorldPlugin_serialized_sample_to_key(
    PRESTypePluginEndpointData endpoint_data,
    HelloWorld *sample,
    struct ZHCdrStream *stream, 
    ZHBool deserialize_encapsulation,  
    ZHBool deserialize_key, 
    void *endpoint_plugin_qos)
{
    char * position = NULL;


    if(deserialize_encapsulation) {
        if (!ZHCdrStream_deserializeAndSetCdrEncapsulation(stream)) {
            return ZH_FALSE;
        }

        position = ZHCdrStream_resetAlignment(stream);

    }

    if (deserialize_key) {

        if (!HelloWorldPlugin_deserialize_sample(
            endpoint_data, sample, stream, ZH_FALSE, 
            ZH_TRUE, endpoint_plugin_qos)) {
            return ZH_FALSE;
        }

    }


    if(deserialize_encapsulation) {
        ZHCdrStream_restoreAlignment(stream,position);
    }


    return ZH_TRUE;
}


 
struct PRESTypePlugin *HelloWorldPlugin_new(void) 
{ 
    struct PRESTypePlugin *plugin = NULL;
    const struct PRESTypePluginVersion PLUGIN_VERSION = 
        PRES_TYPE_PLUGIN_VERSION_2_0;

    ZHOsapiHeap_allocateStructure(
        &plugin, struct PRESTypePlugin);
    if (plugin == NULL) {
       return NULL;
    }

    plugin->version = PLUGIN_VERSION;

    plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        HelloWorldPlugin_on_participant_attached;
    plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        HelloWorldPlugin_on_participant_detached;
    plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        HelloWorldPlugin_on_endpoint_attached;
    plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        HelloWorldPlugin_on_endpoint_detached;

    plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        HelloWorldPlugin_copy_sample;
    plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        HelloWorldPlugin_create_sample;
    plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        HelloWorldPlugin_destroy_sample;

    plugin->serializeFnc =
        (PRESTypePluginSerializeFunction)
        HelloWorldPlugin_serialize;
    plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction)
        HelloWorldPlugin_deserialize;
    plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        HelloWorldPlugin_get_serialized_sample_max_size;
    plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        HelloWorldPlugin_get_serialized_sample_min_size;

    plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        HelloWorldPlugin_get_sample;
    plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        HelloWorldPlugin_return_sample;

    plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        HelloWorldPlugin_get_key_kind;


    
    plugin->serializeKeyFnc = NULL;
    plugin->deserializeKeyFnc = NULL;
    plugin->getKeyFnc = NULL;
    plugin->returnKeyFnc = NULL;
    plugin->instanceToKeyFnc = NULL;
    plugin->keyToInstanceFnc = NULL;
    plugin->getSerializedKeyMaxSizeFnc = NULL;
    plugin->instanceToKeyHashFnc = NULL;
    plugin->serializedSampleToKeyHashFnc = NULL;
    plugin->serializedKeyToKeyHashFnc = NULL;
    
    plugin->typeCode =  (struct ZHCdrTypeCode *)HelloWorld_get_typecode();
    
    plugin->languageKind = PRES_TYPEPLUGIN_DDS_TYPE; 

    plugin->getBuffer = 
        (PRESTypePluginGetBufferFunction)
        HelloWorldPlugin_get_buffer;
    plugin->returnBuffer = 
        (PRESTypePluginReturnBufferFunction)
        HelloWorldPlugin_return_buffer;
    plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        HelloWorldPlugin_get_serialized_sample_size;

    plugin->endpointTypeName = HelloWorldTYPENAME;

    return plugin;
}

void
HelloWorldPlugin_delete(struct PRESTypePlugin *plugin)
{
    ZHOsapiHeap_freeStructure(plugin);
} 
