// @author Alexander Rykovanov 2012
/// @email rykovanov.as@gmail.com
/// @brief Opc Ua binary session services.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at 
/// http://www.gnu.org/licenses/lgpl.html)
///

#include "binary_serialization.h"

#include <opc/ua/protocol/binary/stream.h>
#include <opc/ua/protocol/types.h>
#include <opc/ua/protocol/attribute.h>
#include <opc/ua/attribute_ids.h>

#include <algorithm>
#include <memory>
#include <string>

namespace OpcUa
{
  // TODO move to appropriate file
  AttributeValueID::AttributeValueID()
    : Attribute(AttributeID::VALUE)
  {
  }

  ReadParameters::ReadParameters()
    : MaxAge(0)
    , TimestampsType(TimestampsToReturn::NEITHER)
  {

  }

  ReadRequest::ReadRequest()
    : TypeID(READ_REQUEST)
  {
  }


  ReadResponse::ReadResponse()
    : TypeID(READ_RESPONSE)
  {
  }


  WriteRequest::WriteRequest()
    : TypeID(WRITE_REQUEST)
  {
  }


  WriteResponse::WriteResponse()
    : TypeID(WRITE_RESPONSE)
  {
  }

  NodeAttributes::NodeAttributes(ObjectAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::ObjectAttr, 0);
    ObjectAttr = attr;
    //Header.Encoding = 
  }
  NodeAttributes::NodeAttributes(VariableAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::VariableAttr, 0);
    VariableAttr = attr;
  }
  NodeAttributes::NodeAttributes(MethodAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::MethodAttr, 0);
    MethodAttr = attr;
  }
  NodeAttributes::NodeAttributes(ObjectTypeAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::ObjectTypeAttr, 0);
    ObjectTypeAttr = attr;
  }
  NodeAttributes::NodeAttributes(VariableTypeAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::VariableTypeAttr, 0);
    VariableTypeAttr = attr;
  }
  NodeAttributes::NodeAttributes(ReferenceTypeAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::ReferenceTypeAttr, 0);
    ReferenceTypeAttr = attr;
  }
  NodeAttributes::NodeAttributes(DataTypeAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::DataTypeAttr, 0);
    DataTypeAttr = attr;
  }
  NodeAttributes::NodeAttributes(ViewAttributes attr)
  {
    Header.TypeID = FourByteNodeID(NodeAttributesIds::ViewAttr, 0);
    ViewAttr = attr;
  }



  namespace Binary
  {

    template<> 
    std::size_t RawSize<AttributeID>(const AttributeID&)
    {
      return 4;
    }

    template<>
    void DataSerializer::Serialize<AttributeID>(const AttributeID& attr)
    {
      *this << static_cast<uint32_t>(attr);
    }

    template<>
    void DataDeserializer::Deserialize<AttributeID>(AttributeID& t)
    {
      uint32_t tmp = 0;
      *this >> tmp;
      t = static_cast<AttributeID>(tmp);
    }


    //---------------------------------------------------
    // TimestampsToReturn
    //---------------------------------------------------


    template<> 
    std::size_t RawSize<TimestampsToReturn>(const TimestampsToReturn&)
    {
      return 4;
    }

    template<>
    void DataSerializer::Serialize<TimestampsToReturn>(const TimestampsToReturn& t)
    {
      *this << static_cast<uint32_t>(t);
    }

    template<>
    void DataDeserializer::Deserialize<TimestampsToReturn>(TimestampsToReturn& t)
    {
      uint32_t tmp = 0;
      *this >> tmp;
      t = static_cast<TimestampsToReturn>(tmp);
    }
    //---------------------------------------------------
    // AttributeValueID
    //---------------------------------------------------

    template<>
    std::size_t RawSize<AttributeValueID>(const AttributeValueID& attr)
    {
      return RawSize(attr.Node) + RawSize(attr.Attribute) + RawSize(attr.IndexRange) + RawSize(attr.DataEncoding);
    }

    template<>
    void DataSerializer::Serialize<AttributeValueID>(const AttributeValueID& attr)
    {
      *this << attr.Node;
      *this << attr.Attribute;
      *this << attr.IndexRange;
      *this << attr.DataEncoding;
    }

    template<>
    void DataDeserializer::Deserialize<AttributeValueID>(AttributeValueID& attr)
    {
      *this >> attr.Node;
      *this >> attr.Attribute;
      *this >> attr.IndexRange;
      *this >> attr.DataEncoding;
    }

    //---------------------------------------------------
    // ReadParameters
    //---------------------------------------------------

    template<>
    std::size_t RawSize<ReadParameters>(const ReadParameters& params)
    {
      return RawSize(params.MaxAge) +
        RawSize(params.TimestampsType) +
        RawSizeContainer(params.AttributesToRead);
    }

    template<>
    void DataSerializer::Serialize<ReadParameters>(const ReadParameters& params)
    {
      *this << params.MaxAge;
      *this << params.TimestampsType;
      SerializeContainer(*this, params.AttributesToRead);
    }

    template<>
    void DataDeserializer::Deserialize<ReadParameters>(ReadParameters& params)
    {
      *this >> params.MaxAge;
      *this >> params.TimestampsType;
      DeserializeContainer(*this, params.AttributesToRead);
    }

    //---------------------------------------------------
    // ReadRequest
    //---------------------------------------------------

    template<>
    std::size_t RawSize<ReadRequest>(const ReadRequest& request)
    {
      return RawSize(request.TypeID) + RawSize(request.Header) + RawSize(request.Parameters);
    }

    template<>
    void DataSerializer::Serialize<ReadRequest>(const ReadRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    template<>
    void DataDeserializer::Deserialize<ReadRequest>(ReadRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    //---------------------------------------------------
    // ReadResult
    //---------------------------------------------------
    template<>
    std::size_t RawSize<ReadResult>(const ReadResult& result)
    {
      return RawSizeContainer(result.Results) +
        RawSizeContainer(result.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<ReadResult>(const ReadResult& result)
    {
      SerializeContainer(*this, result.Results, 0);
      SerializeContainer(*this, result.Diagnostics, 0);
    }

    template<>
    void DataDeserializer::Deserialize<ReadResult>(ReadResult& result)
    {
      DeserializeContainer(*this, result.Results);
      DeserializeContainer(*this, result.Diagnostics);
    }


    //---------------------------------------------------
    // ReadResponse
    //---------------------------------------------------
    template<>
    std::size_t RawSize<ReadResponse>(const ReadResponse& resp)
    {
      return RawSize(resp.TypeID) + RawSize(resp.Header) + RawSize(resp.Result);
    }

    template<>
    void DataSerializer::Serialize<ReadResponse>(const ReadResponse& resp)
    {
      *this << resp.TypeID;
      *this << resp.Header;
      *this << resp.Result;
    }

    template<>
    void DataDeserializer::Deserialize<ReadResponse>(ReadResponse& resp)
    {
      *this >> resp.TypeID;
      *this >> resp.Header;
      *this >> resp.Result;
    }

    //---------------------------------------------------
    // WriteValue
    //---------------------------------------------------

    template<>
    std::size_t RawSize<WriteValue>(const WriteValue& val)
    {
        return RawSize(val.Node) +
        RawSize(val.Attribute) +
        RawSize(val.NumericRange) +
        RawSize(val.Data);
    }

    template<>
    void DataSerializer::Serialize<WriteValue>(const WriteValue& val)
    {
      *this << val.Node;
      *this << val.Attribute;
      *this << val.NumericRange;
      *this << val.Data;
    }

    template<>
    void DataDeserializer::Deserialize<WriteValue>(WriteValue& val)
    {
      *this >> val.Node;
      *this >> val.Attribute;
      *this >> val.NumericRange;
      *this >> val.Data;
    }


    //---------------------------------------------------
    // WriteParameters
    //---------------------------------------------------
    template<>
    std::size_t RawSize<WriteParameters>(const WriteParameters& parameters)
    {
      return RawSizeContainer(parameters.NodesToWrite);
    }

    template<>
    void DataSerializer::Serialize<WriteParameters>(const WriteParameters& parameters)
    {
      SerializeContainer(*this, parameters.NodesToWrite);
    }

    template<>
    void DataDeserializer::Deserialize<WriteParameters>(WriteParameters& parameters)
    {
      DeserializeContainer(*this, parameters.NodesToWrite);
    }


    //---------------------------------------------------
    // WriteRequest
    //---------------------------------------------------
    template<>
    std::size_t RawSize<WriteRequest>(const WriteRequest& request)
    {
      return RawSize(request.TypeID) + RawSize(request.Header) + RawSize(request.Parameters);
    }

    template<>
    void DataSerializer::Serialize<WriteRequest>(const WriteRequest& request)
    {
      *this << request.TypeID;
      *this << request.Header;
      *this << request.Parameters;
    }

    template<>
    void DataDeserializer::Deserialize<WriteRequest>(WriteRequest& request)
    {
      *this >> request.TypeID;
      *this >> request.Header;
      *this >> request.Parameters;
    }

    //---------------------------------------------------
    // WriteResult
    //---------------------------------------------------
    template<>
    std::size_t RawSize<WriteResult>(const WriteResult& result)
    {
      return RawSizeContainer(result.StatusCodes) + RawSizeContainer(result.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<WriteResult>(const WriteResult& result)
    {
      SerializeContainer(*this, result.StatusCodes, 0);
      SerializeContainer(*this, result.Diagnostics, 0);
    }

    template<>
    void DataDeserializer::Deserialize<WriteResult>(WriteResult& result)
    {
      DeserializeContainer(*this, result.StatusCodes);
      DeserializeContainer(*this, result.Diagnostics);
    }

    //---------------------------------------------------
    // WriteResponse
    //---------------------------------------------------
    template<>
    std::size_t RawSize<WriteResponse>(const WriteResponse& resp)
    {
      return RawSize(resp.TypeID) + RawSize(resp.Header) + RawSize(resp.Result);
    }

    template<>
    void DataSerializer::Serialize<WriteResponse>(const WriteResponse& resp)
    {
      *this << resp.TypeID;
      *this << resp.Header;
      *this << resp.Result;
    }

    template<>
    void DataDeserializer::Deserialize<WriteResponse>(WriteResponse& resp)
    {
      *this >> resp.TypeID;
      *this >> resp.Header;
      *this >> resp.Result;
    }

    //
    //AddNodeRequest
    //

    template<>
    std::size_t RawSize<ObjectAttributes>(const ObjectAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.EventNotifier) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<ObjectAttributes>(const ObjectAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.EventNotifier;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<ObjectAttributes>(ObjectAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.EventNotifier;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }

    template<>
    std::size_t RawSize<VariableAttributes>(const VariableAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.Value) + 
        RawSize(val.Type) + 
        RawSize(val.Rank) + 
        RawSizeContainer(val.Dimensions) + 
        RawSize(val.AccessLevel) + 
        RawSize(val.UserAccessLevel) + 
        RawSize(val.MinimumSamplingInterval) + 
        RawSize(val.Historizing) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<VariableAttributes>(const VariableAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.Value;
      *this << val.Type;
      *this << val.Rank;
      *this << val.Dimensions;
      *this << val.AccessLevel;
      *this << val.UserAccessLevel;
      *this << val.MinimumSamplingInterval;
      *this << val.Historizing;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<VariableAttributes>(VariableAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.Value;
      *this >> val.Type;
      *this >> val.Rank;
      *this >> val.Dimensions;
      *this >> val.AccessLevel;
      *this >> val.UserAccessLevel;
      *this >> val.MinimumSamplingInterval;
      *this >> val.Historizing;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }


    template<>
    std::size_t RawSize<MethodAttributes>(const MethodAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.Executable) + 
        RawSize(val.UserExecutable) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<MethodAttributes>(const MethodAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.Executable;
      *this << val.UserExecutable;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<MethodAttributes>(MethodAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.Executable;
      *this >> val.UserExecutable;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }

    template<>
    std::size_t RawSize<ObjectTypeAttributes>(const ObjectTypeAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.IsAbstract) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<ObjectTypeAttributes>(const ObjectTypeAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.IsAbstract;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<ObjectTypeAttributes>(ObjectTypeAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.IsAbstract;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }


    template<>
    std::size_t RawSize<VariableTypeAttributes>(const VariableTypeAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.Value) + 
        RawSize(val.Type) + 
        RawSize(val.Rank) + 
        RawSizeContainer(val.Dimensions) + 
        RawSize(val.IsAbstract) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<VariableTypeAttributes>(const VariableTypeAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.Value;
      *this << val.Type;
      *this << val.Rank;
      *this << val.Dimensions;
      *this << val.IsAbstract;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<VariableTypeAttributes>(VariableTypeAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.Value;
      *this >> val.Type;
      *this >> val.Rank;
      *this >> val.Dimensions;
      *this >> val.IsAbstract;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }


    template<>
    std::size_t RawSize<ReferenceTypeAttributes>(const ReferenceTypeAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.IsAbstract) + 
        RawSize(val.Symmetric) + 
        RawSize(val.InverseName) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<ReferenceTypeAttributes>(const ReferenceTypeAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.IsAbstract;
      *this << val.Symmetric;
      *this << val.InverseName;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<ReferenceTypeAttributes>(ReferenceTypeAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.IsAbstract;
      *this >> val.Symmetric;
      *this >> val.InverseName;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }


    template<>
    std::size_t RawSize<DataTypeAttributes>(const DataTypeAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.IsAbstract) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<DataTypeAttributes>(const DataTypeAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.IsAbstract;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<DataTypeAttributes>(DataTypeAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.IsAbstract;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }

    template<>
    std::size_t RawSize<ViewAttributes>(const ViewAttributes& val)
    {
      return RawSize(val.Attributes) + 
        RawSize(val.DisplayName) + 
        RawSize(val.Description) + 
        RawSize(val.ContainsNoLoops) + 
        RawSize(val.WriteMask) + 
        RawSize(val.UserWriteMask)
        ;
    }

    template<>
    void DataSerializer::Serialize<ViewAttributes>(const ViewAttributes& val)
    {
      *this << val.Attributes;
      *this << val.DisplayName;
      *this << val.Description;
      *this << val.ContainsNoLoops;
      *this << val.WriteMask;
      *this << val.UserWriteMask;
    }

    template<>
    void DataDeserializer::Deserialize<ViewAttributes>(ViewAttributes& val)
    {
      *this >> val.Attributes;
      *this >> val.DisplayName;
      *this >> val.Description;
      *this >> val.ContainsNoLoops;
      *this >> val.WriteMask;
      *this >> val.UserWriteMask;
    }




    template<>
    std::size_t RawSize<NodeAttributes>(const NodeAttributes& val)
    {
      size_t total = 0;
      total += RawSize(val.Header);
      if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectAttr, 0))
      {
        total += RawSize(val.ObjectAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableAttr, 0))
      {
        total += RawSize(val.VariableAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::MethodAttr, 0))
      {
        total += RawSize(val.MethodAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectTypeAttr, 0))
      {
        total += RawSize(val.ObjectTypeAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableTypeAttr, 0))
      {
        total += RawSize(val.VariableTypeAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ReferenceTypeAttr, 0))
      {
        total += RawSize(val.ReferenceTypeAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::DataTypeAttr, 0))
      {
        total += RawSize(val.DataTypeAttr);
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ViewAttr, 0))
      {
        total += RawSize(val.ViewAttr);
      }
      return total;
    }

    template<>
    void DataSerializer::Serialize<NodeAttributes>(const NodeAttributes& val)
    {
      *this << val.Header;
      if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectAttr, 0))
      {
        *this << val.ObjectAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableAttr, 0))
      {
        *this << val.VariableAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::MethodAttr, 0))
      {
        *this << val.MethodAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectTypeAttr, 0))
      {
        *this << val.ObjectTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableTypeAttr, 0))
      {
        *this << val.VariableTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ReferenceTypeAttr, 0))
      {
        *this << val.ReferenceTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::DataTypeAttr, 0))
      {
        *this << val.DataTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ViewAttr, 0))
      {
        *this << val.ViewAttr;
      }
    }

    template<>
    void DataDeserializer::Deserialize<NodeAttributes>(NodeAttributes& val)
    {
      *this >> val.Header;
      if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectAttr, 0))
      {
        *this >> val.ObjectAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableAttr, 0))
      {
        *this >> val.VariableAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::MethodAttr, 0))
      {
        *this >> val.MethodAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ObjectTypeAttr, 0))
      {
        *this >> val.ObjectTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::VariableTypeAttr, 0))
      {
        *this >> val.VariableTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ReferenceTypeAttr, 0))
      {
        *this >> val.ReferenceTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::DataTypeAttr, 0))
      {
        *this >> val.DataTypeAttr;
      }
      else if (val.Header.TypeID == FourByteNodeID(NodeAttributesIds::ViewAttr, 0))
      {
        *this >> val.ViewAttr;
      }
    }

    template<>
    std::size_t RawSize<AddNodesItem>(const AddNodesItem& resp)
    {
      return RawSize(resp.ParentNodeId) + 
        RawSize(resp.ReferenceTypeId) +
        RawSize(resp.RequestedNewNodeID) +
        RawSize(resp.BrowseName) +
        RawSize(resp.Class) +
        RawSize(resp.Attributes) +
        RawSize(resp.TypeDefinition);
    }

    template<>
    void DataSerializer::Serialize<AddNodesItem>(const AddNodesItem& resp)
    {
      *this << resp.ParentNodeId;
      *this << resp.ReferenceTypeId;
      *this << resp.RequestedNewNodeID;
      *this << resp.BrowseName;
      *this << resp.Class;
      *this << resp.Attributes;
      *this << resp.TypeDefinition;
    }

    template<>
    void DataDeserializer::Deserialize<AddNodesItem>(AddNodesItem& resp)
    {
      *this >> resp.ParentNodeId;
      *this >> resp.ReferenceTypeId;
      *this >> resp.RequestedNewNodeID;
      *this >> resp.BrowseName;
      *this >> resp.Class;
      *this >> resp.Attributes;
      *this >> resp.TypeDefinition;
    }


    template<>
    void DataDeserializer::Deserialize<std::vector<AddNodesItem>>(std::vector<AddNodesItem>& ack)
    {
      DeserializeContainer(*this, ack);
    }

    template<>
    void DataSerializer::Serialize<std::vector<AddNodesItem>>(const std::vector<AddNodesItem>& ack)
    {
      SerializeContainer(*this, ack);
    }



    template<>
    std::size_t RawSize<AddNodesRequest>(const AddNodesRequest& resp)
    {
      return RawSize(resp.Header) + RawSizeContainer(resp.NodesToAdd);
    }

    template<>
    void DataSerializer::Serialize<AddNodesRequest>(const AddNodesRequest& resp)
    {
      *this << resp.Header;
      *this << resp.NodesToAdd;
    }

    template<>
    void DataDeserializer::Deserialize<AddNodesRequest>(AddNodesRequest& resp)
    {
      *this >> resp.Header;
      *this >> resp.NodesToAdd;
    }

    template<>
    std::size_t RawSize<AddNodesResult>(const AddNodesResult& resp)
    {
      return RawSize(resp.Status) + RawSize(resp.AddedNodeID);
    }

    template<>
    void DataSerializer::Serialize<AddNodesResult>(const AddNodesResult& resp)
    {
      *this << resp.Status;
      *this << resp.AddedNodeID;
    }

    template<>
    void DataDeserializer::Deserialize<AddNodesResult>(AddNodesResult& resp)
    {
      *this >> resp.Status;
      *this >> resp.AddedNodeID;
    }


    template<>
    void DataDeserializer::Deserialize<std::vector<AddNodesResult>>(std::vector<AddNodesResult>& ack)
    {
      DeserializeContainer(*this, ack);
    }

    template<>
    void DataSerializer::Serialize<std::vector<AddNodesResult>>(const std::vector<AddNodesResult>& ack)
    {
      SerializeContainer(*this, ack);
    }






    template<>
    std::size_t RawSize<AddNodesResponse>(const AddNodesResponse& resp)
    {
      return RawSize(resp.Header) + RawSizeContainer(resp.results) + RawSize(resp.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<AddNodesResponse>(const AddNodesResponse& resp)
    {
      *this << resp.Header;
      *this << resp.results;
      *this << resp.Diagnostics;
    }

    template<>
    void DataDeserializer::Deserialize<AddNodesResponse>(AddNodesResponse& resp)
    {
      *this >> resp.Header;
      *this >> resp.results;
      *this >> resp.Diagnostics;
    }

  
    //
    // AddReferences
    //




    template<>
    std::size_t RawSize<AddReferencesResponse>(const AddReferencesResponse& resp)
    {
      return RawSize(resp.Header) + RawSizeContainer(resp.Results) + RawSize(resp.Diagnostics);
    }

    template<>
    void DataSerializer::Serialize<AddReferencesResponse>(const AddReferencesResponse& resp)
    {
      *this << resp.Header;
      *this << resp.Results;
      *this << resp.Diagnostics;
    }

    template<>
    void DataDeserializer::Deserialize<AddReferencesResponse>(AddReferencesResponse& resp)
    {
      *this >> resp.Header;
      *this >> resp.Results;
      *this >> resp.Diagnostics;
    }

     template<>
    std::size_t RawSize<AddReferencesItem>(const AddReferencesItem& val)
    {
      return RawSize(val.SourceNodeID) + 
        RawSize(val.ReferenceTypeId) + 
        RawSize(val.IsForward) + 
        RawSize(val.TargetServerUri) + 
        RawSize(val.TargetNodeID) + 
        RawSize(val.TargetNodeClass)
        ;
    }

    template<>
    void DataSerializer::Serialize<AddReferencesItem>(const AddReferencesItem& val)
    {
      *this << val.SourceNodeID;
      *this << val.ReferenceTypeId;
      *this << val.IsForward;
      *this << val.TargetServerUri;
      *this << val.TargetNodeID;
      *this << val.TargetNodeClass;
    }

    template<>
    void DataDeserializer::Deserialize<AddReferencesItem>(AddReferencesItem& val)
    {
      *this >> val.SourceNodeID;
      *this >> val.ReferenceTypeId;
      *this >> val.IsForward;
      *this >> val.TargetServerUri;
      *this >> val.TargetNodeID;
      *this >> val.TargetNodeClass;
    }

    template<>
    std::size_t RawSize(const std::vector<AddReferencesItem>& ack)
    {
      return RawSizeContainer(ack);
    }



    template<>
    void DataDeserializer::Deserialize<std::vector<AddReferencesItem>>(std::vector<AddReferencesItem>& ack)
    {
      DeserializeContainer(*this, ack);
    }

    template<>
    void DataSerializer::Serialize<std::vector<AddReferencesItem>>(const std::vector<AddReferencesItem>& ack)
    {
      SerializeContainer(*this, ack);
    }

     template<>
    std::size_t RawSize<AddReferencesRequest>(const AddReferencesRequest& val)
    {
      return RawSize(val.Header) + 
        RawSizeContainer(val.ReferencesToAdd)
        ;
    }

    template<>
    void DataSerializer::Serialize<AddReferencesRequest>(const AddReferencesRequest& val)
    {
      *this << val.Header;
      *this << val.ReferencesToAdd;
    }

    template<>
    void DataDeserializer::Deserialize<AddReferencesRequest>(AddReferencesRequest& val)
    {
      *this >> val.Header;
      *this >> val.ReferencesToAdd;
    }




  } // namespace Binary
} // namespace OpcUa

