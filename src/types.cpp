/******************************************************************************
 *   Copyright (C) 2014-2014 Olivier Roulet-Dubonnet          *
 *   olivier.roulet@gmail.com          *
 *                      *
 *   This library is free software; you can redistribute it and/or modify   *
 *   it under the terms of the GNU Lesser General Public License as      *
 *   published by the Free Software Foundation; version 3 of the License.   *
 *                      *
 *   This library is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of      *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the      *
 *   GNU Lesser General Public License for more details.        *
 *                      *
 *   You should have received a copy of the GNU Lesser General Public License *
 *   along with this library; if not, write to the          *
 *   Free Software Foundation, Inc.,              *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.        *
 ******************************************************************************/

#include<opc/ua/protocol/types.h>

namespace OpcUa
{
  OpcUa::QualifiedName OpcUa::QualifiedName::ParseFromString(const std::string& str, uint16_t default_ns)
{
  std::size_t found = str.find(":");
  if (found != std::string::npos)
  {
    uint16_t ns = std::stoi(str.substr(0, found));
    std::string name = str.substr(found+1, str.length() - found);
    return QualifiedName(ns, name);
  }

  return QualifiedName(default_ns, str);
}

}
