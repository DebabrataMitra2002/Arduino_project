functions.h file:

//=======================================
//handle function: send webpage to client
//=======================================
void handleRoot()
{
  server.send(200,"text/html", webpageCont);
}
//=====================================================
//function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  //--------------------------------------------------
  if(type == WStype_TEXT)
  {
    byte separator=payloadString.indexOf('=');
    String var = payloadString.substring(0,separator);
    String val = payloadString.substring(separator+1);
    //------------------------------------------------
    if(var == "fanLEDonoff")
    {
      fanLEDonoff = false;
      if(val == "ON") fanLEDonoff = true;
    }
    //------------------------------------------------
    if(var == "humLEDonoff")
    {
      humLEDonoff = false;
      if(val == "ON") humLEDonoff = true;
    }
  }
}

