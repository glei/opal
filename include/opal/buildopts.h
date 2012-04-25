/* include/opal/buildopts.h.  Generated from buildopts.h.in by configure.  */
/*
 * buildopts.h
 *
 * Build options generated by the configure script.
 *
 * Portable Windows Library
 *
 * Copyright (c) 2003 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Portable Windows Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Revision: 26372 $
 * $Author: rjongbloed $
 * $Date: 2011-08-31 11:41:39 +0900 (水, 31 8 2011) $
 */

#ifndef OPAL_BUILDOPTS_H
#define OPAL_BUILDOPTS_H

#include <ptbuildopts.h>

/////////////////////////////////////////////////
//
// OPAL Version 
//

#define OPAL_MAJOR 3
#define OPAL_MINOR 11
#define OPAL_BUILD 0
#define OPAL_VERSION "3.11.0"

/* #undef OPAL_PTLIB_SSL */
#define OPAL_PTLIB_ASN 1
/* #undef OPAL_PTLIB_EXPAT */
/* #undef OPAL_PTLIB_AUDIO */
#define OPAL_PTLIB_VIDEO 1
/* #undef OPAL_PTLIB_WAVFILE */
#define OPAL_PTLIB_DTMF 1
#define OPAL_PTLIB_IPV6 1
#ifndef _WIN32_WCE
/* #undef OPAL_PTLIB_DNS */
#endif
#ifndef P_IPHONEOS
/* #undef OPAL_PTLIB_LDAP */
#endif
/* #undef OPAL_PTLIB_VXML */
#define OPAL_PTLIB_CONFIG_FILE 1
#define OPAL_AEC 1


// If a "configure" did not set these variables above then they get set from PTlib variables

#if defined(P_SSL) && !defined(OPAL_PTLIB_SSL)
  #define  OPAL_PTLIB_SSL P_SSL
#endif
#if defined(P_ASN) && !defined(OPAL_PTLIB_ASN)
  #define OPAL_PTLIB_ASN 1
#endif
#if defined(P_EXPAT) && !defined(OPAL_PTLIB_EXPAT)
  #define  OPAL_PTLIB_EXPAT P_EXPAT
#endif
#if defined(P_AUDIO) && !defined(OPAL_PTLIB_AUDIO)
  #define  OPAL_PTLIB_AUDIO P_AUDIO
#endif
#if defined(P_VIDEO) && !defined(OPAL_PTLIB_VIDEO)
  #define OPAL_PTLIB_VIDEO 1
#endif
#if defined(P_WAVFILE) && !defined(OPAL_PTLIB_WAVFILE)
  #define  OPAL_PTLIB_WAVFILE P_WAVFILE
#endif
#if defined(P_DTMF) && !defined(OPAL_PTLIB_DTMF)
  #define OPAL_PTLIB_DTMF 1
#endif
#if defined(P_HAS_IPV6) && !defined(OPAL_PTLIB_IPV6)
  #define OPAL_PTLIB_IPV6 1
#endif
#if defined(P_DNS) && !defined(OPAL_PTLIB_DNS)
  #define  OPAL_PTLIB_DNS P_DNS
#endif
#if defined(P_LDAP) && !defined(OPAL_PTLIB_LDAP)
  #define  OPAL_PTLIB_LDAP P_LDAP
#endif
#if defined(P_VXML) && !defined(OPAL_PTLIB_VXML)
  #define  OPAL_PTLIB_VXML P_VXML
#endif
#if defined(P_CONFIG_FILE) && !defined(OPAL_PTLIB_CONFIG_FILE)
  #define OPAL_PTLIB_CONFIG_FILE 1
#endif

#define OPAL_PLUGIN_DIR "/usr/local/lib/opal-3.11.0"

// Video
#if P_VIDEO
  #define OPAL_VIDEO 1
#endif


/////////////////////////////////////////////////
//
// Protocol support
//

#define OPAL_IAX2 0
#define OPAL_SIP 0
#if P_ASN
#define OPAL_H323 1
#endif
#define OPAL_LID 1
/* #undef OPAL_CAPI */
/* #undef OPAL_DAHDI */
/* #undef OPAL_T120DATA */

#if OPAL_PTLIB_VXML
/*   #undef OPAL_IVR */
#endif

#if OPAL_H323
  #if OPAL_VIDEO
    #define OPAL_H239 1
  #endif
  #define OPAL_H501 1
  
  #define OPAL_H450 1
  #if OPAL_H450
    #define H323_H450   OPAL_H450
  #endif

  #define OPAL_H460 1
  #if OPAL_H460
    #define H323_H460   OPAL_H460
  #endif
#else // OPAL_H323
  #define H323_DISABLE_H225 1
  #define H323_DISABLE_H235 1
  #define H323_DISABLE_H245 1
#endif // OPAL_H323


