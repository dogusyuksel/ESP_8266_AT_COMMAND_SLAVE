//------------------------------------------------------------------------------------
// Libraries Needed For This Project
//------------------------------------------------------------------------------------
#include <ESP8266WiFi.h>    // The Basic Function Of The ESP NOD MCU
#include <string.h>
#include <stdio.h>

//definitions
#define VERSION                         "00.00.04"
#define MANUFACTURER                    "dodo_corp"
#define PRODUCT                         "NODE"
#define IDENTIFICATION_STRING           MANUFACTURER "_" PRODUCT "_" VERSION
#define MAX_SERIAL_READ_DATA_BUFFER_LEN 256
#define CR                              0x0D
#define MIN_AT_COMMAND_LEN              2
//#define ECHO_ON                         1
#define ERROR_PREFIX                    "ERR"
#define BAUDRATE_DEFAULT_VALUE          9600
#define SEQUENTIAL_DIGITAL_PIN_COUNT    9
#define SEQUENTIAL_ANALOG_PIN_COUNT     1
#define ACCESS_POINT_CONNECTION_TIMEOUT 30000
#define MAX_CONNECTED_DEVICE_COUNT      4  //from this link: https://github.com/esp8266/Arduino/issues/570
#define LED0                            2         // WIFI Module LED
#define LED_TOGGLE_CONSTANT             1000


//Enumerations and structure here
typedef enum
{
  ERR_OK,
  ERR_UNEXPECTED,
  ERR_WRONG_COMMAND,
  ERR_NO_HW_SUPPORT,
  ERR_WRONG_DATA,
  ERR_CANNOT_JOIN_ACCESS_POINT,
  ERR_NOT_CONNECTED_WIFI,
  ERR_WIFI_DISCONNECTED,
  ERR_UNUSED_COMMAND,
  ERR_NOT_CONNECTED_TCP,
  ERR_NO_CONNECTED_DEVICE,
  ERR_NO_SERVER_DATA,
  ERR_NOT_SUPPORTED,
  ERR_CANNOT_GET_IP_ADDRESSES,
  ERR_TCP_CONN_EXIST
} ERROR_CODES;

typedef enum
{
  STA_COMMAND,
  STA_TRANSPARENT
} DEVICE_STATUS;

typedef enum
{
  STA_CLIENT,
  STA_SERVER
} MODEM_STATUS;

typedef enum
{
  COMMAND_GET,    //note that, GET commands have no additional data part so we can control them by their len
  COMMAND_SET
} AT_COMMAND_TYPE;


//NOTE THAT: p means plus, m means minus e means equal sign, q question mark
typedef enum
{
  AT = 1,         //1
  ATI,
  ATpGMI,
  ATpGMM,
  ATpGMR,         //5
  ATpDEF,
  ATpCUR,
  ATpQPOWD,
  ATpCIOBOUDq,
  ATpSETDOq,      //10
  ATpGETDIq,      
  ATpGETAIq,
  ATpRST,
  ATpCWLAPq,
  ATpCWJAPq,      //15
  ATpCWQAP,       
  ATpCIFSRq,
  ATpCWSAPq,
  ATpCWMODEq,
  ATpCIPMUXq,     //20
  ATpCWLIF,       
  ATpCIPSTATUS,
  ATpCIPSTATUSe,
  ATpCIPCLOSE,
  ATpCIOBOUDe,    //25
  ATpCWJAPe,      
  ATpCWMODEe,
  ATpCIPMUXe,
  ATpCONNe,
  ATpGETDTe,    //30
  ATpSENDe,
  ATpGETDT,
  NUMBER_OF_AT_COMMANDS     //DO NOT REMOVE IT AND IT MUST BE LOCATED AT THE END OF THIS ENUM LIST
} AT_COMMAND_ID;

