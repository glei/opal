/*
 * console_mgs.cxx
 *
 * An OpalManager derived class for use in a console application, providing
 * a standard set of command line arguments for configuring many system
 * parameters. Used by the sample applications such as faxopal, ovropal etc.
 *
 * Copyright (c) 2010 Vox Lucida Pty. Ltd.
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
 * The Original Code is Open Phone Abstraction Library.
 *
 * The Initial Developer of the Original Code is Vox Lucida Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Revision: 26559 $
 * $Author: rjongbloed $
 * $Date: 2011-10-07 12:03:01 +0900 (金, 07 10 2011) $
 */

#include <ptlib.h>

#ifdef __GNUC__
#pragma implementation "console_mgr.h"
#endif

#include <opal/console_mgr.h>

#if P_CLI

#include <sip/sipep.h>
#include <h323/h323ep.h>
#include <h323/gkclient.h>
#include <lids/lidep.h>


static void PrintVersion(ostream & strm)
{
  const PProcess & process = PProcess::Current();
  strm << process.GetName()
        << " version " << process.GetVersion(true) << "\n"
          "  by   " << process.GetManufacturer() << "\n"
          "  on   " << process.GetOSClass() << ' ' << process.GetOSName()
        << " (" << process.GetOSVersion() << '-' << process.GetOSHardware() << ")\n"
          "  with PTLib v" << PProcess::GetLibVersion() << "\n"
          "  and  OPAL  v" << OpalGetVersion()
        << endl;
}


#if OPAL_SIP
static bool SetRegistrationParams(SIPRegister::Params & params,
                                  PString & error,
                                  const PArgList & args, 
                                  const char * mode,
                                  const char * ttl)
{
  if (args.HasOption(mode)) {
    PCaselessString str = args.GetOptionString("register-mode");
    if (str == "normal")
      params.m_compatibility = SIPRegister::e_FullyCompliant;
    else if (str == "single")
      params.m_compatibility = SIPRegister::e_CannotRegisterMultipleContacts;
    else if (str == "public")
      params.m_compatibility = SIPRegister::e_CannotRegisterPrivateContacts;
    else {
      error = "Unknown SIP registration mode " + str;
      return false;
    }
  }

  params.m_expire = args.GetOptionString(ttl, "300").AsUnsigned();
  if (params.m_expire < 30) {
    error = "SIP registrar Time To Live must be more than 30 seconds";
    return false;
  }

  return true;
}
#endif // OPAL_SIP

  
/////////////////////////////////////////////////////////////////////////////

OpalManagerConsole::OpalManagerConsole()
{
}


