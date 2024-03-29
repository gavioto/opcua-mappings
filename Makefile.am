# Author: Alexander Rykovanov 2012
#
# Distributed under the GNU LGPL License
# (See accompanying file LICENSE or copy at 
# http://www.gnu.org/copyleft/gpl.html)
#
# $Id:  $
# $Date: $
# $Revision: $



opcincludedir = $(includedir)/opc
opcuaincludedir = $(opcincludedir)/ua
protocolincludedir = $(opcuaincludedir)/protocol
binaryincludedir = $(protocolincludedir)/binary


binaryinclude_HEADERS = \
  include/opc/ua/protocol/binary/stream.h \
  include/opc/ua/protocol/binary/common.h

protocolinclude_HEADERS = \
  include/opc/ua/protocol/attribute.h \
  include/opc/ua/protocol/data_value.h \
  include/opc/ua/protocol/datetime.h \
  include/opc/ua/protocol/endpoints.h \
  include/opc/ua/protocol/guid.h \
  include/opc/ua/protocol/monitored_items.h \
  include/opc/ua/protocol/nodeid.h \
  include/opc/ua/protocol/secure_channel.h \
  include/opc/ua/protocol/session.h \
  include/opc/ua/protocol/subscriptions.h \
  include/opc/ua/protocol/types.h \
  include/opc/ua/protocol/variant.h \
  include/opc/ua/protocol/view.h

opcuainclude_HEADERS = \
  include/opc/ua/describe.h \
  include/opc/ua/channel.h \
  include/opc/ua/extension_identifiers.h \
  include/opc/ua/attribute_ids.h \
  include/opc/ua/message_identifiers.h \
  include/opc/ua/node_classes.h \
  include/opc/ua/object_ids.h \
  include/opc/ua/expanded_object_ids.h \
  include/opc/ua/reference_ids.h \
  include/opc/ua/strings.h \
  include/opc/ua/status_codes.h \
  include/opc/ua/variable_access_level.h

lib_LTLIBRARIES = libopcuabinary.la

libopcuabinary_la_SOURCES = \
  src/binary_variant.cpp \
  src/binary_stream.cpp \
  src/binary_serialization.h \
  src/binary_attribute.cpp \
  src/binary_data_value.cpp \
  src/binary_endpoints.cpp \
  src/binary_messages.cpp \
  src/binary_raw_size.cpp \
  src/binary_session.cpp \
  src/binary_view.cpp \
  src/input_from_buffer.cpp \
  src/monitored_items.cpp \
  src/nodeid.cpp \
  src/subscriptions.cpp \
  src/types.cpp


libopcuabinary_la_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/../../libopccore/include $(GCOV_FLAGS)
libopcuabinary_la_LDFLAGS = $(GCOV_LIBS)

TESTS = opc_ua_binary_test

check_PROGRAMS = $(TESTS)

opc_ua_binary_test_SOURCES =  \
 tests/binary_deserialize.cpp \
 tests/binary_serialize_variant.cpp \
 tests/binary_serialize.cpp \
 tests/binary_serialize_attribute.cpp \
 tests/binary_serialize_data_value.cpp \
 tests/binary_serialize_endpoints.cpp \
 tests/binary_serialize_monitored_items.cpp \
 tests/binary_serialize_session.cpp \
 tests/binary_serialize_view.cpp \
 tests/binary_subscriptions.cpp \
 tests/common.h \
 tests/message_id.cpp \
 tests/node_id.cpp \
 tests/reference_id.cpp \
 tests/test_input_from_buffer.cpp \
 tests/utils.cpp

opc_ua_binary_test_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include -I$(top_srcdir)/../../libopccore/include $(GTEST_INCLUDES) $(GMOCK_INCLUDES) $(GCOV_FLAGS)
opc_ua_binary_test_LDADD = libopcuabinary.la
opc_ua_binary_test_LDFLAGS = -Wl,-z,defs $(GTEST_LIB) $(GTEST_MAIN_LIB) $(GCOV_LIBS) -lpthread 

pkgsharedir = $(libdir)/pkgconfig
pkgshare_DATA = libopcuabinary.pc

pkgconfigdir = $(datarootdir)/pkgconfig
pkgconfig_DATA = libopcuabinary.pc

EXTRA_DIST = debian make_deb.sh

clean-local:
	rm -rvf opcuamappings*$(VERSION)* *.gcov *.gcno *.gcda

dist-deb: dist
	VERSION=$(VERSION) $(top_srcdir)/make_deb.sh

