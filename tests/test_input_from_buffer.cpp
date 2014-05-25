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

#include <opc/ua/input_from_buffer.h>

#include <gtest/gtest.h>


class InputFromBuffer : public testing::Test
{
protected:
  const std::vector<char> SourceBuffer{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};

TEST_F(InputFromBuffer, CanBeCreated)
{
  OpcUa::InputFromBuffer input(&SourceBuffer[0], SourceBuffer.size());
}

TEST_F(InputFromBuffer, ThrowsIfNullBuffer)
{
  ASSERT_THROW(OpcUa::InputFromBuffer(nullptr, 100500), std::invalid_argument);
}

TEST_F(InputFromBuffer, ThrowsIfZeroSize)
{
  ASSERT_THROW(OpcUa::InputFromBuffer((char*)1, 0), std::invalid_argument);
}

TEST_F(InputFromBuffer, ReadReturnsZeroWhenReadZero)
{
  OpcUa::InputFromBuffer input(&SourceBuffer[0], SourceBuffer.size());

  std::vector<char> targetBuf{9,8,7};
  std::vector<char> expectedBuf{9,8,7};
  const size_t sizeToRead = 0;

  ASSERT_EQ(input.Receive(&targetBuf[0], sizeToRead), 0);
  ASSERT_EQ(targetBuf, expectedBuf);
}

TEST_F(InputFromBuffer, ReadSmallBuffer)
{
  OpcUa::InputFromBuffer input(&SourceBuffer[0], SourceBuffer.size());

  std::vector<char> targetBuf{9,8,7};
  const std::vector<char> expectedBuf{0, 1, 2};
  size_t revceivedSize = 0;
  ASSERT_NO_THROW(revceivedSize = input.Receive(&targetBuf[0], 3));
  ASSERT_EQ(revceivedSize, 3);
  ASSERT_EQ(targetBuf, expectedBuf);
}

TEST_F(InputFromBuffer, ReadLargeBuffer)
{
  OpcUa::InputFromBuffer input(&SourceBuffer[0], SourceBuffer.size());

  const std::vector<char> expectedBuf{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11};
  std::vector<char> targetBuf(11, 11);
  size_t revceivedSize = 0;
  ASSERT_NO_THROW(revceivedSize = input.Receive(&targetBuf[0], targetBuf.size()));
  ASSERT_EQ(revceivedSize, SourceBuffer.size());
  ASSERT_EQ(targetBuf, expectedBuf);
}