PString OpalManagerConsole::GetArgumentSpec() const
{
  return "[Global options:]"
         "u-user:            Set local username, defaults to OS username.\n"
         "p-password:        Set password for authentication.\n"
         "D-disable:         Disable use of specified media formats (codecs).\n"
         "P-prefer:          Set preference order for media formats (codecs).\n"
         "O-option:          Set options for media formatm argument is of form fmt:opt=val.\n"
         "-inband-detect.    Disable detection of in-band tones.\n"
         "-inband-send.      Disable transmission of in-band tones.\n"
         "-tel:              Protocol to use for tel: URI, e.g. sip\n"

#if OPAL_SIP
         "[SIP options:]"
         "S-sip:             SIP listens on interface, defaults to udp$*:5060, 'x' disables.\n"
         "r-register:        SIP registration to server.\n"
         "-register-auth-id: SIP registration authorisation id, default is username.\n"
         "-register-proxy:   SIP registration proxy, default is none.\n"
         "-register-ttl:     SIP registration Time To Live, default 300 seconds.\n"
         "-register-mode:    SIP registration mode (normal, single, public).\n"
         "-proxy:            SIP outbound proxy.\n"
         "-sip-ui:           SIP User Indication mode (inband,rfc2833,info-tone,info-string)\n"
#endif

#if OPAL_H323
         "[H.323 options:]"
         "H-h323:            H.323 listens on interface, defaults to tcp$*:1720, 'x' disables.\n"
         "g-gk-host:         H.323 gatekeeper host.\n"
         "G-gk-id:           H.323 gatekeeper identifier.\n"
         "-no-fast.          H.323 fast connect disabled.\n"
         "-no-tunnel.        H.323 tunnel for H.245 disabled.\n"
         "-h323-ui:          H.323 User Indication mode (inband,rfc2833,h245-signal,h245-string)\n"
#endif

#if OPAL_LID
         "[Line Interface options:]"
         "L-lines:           Set Line Interface Devices, 'x' disables.\n"
         "-country:          Select country to use for LID (eg \"US\", \"au\" or \"+61\").\n"
#endif

         "[IP options:]"
#ifdef P_STUN
         "-stun:             Set NAT traversal STUN server\n"
#endif
         "-translate:        Set external IP address if masqueraded\n"
         "-portbase:         Set TCP/UDP/RTP port base\n"
         "-portmax:          Set TCP/UDP/RTP port max\n"
         "-tcp-base:         Set TCP port base (default 0)\n"
         "-tcp-max:          Set TCP port max (default base+99)\n"
         "-udp-base:         Set UDP port base (default 6000)\n"
         "-udp-max:          Set UDP port max (default base+199)\n"
         "-rtp-base:         Set RTP port base (default 5000)\n"
         "-rtp-max:          Set RTP port max (default base+199)\n"
         "-rtp-tos:          Set RTP packet IP TOS bits to n\n"
         "-rtp-size:         Set RTP maximum payload size in bytes.\n"

         "[Debug & General:]"
#if PTRACING
         "t-trace.           Verbosity in error log (more times for more detail)\n"     
         "o-output:          File name for output of log messages\n"       
#endif
         "V-version.         Display application version.\n"
         "h-help.            This help message.\n"
         ;
}


PString OpalManagerConsole::GetArgumentUsage() const
{
  return "[ options ... ]";
}


void OpalManagerConsole::Usage(ostream & strm, const PArgList & args)
{
  strm << "usage: " << PProcess::Current().GetFile().GetTitle() << ' ' << GetArgumentUsage() << "\n\n";
  args.Usage(strm);
}


