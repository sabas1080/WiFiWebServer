/*********************************************************************************************************************************
  WiFiWebServer.hpp - Dead simple web-server.
  For any WiFi shields, such as WiFiNINA W101, W102, W13x, or custom, such as ESP8266/ESP32-AT, Ethernet, etc

  WiFiWebServer is a library for the ESP32-based WiFi shields to run WebServer
  Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
  Forked and modified from Arduino WiFiNINA library https://www.arduino.cc/en/Reference/WiFiNINA
  Built by Khoi Hoang https://github.com/khoih-prog/WiFiWebServer
  Licensed under MIT license

  Original author:
  @file       Esp8266WebServer.h
  @author     Ivan Grokhotkov

  Version: 1.8.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      12/02/2020 Initial coding for SAMD21, Nano 33 IoT, etc running WiFiNINA
  ...
  1.6.0   K Hoang      13/02/2022 Add support to new ESP32-S3 and ESP32_C3
  1.6.1   K Hoang      13/02/2022 Fix v1.6.0 issue
  1.6.2   K Hoang      22/02/2022 Add support to megaAVR using Arduino megaAVR core
  1.6.3   K Hoang      02/03/2022 Fix decoding error bug
  1.7.0   K Hoang      05/04/2022 Fix issue with Portenta_H7 core v2.7.2+
  1.8.0   K Hoang      26/04/2022 Add WiFiMulti library support and examples.
 **********************************************************************************************************************************/

#pragma once

#ifndef WiFiWebServer_HPP
#define WiFiWebServer_HPP

#define USE_NEW_WEBSERVER_VERSION       true

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #if defined(WIFI_USE_PORTENTA_H7)
    #undef WIFI_USE_PORTENTA_H7
  #endif
  #define WIFI_USE_PORTENTA_H7        true
  
  #if defined(USE_NEW_WEBSERVER_VERSION)
    #undef USE_NEW_WEBSERVER_VERSION
  #endif
  #define USE_NEW_WEBSERVER_VERSION   false
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use mbed-portenta architecture for PORTENTA_H7 from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#if    ( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(__SAMD21G18A__) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD21E18A__) || defined(__SAMD51__) || defined(__SAMD51J20A__) || defined(__SAMD51J19A__) \
      || defined(__SAMD51G19A__) || defined(__SAMD51P19A__) || defined(__SAMD21G18A__) )
  #if defined(WIFI_USE_SAMD)
    #undef WIFI_USE_SAMD
  #endif
  #define WIFI_USE_SAMD      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use SAMD architecture from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#if (defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
     defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || \
     defined(NRF52840_CLUE) || defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || \
     defined(MDBT50Q_RX) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )
  #if defined(WIFI_USE_NRF528XX)
    #undef WIFI_USE_NRF528XX
  #endif
  #define WIFI_USE_NRF528XX      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use nFR52 architecture from WiFiWebServer
  #endif
  
  #include <Adafruit_TinyUSB.h>

#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #if defined(WIFI_USE_SAM_DUE)
    #undef WIFI_USE_SAM_DUE
  #endif
  #define WIFI_USE_SAM_DUE      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use SAM_DUE architecture from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(STM32F0) || defined(STM32F1) || defined(STM32F2) || defined(STM32F3)  ||defined(STM32F4) || defined(STM32F7) || \
       defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32H7)  ||defined(STM32G0) || defined(STM32G4) || \
       defined(STM32WB) || defined(STM32MP1) ) && !( defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4) )
  #if (_WIFI_LOGLEVEL_ > 2)     
    #warning STM32F/L/H/G/WB/MP1 board selected
  #endif

  #if defined(WIFI_USE_STM32)
    #undef WIFI_USE_STM32
  #endif
  #define WIFI_USE_STM32      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use STM32 architecture from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_NANO_RP2040_CONNECT) || defined(ARDUINO_ARCH_RP2040) || defined(ARDUINO_RASPBERRY_PI_PICO) || \
      defined(ARDUINO_ADAFRUIT_FEATHER_RP2040) || defined(ARDUINO_GENERIC_RP2040) )
      
  #if (_WIFI_LOGLEVEL_ > 2)    
    #warning RP2040-based board selected
  #endif

  #if defined(WIFI_USE_RP2040)
    #undef WIFI_USE_RP2040
  #endif
  #define WIFI_USE_RP2040      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use RP2040 architecture from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#if ( defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_AVR_NANO_EVERY) )  

  #include "ArduinoSTL.h"
  
  #if defined(WIFI_USE_MEGA_AVR)
    #undef WIFI_USE_MEGA_AVR
  #endif
  #define WIFI_USE_MEGA_AVR      true
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use Arduino megaAVR architecture from WiFiWebServer
  #endif
  