#if !OPAL_H450
  #define H323_DISABLE_X880 1
  #define H323_DISABLE_H4501 1
  #define H323_DISABLE_H4502 1
  #define H323_DISABLE_H4503 1
  #define H323_DISABLE_H4504 1
  #define H323_DISABLE_H4505 1
  #define H323_DISABLE_H4506 1
  #define H323_DISABLE_H4507 1
  #define H323_DISABLE_H4508 1
  #define H323_DISABLE_H4509 1
  #define H323_DISABLE_H45010 1
  #define H323_DISABLE_H45011 1
#endif


#if !OPAL_T120DATA
  #define H323_DISABLE_GCC 1
  #define H323_DISABLE_MCS 1
#endif // OPAL_T120DATA


#if !OPAL_H501
  #define H323_DISABLE_H501 1
#endif


/////////////////////////////////////////////////
//
// Various options
//

#define OPAL_STATISTICS 1
//#define OPAL_RTCP_XR 1
#define GCC_HAS_CLZ 1

#define OPAL_HAS_MIXER 1
#if OPAL_PTLIB_AUDIO
  #define OPAL_HAS_PCSS 1
#endif


/////////////////////////////////////////////////
//
// Media support
//

// G.711 Packet Loss Concealment
#define OPAL_G711PLC 1

#if OPAL_VIDEO
  // Uncompressed video over RTP
  #define OPAL_RFC4175 1

  // JPEG over RTP
/*   #undef OPAL_RFC2435 */
  
  #if OPAL_RFC2435
    #if defined(_MSC_VER)
      #define JPEGLIB_LIBRARY "@JPEGLIB_DIR@/../lib/jpeg.lib"
      #pragma include_alias(<jpeglib.h>, <@JPEGLIB_DIR@/jpeglib.h>)
    #endif
  #endif
#endif


// T.38 Fax
#define OPAL_T38_CAPABILITY 0

#if OPAL_T38_CAPABILITY
  #define OPAL_FAX 1
#endif

#if !OPAL_FAX
  #define H323_DISABLE_T38 1
#endif


// Instant Messaging
#define OPAL_HAS_MSRP 1
#if OPAL_SIP
  #define OPAL_HAS_SIPIM 1
#endif
#define OPAL_HAS_RFC4103 1

#define OPAL_HAS_IM    (OPAL_HAS_SIPIM || OPAL_HAS_MSRP || OPAL_HAS_RFC4103)


// Far end camera control
#define OPAL_HAS_H224 1
#define OPAL_HAS_H281 1


// Use system Speex audio codec
/* #undef OPAL_SYSTEM_SPEEX */
/* #undef OPAL_HAVE_SPEEX_SPEEX_H */
/* #undef OPAL_SPEEX_FLOAT_NOISE */


/////////////////////////////////////////////////
//
// VoiceTronic VPB Line Interface Devide support
//

#if OPAL_LID
/*   #undef HAS_VPB */

  #if HAS_VPB
    #if defined(_MSC_VER)
      #pragma include_alias(<vpbapi.h>, <@VPB_DIR@/src/vpbapi.h>)
      #define VPB_LIBRARY "@VPB_DIR@/win32/libvpb/Debug/libvpb.lib"
    #endif
  #endif
#endif


/////////////////////////////////////////////////
//
// libZRTP support
//

//#undef HAS_LIBZRTP

