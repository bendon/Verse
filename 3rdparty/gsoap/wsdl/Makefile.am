####### This is the input file for automake, which will generate Makefile.in ##########


## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

# INCLUDES=-I$(top_srcdir)/gsoap
# AM_LDFLAGS=$(INCLUDES) -I$(srcdir) -L$(srcdir)
AM_LDFLAGS=-L$(srcdir)
AM_CPPFLAGS=-I$(top_srcdir)/gsoap
SOAP=$(top_builddir)/gsoap/src/soapcpp2
SOAP_CPP_LIB=$(top_builddir)/gsoap/$(WSDL2H_SOAP_CPP_LIB)
SOAP_CPP_SRC=wsdlC.cpp
SOAPHEADER=$(srcdir)/wsdl.h
SOAP_FLAGS=-SC -pwsdl -I$(srcdir) -I$(top_srcdir)/gsoap/import
BUILT_SOURCES=$(SOAP_CPP_SRC)
# WSDL2H_EXTRA_FLAGS=-DWITH_OPENSSL -DWITH_GZIP # defined in configure.in
# WSDL2H_EXTRA_LIBS=-lssl -lcrypto -lz # defined in configure.in

$(SOAP_CPP_SRC) : $(SOAPHEADER)
	$(SOAP) $(SOAP_FLAGS) $(SOAPHEADER)

#LIBS=

bin_PROGRAMS=wsdl2h

wsdl2h_CFLAGS=$(C_DEBUG_FLAGS)
wsdl2h_CXXFLAGS=$(C_DEBUG_FLAGS)
wsdl2h_CPPFLAGS=$(AM_CPPFLAGS) $(SOAPCPP2_NONAMESPACES) -D$(platform)
wsdl2h_SOURCES=wsdl2h.cpp wsdl.cpp schema.cpp types.cpp service.cpp soap.cpp mime.cpp wsp.cpp $(SOAP_CPP_SRC)
wsdl2h_LDADD=$(SOAP_CPP_LIB) $(WSDL2H_EXTRA_LIBS) $(SAMPLE_EXTRA_LIBS)

CLEANFILES= *~ *C.cpp *H.h *Stub.h *.nsmap
