#
# opal_inc.mak
#
# Make symbols include file for Open Phone Abstraction library
#
# Copyright (c) 2001 Equivalence Pty. Ltd.
#
# The contents of this file are subject to the Mozilla Public License
# Version 1.0 (the "License"); you may not use this file except in
# compliance with the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS"
# basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
# the License for the specific language governing rights and limitations
# under the License.
#
# The Original Code is Open Phone Abstraction library.
#
# The Initial Developer of the Original Code is Equivalence Pty. Ltd.
#
# Contributor(s): ______________________________________.
#
# $Revision: 26540 $
# $Author: rjongbloed $
# $Date: 2011-10-06 08:35:10 +0900 (木, 06 10 2011) $
#

ifndef DEBUG_BUILD
DEBUG_BUILD             = 
endif

#detected by configure, needed by Makefile
OSTYPE = Darwin

# Tool names detected by configure
CXX                     = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++ -arch armv7 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk
CC                      = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/gcc -arch armv7 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk
INSTALL                 = /usr/bin/install -c
AR                      = ar
RANLIB                  = ranlib
LD                      = /Developer/Platforms/iPhoneOS.platform/Developer/usr/bin/g++ -arch armv7 -isysroot /Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk
ARCHIVE                 = ar rcs
SWIG                    = 

# The install directories
prefix                  = /usr/local
exec_prefix             = ${prefix}
libdir                  = ${exec_prefix}/lib
includedir              = ${prefix}/include
datarootdir             = ${prefix}/share

# The opal source and destination dirs
OPALDIR                 = /Users/keid/opal
OPAL_SRCDIR             = $(OPALDIR)/src
OPAL_INCDIR             = $(OPALDIR)/include
OPAL_LIBDIR             = ${OPALDIR}/lib_Darwin_arm

# The library file names
RELEASE_LIB_NAME                = libopal
RELEASE_LIB_FILENAME_STATIC     = libopal_s.a
RELEASE_LIB_FILENAME_SHARED     = libopal.dylib
RELEASE_LIB_FILENAME_SHARED_MAJ = @RELEASE_LIB_FILENAME_SHARED_MAJ@
RELEASE_LIB_FILENAME_SHARED_MIN = @RELEASE_LIB_FILENAME_SHARED_MIN@
RELEASE_LIB_FILENAME_SHARED_PAT = libopal.3.11-alpha0.dylib
RELEASE_CFLAGS                  = 
RELEASE_LIBS                    = -L/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/usr/lib -L/usr/local/lib -lpt_s -lresolv -lpthread -lc  
RELEASE_OPAL_OBJDIR	        = ${OPALDIR}/lib_Darwin_arm/obj
RELEASE_OPAL_DEPDIR	        = ${OPALDIR}/lib_Darwin_arm/obj

# The library file names
DEBUG_LIB_NAME                  = libopal_d
DEBUG_LIB_FILENAME_STATIC       = libopal_d_s.a
DEBUG_LIB_FILENAME_SHARED       = libopal_d.dylib
DEBUG_LIB_FILENAME_SHARED_MAJ   = @DEBUG_LIB_FILENAME_SHARED_MAJ@
DEBUG_LIB_FILENAME_SHARED_MIN   = @DEBUG_LIB_FILENAME_SHARED_MIN@
DEBUG_LIB_FILENAME_SHARED_PAT   = libopal_d.3.11-alpha0.dylib
DEBUG_CFLAGS                    = -g3 -ggdb -O0 -D_DEBUG
DEBUG_LIBS                      = -L/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk/usr/lib -L/usr/local/lib -lpt_d_s -lresolv -lpthread -lc  
DEBUG_OPAL_OBJDIR	        = ${OPALDIR}/lib_Darwin_arm/obj_d
DEBUG_OPAL_DEPDIR	        = ${OPALDIR}/lib_Darwin_arm/obj_d