bool OpalManagerConsole::Initialise(PArgList & args, bool verbose)
{
  if (!args.IsParsed()) {
    PArgList::ParseResult result = args.Parse(GetArgumentSpec());
    if (result < 0 || args.HasOption("help")) {
      if (PAssert(result != PArgList::ParseInvalidOptions, "Invalid options specification"))
        Usage(cerr, args);
      return false;
    }
  }

  if (args.HasOption("version")) {
    PrintVersion(cerr);
    return false;
  }

#if PTRACING
  PTrace::Initialise(args.GetOptionCount("trace"),
                     args.HasOption("output") ? (const char *)args.GetOptionString("output") : NULL,
                PTrace::Blocks | PTrace::Timestamp | PTrace::Thread | PTrace::FileAndLine);
#endif

  if (args.HasOption("option")) {
    PStringArray options = args.GetOptionString("option").Lines();
    for (PINDEX i = 0; i < options.GetSize(); ++i) {
      PRegularExpression parse("\\([A-Za-z].*\\):\\([A-Za-z].*\\)=\\(.*\\)");
      PStringArray subexpressions(4);
      if (!parse.Execute(options[i], subexpressions)) {
        cerr << "Invalid media format option \"" << options[i] << '"' << endl;
        return false;
      }

      OpalMediaFormat format(subexpressions[1]);
      if (!format.IsValid()) {
        cerr << "Unknown media format \"" << subexpressions[1] << '"' << endl;
        return false;
      }
      if (!format.HasOption(subexpressions[2])) {
        cerr << "Unknown option name \"" << subexpressions[2] << "\""
                " in media format \"" << subexpressions[1] << '"' << endl;
        return false;
      }
      if (!format.SetOptionValue(subexpressions[2], subexpressions[3])) {
        cerr << "Ilegal value \"" << subexpressions[3] << "\""
                " for option name \"" << subexpressions[2] << "\""
                " in media format \"" << subexpressions[1] << '"' << endl;
        return false;
      }
      OpalMediaFormat::SetRegisteredMediaFormat(format);
    }
  }

  if (args.HasOption("disable"))
    SetMediaFormatMask(args.GetOptionString("disable").Lines());
  if (args.HasOption("prefer"))
    SetMediaFormatOrder(args.GetOptionString("prefer").Lines());
  if (verbose) {
    OpalMediaFormatList formats = OpalMediaFormat::GetAllRegisteredMediaFormats();
    formats.Remove(GetMediaFormatMask());
    formats.Reorder(GetMediaFormatOrder());
    cout << "Media Formats: " << setfill(',') << formats << setfill(' ') << endl;
  }

  if (args.HasOption("translate")) {
    SetTranslationAddress(args.GetOptionString("translate"));
    if (verbose)
      cout << "External address set to " << GetTranslationAddress() << '\n';
  }

  if (args.HasOption("portbase")) {
    unsigned portbase = args.GetOptionString("portbase").AsUnsigned();
    unsigned portmax  = args.GetOptionString("portmax").AsUnsigned();
    SetTCPPorts  (portbase, portmax);
    SetUDPPorts  (portbase, portmax);
    SetRtpIpPorts(portbase, portmax);
  }

  if (args.HasOption("tcp-base"))
    SetTCPPorts(args.GetOptionString("tcp-base").AsUnsigned(),
                args.GetOptionString("tcp-max").AsUnsigned());

  if (args.HasOption("udp-base"))
    SetUDPPorts(args.GetOptionString("udp-base").AsUnsigned(),
                args.GetOptionString("udp-max").AsUnsigned());

  if (args.HasOption("rtp-base"))
    SetRtpIpPorts(args.GetOptionString("rtp-base").AsUnsigned(),
                  args.GetOptionString("rtp-max").AsUnsigned());

  if (args.HasOption("rtp-tos")) {
    unsigned tos = args.GetOptionString("rtp-tos").AsUnsigned();
    if (tos > 255) {
      cerr << "IP Type Of Service bits must be 0 to 255.\n";
      return false;
    }
    SetMediaTypeOfService(tos);
  }

  if (args.HasOption("rtp-size")) {
    unsigned size = args.GetOptionString("rtp-size").AsUnsigned();
    if (size < 32 || size > 65500) {
      cerr << "RTP maximum payload size 32 to 65500.\n";
      return false;
    }
    SetMaxRtpPayloadSize(size);
  }

  if (verbose)
    cout << "TCP ports: " << GetTCPPortBase() << '-' << GetTCPPortMax() << "\n"
            "UDP ports: " << GetUDPPortBase() << '-' << GetUDPPortMax() << "\n"
            "RTP ports: " << GetRtpIpPortBase() << '-' << GetRtpIpPortMax() << "\n"
            "RTP IP TOS: 0x" << hex << (unsigned)GetMediaTypeOfService() << dec << "\n"
            "RTP payload size: " << GetMaxRtpPayloadSize() << '\n';

#ifdef P_STUN
  if (args.HasOption("stun")) {
    if (verbose)
      cout << "STUN server: " << flush;
    PSTUNClient::NatTypes natType = SetSTUNServer(args.GetOptionString("stun"));
    if (verbose) {
      PNatMethod * natMethod = GetNatMethod();
      if (natMethod == NULL)
        cout << "Unavailable";
      else {
        cout << '"' << natMethod->GetServer() << "\" replies " << natType;
        PIPSocket::Address externalAddress;
        if (natType != PSTUNClient::BlockedNat && natMethod->GetExternalAddress(externalAddress))
          cout << " with external address " << externalAddress;
      }
      cout << endl;
    }
  }
#endif

  if (args.HasOption("user"))
    SetDefaultUserName(args.GetOptionString("user"));

  if (verbose) {
    PIPSocket::InterfaceTable interfaceTable;
    if (PIPSocket::GetInterfaceTable(interfaceTable))
      cout << "Detected " << interfaceTable.GetSize() << " network interfaces:\n"
           << setfill('\n') << interfaceTable << setfill(' ');
  }

  PCaselessString interfaces;

#if OPAL_SIP
  // Set up SIP
  interfaces = args.GetOptionString("sip");
  if (interfaces != "x") {
    SIPEndPoint * sip  = CreateSIPEndPoint();
    if (!sip->StartListeners(interfaces.Lines())) {
      cerr << "Could not start SIP listeners." << endl;
      return false;
    }
    if (verbose)
      cout << "SIP listening on: " << setfill(',') << sip->GetListeners() << setfill(' ') << '\n';

    if (args.HasOption("sip-ui")) {
      PCaselessString str = args.GetOptionString("sip-ui");
      if (str == "inband")
        sip->SetSendUserInputMode(OpalConnection::SendUserInputInBand);
      else if (str == "rfc2833")
        sip->SetSendUserInputMode(OpalConnection::SendUserInputAsRFC2833);
      else if (str == "info-tone")
        sip->SetSendUserInputMode(OpalConnection::SendUserInputAsTone);
      else if (str == "info-string")
        sip->SetSendUserInputMode(OpalConnection::SendUserInputAsString);
      else {
        cerr << "Unknown SIP user indication mode \"" << str << '"' << endl;
        return false;
      }
    }

    if (verbose)
      cout << "SIP options: "
           << sip->GetSendUserInputMode() << '\n';

    if (args.HasOption("proxy")) {
      sip->SetProxy(args.GetOptionString("proxy"), args.GetOptionString("user"), args.GetOptionString("password"));
      if (verbose)
        cout << "SIP proxy: " << sip->GetProxy() << '\n';
    }

    if (args.HasOption("register")) {
      SIPRegister::Params params;
      params.m_addressOfRecord = args.GetOptionString("register");
      params.m_authID = args.GetOptionString("register-auth-id");
      params.m_registrarAddress = args.GetOptionString("register-proxy");
      params.m_password = args.GetOptionString("password");

      PString error;
      if (!SetRegistrationParams(params, error, args, "register-mode", "register-ttl")) {
        cerr << error << endl;
        return false;
      }

      if (verbose)
        cout << "SIP registrar: " << flush;
      PString aor;
      SIP_PDU::StatusCodes status;
      if (!sip->Register(params, aor, &status)) {
        cerr << "\nSIP registration to " << params.m_addressOfRecord
             << " failed (" << status << ')' << endl;
        return false;
      }
      if (verbose)
        cout << aor << '\n';
    }
  }
#endif // OPAL_SIP


#if OPAL_H323
  // Set up H.323
  interfaces = args.GetOptionString("h323");
  if (interfaces != "x") {
    H323EndPoint * h323 = CreateH323EndPoint();
    if (!h323->StartListeners(interfaces.Lines())) {
      cerr << "Could not start H.323 listeners." << endl;
      return false;
    }
    if (verbose)
      cout << "H.323 listening on: " << setfill(',') << h323->GetListeners() << setfill(' ') << '\n';

    h323->DisableFastStart(args.HasOption("no-fast"));
    h323->DisableH245Tunneling(args.HasOption("no-tunnel"));

    if (args.HasOption("h323-ui")) {
      PCaselessString str = args.GetOptionString("h323-ui");
      if (str == "inband")
        h323->SetSendUserInputMode(OpalConnection::SendUserInputInBand);
      else if (str == "rfc2833")
        h323->SetSendUserInputMode(OpalConnection::SendUserInputAsRFC2833);
      else if (str == "h245-signal")
        h323->SetSendUserInputMode(OpalConnection::SendUserInputAsTone);
      else if (str == "h245-string")
        h323->SetSendUserInputMode(OpalConnection::SendUserInputAsString);
      else {
        cerr << "Unknown H.323 user indication mode \"" << str << '"' << endl;
        return false;
      }
    }

    if (verbose)
      cout << "H.323 options: "
           << (h323->IsFastStartDisabled() ? "Slow" : "Fast") << " connect, "
           << (h323->IsH245TunnelingDisabled() ? "Separate" : "Tunnelled") << " H.245, "
           << h323->GetSendUserInputMode() << '\n';

    if (args.HasOption("gk-host") || args.HasOption("gk-id")) {
      if (verbose)
        cout << "H.323 Gatekeeper: " << flush;
      if (!h323->UseGatekeeper(args.GetOptionString("gk-host"), args.GetOptionString("gk-id"))) {
        cerr << "\nCould not complete gatekeeper registration" << endl;
        return false;
      }
      if (verbose)
        cout << *h323->GetGatekeeper() << flush;
    }
  }
#endif // OPAL_H323

#if OPAL_LID
  // If we have LIDs speficied in command line, load them
  if (args.HasOption("lines")) {
    OpalLineEndPoint * lines = CreateLineEndPoint();
    if (!lines->AddDeviceNames(args.GetOptionString("lines").Lines())) {
      cerr << "Could not start Line Interface Device(s)" << endl;
      return false;
    }
    if (verbose)
      cout << "Line Interface listening on: " << setfill(',') << lines->GetLines() << setfill(' ') << endl;

    PString country = args.GetOptionString("country");
    if (!country.IsEmpty()) {
      if (!lines->SetCountryCodeName(country))
        cerr << "Could not set LID to country name \"" << country << '"' << endl;
      else if (verbose)
        cout << "LID to country: " << lines->GetLine("*")->GetDevice().GetCountryCodeName() << endl;
    }
  }
#endif // OPAL_LID

  PString telProto = args.GetOptionString("tel");
  if (!telProto.IsEmpty()) {
    OpalEndPoint * ep = FindEndPoint(telProto);
    if (ep == NULL) {
      cerr << "The \"tel\" URI cannot be mapped to protocol \"" << telProto << '"' << endl;
      return false;
    }

    AttachEndPoint(ep, "tel");
    if (verbose)
      cout << "tel URI mapped to: " << ep->GetPrefixName() << '\n';
  }

  return true;
}