#if defined(HAS_LIBZRTP) && !defined(_WIN32_WCE)

  //Temporarily disabled until security API is sorted out
  //#define OPAL_ZRTP  1

  #if defined(_MSC_VER)

    #ifdef _DEBUG
      #define LIBZRTP_LIBRARY "@LIBZRTP_DIR@/Debug/libzrtp.lib"
    #else
      #define LIBZRTP_LIBRARY "@LIBZRTP_DIR@/Release/libzrtp.lib"
    #endif

    #pragma comment(lib, LIBZRTP_LIBRARY)

    #pragma include_alias("WINCONFIG/config.h",         "@LIBZRTP_DIR@/srtp_win32k/WINCONFIG/config.h")
    #pragma include_alias("WINCONFIG\config.h",         "@LIBZRTP_DIR@/srtp_win32k/WINCONFIG/config.h")

    #pragma include_alias(<zrtp.h>,                     <@LIBZRTP_DIR@/include/zrtp.h>)
    #pragma include_alias(<zrtp_log.h>,                 <@LIBZRTP_DIR@/include/zrtp_log.h>)
    #pragma include_alias(<zrtp_types.h>,               <@LIBZRTP_DIR@/include/zrtp_types.h>)   
    #pragma include_alias(<zrtp_crypto.h>,              <@LIBZRTP_DIR@/include/zrtp_crypto.h>)
    #pragma include_alias(<zrtp_protocol.h>,            <@LIBZRTP_DIR@/include/zrtp_protocol.h>)
    #pragma include_alias(<zrtp_string.h>,              <@LIBZRTP_DIR@/include/zrtp_string.h>)
    #pragma include_alias(<zrtp_iface.h>,               <@LIBZRTP_DIR@/include/zrtp_iface.h>)
    #pragma include_alias(<zrtp_error.h>,               <@LIBZRTP_DIR@/include/zrtp_error.h>)
    #pragma include_alias(<zrtp_net.h>,                 <@LIBZRTP_DIR@/include/zrtp_net.h>)
    #pragma include_alias(<zrtp_system.h>,              <@LIBZRTP_DIR@/include/zrtp_system.h>)
    #pragma include_alias("bn.h",                       "@LIBZRTP_DIR@/bnlib/bn.h")
    #pragma include_alias(<bn.h>,                       <@LIBZRTP_DIR@/bnlib/bn.h>)
    #pragma include_alias("bnsize00.h",                 "@LIBZRTP_DIR@/bnlib/bnsize00.h")
    #pragma include_alias(<bnsize00.h>,                 <@LIBZRTP_DIR@/bnlib/bnsize00.h>)

    #pragma include_alias("aes.h",                      "@LIBZRTP_DIR@/bgaes/aes.h")
    #pragma include_alias("sha2.h",                     "@LIBZRTP_DIR@/bgaes/sha2.h")

    #pragma include_alias("zrtp_win_config.h",          "@LIBZRTP_DIR@/config/zrtp_win_config.h")


    // ZRTP includes SRTP, so include SRTP headers

    #pragma include_alias("srtp.h",              "@LIBZRTP_DIR@/srtp_win32k/include/srtp.h")
    #pragma include_alias(<srtp.h>,              <@LIBZRTP_DIR@/srtp_win32k/include/srtp.h>)
    #pragma include_alias("srtp/srtp.h",         "@LIBZRTP_DIR@/srtp_win32k/include/srtp.h")
    #pragma include_alias(<srtp/include/srtp.h>, <@LIBZRTP_DIR@/srtp_win32k/include/srtp.h>)
    #pragma include_alias("crypto_kernel.h",     "@LIBZRTP_DIR@/srtp_win32k/crypto/include/crypto_kernel.h")
    #pragma include_alias("rdbx.h",              "@LIBZRTP_DIR@/srtp_win32k/crypto/include/rdbx.h")
    #pragma include_alias("rdb.h",               "@LIBZRTP_DIR@/srtp_win32k/crypto/include/rdb.h")
    #pragma include_alias("integers.h",          "@LIBZRTP_DIR@/srtp_win32k/crypto/include/integers.h")

    // end of SRTP headers

  #endif
#endif


/////////////////////////////////////////////////
//
// libSRTP support
//

/* #undef HAS_LIBSRTP */

#if HAS_LIBSRTP && !OPAL_ZRTP && !defined(_WIN32_WCE)

  //Temporarily disabled until security API is sorted out
  //#define OPAL_SRTP  1

  #if defined(_MSC_VER)

    #pragma include_alias("srtp/srtp.h",         "@LIBSRTP_DIR@/include/srtp.h")
    #pragma include_alias(<srtp/include/srtp.h>, <@LIBSRTP_DIR@/include/srtp.h>)
    #pragma include_alias("crypto_kernel.h",     "@LIBSRTP_DIR@/crypto/include/crypto_kernel.h")
    #pragma include_alias("rdbx.h",              "@LIBSRTP_DIR@/crypto/include/rdbx.h")
    #pragma include_alias("rdb.h",               "@LIBSRTP_DIR@/crypto/include/rdb.h")
    #pragma include_alias("integers.h",          "@LIBSRTP_DIR@/crypto/include/integers.h")

    #ifdef _DEBUG
      #define LIBSRTP_LIBRARY "@LIBSRTP_DIR@/Debug/libsrtp.lib"
    #else
      #define LIBSRTP_LIBRARY "@LIBSRTP_DIR@/Release/libsrtp.lib"
    #endif
  #endif
#endif


/////////////////////////////////////////////////
//
// Java JNI support
//

/* #undef OPAL_JAVA */

#if OPAL_JAVA
  #if defined(_MSC_VER)
    #pragma include_alias(<jni.h>,    <@JAVA_DIR@/include/jni.h>)
    #pragma include_alias("jni_md.h", "@JAVA_DIR@/include/win32/jni_md.h")
  #endif
#endif


/////////////////////////////////////////////////
//
// Ruby support
//

#if !defined(_WIN32_WCE)
/* #undef OPAL_RUBY */
#endif

#if OPAL_RUBY

  #if defined(_MSC_VER)
    #define RUBY_MSC_VER 1200

    #pragma include_alias(<ruby.h>, <@RUBY_DIR@/ruby.h>)
    #pragma include_alias("ruby/config.h", "@RUBY_DIR@/i386-mswin32/ruby/config.h")
    #pragma include_alias("ruby/io.h", "@RUBY_DIR@/ruby/io.h")
    #pragma include_alias("ruby/encoding.h", "@RUBY_DIR@/ruby/encoding.h")
    #pragma include_alias("ruby/oniguruma.h", "@RUBY_DIR@/ruby/oniguruma.h")

    #define RUBY_LIBRARY "@RUBY_DIR@/../../lib/msvcrt-ruby191.lib"
  #endif

#endif


#endif // OPAL_BUILDOPTS_H


// End Of File ///////////////////////////////////////////////////////////////