#elif ( defined(__AVR_ATmega4809__)     || defined(ARDUINO_AVR_ATmega4809) || defined(ARDUINO_AVR_ATmega4808) || \
      defined(ARDUINO_AVR_ATmega3209) || defined(ARDUINO_AVR_ATmega3208) || defined(ARDUINO_AVR_ATmega1609) || \
      defined(ARDUINO_AVR_ATmega1608) || defined(ARDUINO_AVR_ATmega809)  || defined(ARDUINO_AVR_ATmega808) )  
  
  #if defined(WIFI_USE_MEGACOREX)
    #undef WIFI_USE_MEGACOREX
  #endif
  #define WIFI_USE_MEGACOREX      true
  #error megaAVR architecture and MegaCoreX from WiFiWebServer not supported yet
  
#endif

/////////////////////////////////////////////////////////////////////////

// To support lambda function in class
#include <functional-vlpp.h>

#if !defined(USE_WIFI_NINA)
  #define USE_WIFI_NINA     true
#endif

// Modify to use new WiFiNINA_Generic library to support boards besides Nano-33 IoT, MKRWiFi1010, Adafruit MetroM4, etc.
#if USE_WIFI_NINA
  #include <WiFiNINA_Generic.h>
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use WiFiNINA_Generic from WiFiWebServer
  #endif
#elif USE_WIFI101
  #include <WiFi101.h>
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use WiFi101 from WiFiWebServer
  #endif
#elif USE_WIFI_CUSTOM
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use Custom WiFi for WiFiWebServer
  #endif
#else
  #include <WiFi.h>
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning Use WiFi.h from WiFiWebServer
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#include "utility/mimetable.h"
#include "utility/RingBuffer.h"

// KH, For PROGMEM commands
// ESP32/ESP8266 includes <pgmspace.h> by default, and memccpy_P was already defined there
#if !(ESP32 || ESP8266 || defined(ARDUINO_PORTENTA_H7_M7) || defined(ARDUINO_PORTENTA_H7_M4))
  #include <avr/pgmspace.h>
  #define memccpy_P(dest, src, c, n) memccpy((dest), (src), (c), (n))
#endif

/////////////////////////////////////////////////////////////////////////

// Permit redefinition of SENDCONTENT_P_BUFFER_SZ in sketch, default is 4K, minimum is 256 bytes
#ifndef SENDCONTENT_P_BUFFER_SZ
  #define SENDCONTENT_P_BUFFER_SZ     4096
  
  #if (_WIFI_LOGLEVEL_ > 2)
    #warning SENDCONTENT_P_BUFFER_SZ using default 4 Kbytes
  #endif
#else
  #if (SENDCONTENT_P_BUFFER_SZ < 256)
    #undef SENDCONTENT_P_BUFFER_SZ
    #define SENDCONTENT_P_BUFFER_SZ   256
    
    #if (_WIFI_LOGLEVEL_ > 2)
      #warning SENDCONTENT_P_BUFFER_SZ reset to min 256 bytes
    #endif
  #endif
#endif

/////////////////////////////////////////////////////////////////////////

#ifndef PGM_VOID_P
  #define PGM_VOID_P const void *
#endif

//////

enum HTTPMethod 
{ 
  HTTP_ANY, 
  HTTP_GET,
  HTTP_HEAD,
  HTTP_POST, 
  HTTP_PUT, 
  HTTP_PATCH, 
  HTTP_DELETE, 
  HTTP_OPTIONS 
};

enum HTTPUploadStatus 
{ 
  UPLOAD_FILE_START, 
  UPLOAD_FILE_WRITE, 
  UPLOAD_FILE_END,
  UPLOAD_FILE_ABORTED
};

enum HTTPClientStatus 
{ 
  HC_NONE, 
  HC_WAIT_READ, 
  HC_WAIT_CLOSE 
};

enum HTTPAuthMethod 
{ 
  BASIC_AUTH, 
  DIGEST_AUTH 
};

#define HTTP_DOWNLOAD_UNIT_SIZE 1460

