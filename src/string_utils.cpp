/******************************************************************************
 *   Copyright (C) 2013-2014 by Alexander Rykovanov                        *
 *   rykovanov.as@gmail.com                                                   *
 *                                                                            *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License as           *
 *   published by the Free Software Foundation; version 3 of the License.     *
 *                                                                            *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU Lesser General Public License for more details.                      *
 *                                                                            *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 ******************************************************************************/

#include <opc/ua/string_utils.h>
#include <sstream>


OpcUa::String OpcUa::ToString(const OpcUa::NodeID& id)
{
  std::ostringstream os;
  os << "NodeID(" ;
  OpcUa::NodeIDEncoding encoding = static_cast<OpcUa::NodeIDEncoding>(id.Encoding & OpcUa::NodeIDEncoding::EV_VALUE_MASK);

  switch (encoding)
  {
    case OpcUa::NodeIDEncoding::EV_TWO_BYTE:
    {
      os << (unsigned)id.TwoByteData.Identifier ;
      break;
    }

    case OpcUa::NodeIDEncoding::EV_FOUR_BYTE:
    {
      os << (unsigned)id.FourByteData.NamespaceIndex << ":" << (unsigned)id.FourByteData.Identifier ;
      break;
    }

    case OpcUa::NodeIDEncoding::EV_NUMERIC:
    {
      os << (unsigned)id.NumericData.NamespaceIndex << ":" << (unsigned)id.NumericData.Identifier ;
      break;
    }
#ifndef __ENABLE_EMBEDDED_PROFILE__
    case OpcUa::NodeIDEncoding::EV_STRING:
    {
      os << (unsigned)id.StringData.NamespaceIndex << ":" << id.StringData.Identifier.c_str();
      break;
    }

    case OpcUa::NodeIDEncoding::EV_BYTE_STRING:
    {
      os << (unsigned)id.BinaryData.NamespaceIndex << ":";
      for (auto val : id.BinaryData.Identifier) {os << (unsigned)val; }
      break;
    }

    case OpcUa::NodeIDEncoding::EV_GUID:
    {
      os << (unsigned)id.GuidData.NamespaceIndex ;
      const OpcUa::Guid& guid = id.GuidData.Identifier;
      os << ":" << std::hex << guid.Data1 << "-" << guid.Data2 << "-" << guid.Data3;
      for (auto val : guid.Data4) {os << (unsigned)val; }
      break;
    }
#endif
    default:
    {
      os << "unknown id type:" << (unsigned)encoding ;
      break;
    }
  }
  os << ")";
  return String(os.str().c_str());
}

OpcUa::String OpcUa::ToString(const OpcUa::Guid& guid)
{
  char buf[36] = {0};
  sprintf(buf, "%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
  return String(buf);
}

OpcUa::Guid OpcUa::ToGuid(const OpcUa::String& str)
{
  if (str.size() != 35)
  {
    return OpcUa::Guid();
  }
  Guid guid;

  unsigned data1 = 0;
  unsigned data2 = 0;
  unsigned data3 = 0;
  unsigned data4 = 0;
  unsigned data5 = 0;
  unsigned data6 = 0;
  unsigned data7 = 0;
  unsigned data8 = 0;
  unsigned data9 = 0;
  unsigned data10 = 0;
  unsigned data11 = 0;
  const int parts = sscanf(str.c_str(), "%08X-%04X-%04X-%02X%02X%02X%02X%02X%02X%02X%02X",
      &data1, &data2, &data3, &data4, &data5, &data6, &data7, &data8, &data9, &data10, &data11);

  guid.Data1    = static_cast<uint32_t>(data1);
  guid.Data2    = static_cast<uint16_t>(data2);
  guid.Data3    = static_cast<uint16_t>(data3);
  guid.Data4[0] = static_cast<uint8_t>(data4);
  guid.Data4[1] = static_cast<uint8_t>(data5);
  guid.Data4[2] = static_cast<uint8_t>(data6);
  guid.Data4[3] = static_cast<uint8_t>(data7);
  guid.Data4[4] = static_cast<uint8_t>(data8);
  guid.Data4[5] = static_cast<uint8_t>(data9);
  guid.Data4[6] = static_cast<uint8_t>(data10);
  guid.Data4[7] = static_cast<uint8_t>(data11);

  if (parts != 11)
  {
    return OpcUa::Guid();
  }
  return guid;
}