void OpalManagerConsole::Run()
{
  m_endRun.Wait();
}


void OpalManagerConsole::EndRun()
{
  m_endRun.Signal();
}


#if OPAL_SIP
SIPEndPoint * OpalManagerConsole::CreateSIPEndPoint()
{
  return new SIPEndPoint(*this);
}
#endif // OPAL_SIP


#if OPAL_H323
H323EndPoint * OpalManagerConsole::CreateH323EndPoint()
{
  return new H323EndPoint(*this);
}
#endif // OPAL_H323


#if OPAL_LID
OpalLineEndPoint * OpalManagerConsole::CreateLineEndPoint()
{
  return new OpalLineEndPoint(*this);
}
#endif // OPAL_LID


/////////////////////////////////////////////////////////////////////////////

OpalManagerCLI::OpalManagerCLI()
  : m_cli(NULL)
{
}


OpalManagerCLI::~OpalManagerCLI()
{
  delete m_cli;
}


PString OpalManagerCLI::GetArgumentSpec() const
{
  PString spec = OpalManagerConsole::GetArgumentSpec();
  // Insert just before the version option
  spec.Splice("F-script-file: Execute script file in CLI\n"
              "-cli: Enable telnet command line sessions on port.\n",
              spec.Find("V-version"));
  return spec;
}