// Permit user to increase HTTP_UPLOAD_BUFLEN larger than default 2K
//#define HTTP_UPLOAD_BUFLEN 2048
#if !defined(HTTP_UPLOAD_BUFLEN)
  #define HTTP_UPLOAD_BUFLEN 2048
#endif

#define HTTP_MAX_DATA_WAIT    5000 //ms to wait for the client to send the request
#define HTTP_MAX_POST_WAIT    5000 //ms to wait for POST data to arrive
#define HTTP_MAX_SEND_WAIT    5000 //ms to wait for data chunk to be ACKed
#define HTTP_MAX_CLOSE_WAIT   2000 //ms to wait for the client to close the connection

#define CONTENT_LENGTH_UNKNOWN ((size_t) -1)
#define CONTENT_LENGTH_NOT_SET ((size_t) -2)

/////////////////////////////////////////////////////////////////////////

#define RETURN_NEWLINE       "\r\n"

#include <string>
#include <Arduino.h>

typedef std::string WWString;

/////////////////////////////////////////////////////////////////////////

class WiFiWebServer;

typedef struct 
{
  HTTPUploadStatus status;
  String  filename;
  String  name;
  String  type;
  size_t  totalSize;      // file size
  size_t  currentSize;    // size of data currently in buf
  size_t  contentLength;  // size of entire post request, file size + headers and other request data.
  uint8_t buf[HTTP_UPLOAD_BUFLEN];
} HTTPUpload;

#include "utility/RequestHandler.h"

#if (ESP32 || ESP8266)
    #include "FS.h"
#endif

class WiFiWebServer
{
  public:
    WiFiWebServer(int port = 80);
    ~WiFiWebServer();

    void begin();
    void handleClient();

    void close();
    void stop();

    bool authenticate(const char * username, const char * password);
    void requestAuthentication();

    typedef vl::Func<void(void)> THandlerFunction;
    //typedef std::function<void(void)> THandlerFunction;
    //typedef void (*THandlerFunction)(void);

    void on(const String &uri, THandlerFunction handler);
    void on(const String &uri, HTTPMethod method, THandlerFunction fn);
    void on(const String &uri, HTTPMethod method, THandlerFunction fn, THandlerFunction ufn);
    void addHandler(RequestHandler* handler);
    void onNotFound(THandlerFunction fn);   //called when handler is not assigned
    void onFileUpload(THandlerFunction fn); //handle file uploads

    String uri() 
    {
      return _currentUri;
    }
    
    HTTPMethod method() 
    {
      return _currentMethod;
    }
    
    WiFiClient client() 
    {
      return _currentClient;
    }
    
    //KH
#if USE_NEW_WEBSERVER_VERSION
    HTTPUpload& upload() 
    {
      return *_currentUpload;
    }
#else
    HTTPUpload& upload() 
    {
      return _currentUpload;
    }
#endif
    
    String arg(const String& name);         // get request argument value by name
    String arg(int i);                      // get request argument value by number
    String argName(int i);                  // get request argument name by number
    
    int     args();                         // get arguments count
    bool    hasArg(const String& name);     // check if argument exists
    void    collectHeaders(const char* headerKeys[], const size_t headerKeysCount); // set the request headers to collect
    String  header(const String& name);     // get request header value by name
    String  header(int i);                  // get request header value by number
    String  headerName(int i);              // get request header name by number
    int     headers();                      // get header count
    bool    hasHeader(const String& name);  // check if header exists

    String hostHeader();                    // get request host header if available or empty String if not

    // send response to the client
    // code - HTTP response code, can be 200 or 404
    // content_type - HTTP content type, like "text/plain" or "image/png"
    // content - actual content body
    void send(int code, const char* content_type = NULL, const String& content = String(""));
    void send(int code, char* content_type, const String& content);
    void send(int code, const String& content_type, const String& content);
    //KH
    void send(int code, char*  content_type, const String& content, size_t contentLength);
    
    void setContentLength(size_t contentLength);
    void sendHeader(const String& name, const String& value, bool first = false);
    void sendContent(const String& content);
    void sendContent(const String& content, size_t size);

    // KH, Restore PROGMEM commands
    void send_P(int code, PGM_P content_type, PGM_P content);
    void send_P(int code, PGM_P content_type, PGM_P content, size_t contentLength);
    