typedef struct
{
  AT_COMMAND_ID atCommandID;
  char atCommandText[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  char atCommandResponse[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  bool atCommandResponseDirect;
  AT_COMMAND_TYPE atCommandType;
  bool bSendAfterExecution;
} AT_COMMAND_STRUCTURE;


//variables
AT_COMMAND_STRUCTURE AT_Command_Structure[NUMBER_OF_AT_COMMANDS] = 
{
  {AT,            "AT",             "OK",                                     true,         COMMAND_GET,          false},   //check device is ready or not, returns "OK",, directly send the initial string 
  {ATI,           "ATI",            IDENTIFICATION_STRING,                    true,         COMMAND_GET,          false},   //it returns identification string, directly send the initial string
  {ATpGMI,        "AT+GMI",         MANUFACTURER,                             true,         COMMAND_GET,          false},   //it returns manufacturer, directly send the initial string
  {ATpGMM,        "AT+GMM",         PRODUCT,                                  true,         COMMAND_GET,          false},   //it returns product, directly send the initial string
  {ATpGMR,        "AT+GMR",         VERSION,                                  true,         COMMAND_GET,          false},   //it returns version, directly send the initial string
  {ATpDEF,        "AT+DEF",         "OK",                                     true,         COMMAND_SET,          true },   //it sets all parameters to default, normally it will sen "OK" BUT JUST AFTER OPERATION WAS FINISHED
  {ATpCUR,        "AT+CUR",         "",                                       false,        COMMAND_GET,          true },   //it returns all canfigurations 
  {ATpQPOWD,      "AT+QPOWD",       "",                                       false,        COMMAND_SET,          true },   //Urgent power off, returns "OK", but we dont have a power off hardware support for this card
  {ATpCIOBOUDq,   "AT+CIOBOUD?",    "",                                       false,        COMMAND_GET,          true },   //it returns current baud rate
  {ATpSETDOq,     "AT+SETDO=",      "",                                       false,        COMMAND_SET,          true },   //it set a pin DO and write a value over on it
  {ATpGETDIq,     "AT+GETDI=",      "",                                       false,        COMMAND_GET,          true },   //it sets a pin DI and returns its value to master
  {ATpGETAIq,     "AT+GETAI=",      "",                                       false,        COMMAND_GET,          true },   //it sets a pin as AI and returns its raw data value to master
  {ATpRST,        "AT+RST",         "RESET_ON",                               true,         COMMAND_SET,          true },   //soft reset
  {ATpCWLAPq,     "AT+CWLAP?",      "",                                       false,        COMMAND_GET,          false},   //UNUSED COMMAND
  {ATpCWJAPq,     "AT+CWJAP?",      "",                                       false,        COMMAND_GET,          true },   //returns current connected wifi name
  {ATpCWQAP,      "AT+CWQAP",       "OK",                                     true,         COMMAND_SET,          true },   //it quits access point
  {ATpCIFSRq,     "AT+CIFSR?",      "",                                       false,        COMMAND_GET,          true },   //returns local ip address
  {ATpCWSAPq,     "AT+CWSAP?",      "",                                       false,        COMMAND_GET,          false},   //UNUSED COMMAND
  {ATpCWMODEq,    "AT+CWMODE?",     "",                                       false,        COMMAND_GET,          true },   //returns modem status, server or client
  {ATpCIPMUXq,    "AT+CIPMUX?",     "OK",                                     true,         COMMAND_GET,          true },   //check TCP connection is exists or not
  {ATpCWLIF,      "AT+CWLIF",       "",                                       false,        COMMAND_GET,          true },   //check joined devices ip, returns "IP:xxxxxx,yyyyyy,zzzzzz
  {ATpCIPSTATUS,  "AT+CIPSTATUS",   "",                                       false,        COMMAND_GET,          true },   //it returns the device status
  {ATpCIPSTATUSe, "AT+CIPSTATUS=",  "OK",                                     true,         COMMAND_SET,          true },   //it sets the device status
  {ATpCIPCLOSE,   "AT+CIPCLOSE",    "OK",                                     true,         COMMAND_SET,          true },   //it closes the TCP connection
  {ATpCIOBOUDe,   "AT+CIOBOUD=",    "",                                       false,        COMMAND_SET,          true },   //it sets baud rate, we will wait just integer number after '='
  {ATpCWJAPe,     "AT+CWJAP=",      "",                                       false,        COMMAND_SET,          true },   //we get SSID and Pass and then connect to an WiFi network
  {ATpCWMODEe,    "AT+CWMODE=",     "OK",                                     true,         COMMAND_SET,          true },   //change modem mode
  {ATpCIPMUXe,    "AT+CIPMUX=",     "",                                       false,        COMMAND_GET,          false},   //UNUSED COMMAND
  {ATpCONNe,      "AT+CONN=",       "OK",                                     true,         COMMAND_SET,          true },   //Connect to specified server
  {ATpGETDTe,     "AT+GETDT=",      "",                                       false,        COMMAND_GET,          true },   //it is used for getting a client data that previously connected to this device
  {ATpSENDe,      "AT+SEND=",       "OK",                                     true,         COMMAND_SET,          true },   //send n data to server in command mode
  {ATpGETDT,      "AT+GETDT",       "",                                       false,        COMMAND_GET,          true }    //it sends a data that came from server when we are in client mode
};
DEVICE_STATUS xglbDeviceStatus = STA_COMMAND;
MODEM_STATUS  xglbModemStatus  = STA_CLIENT;
#ifdef ECHO_ON
  bool bIsEchoOn = true;
#else
  bool bIsEchoOn = false;
#endif
String sLastConnectedAccessPointName = "";
String sLastConnectedAccessPointPass = "";
WiFiClient xglbClient;
String sLastConnectedHostName = "";
unsigned int uiLastConnectedHostPort = 0;
char *sServerAnswer = NULL;

WiFiClient glb_clientList[MAX_CONNECTED_DEVICE_COUNT];                              //used for client instance      , if we are in server mode
IPAddress  glb_clientIPAddresses[MAX_CONNECTED_DEVICE_COUNT];                       //used for clients' ip address  , if we are in server mode
long       glb_LastDataComeFromClientsMillis[MAX_CONNECTED_DEVICE_COUNT];           //used for clients' last success connection/communication time      , if we are in server mode
bool       glb_clientStatusList[MAX_CONNECTED_DEVICE_COUNT];                        //used for 'connected' status for each client      , if we are in server mode
String     glb_clientsDataString[MAX_CONNECTED_DEVICE_COUNT];                       //they holds last packet of the connected devices

//timer related variables
unsigned long ulStartingMillis = 0;
unsigned short usTimerMillis = 0;

unsigned int ledToggleCounter = 0;
unsigned long ledToggleMillis = 0;

//current values
int iCurrentBaudRate = BAUDRATE_DEFAULT_VALUE;

//function prototypes
void startTimer(unsigned short elapsedTime);
bool isTimeOut(void);
void toggleLed(void);

void vSendQuickResponseAfterExecution(AT_COMMAND_ID theCommand);

unsigned short usGetATCommandPacket(char *commandBuffer, unsigned int len); //it returns len of the command
AT_COMMAND_ID  xATCommandParser(char *commandBuffer, unsigned short commandLen, char *commandDataPart, unsigned short *commandDataLen); //It returns AT Command ID
ERROR_CODES xAtCommandSender(AT_COMMAND_ID theCommand, char *commandDataPart, unsigned short commandDataLen); //it send a response and returns a error code

ERROR_CODES xSetAllParametersToDefault(void); //it sets all parameters to default
ERROR_CODES xDisplayCurrentConfiguration();   //it display curret configuration
ERROR_CODES xSetBaudRate(char *commandDataPart, unsigned short commandDataLen); //it changed the baud rate
ERROR_CODES xSetDigitalOutput(char *commandDataPart, unsigned short commandDataLen);  //it set a pin as DO and write a value over on it
ERROR_CODES xGetDigitalInput(char *commandDataPart, unsigned short commandDataLen);   //it returns DI value of the specified pin
ERROR_CODES xGetAnalogInputInput(char *commandDataPart, unsigned short commandDataLen);   //it returns AI value of the specified pin (returns RAW data, not voltage value)
ERROR_CODES xJoinAccessPoint(char *commandDataPart, unsigned short commandDataLen);   //it joins an access point
ERROR_CODES xQuitAccessPoint(void); //quit access point
ERROR_CODES xChangeModemMode(char *commandDataPart, unsigned short commandDataLen);   //it changes modem mode
ERROR_CODES xChangeDeviceMode(char *commandDataPart, unsigned short commandDataLen);   //it changes modem mode
ERROR_CODES xCollectConnectedDevicesIPAddresses(char *commandDataPart, unsigned short commandDataLen); //it sends all connected deviceses (If we are a server mode) IP addresses
ERROR_CODES xCloseCurrentConnections(void); //it closes the current connections (operation will be changed in case the mode is server or client)
ERROR_CODES xConnectToHost(char *commandDataPart, unsigned short commandDataLen); //connect to a specified host and port
ERROR_CODES xSendClientsData(char *commandDataPart, unsigned short commandDataLen); //send clients data to master
ERROR_CODES xSendIncomingDataToServer(char *commandDataPart, unsigned short commandDataLen); //send data to connected server
ERROR_CODES xSendServerDataToMaster(void); //send servers data to master

void setup() 
{
  xSetAllParametersToDefault(); //call just this.
  
  Serial.println("DEVICE STARTED");
}

//====================================================================================
  
void loop()
{
  //arrange led blink to understand the system is alive
  toggleLed();

  if(xglbModemStatus  == STA_SERVER)
  {
    //acceps connections and receive their data
    //TODO, fill here later  

    xglbModemStatus  = STA_CLIENT;
  }
  else
  {
    //close acceptence and clear buffers
    //TODO fill here later

    //control any answers that came from server side
    if((WiFi.status() == WL_CONNECTED) && (xglbClient.status() != 0))
    {
      while(xglbClient.available())
      {
        String line = xglbClient.readStringUntil(CR);
        int lineLen = line.length();
        sServerAnswer = (char *)realloc(sServerAnswer, (lineLen + 1));
        memset(sServerAnswer, 0, (lineLen + 1));
        line.toCharArray(sServerAnswer, (lineLen + 1));
        Serial.print("DTRDY," + String(lineLen) + "\x0D");
      }
    }
  }

  if(xglbDeviceStatus == STA_COMMAND)
  {
    char cSerialReadBuffer[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cSerialReadBuffer, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
    unsigned short dataLen = 0;
    char cSerialReadBufferDataPart[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cSerialReadBufferDataPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
    unsigned short dataPartLen = 0;
    if((dataLen = usGetATCommandPacket(cSerialReadBuffer, MAX_SERIAL_READ_DATA_BUFFER_LEN)) > 0)
    {
      //received command, then parse and action here
      AT_COMMAND_ID receivedCOmmandID = xATCommandParser(cSerialReadBuffer, dataLen, cSerialReadBufferDataPart, &dataPartLen);
      ERROR_CODES commandParserErrorCode = ERR_OK;
      if((commandParserErrorCode = xAtCommandSender(receivedCOmmandID, cSerialReadBufferDataPart, dataPartLen)) != ERR_OK)
      {
        //send error code here (global error code)
        char errorAnswerBuffer[MAX_SERIAL_READ_DATA_BUFFER_LEN];
        memset(errorAnswerBuffer, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
        sprintf(errorAnswerBuffer, "%s_%d\x0D", (char *)ERROR_PREFIX, (int)commandParserErrorCode);
        Serial.write(errorAnswerBuffer, strlen(errorAnswerBuffer));
      }
    }
  }
  else
  {
    //TODO, we are in transparent mode now
    xglbDeviceStatus = STA_COMMAND;
    //Do it later
  }
}

//quick functions
void startTimer(unsigned short elapsedTime)
{
  ulStartingMillis = millis();
  usTimerMillis = elapsedTime;
}

bool isTimeOut(void)
{
  ESP.wdtFeed();
  if((millis() - ulStartingMillis) >= usTimerMillis)
    return true;
  return false;
}

void toggleLed()
{
  if((millis() - ledToggleMillis) >  LED_TOGGLE_CONSTANT)
  {
    ledToggleMillis = millis();
    if(((ledToggleCounter++)%2) == 0)
    {
      digitalWrite(LED0, !HIGH);
    }
    else
    {
     digitalWrite(LED0, !LOW);
    }
  }
  
  if(ledToggleCounter >= LED_TOGGLE_CONSTANT)
    ledToggleCounter = 0;
}


void vSendQuickResponseAfterExecution(AT_COMMAND_ID theCommand)
{
  for(int i = 0; i < NUMBER_OF_AT_COMMANDS; i++)
  {
    if( (AT_Command_Structure[i].atCommandID == theCommand) && (strlen(AT_Command_Structure[i].atCommandResponse) != 0) && (AT_Command_Structure[i].atCommandResponseDirect == true) && (AT_Command_Structure[i].bSendAfterExecution == true))
    {
      if(bIsEchoOn)
      {
        //TODO, send echo for quick responded commands
      }
      
      Serial.print(String(AT_Command_Structure[i].atCommandResponse) + "\x0D");
    }
  }
}


ERROR_CODES xAtCommandSender(AT_COMMAND_ID theCommand, char *commandDataPart, unsigned short commandDataLen)  //char *commandDataPart, unsigned short commandDataLen we will use these things to parse data
{
  ERROR_CODES returnValue = ERR_OK;

  char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  int iBufferToSendLen = 0;
  memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);

  //send quick response here
  for(int i = 0; i < NUMBER_OF_AT_COMMANDS; i++)
  {
    if( (AT_Command_Structure[i].atCommandID == theCommand) && (strlen(AT_Command_Structure[i].atCommandResponse) != 0) && (AT_Command_Structure[i].atCommandResponseDirect == true) && (AT_Command_Structure[i].bSendAfterExecution == false))
    {
      if(bIsEchoOn)
      {
        //TODO, send echo for quick responded commands
      }
      
      Serial.print(String(AT_Command_Structure[i].atCommandResponse) + "\x0D");
      return returnValue;
    }
  }

  switch (theCommand) 
  {
    //NOTE THAT: Use first line serial prints as ECHO, just in case
    case AT:
      // statements
      if(bIsEchoOn)
        Serial.print("AT\x0D");
      break;
    case ATI:
      // statements
      if(bIsEchoOn)
        Serial.print("ATI\x0D");
      break;
    case ATpGMI:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GMI\x0D");
      break;
    case ATpGMM:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GMM\x0D");
      break;
    case ATpGMR:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GMR\x0D");
      break;
    case ATpDEF:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+DEF\x0D");
      //it sets all parameters to default values
      returnValue = xSetAllParametersToDefault();
      break;
    case ATpCUR:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CUR\x0D");
      //display current configuration
      returnValue = xDisplayCurrentConfiguration();
      break;
    case ATpQPOWD:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+QPOWD\x0D");
      //do urgent power off
      returnValue = ERR_NO_HW_SUPPORT;
      break;
    case ATpCIOBOUDq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIOBOUD?\x0D");
      //return baudrate
      sprintf(cBufferToSend, "BAUD%d\x0D", iCurrentBaudRate);
      iBufferToSendLen = strlen(cBufferToSend);
      Serial.write(cBufferToSend, iBufferToSendLen);
      break;
    case ATpSETDOq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+SETDO?=\x0D");
      //set a pin as DO and write a value over on it
      returnValue = xSetDigitalOutput(commandDataPart, commandDataLen);
      break;
    case ATpGETDIq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GETDI=\x0D");
      //set a pin as DI and return its value
      returnValue = xGetDigitalInput(commandDataPart, commandDataLen);
      break;
    case ATpGETAIq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GETAI=\x0D");
      //set a pin as AI and return its value
      returnValue = xGetAnalogInputInput(commandDataPart, commandDataLen);
      break;
    case ATpRST:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+RST\x0D");
      //do soft reset
      vSendQuickResponseAfterExecution(ATpRST);
      delay(50);
      ESP.reset();
      break;
    case ATpCWLAPq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWLAP?\x0D");
      //This is unused for now (maybe future use)
      returnValue = ERR_UNUSED_COMMAND;
      break;
    case ATpCWJAPq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWJAP?\x0D");
      //send currently connected access point name
      if(WiFi.status() == WL_CONNECTED)
        Serial.print(sLastConnectedAccessPointName + " OK\x0D");
       else
      {
        returnValue = ERR_NOT_CONNECTED_WIFI;
        sLastConnectedAccessPointName = "";
        sLastConnectedAccessPointPass = "";
      }
      break;
    case ATpCWQAP:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWQAP\x0D");
      //quit access point
      returnValue = xQuitAccessPoint();
      break;
    case ATpCIFSRq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIFSR?\x0D");
      //returns local ip address
      if(WiFi.status() == WL_CONNECTED)
        Serial.print("IP: " + String(WiFi.localIP()) + "\x0D");
       else
      {
        returnValue = ERR_NOT_CONNECTED_WIFI;
        sLastConnectedAccessPointName = "";
        sLastConnectedAccessPointPass = "";
      }
      break;
    case ATpCWSAPq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWSAP?\x0D");
      //This is unused for now (maybe future use)
      returnValue = ERR_UNUSED_COMMAND;
      break;
    case ATpCWMODEq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWMODE?\x0D");
      //retusn modem mode, server or client
      if(xglbModemStatus == STA_CLIENT) //return "CLIENT"
        Serial.print("CLIENT\x0D");
      else //we assume that it is server anyway
        Serial.print("SERVER\x0D");
      break;
    case ATpCIPMUXq:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIPMUX?\x0D");
      //check TCP connection is exists or not
      if((xglbClient.status() == 0))// && (sLastConnectedHostName == "") && (uiLastConnectedHostPort == 0)) //it means connection not exist
      {
        returnValue = ERR_NOT_CONNECTED_TCP;
        return returnValue;
      }
      vSendQuickResponseAfterExecution(ATpCIPMUXq);
      break;
    case ATpCWLIF:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWLIF\x0D");
      //check joined devices ip, returns "IP:xxxxxx,yyyyyy,zzzzzz
      returnValue = xCollectConnectedDevicesIPAddresses(commandDataPart, commandDataLen);
      break;
    case ATpCIPSTATUS:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIPSTATUS\x0D");
      //it returns the device status
      if((int)xglbDeviceStatus == 0) //it is in command mode
        Serial.print("CMM\x0D");
      else
        Serial.print("TRN\x0D");
      break;
    case ATpCIPSTATUSe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIPSTATUS=\x0D");
      //it sets the device status
      returnValue = xChangeDeviceMode(commandDataPart, commandDataLen);
      break;
    case ATpCIPCLOSE:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIPCLOSE\x0D");
      //it closes the TCP connection
      returnValue = xCloseCurrentConnections();  //closing operation is different in order to server or client mode
      break;
    case ATpCIOBOUDe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIOBOUD=\x0D");
      //set new baud rate and restart the uart here
      returnValue = xSetBaudRate(commandDataPart, commandDataLen);
      break;
    case ATpCWJAPe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWJAP=\x0D");
      //join an access point with name and password, parse the command and execute it in here.
      returnValue = xJoinAccessPoint(commandDataPart, commandDataLen);
      break;
    case ATpCWMODEe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CWJAP=\x0D");
      //change modem mode
      returnValue = xChangeModemMode(commandDataPart, commandDataLen);
      break;
    case ATpCIPMUXe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CIPMUX=\x0D");
      //This is unused for now (maybe future use)
      returnValue = ERR_UNUSED_COMMAND;
      break;
    case ATpCONNe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+CONN=\x0D");
      //connect specified port and host
      returnValue = xConnectToHost(commandDataPart, commandDataLen);
      break;
    case ATpGETDTe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GETDT=\x0D");
      //it sends Nth clients data to master
      returnValue = xSendClientsData(commandDataPart, commandDataLen);
      break;
    case ATpSENDe:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+SEND=\x0D");
      //it sends N data to server in command mode
      returnValue = xSendIncomingDataToServer(commandDataPart, commandDataLen);
      break;
    case ATpGETDT:
      // statements
      if(bIsEchoOn)
        Serial.print("AT+GETDT\x0D");
      //it sends the data that came from server in command mode(remember to clear keys after sending the data)
      returnValue = xSendServerDataToMaster();
      break;
    default:
      // statements
      returnValue = ERR_WRONG_COMMAND;
  }

  return returnValue;
}

AT_COMMAND_ID  xATCommandParser(char *commandBuffer, unsigned short commandLen, char *commandDataPart, unsigned short *commandDataLen)
{
  AT_COMMAND_ID returnValue = (AT_COMMAND_ID)0;

  char *commandToCompare = (char *)malloc(commandLen * sizeof(char));
  memcpy(commandToCompare, commandBuffer, commandLen);
  unsigned short commandPartOfTheCommandLen = commandLen;
  
  //since code is here, it is a proper packed as AT command, lets parse it
  //Note that, SET commands has '=' sign, so lets control it first
  if (strstr(commandBuffer, "=") != NULL) 
  {
    // contains
    char *token = strtok(commandBuffer, "=");
    commandToCompare = (char *)realloc(commandToCompare, (strlen(token) + 1)); // +1 means '=' character
    memcpy(commandToCompare, token, strlen(token));
    commandToCompare[(int)(strlen(token))] = '=';
    commandPartOfTheCommandLen = strlen(token) + 1;   //  +1 means '=' character

    //hold the rest of the array to use them in action
    memcpy(commandDataPart, &commandBuffer[(int)(strlen(token) + 1)], (int)(commandLen - strlen(token) - 1));
    *commandDataLen = (unsigned short)(commandLen - strlen(token) - 1);
  }
  
  int i = 0;
  for(i = 0; i < NUMBER_OF_AT_COMMANDS; i++)
  {
    int savedCommandLen = strlen(AT_Command_Structure[i].atCommandText);
    if(commandPartOfTheCommandLen == savedCommandLen) //in case of any memory error
    {
      if(memcmp(commandToCompare, AT_Command_Structure[i].atCommandText, commandPartOfTheCommandLen) == 0)
      {
        free(commandToCompare);
        return AT_Command_Structure[i].atCommandID;
      }
    }
  }
  free(commandToCompare);
  return returnValue;
}

unsigned short usGetATCommandPacket(char *commandBuffer, unsigned int len)
{
  unsigned short usReadDataCounter = 0;
  //memset(commandBuffer, 0, len);
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    commandBuffer[usReadDataCounter++] = inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == CR) 
    {
      //control their initial part wheather or not they have "AT" keyword
      //convert all their string character parts to upper case
      for(int i = 0; i < usReadDataCounter; i++)
      {
        if(commandBuffer[i] == '=') //do not change rest of the command
          break;
          
        if((commandBuffer[i]<= 0x7A) && (commandBuffer[i]>= 0x61))
        {
          commandBuffer[i] = commandBuffer[i] - 0x20;
        }
      }
      //control "AT" part
      if(usReadDataCounter > MIN_AT_COMMAND_LEN)
      {
        if((commandBuffer[0] == 'A') && (commandBuffer[1] == 'T'))
        {
          Serial.flush();
          return (usReadDataCounter - 1);  //-1 because discard CR at the end
        }
      }
      Serial.flush();
      return 0;
    }
  }
  Serial.flush();
  return 0;
}


ERROR_CODES xSetAllParametersToDefault()
{
  ERROR_CODES returnValue = ERR_OK;

  if(sServerAnswer != NULL)
    free(sServerAnswer);
  sServerAnswer = (char *)malloc(sizeof(char)); //just allocate 1 char
  sServerAnswer[0] = 0;

  pinMode(LED0, OUTPUT);          // WIFI OnBoard LED Light
  digitalWrite(LED0, !LOW);       // Turn WiFi LED Off

  iCurrentBaudRate = BAUDRATE_DEFAULT_VALUE;
  Serial.begin(iCurrentBaudRate);           // Computer Communication
  delay(5);

  WiFi.disconnect();    // ReStart To Connect
  WiFi.mode(WIFI_OFF);
  delay(50);

  if(returnValue == ERR_OK)
    vSendQuickResponseAfterExecution(ATpDEF);
  
  return returnValue;
}

ERROR_CODES xDisplayCurrentConfiguration()
{
  ERROR_CODES returnValue = ERR_OK;

  char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  
  sprintf(cBufferToSend, "BAUD%d\x0D", iCurrentBaudRate);
  int iBufferToSendLen = strlen(cBufferToSend);
  Serial.write(cBufferToSend, iBufferToSendLen);

  return returnValue;
}

ERROR_CODES xSetBaudRate(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;
  //first, control every single byte if or not they are decimal, if not return an error
  for(int i = 0; i < commandDataLen; i++)
  {
    if((commandDataPart[i]<'0') || (commandDataPart[i]>'9'))
      returnValue = ERR_WRONG_DATA;
  }
  if(returnValue == ERR_OK)
  {
    //send answer with old baud rate
    char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);

    sprintf(cBufferToSend, "BAUD%s\x0D", commandDataPart);
    int iBufferToSendLen = strlen(cBufferToSend);
    Serial.write(cBufferToSend, iBufferToSendLen);
    delay(100);//wait some time otherwise we cannot see the answer at other side
    
    //string to int operation
    int dummyBaud = 0;
    sscanf(commandDataPart, "%d", &dummyBaud);
    iCurrentBaudRate = dummyBaud;
    //change serial baud here
    Serial.begin(iCurrentBaudRate);           // Computer Communication
    delay(5);
  }
  return returnValue;
}

/*
* we can only use ESP pins between D0 - D8 and A pin only
* Here are the numerical representation of them;
* D0 --> 0
* D1 --> 1
* ...
* D8 --> 8
* and 0 means RESET, others are SET meaning
*/
ERROR_CODES xSetDigitalOutput(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;
  
  char cBufferFirstPart[MAX_SERIAL_READ_DATA_BUFFER_LEN]; //it cannot exceed 4 digit
  memset(cBufferFirstPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  char cBufferSecondPart[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  memset(cBufferSecondPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);

  //since the data part's format like this "N1,N2", lets first we split the string for delimiter ','
  if (strstr(commandDataPart, ",") != NULL) 
  {
    // contains
    char *token = strtok(commandDataPart, ",");
    memcpy(cBufferFirstPart, token, strlen(token));
    int firstPartLen = strlen(token);
    memcpy(cBufferSecondPart, &commandDataPart[firstPartLen + 1], commandDataLen - (firstPartLen + 1)); // +1 means ','
    int secondPartLen = commandDataLen - (firstPartLen + 1);

    //control the buffers elemnts are decimal or not
    for(int i = 0; i < firstPartLen; i++)
    {
      if((cBufferFirstPart[i]<'0') || (cBufferFirstPart[i]>'9'))
        returnValue = ERR_WRONG_DATA;
    }
    for(int i = 0; i < secondPartLen; i++)
    {
      if((cBufferSecondPart[i]<'0') || (cBufferSecondPart[i]>'9'))
        returnValue = ERR_WRONG_DATA;
    }

    if(returnValue != ERR_OK)
      return returnValue;

    //now we can convert thems to integers, control is it proper for ESP and set the DO
    int pinNumber = 0;
    sscanf(cBufferFirstPart, "%d", &pinNumber);
    int pinValue = 0;
    sscanf(cBufferSecondPart, "%d", &pinValue);

    if(pinNumber >= SEQUENTIAL_DIGITAL_PIN_COUNT)
    {
      returnValue = ERR_WRONG_DATA;
      return returnValue;
    }

    int realPinNumber = 0;
    //now we can set DO
    switch (pinNumber) 
    {
      case 0:
        // statements
        pinMode(D0, OUTPUT);
        realPinNumber = D0;
        break;
      case 1:
        // statements
        pinMode(D1, OUTPUT);
        realPinNumber = D1;
        break;
      case 2:
        // statements
        pinMode(D2, OUTPUT);
        realPinNumber = D2;
        break;
      case 3:
        // statements
        pinMode(D3, OUTPUT);
        realPinNumber = D3;
        break;
      case 4:
        // statements
        pinMode(D4, OUTPUT);
        realPinNumber = D4;
        break;
      case 5:
        // statements
        pinMode(D5, OUTPUT);
        realPinNumber = D5;
        break;
      case 6:
        // statements
        pinMode(D6, OUTPUT);
        realPinNumber = D6;
        break;
      case 7:
        // statements
        pinMode(D7, OUTPUT);
        realPinNumber = D7;
        break;
      case 8:
        // statements
        pinMode(D8, OUTPUT);
        realPinNumber = D8;
        break;
      default:
        returnValue = ERR_WRONG_DATA;
    }
    
    if(returnValue != ERR_OK)
      return returnValue;

    char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
    
    if(pinValue == 0) //it means RESET
    {
      digitalWrite(realPinNumber, LOW);
      sprintf(cBufferToSend,"%dRST\x0D", pinNumber);
    }
    else  //it means SET
    {
      digitalWrite(realPinNumber, HIGH);  
      sprintf(cBufferToSend,"%dSET\x0D", pinNumber);
    }
    delay(10);
    Serial.write(cBufferToSend, strlen(cBufferToSend));
  }
  else //it means there is no ',' in the data
    returnValue = ERR_WRONG_DATA;


  return returnValue;
}


ERROR_CODES xGetDigitalInput(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;
  //first, control every single byte if or not they are decimal, if not return an error
  for(int i = 0; i < commandDataLen; i++)
  {
    if((commandDataPart[i]<'0') || (commandDataPart[i]>'9'))
      returnValue = ERR_WRONG_DATA;
  }
  if(returnValue == ERR_OK)
  {
    //string to int operation
    int pinNumber = 0;
    sscanf(commandDataPart, "%d", &pinNumber);

    //control the pin number is in the range of ESP8266
    if(pinNumber >= SEQUENTIAL_DIGITAL_PIN_COUNT)
    {
      returnValue = ERR_WRONG_DATA;
      return returnValue;
    }
    
    int realPinNumber = 0;
    //now we can set DI
    switch (pinNumber) 
    {
      case 0:
        // statements
        pinMode(D0, INPUT);
        realPinNumber = D0;
        break;
      case 1:
        // statements
        pinMode(D1, INPUT);
        realPinNumber = D1;
        break;
      case 2:
        // statements
        pinMode(D2, INPUT);
        realPinNumber = D2;
        break;
      case 3:
        // statements
        pinMode(D3, INPUT);
        realPinNumber = D3;
        break;
      case 4:
        // statements
        pinMode(D4, INPUT);
        realPinNumber = D4;
        break;
      case 5:
        // statements
        pinMode(D5, INPUT);
        realPinNumber = D5;
        break;
      case 6:
        // statements
        pinMode(D6, INPUT);
        realPinNumber = D6;
        break;
      case 7:
        // statements
        pinMode(D7, INPUT);
        realPinNumber = D7;
        break;
      case 8:
        // statements
        pinMode(D8, INPUT);
        realPinNumber = D8;
        break;
      default:
        returnValue = ERR_WRONG_DATA;
    }
    
    if(returnValue != ERR_OK)
      return returnValue;

    char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
    
    //now, we can read the digital pin status
    if( digitalRead(realPinNumber) == HIGH) //we read HIGH
    {
      sprintf(cBufferToSend, "%dSET\x0D", pinNumber);
    }
    else  //state is LOW aleady
    {
      sprintf(cBufferToSend, "%dRST\x0D", pinNumber);
    }
    delay(10);
    Serial.write(cBufferToSend, strlen(cBufferToSend));
  }
  return returnValue;
}

/*
* it returns 1024 when 3V3 connected to A0 or it returns 0 when GND is connected to the pin
*/
ERROR_CODES xGetAnalogInputInput(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;
  //first, control every single byte if or not they are decimal, if not return an error
  for(int i = 0; i < commandDataLen; i++)
  {
    if((commandDataPart[i]<'0') || (commandDataPart[i]>'9'))
      returnValue = ERR_WRONG_DATA;
  }
  if(returnValue == ERR_OK)
  {
    //string to int operation
    int pinNumber = 0;
    sscanf(commandDataPart, "%d", &pinNumber);

    //control the pin number is in the range of ESP8266
    if(pinNumber >= SEQUENTIAL_ANALOG_PIN_COUNT)
    {
      returnValue = ERR_WRONG_DATA;
      return returnValue;
    }

    //we know that there is just ONE Analog Input exists on the ESP8266
    //we will not control the pin number is 0 or not, whatever the pin number, we will return the same (A0) pin value
    int readAnalogValue = analogRead(A0);

    char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
    memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
    
    sprintf(cBufferToSend, "RAW%d\x0D", readAnalogValue);
    
    delay(10);
    Serial.write(cBufferToSend, strlen(cBufferToSend));
  }
  return returnValue;
}

ERROR_CODES xJoinAccessPoint(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;

  Serial.print("TRYING...\x0D");    //send to master to declare we get the command
  
  //check TCP connection is exists or not
  if((xglbClient.status() == 0))// && (sLastConnectedHostName == "") && (uiLastConnectedHostPort == 0)) //it means connection not exist
  {
    //no problem
  }
  else
    return ERR_TCP_CONN_EXIST;
  
  char cBufferFirstPart[MAX_SERIAL_READ_DATA_BUFFER_LEN]; //it cannot exceed 4 digit
  memset(cBufferFirstPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  char cBufferSecondPart[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  memset(cBufferSecondPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);

  //since the data part's format like this "N1,N2", lets first we split the string for delimiter ','
  if (strstr(commandDataPart, ",") == NULL) 
  {
    returnValue = ERR_WRONG_DATA;
    return returnValue;
  }
  
  // contains the delimiter
  char *token = strtok(commandDataPart, ",");
  memcpy(cBufferFirstPart, token, strlen(token));
  int firstPartLen = strlen(token);
  memcpy(cBufferSecondPart, &commandDataPart[firstPartLen + 1], commandDataLen - (firstPartLen + 1)); // +1 means ','
  int secondPartLen = commandDataLen - (firstPartLen + 1);

  //control the buffers elemnts are readable characters
  for(int i = 0; i < firstPartLen; i++)
  {
    if((cBufferFirstPart[i]<' ') || (cBufferFirstPart[i]>'~'))
      returnValue = ERR_WRONG_DATA;
  }
  for(int i = 0; i < secondPartLen; i++)
  {
    if((cBufferSecondPart[i]<' ') || (cBufferSecondPart[i]>'~'))
      returnValue = ERR_WRONG_DATA;
  }

  if(returnValue != ERR_OK)
    return returnValue;
    
  WiFi.disconnect();    // ReStart To Connect
  WiFi.mode(WIFI_OFF);
  delay(50);
  /* in this part it should load the ssid and password 
     * from eeprom they try to connect using them */
  WiFi.mode(WIFI_STA);            // To Avoid Broadcasting An SSID
  WiFi.begin((cBufferFirstPart), (cBufferSecondPart));      // The SSID That We Want To Connect To
    
  startTimer(ACCESS_POINT_CONNECTION_TIMEOUT); //wait a specified timeout to control connection status
  while (1)
  {
    delay(500);//we get this from ESP original example, DO NOT REMOVE THIS LINE
    if((WiFi.status() == WL_CONNECTED) || (isTimeOut())) { break; }
  }

  sLastConnectedAccessPointName = "";
  sLastConnectedAccessPointPass = "";
  
  if(WiFi.status() != WL_CONNECTED)
  {
    returnValue = ERR_CANNOT_JOIN_ACCESS_POINT;
    return returnValue;
  }
    
  //here we are connected, then send the answer
  Serial.print("OK\x0D");

  sLastConnectedAccessPointName = String(cBufferFirstPart);
  sLastConnectedAccessPointPass = String(cBufferSecondPart);

  return returnValue;
}

ERROR_CODES xQuitAccessPoint(void)
{
  ERROR_CODES returnValue = ERR_OK;

  Serial.print("TRYING...\x0D");

  //check TCP connection is exists or not
  if((xglbClient.status() == 0))// && (sLastConnectedHostName == "") && (uiLastConnectedHostPort == 0)) //it means connection not exist
  {
    //no problem
  }
  else
    return ERR_TCP_CONN_EXIST;

  WiFi.disconnect();    
  WiFi.mode(WIFI_OFF);
  
  startTimer(ACCESS_POINT_CONNECTION_TIMEOUT); //wait a specified timeout to control connection status
  while (1)
  {
    delay(500);//we get this from ESP original example, DO NOT REMOVE THIS LINE
    if((WiFi.status() != WL_CONNECTED) || (isTimeOut())) { break; }
  }

  if(WiFi.status() == WL_CONNECTED) //it means disconnected problem
  {
    returnValue = ERR_WIFI_DISCONNECTED;
    return returnValue;
  }
  
  if(returnValue == ERR_OK)
  {
    sLastConnectedAccessPointName = "";
    sLastConnectedAccessPointPass = "";
    sLastConnectedHostName = "";
    uiLastConnectedHostPort = 0;
    vSendQuickResponseAfterExecution(ATpCWQAP);
  }

  return returnValue;
}


ERROR_CODES xChangeModemMode(char *commandDataPart, unsigned short commandDataLen)
{  
  ERROR_CODES returnValue = ERR_OK;

  //disconnect other connections and create an access point in server mode (xglbModemStatus  = STA_CLIENT;)
  if(commandDataLen != 1)
  {
    returnValue = ERR_WRONG_DATA;
    return returnValue;
  }  

  //we expect '0' or 'else' status to select client or server
  if(commandDataPart[0] == '0') //select client
    xglbModemStatus = STA_CLIENT;
  else
    return ERR_NOT_SUPPORTED;
    //xglbModemStatus = STA_SERVER;

  //disconnect from access point (doing this also close the TCP connections) and return message
  //returnValue = xQuitAccessPoint();

  if(returnValue == ERR_OK)
    vSendQuickResponseAfterExecution(ATpCWMODEe);

  return returnValue;
}


ERROR_CODES xChangeDeviceMode(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;

  //control data len
  if(commandDataLen != 1)
  {
    returnValue = ERR_WRONG_DATA;
    return returnValue;
  }  

  //we assume that 0 means datamode, else is transparent mode
  if(commandDataPart[0] == '0')
    xglbDeviceStatus = STA_COMMAND;
  else
    xglbDeviceStatus = STA_TRANSPARENT;

  //send response
  if(returnValue == ERR_OK)
    vSendQuickResponseAfterExecution(ATpCIPSTATUSe);

  return returnValue;
}


ERROR_CODES xCollectConnectedDevicesIPAddresses(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;

  if((WiFi.status() != WL_CONNECTED) || (xglbModemStatus != STA_SERVER))
    return ERR_CANNOT_GET_IP_ADDRESSES;
  
  char cBufferToSend[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  memset(cBufferToSend, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  memcpy(cBufferToSend, (char *)"IP:", 3);

  int dummyCounter = 0;
  for(int i = 0; i < MAX_CONNECTED_DEVICE_COUNT; i++)
  {
    dummyCounter++;
    if(glb_clientStatusList[i] == true) //it means if the client is alive
    {
      String theIP = String(glb_clientIPAddresses[i]);
      char *dummyBuff = (char *)malloc((theIP.length() + 1) * sizeof(char));
      memset(dummyBuff, 0, theIP.length() + 1);
      theIP.toCharArray(dummyBuff, theIP.length());
      strcat(cBufferToSend, dummyBuff);
      free(dummyBuff);
      if(((i + 1) != MAX_CONNECTED_DEVICE_COUNT) && (glb_clientStatusList[i + 1] == true))
        strcat(cBufferToSend, (char *)(","));
    }
  }

  if(dummyCounter == 0)
  {
    returnValue = ERR_NO_CONNECTED_DEVICE;
    return returnValue;
  }

  //send answer 
  Serial.print(String(cBufferToSend) + String("\x0D"));
  
  return returnValue;
}

ERROR_CODES xCloseCurrentConnections(void)
{
  ERROR_CODES returnValue = ERR_OK;

  if(xglbModemStatus  == STA_CLIENT)
  {
    xglbClient.stop();
    delay(50);
    if(xglbClient.status() != 0) // it means not connected
    {
      returnValue = ERR_NOT_CONNECTED_TCP;
    }
  }
  else //server mode, close connected other devices connections
  {
    for(int i = 0; i < MAX_CONNECTED_DEVICE_COUNT; i++)
    {
      if(glb_clientStatusList[i] == true)
      {
        glb_clientList[i].stop ();
        glb_clientStatusList[i] = false;
      }
    }
  }

  if(returnValue == ERR_OK)
  {
    sLastConnectedHostName = "";
    uiLastConnectedHostPort = 0;
    vSendQuickResponseAfterExecution(ATpCIPCLOSE);
  }

  return returnValue;
}


ERROR_CODES xConnectToHost(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;

  //control parameters here
  //first, look at the ',' sign because we expect one host name and one port respectively
  if (strstr(commandDataPart, ",") == NULL) 
  {
    returnValue = ERR_WRONG_DATA;
    return returnValue;
  }

  char cBufferFirstPart[MAX_SERIAL_READ_DATA_BUFFER_LEN]; //it cannot exceed 4 digit
  memset(cBufferFirstPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  char cBufferSecondPart[MAX_SERIAL_READ_DATA_BUFFER_LEN];
  memset(cBufferSecondPart, 0, MAX_SERIAL_READ_DATA_BUFFER_LEN);
  
  //control ip has 3 dot (expected ip format xxx.xxx.xxx.xxx) and control port it has only numerical value
  char *token = strtok(commandDataPart, ",");
  memcpy(cBufferFirstPart, token, strlen(token));
  int firstPartLen = strlen(token);
  memcpy(cBufferSecondPart, &commandDataPart[firstPartLen + 1], commandDataLen - (firstPartLen + 1)); // +1 means ','
  int secondPartLen = commandDataLen - (firstPartLen + 1);

  int dotCounter = 0;
  //control the buffers elemnts are readable characters
  for(int i = 0; i < firstPartLen; i++)
  {
    if(cBufferFirstPart[i] == '.')
      dotCounter++;
    else
    {
      if((cBufferFirstPart[i]<'0') || (cBufferFirstPart[i]>'9'))
        returnValue = ERR_WRONG_DATA;
    }
  }
  if(dotCounter != 3)
    returnValue = ERR_WRONG_DATA;
  
  for(int i = 0; i < secondPartLen; i++)
  {
    if((cBufferSecondPart[i]<'0') || (cBufferSecondPart[i]>'9'))
      returnValue = ERR_WRONG_DATA;
  }

  if(returnValue != ERR_OK)
    return returnValue;

  //then convert them to integer
  int ip1 = 0, ip2 = 0, ip3 = 0, ip4 = 0, port = 0;
  //char cIP1[4] = {0, 0, 0, 0}, cIP2[4] = {0, 0, 0, 0}, cIP3[4] = {0, 0, 0, 0}, cIP4[4] = {0, 0, 0, 0};
  int dummyLenHolder = 0;
  token = strtok(&cBufferFirstPart[0], ".");
  dummyLenHolder = strlen(token) + dummyLenHolder;
  sscanf(token, "%d", &ip1);
  
  token = strtok(&cBufferFirstPart[dummyLenHolder + 1], "."); //+1 means '.' character
  dummyLenHolder = strlen(token) + dummyLenHolder + 1;
  sscanf(token, "%d", &ip2);
  
  token = strtok(&cBufferFirstPart[dummyLenHolder + 1], "."); //+1 means '.' character
  dummyLenHolder = strlen(token) + dummyLenHolder + 1;
  sscanf(token, "%d", &ip3);
  
  String dummyString = String(ip1) + "." + String(ip2) + "." + String(ip3) + ".";
  sscanf(&cBufferFirstPart[dummyString.length()], "%d", &ip4);

  sscanf(cBufferSecondPart, "%d", &port);


  //control ip parts are less then 255 and port is less then 65535
  if((ip1 > 255) || (ip2 > 255) || (ip3 > 255) || (ip4 > 255) || (port > 65535))
  {
    returnValue = ERR_WRONG_DATA;
    return returnValue;
  }

  //then everything is fine
  uiLastConnectedHostPort = port;
  sLastConnectedHostName = String(ip1) + "." + String(ip2) + "." + String(ip3) + "." + String(ip4);

  xglbClient.stop();

  // If Sucessfully Connected Send Connection Message
  if(xglbClient.connect(sLastConnectedHostName, uiLastConnectedHostPort))
  {
    xglbClient.flush();
  }
  else
  {
    //cannot connect situation
    returnValue = ERR_NOT_CONNECTED_TCP;
  }

  if(returnValue == ERR_OK)
    vSendQuickResponseAfterExecution(ATpCONNe);
  return returnValue;
}


ERROR_CODES xSendClientsData(char *commandDataPart, unsigned short commandDataLen)
{
  //TODO, fill here later
  return ERR_NOT_SUPPORTED;
}


ERROR_CODES xSendIncomingDataToServer(char *commandDataPart, unsigned short commandDataLen)
{
  ERROR_CODES returnValue = ERR_OK;
  //we dont need to control data, just control the connections and send the data
  if(xglbClient.status() != 0)
  {
    xglbClient.println((String(commandDataPart)).substring(0,commandDataLen) + "\x0D");
    vSendQuickResponseAfterExecution(ATpSENDe);
  }
  else
  {
    returnValue = ERR_NOT_CONNECTED_TCP;
  }
  return returnValue;
}



ERROR_CODES xSendServerDataToMaster()
{
  ERROR_CODES returnValue = ERR_OK;

  //control access point joining and TCP/IP connection is alive then change the mode (xglbModemStatus)
  if(WiFi.status() != WL_CONNECTED)
  {
    returnValue = ERR_NOT_CONNECTED_WIFI;
    return returnValue;
  }

  //control is TCP/IP connection exist
  if((xglbClient.status() == 0) && (sLastConnectedHostName == "") && (uiLastConnectedHostPort == 0)) //it means connection not exist
  {
    returnValue = ERR_NOT_CONNECTED_TCP;
    return returnValue;
  }

  if(strlen(sServerAnswer) == 0)
    returnValue = ERR_NO_SERVER_DATA;
  else
  {
    Serial.print("DT:" + String(sServerAnswer) + "\x0D");
    memset(sServerAnswer, 0, sizeof(sServerAnswer));
  }
  return returnValue;
}