bool OpalManagerCLI::Initialise(PArgList & args, bool verbose)
{
  if (!OpalManagerConsole::Initialise(args, verbose))
    return false;

  if (m_cli == NULL) {
    unsigned port = 0;
    if (args.HasOption("cli")) {
      port = args.GetOptionString("cli").AsUnsigned();
      if (port == 0 || port > 65535) {
        cerr << "Illegal CLI port " << port << endl;
        return false;
      }
    }

#if P_TELNET
    m_cli = CreatePCLI((WORD)port);
#else
    m_cli = CreatePCLI();
#endif
    if (m_cli == NULL)
      return false;
  }

  m_cli->SetPrompt(PProcess::Current().GetName());

#if OPAL_SIP
  m_cli->SetCommand("register", PCREATE_NOTIFIER(CmdRegister),
                    "Register with SIP registrar",
                    "[ options ] <address> [ <password> ]");
#endif

#if P_NAT
  m_cli->SetCommand("nat address", PCREATE_NOTIFIER(CmdNat),
                    "Set NAT method and address",
                    "<method> <address>");
#endif

#if PTRACING
  m_cli->SetCommand("trace", PCREATE_NOTIFIER(CmdTrace),
                    "Set trace level (1..6) and filename",
                    "<n> [ <filename> ]");
#endif

  m_cli->SetCommand("list codecs", PCREATE_NOTIFIER(CmdListCodecs),
                    "List available codecs");
  m_cli->SetCommand("delay", PCREATE_NOTIFIER(CmdDelay),
                    "Delay for the specified numebr of seconds",
                    "seconds");
  m_cli->SetCommand("version", PCREATE_NOTIFIER(CmdVersion),
                    "Print application vesion number and library details.");
  m_cli->SetCommand("quit\nq\nexit", PCREATE_NOTIFIER(CmdQuit),
                    "Quit command line interpreter, note quitting from console also shuts down application.");
  m_cli->SetCommand("shutdown", PCREATE_NOTIFIER(CmdShutDown),
                    "Shut down the application");
  return true;
}