    void sendContent_P(PGM_P content);
    void sendContent_P(PGM_P content, size_t size);
    //////

    static String urlDecode(const String& text);
    
#if !(ESP32 || ESP8266)
    template<typename T> size_t streamFile(T &file, const String& contentType) 
    {
      using namespace mime;
      setContentLength(file.size());
      
      if (String(file.name()).endsWith(mimeTable[gz].endsWith) && contentType != mimeTable[gz].mimeType && contentType != mimeTable[none].mimeType) 
      {
        sendHeader("Content-Encoding", "gzip");
      }
      
      send(200, contentType, "");
      
      return _currentClient.write(file);
    }
    
#else
    
    void serveStatic(const char* uri, fs::FS& fs, const char* path, const char* cache_header = NULL ); // serve static pages from file system

    // Handle a GET request by sending a response header and stream file content to response body
      template<typename T>
      size_t streamFile(T &file, const String& contentType) 
      {
        return streamFile(file, contentType, HTTP_GET);
      }

      // Implement GET and HEAD requests for files.
      // Stream body on HTTP_GET but not on HTTP_HEAD requests.
      template<typename T>
      size_t streamFile(T &file, const String& contentType, HTTPMethod requestMethod) 
      {
        size_t contentLength = 0;
        
        _streamFileCore(file.size(), file.name(), contentType);
        
        if (requestMethod == HTTP_GET) 
        {
            contentLength = _customClientWrite(file);
        }
        return contentLength
        ;
      }
#endif    

  protected:
    void _addRequestHandler(RequestHandler* handler);
    void _handleRequest();
    void _finalizeResponse();
    bool _parseRequest(WiFiClient& client);
    
    //KH
    #if USE_NEW_WEBSERVER_VERSION
    void _parseArguments(const String& data);
    int  _parseArgumentsPrivate(const String& data, vl::Func<void(String&,String&,const String&,int,int,int,int)> handler);
    bool _parseForm(WiFiClient& client, const String& boundary, uint32_t len);
    #else
    void _parseArguments(const String& data);
    bool _parseForm(WiFiClient& client, const String& boundary, uint32_t len);
    #endif
    
    static String _responseCodeToString(int code);    
    bool          _parseFormUploadAborted();
    void          _uploadWriteByte(uint8_t b);
    uint8_t       _uploadReadByte(WiFiClient& client);
    void          _prepareHeader(String& response, int code, const char* content_type, size_t contentLength);
    void          _prepareHeader(WWString& response, int code, const char* content_type, size_t contentLength);
    bool          _collectHeader(const char* headerName, const char* headerValue);
    
#if (ESP32 || ESP8266)
    void _streamFileCore(const size_t fileSize, const String & fileName, const String & contentType);

    template<typename T>
    size_t _customClientWrite(T &file) 
    {
      char buffer[256];
      size_t contentLength = 0;
      size_t bytesRead = 0;

      // read up to sizeof(buffer) bytes
      while ((bytesRead = file.readBytes(buffer, sizeof(buffer))) > 0)
      {
        _currentClient.write(buffer, bytesRead);
        contentLength += bytesRead;
      }

      return contentLength;
    }
#endif
    
    struct RequestArgument 
    {
      String key;
      String value;
    };

    WiFiServer  _server;

    WiFiClient        _currentClient;
    HTTPMethod        _currentMethod;
    String            _currentUri;
    uint8_t           _currentVersion;
    HTTPClientStatus  _currentStatus;
    unsigned long     _statusChange;

    RequestHandler*   _currentHandler   = nullptr;
    RequestHandler*   _firstHandler     = nullptr;
    RequestHandler*   _lastHandler      = nullptr;
    THandlerFunction  _notFoundHandler;
    THandlerFunction  _fileUploadHandler;

    int               _currentArgCount;
    RequestArgument*  _currentArgs      = nullptr;

    //KH = nullptr
#if USE_NEW_WEBSERVER_VERSION
    HTTPUpload*       _currentUpload    = nullptr;
    int               _postArgsLen;
    RequestArgument*  _postArgs         = nullptr;
    
#else
    HTTPUpload        _currentUpload;
#endif
    
    int               _headerKeysCount;
    RequestArgument*  _currentHeaders   = nullptr;
    size_t            _contentLength;
    String            _responseHeaders;

    String            _hostHeader;
    bool              _chunked;
};

#endif    // WiFiWebServer_HPP
