# Copyright (c) 2013-2016 The Dealtoken Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(ERROR_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

BITCOIN_CONFIG_INCLUDES=-I$(builddir)/config
BITCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

LIBDEALTOKEN_SERVER=libDealtoken_server.a
LIBDEALTOKEN_COMMON=libDealtoken_common.a
LIBDEALTOKEN_CLI=libDealtoken_cli.a
LIBDEALTOKENQT=qt/libDealtokenqt.a
if ENABLE_WALLET
LIBDEALTOKEN_WALLET=libDealtoken_wallet.a
endif

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBDEALTOKEN_COMMON) \
  $(LIBDEALTOKEN_SERVER) \
  $(LIBDEALTOKEN_CLI) \
  $(LIBDEALTOKEN_WALLET) 

bin_PROGRAMS =
noinst_LIBRARIES = 
noinst_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_BITCOIND
  bin_PROGRAMS += Dealtokend
endif

if BUILD_BITCOIN_UTILS
  bin_PROGRAMS += Dealtoken-cli
endif

.PHONY: FORCE
# Dealtoken core #
BITCOIN_CORE_H = \
  addrman.h \
  alert.h \
  allocators.h \
  base58.h \
  bignum.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  bloom.h \
  checkpoints.h \
  checkpointsync.h \
  checkqueue.h \
  clientversion.h \
  compat.h \
  crypter.h \
  db.h \
  hash.h \
  init.h \
  key.h \
  kernel.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  mruset.h \
  netbase.h \
  net.h \
  protocol.h \
  script.h \
  serialize.h \
  sync.h \
  threadsafety.h \
  txdb.h \
  ui_interface.h \
  uint256.h \
  util.h \
  version.h \
  walletdb.h \
  wallet.h

JSON_H = \
  json/json_spirit.h \
  json/json_spirit_error_position.h \
  json/json_spirit_reader.h \
  json/json_spirit_reader_template.h \
  json/json_spirit_stream_reader.h \
  json/json_spirit_utils.h \
  json/json_spirit_value.h \
  json/json_spirit_writer.h \
  json/json_spirit_writer_template.h 

obj/build.h: FORCE
	@$(MKDIR_P) $(abs_top_builddir)/src/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libDealtoken_common_a-version.$(OBJEXT): obj/build.h

# server: shared between Dealtokend and Dealtoken-qt
libDealtoken_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libDealtoken_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libDealtoken_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  rpcserver.cpp \
  bloom.cpp \
  checkpoints.cpp \
  checkpointsync.cpp \
  crypter.cpp \
  init.cpp \
  kernel.cpp \
  keystore.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  net.cpp \
  noui.cpp \
  rpcblockchain.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  txdb.cpp \
  $(JSON_H) \
  $(BITCOIN_CORE_H)

# wallet: shared between Dealtokend and Dealtoken-qt, but only linked
# when wallet enabled  
libDealtoken_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libDealtoken_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)  
libDealtoken_wallet_a_SOURCES = \
  db.cpp \
  rpcdump.cpp \
  rpcmining.cpp \
  rpcminting.cpp \
  script.cpp \
  kernelrecord.cpp \
  wallet.cpp \
  walletdb.cpp \
  rpcwallet.cpp \
  $(BITCOIN_CORE_H)


# common: shared between Dealtokend, and Dealtoken-qt and non-server tools
libDealtoken_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libDealtoken_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)  
libDealtoken_common_a_SOURCES = \
  hash.cpp \
  key.cpp \
  netbase.cpp \
  protocol.cpp \
  rpcprotocol.cpp \
  sync.cpp \
  util.cpp \
  version.cpp \
  $(BITCOIN_CORE_H)


# cli: shared between Dealtoken-cli and Dealtoken-qt
libDealtoken_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
libDealtoken_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)  
libDealtoken_cli_a_SOURCES = \
  rpcclient.cpp \
  $(BITCOIN_CORE_H)

nodist_libDealtoken_common_a_SOURCES = $(top_srcdir)/src/obj/build.h
#

# Dealtokend binary #
Dealtokend_SOURCES = Dealtokend.cpp
Dealtokend_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES)
Dealtokend_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
Dealtokend_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
Dealtokend_SOURCES += Dealtokend-res.rc
endif

Dealtokend_LDADD = \
  $(LIBDEALTOKEN_SERVER) \
  $(LIBDEALTOKEN_COMMON) \
  $(LIBDEALTOKEN_WALLET) \
  $(LIBDEALTOKEN_CLI) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) 

Dealtokend_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# Dealtoken-cli binary #
Dealtoken_cli_SOURCES = Dealtoken-cli.cpp
Dealtoken_cli_CPPFLAGS = $(AM_CPPFLAGS) $(BITCOIN_INCLUDES) $(EVENT_CFLAGS)
Dealtoken_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
Dealtoken_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
Dealtoken_cli_SOURCES += Dealtoken-cli-res.rc
endif

Dealtoken_cli_LDADD = \
  $(LIBDEALTOKEN_CLI) \
  $(LIBDEALTOKEN_COMMON)

Dealtoken_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)


CLEANFILES = $(EXTRA_LIBRARIES)
CLEANFILES += leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno
DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb


config/Dealtoken-config.h: config/stamp-h1
	@$(MAKE) -C $(top_builddir) $(subdir)/$(@)
config/stamp-h1: $(top_srcdir)/$(subdir)/config/Dealtoken-config.h.in $(top_builddir)/config.status
	$(AM_V_at)$(MAKE) -C $(top_builddir) $(subdir)/$(@)
$(top_srcdir)/$(subdir)/config/Dealtoken-config.h.in:  $(am__configure_deps)
	$(AM_V_at)$(MAKE) -C $(top_srcdir) $(subdir)/config/Dealtoken-config.h.in

clean-local:
	-$(MAKE) -C leveldb clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_QT
include Makefile.qt.include
endif