void OpalManagerCLI::Run()
{
  if (PAssertNULL(m_cli) == NULL)
    return;

  if (PProcess::Current().GetArguments().HasOption("script-file")) {
    // if there is a script file, process commands
    PString filename = PProcess::Current().GetArguments().GetOptionString("script-file");
    PTextFile scriptFile;
    if (scriptFile.Open(filename)) {
      PCLIStandard * stdCLI = dynamic_cast<PCLIStandard *>(m_cli);
      if (stdCLI != NULL)
        stdCLI->RunScript(scriptFile);
      else
        m_cli->Run(&scriptFile, new PNullChannel, false, true);
    }
    else
      cerr << "error: cannot open script file \"" << filename << '"' << endl;
  }

  if (m_cli != NULL)
    m_cli->Start(false);
}


void OpalManagerCLI::EndRun()
{
  if (m_cli != NULL)
    m_cli->Stop();
  OpalManagerConsole::EndRun();
}


#if P_TELNET
PCLI * OpalManagerCLI::CreatePCLI(WORD port)
{
  if (port == 0)
    return new PCLIStandard;

  PCLI * cli = new PCLITelnet(port);
  cli->StartContext(new PConsoleChannel(PConsoleChannel::StandardInput),
                    new PConsoleChannel(PConsoleChannel::StandardOutput));
  return cli;
}
#else
PCLI * OpalManagerCLI::CreatePCLI()
{
  return new PCLIStandard;
}
#endif


