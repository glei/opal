/*
 * t38mf.cxx
 *
 * T.38 Media Format descriptions
 *
 * Open Phone Abstraction Library
 * Formally known as the Open H323 project.
 *
 * Copyright (c) 2008 Vox Lucida
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
 * The Original Code is Open Phone Abstraction Library
 *
 * The Initial Developer of the Original Code is Vox Lucida
 *
 * Contributor(s): ______________________________________.
 *
 * $Revision: 26281 $
 * $Author: csoutheren $
 * $Date: 2011-08-08 11:07:43 +0900 (月, 08 8 2011) $
 */

#include <ptlib.h>
#include <opal/buildopts.h>

#include <t38/t38proto.h>
#include <opal/mediafmt.h>
#include <opal/mediasession.h>


#define new PNEW


#if OPAL_T38_CAPABILITY
#if OPAL_PTLIB_ASN

#include <rtp/rtp.h>

OPAL_INSTANTIATE_MEDIATYPE(fax, OpalFaxMediaType);


/////////////////////////////////////////////////////////////////////////////

const OpalMediaFormat & GetOpalT38()
{
  static class T38MediaFormat : public OpalMediaFormat {
    public:
      T38MediaFormat()
        : OpalMediaFormat(OPAL_T38,
                          "fax",
                          RTP_DataFrame::T38,
                          "t38",
                          false, // No jitter for data
                          1440, // 100's bits/sec
                          512,
                          0,
                          0)
      {
        static const char * const RateMan[] = { "localTCF", "transferredTCF" };
        AddOption(new OpalMediaOptionEnum("T38FaxRateManagement", false, RateMan, PARRAYSIZE(RateMan), OpalMediaOption::EqualMerge, 1));
        AddOption(new OpalMediaOptionInteger("T38FaxVersion", false, OpalMediaOption::MinMerge, 0, 0, 1));
      }
  } const T38;
  return T38;
}


/////////////////////////////////////////////////////////////////////////////

OpalFaxMediaType::OpalFaxMediaType()
  : OpalMediaTypeDefinition("fax", "image", 3) // Must be 3 for H.323 operation
{
}


OpalMediaSession * OpalFaxMediaType::CreateMediaSession(OpalConnection & conn, unsigned sessionID) const
{
  return new OpalFaxSession(conn, sessionID);
}


#endif // OPAL_PTLIB_ASN
#endif // OPAL_T38_CAPABILITY


// End of File ///////////////////////////////////////////////////////////////