# Compile and linker flags
CFLAGS           :=  -Wall -Wextra -Wstrict-aliasing -Wfloat-equal -Wno-comment -Wno-unused -Winit-self -Wno-missing-field-initializers -DPTRACING=2 -D_REENTRANT -fno-exceptions -I/usr/local/include   -fPIC  -I/Library/Ruby/Site/1.8 -I/Library/Ruby/Site/1.8/powerpc-darwin11.0 -I/Library/Ruby/Site/1.8/universal-darwin11.0 -I/Library/Ruby/Site -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby/1.8 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby/1.8/universal-darwin11.0 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/powerpc-darwin11.0 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/universal-darwin11.0 -I. -I$(OPAL_INCDIR) $(CFLAGS)
CXXFLAGS         :=  -Wall -Wextra -Wstrict-aliasing -Wfloat-equal -Wno-comment -Wno-unused -Winit-self -Wno-missing-field-initializers -DPTRACING=2 -D_REENTRANT -fno-exceptions -I/usr/local/include   -felide-constructors -Wreorder -fPIC  -I/Library/Ruby/Site/1.8 -I/Library/Ruby/Site/1.8/powerpc-darwin11.0 -I/Library/Ruby/Site/1.8/universal-darwin11.0 -I/Library/Ruby/Site -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby/1.8 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby/1.8/universal-darwin11.0 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/vendor_ruby -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/powerpc-darwin11.0 -I/System/Library/Frameworks/Ruby.framework/Versions/1.8/usr/lib/ruby/1.8/universal-darwin11.0 -I. -I$(OPAL_INCDIR) $(CXXFLAGS)
LFLAGS           := @LFLAGS@
LIBS             +=  -lc
LDSOOPTS          = -dynamiclib

HAVE_RANLIB      := no

OPAL_H323         = yes
OPAL_SIP          = yes
OPAL_IAX2         = yes
OPAL_VIDEO        = yes
OPAL_ZRTP         = no
OPAL_LID	  = yes
OPAL_CAPI	  = no
OPAL_DAHDI	  = no
OPAL_IVR	  = no
OPAL_HAS_H224     = yes
OPAL_HAS_H281     = yes
OPAL_H450         = yes
OPAL_H460         = yes
OPAL_H501         = yes
OPAL_T120DATA     = no
OPAL_SRTP	  = no
OPAL_RFC4175	  = yes
OPAL_RFC2435	  = no
OPAL_AEC          = yes
OPAL_G711PLC      = yes
OPAL_T38_CAP	  = yes
OPAL_FAX          = yes
OPAL_JAVA         = no
SPEEXDSP_SYSTEM   = no
OPAL_HAS_MSRP	  = yes
OPAL_HAS_SIPIM	  = yes
OPAL_HAS_RFC4103  = yes
OPAL_HAS_MIXER    = yes
OPAL_HAS_PCSS     = yes

OPAL_PLUGINS      = no
OPAL_SAMPLES      = no

OPAL_PTLIB_SSL    = no
OPAL_PTLIB_SSL_AES= no
OPAL_PTLIB_ASN    = yes
OPAL_PTLIB_EXPAT  = no
OPAL_PTLIB_AUDIO  = no
OPAL_PTLIB_VIDEO  = yes
OPAL_PTLIB_WAVFILE= no
OPAL_PTLIB_DTMF   = yes
OPAL_PTLIB_IPV6   = yes
OPAL_PTLIB_DNS    = no
OPAL_PTLIB_LDAP   = no
OPAL_PTLIB_VXML   = no
OPAL_PTLIB_CONFIG_FILE=yes
OPAL_PTLIB_STUN   = yes
OPAL_PTLIB_CLI    = yes


ifeq ($(DEBUG_BUILD),yes)
  CFLAGS   := $(DEBUG_CFLAGS) $(CFLAGS)
  CXXFLAGS := $(DEBUG_CFLAGS) $(CXXFLAGS)
  LIBS     += $(DEBUG_LIBS)
  LIB_NAME  = $(DEBUG_LIB_NAME)
else
  CFLAGS   := $(RELEASE_CFLAGS) $(CFLAGS)
  CXXFLAGS := $(RELEASE_CFLAGS) $(CXXFLAGS)
  LIBS     += $(RELEASE_LIBS)
  LIB_NAME  = $(RELEASE_LIB_NAME)
endif

# End of file