#if OPAL_SIP
void OpalManagerCLI::CmdRegister(PCLI::Arguments & args, INT)
{
  if (args.Parse("a-auth-id: Override user for authorisation\n"
                  "r-realm: Set realm for authorisation\n"
                  "p-proxy: Set proxy for registration\n"
                  "m-mode: Set registration mode (normal, single, public)\n"
                  "t-ttl: Set Time To Live for registration\n") <= PArgList::ParseNoArguments) {
    args.WriteUsage();
    return;
  }

  SIPRegister::Params params;

  params.m_addressOfRecord  = args[0];
  params.m_password         = args[1];
  params.m_authID           = args.GetOptionString('a');
  params.m_realm            = args.GetOptionString('r');
  params.m_proxyAddress     = args.GetOptionString('p');

  PString error;
  if (!SetRegistrationParams(params, error, args, "mode", "ttl")) {
    args.WriteError(error);
    return;
  }

  args.GetContext() << "Registering with " << params.m_addressOfRecord << " ..." << flush;

  PString aor;
  if (FindEndPointAs<SIPEndPoint>("sip")->Register(params, aor, false))
    args.GetContext() << "succeeded" << endl;
  else
    args.GetContext() << "failed" << endl;
}
#endif


#if P_NAT
void OpalManagerCLI::CmdNat(PCLI::Arguments & args, INT)
{
  if (args.GetCount() < 2) {
    args.WriteUsage();
    return;
  }

  if (!SetNATServer(args[0], args[1])) {
    args.WriteError("STUN server offline or unsuitable NAT type");
    return;
  }

  PCLI::Context & out = args.GetContext();
  out << m_natMethod->GetName() << " server \"" << m_natMethod->GetServer() << " replies " << m_natMethod->GetNatType();
  PIPSocket::Address externalAddress;
  if (m_natMethod->GetExternalAddress(externalAddress))
    out << " with address " << externalAddress;
  out.flush();
}
#endif


#if PTRACING
void OpalManagerCLI::CmdTrace(PCLI::Arguments & args, INT)
{
  if (args.GetCount() == 0)
    args.WriteUsage();
  else
    PTrace::Initialise(args[0].AsUnsigned(),
                       args.GetCount() > 1 ? (const char *)args[1] : NULL,
                       PTrace::GetOptions());
}
#endif // PTRACING


void OpalManagerCLI::CmdListCodecs(PCLI::Arguments & args, INT)
{
  OpalMediaFormatList formats;
  OpalMediaFormat::GetAllRegisteredMediaFormats(formats);

  PCLI::Context & out = args.GetContext();
  OpalMediaFormatList::iterator format;
  for (format = formats.begin(); format != formats.end(); ++format) {
    if (format->GetMediaType() == OpalMediaType::Audio() && format->IsTransportable())
      out << *format << '\n';
  }

#if OPAL_VIDEO
  for (format = formats.begin(); format != formats.end(); ++format) {
    if (format->GetMediaType() == OpalMediaType::Video() && format->IsTransportable())
      out << *format << '\n';
  }
#endif

  for (format = formats.begin(); format != formats.end(); ++format) {
    if (format->GetMediaType() != OpalMediaType::Audio() &&
#if OPAL_VIDEO
        format->GetMediaType() != OpalMediaType::Video() &&
#endif
        format->IsTransportable())
      out << *format << '\n';
  }

  out.flush();
}


void OpalManagerCLI::CmdDelay(PCLI::Arguments & args, INT)
{
  if (args.GetCount() < 1)
    args.WriteUsage();
  else {
    PTimeInterval delay(0, args[0].AsUnsigned());
    m_endRun.Wait(delay);
  }
}


void OpalManagerCLI::CmdVersion(PCLI::Arguments & args, INT)
{
  PrintVersion(args.GetContext());
}


void OpalManagerCLI::CmdQuit(PCLI::Arguments & args, INT)
{
  if (PIsDescendant(args.GetContext().GetBaseReadChannel(), PConsoleChannel))
    CmdShutDown(args, 0);
  else
    args.GetContext().Stop();
}


void OpalManagerCLI::CmdShutDown(PCLI::Arguments & args, INT)
{
  args.GetContext().GetCLI().Stop();
}


#endif // P_CLI


/////////////////////////////////////////////////////////////////////////////
