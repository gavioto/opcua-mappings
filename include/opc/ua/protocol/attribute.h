/// @author Alexander Rykovanov 2012
/// @email rykovanov.as@gmail.com
/// @brief Opc Ua Binary. Attributes service.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///

#ifndef __OPC_UA_BINARY_ATTRIBUTES_H__
#define __OPC_UA_BINARY_ATTRIBUTES_H__

#include <opc/ua/attribute_ids.h>
#include <opc/ua/protocol/data_value.h>
#include <opc/ua/protocol/types.h>
#include <opc/ua/protocol/variant.h>
#include <opc/ua/node_classes.h>

namespace OpcUa
{
  struct NodeAttributesIds
  {
    static const uint16_t ObjectAttr = 354;
    static const uint16_t VariableAttr = 357;
    static const uint16_t MethodAttr = 360;
    static const uint16_t ObjectTypeAttr = 363;
    static const uint16_t VariableTypeAttr = 366 ;
    static const uint16_t ReferenceTypeAttr = 369;
    static const uint16_t DataTypeAttr = 372;
    static const uint16_t ViewAttr = 375;
  };

  struct AttributeValueID
  {
    NodeID Node;
    AttributeID Attribute;
    std::string IndexRange;
    QualifiedName DataEncoding;

    AttributeValueID();
  };

  struct ReadParameters
  {
    Duration MaxAge;
    TimestampsToReturn TimestampsType;
    std::vector<AttributeValueID> AttributesToRead;

    ReadParameters();
  };

  struct ReadRequest
  {
    NodeID TypeID;
    RequestHeader Header;
    ReadParameters Parameters;

    ReadRequest();
  };

  struct ReadResult
  {
    std::vector<DataValue> Results;
    DiagnosticInfoList Diagnostics;
  };


  struct ReadResponse
  {
    NodeID TypeID;
    ResponseHeader Header;
    ReadResult Result;

    ReadResponse();
  };


  struct WriteValue
  {
    NodeID Node;
    AttributeID Attribute;
    std::string NumericRange;
    DataValue Data;
  };

  struct WriteParameters
  {
    std::vector<WriteValue> NodesToWrite;
  };

  struct WriteRequest
  {
    NodeID TypeID;
    RequestHeader Header;
    WriteParameters Parameters;

    WriteRequest();
  };

  struct WriteResult
  {
    std::vector<StatusCode> StatusCodes;
    DiagnosticInfoList Diagnostics;
  };

  struct WriteResponse
  {
    NodeID TypeID;
    ResponseHeader Header;
    WriteResult Result;

    WriteResponse();
  };


  /*
   * AaddNode Message definition
   * FIXME: To be finished

  */

  struct ObjectAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    uint8_t EventNotifier;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct VariableAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    DataValue Value;
    NodeID Type;
    int32_t Rank;
    std::vector<uint32_t> Dimensions;
    uint32_t AccessLevel;
    uint32_t UserAccessLevel;
    Duration MinimumSamplingInterval;
    bool Historizing;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct MethodAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    bool Executable;
    bool UserExecutable;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct ObjectTypeAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    bool IsAbstract;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct VariableTypeAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    DataValue Value;
    NodeID Type;
    int32_t Rank;
    std::vector<uint32_t> Dimensions;
    bool IsAbstract;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct ReferenceTypeAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    bool IsAbstract;
    bool Symmetric;
    LocalizedText InverseName;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct DataTypeAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    bool IsAbstract;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };

  struct ViewAttributes
  {
    uint32_t Attributes;
    LocalizedText DisplayName;
    LocalizedText Description;
    bool ContainsNoLoops;
    uint32_t WriteMask;
    uint32_t UserWriteMask;
  };


  struct NodeAttributes
  {
    ExtensionObjectHeader Header;
    ObjectAttributes ObjectAttr;
    VariableAttributes VariableAttr;
    MethodAttributes MethodAttr;
    ObjectTypeAttributes ObjectTypeAttr;
    VariableTypeAttributes VariableTypeAttr;
    ReferenceTypeAttributes ReferenceTypeAttr;
    DataTypeAttributes DataTypeAttr;
    ViewAttributes ViewAttr;

    NodeAttributes(){}
    NodeAttributes(ObjectAttributes);
    NodeAttributes(VariableAttributes);
    NodeAttributes(MethodAttributes);
    NodeAttributes(ObjectTypeAttributes);
    NodeAttributes(VariableTypeAttributes);
    NodeAttributes(ReferenceTypeAttributes);
    NodeAttributes(DataTypeAttributes);
    NodeAttributes(ViewAttributes);

  };

  struct AddNodesItem
  {
    NodeID ParentNodeId;
    NodeID ReferenceTypeId;
    NodeID RequestedNewNodeID;
    QualifiedName BrowseName;
    NodeClass Class;
    NodeAttributes Attributes;
    NodeID TypeDefinition;

  };

  struct AddNodesRequest
  {
    RequestHeader Header;
    std::vector<AddNodesItem> NodesToAdd;
  };

  struct AddNodesResult
  {
    StatusCode Status;
    NodeID AddedNodeID;
  };

  struct AddNodesResponse
  {
    ResponseHeader Header;
    std::vector<AddNodesResult> results;
    DiagnosticInfoList Diagnostics;
  };


} // namespace OpcUa

#endif // __OPC_UA_BINARY_ATTRIBUTES_H__
