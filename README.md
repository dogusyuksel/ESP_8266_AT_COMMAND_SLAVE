# ESP_8266_AT_COMMAND_SLAVE
This project can be used for using ESP as at command slave with specified AT commands



GENERAL EXPLANATIONS
-----------------------

This software is used to use ESP8266 module with extended AT commands. After this code loaded to the device, you can understand the device is working correctly by observing the led blinks. Devices default BAUD is 9600 and AT commands’ case is not important.

Other necessary informations, like error codes, will be given in this document later.




GET COMMANDS
---------------------------

AT
--------------------

It checks the device is ready or not. Statically, it returns “OK”

Eg:	Send		AT<CR>
	Get		OK<CR>

ATI
--------------------

It returns identification information of the device. Statically, it returns “Opthema_Node_xxxx” where xxxx refers to software version of the ESP8266.

Eg:	Send		ATI<CR>
	Get		Node_Module_XXXX<CR>

AT+GMI
--------------------

It returns manufacturer identification. Statically, it returns “Opthema”.

Eg:	Send		AT+GMI<CR>
	Get		dodo_corp<CR>

AT+GMM
--------------------

It requests model identification. Statically, it returns “Node”.

Eg:	Send		AT+GMM<CR>
	Get		Node<CR>

AT+GMR
--------------------

It requests version of the softwarerelease.

Eg:	Send		AT+GMR<CR>
	Get		00.00.04<CR>


AT+CUR
--------------------

It returns device’s current configurations.
Currently, it only sends baud rate with “BAUD” keyword.

Eg:	Send		AT+CUR<CR>
	Get		BAUD9600<CR>

AT+CIOBOUD?
--------------------

It returns current baud rate with “BAUD” label.

Eg:	Send		AT+CIOBOUD? <CR>
	Get		BAUDxxxx<CR>

AT+GETDI
--------------------

It sets a pin as digital input and read its status.

Eg:	Send		AT+GETDI=1<CR>			, read D1 and get its status
	Get		1SET<CR>

/*
* we can only use ESP pins between D0 - D8 and A pin only
* Here are the numerical representation of them;
* D0 --> 0
* D1 --> 1
* ...
* D8 --> 8
* and 0 means RESET, others are SET meaning
*/

AT+GETAI
--------------------

It returns raw analog value of specified pin.
ESP has only one pin so we just except pin number 0, otherwise error returns.

Eg:	Send		AT+GETAI=1<CR>		, get A1 raw value
	Get		RAW752<CR>

AT+CIPSTATUS
--------------------

It returns chip status. Currently we get COMMAND and TRANSPARENT mode. Transparent mode is not used for this version.

Eg:	Send		AT+CIPSTATUS<CR>
	Get		CMM<CR>		, CMM for command, TRN for transparent

AT+CWJAP?
--------------------

It returns currently joined access point name.

Eg:	Send		AT+CWJAP?<CR>
	Get		XXXXXXX OK<CR>

AT+CIFSR?
--------------------

It returns IP address of the ESP if it is connected to an access point.

Eg:	Send		AT+CIFSR?<CR>
	Get		1921681256<CR>

AT+CWMODE
--------------------

It gets modem mode. It returns SERVER or CLIENT. SERVER mode is not supported for this version.

Eg:	Send		AT+CWMODE?<CR>
	Get		CLIENT<CR>

AT+CIPMUX?
--------------------

It checks TCP connection exists or not.

Eg:	Send		AT+CIPMUX?<CR>
	Get		OK<CR>

AT+CWLIF
--------------------

It returns connected devices’ ip address if device is in server mode. It is not supported for this version.

Eg:	Send		AT+CWLIF<CR>
	Get		IP:xxxxx,yyyyy<CR>

AT+GETDT
--------------------

It sends specified-number client’s ip address. Since this version does not have server mode, this command returns an error.

Eg:	Send		AT+GETDT=1<CR>		, get 1. Client’s ip address
	Get		ERR_xx<CR>

AT+GETDT
--------------------

It returns data that comes from server when ESP in client mode.
When data is ready, ESP sends “DTRDY,x” where is is the length of data.

Eg:	Send		AT+GETDT<CR>
	Get		DT:asd	<CR>		, where asd is the data

SET COMMANDS
---------------------------

AT+DEF
--------------------

It sets all device parameters to default. Statically, it returns “OK”.
Currently, it sets the BAUD to 9600 and kills all wifi connections.

Eg:	Send		AT+DEF<CR>
	Get		OK<CR>

AT+QPOWD
--------------------

Make an urgent power-off. Since we do not have HW support for this command, we return a specified error.

Eg:	Send		AT+QPOWD<CR>
	Get		ERR_xx<CR>


AT+CIOBOUD
--------------------

It sets the communication baud rate.

Eg:	Send		AT+CIOBOUD=115200<CR>
	Get		BAUD115200<CR>

AT+SETDO
--------------------

It sets a pin as digital output and write a value over on it.

Eg:	Send		AT+SETDO=1,0<CR>		, it sets D1 to LOW
	Get		1RST<CR>

/*
* we can only use ESP pins between D0 - D8 and A pin only
* Here are the numerical representation of them;
* D0 --> 0
* D1 --> 1
* ...
* D8 --> 8
* and 0 means RESET, others are SET meaning
*/

AT+RST
--------------------

Soft reset call. After this code, ESP restart from its ‘setup’ configurations.

Eg:	Send		AT+RST<CR>
	Get		RESET_ON<CR>		, then we get “DEVICE STARTED”

AT+CIPSTATUS
--------------------

It sets chips status. Command or transparent mode arrangement can be done with this command.
Currently, we are not support transparent mode. So if you try to set transparent mode, you will got no error but the commandwill not effect the ESP.

Eg:	Send		AT+CIPSTATUS=0<CR>	, 0 for command, 1 for transparent
	Get		OK<CR>

AT+CWJAP
--------------------

This command lets the ESP to join an access point.

Eg:	Send		AT+CWJAP=IoTYazilim,iot123!_2018<CR>
	Get		TRYING...<CR>	,if succeed then returns OK

NOTE THAT: Timeout is 30 second for this version.

AT+CWQAP
--------------------

It quits from currently connected access point.

Eg:	Send		AT+CWQAP<CR>
	Get		TRYING... <CR>          , if succeed then return OK

AT+CWMODE
--------------------

It sets the modem mode as server or client. You cannot set as server in this version. 0 means client, else means server mode.

Eg:	Send		AT+CWMODE=0<CR>
	Get		OK<CR>

AT+CONN
--------------------

It makes a TCP connection to specified ip and port. First argument is ip, other is port number.

Eg:	Send		AT+CONN=10.60.70.146,9001<CR>
	Get		OK<CR>

AT+CIPCLOSE
--------------------

It closes current TCP connection.

Eg:	Send		AT+CIPCLOSE<CR>
	Get		OK<CR>

AT+SEND
--------------------

It sends data to server when ESP in client mode.

Eg:	Send		AT+SEND=asd<CR>		, sends “asd” to server
	Get		OK<CR>



ERROR TYPES
--------------------


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
