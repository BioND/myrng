ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS} -I m4

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = myrngWELL.pc myrngMT.pc

EXTRA_DIST = myrngWELL.pc myrngMT.pc README.md Doxyfile

lib_LTLIBRARIES = libmyrngWELL-@PACKAGE_VERSION@.la libmyrngMT-@PACKAGE_VERSION@.la
libmyrngWELL_@PACKAGE_VERSION@_la_CPPFLAGS = -DNDEBUG
libmyrngMT_@PACKAGE_VERSION@_la_CPPFLAGS = -DNDEBUG
libmyrngWELL_@PACKAGE_VERSION@_la_LDFLAGS = -version-info 0:0:0
libmyrngMT_@PACKAGE_VERSION@_la_LDFLAGS = -version-info 0:0:0

libmyrngWELL_@PACKAGE_VERSION@_la_SOURCES = \
	myrng/myrngWELL.cpp \
	myrng/WELLEngine.cpp
	
libmyrngMT_@PACKAGE_VERSION@_la_SOURCES = \
	myrng/myrngMT.cpp \
	myrng/MTEngine.cpp

nobase_include_HEADERS = \
	myrng/myrng.h \
	myrng/myrngMT.h \
	myrng/myrngWELL.h \
	myrng/MTEngine.h \
	myrng/WELLEngine.h \
	myrng/RandomVariates.h \
	myrng/util.h
	
check_PROGRAMS = testWELL testMT

testWELL_SOURCES = test/testWELL.cpp test/RNGTests.h
testMT_SOURCES = test/testMT.cpp test/RNGTests.h

testWELL_CXXFLAGS = -O2 -DNDEBUG
testMT_CXXFLAGS = -O2 -DNDEBUG

testWELL_LDADD = libmyrngWELL-@PACKAGE_VERSION@.la
testMT_LDADD = libmyrngMT-@PACKAGE_VERSION@.la

if HAVE_DOXYGEN

DOCDIR = doc
MOSTLYCLEANFILES = -r $(DOCDIR)
	
doxygen-doc: $(DOCDIR)/doxygen.stamp 

$(DOCDIR)/doxygen.stamp: Doxyfile
	$(DOXYGEN) $(DOXYFLAGS) $<
	echo Timestamp > $@

endif
