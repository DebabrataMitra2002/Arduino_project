
webpage.h file:

//=========================================
//HTML, CSS & JavaScript Codes for Webpage
//=========================================
const char webpageCont[] PROGMEM = 
R"=====(
<!DOCTYPE HTML>
<html>
<title>ESP32 WebSocket Server</title>
<!------------------------------------------CSS----------------------------------------->
<style>
    #dynRectangle1
    {
        width:0px;
        height:12px;
        top: 9px;
        background-color: rgba(255, 0, 0, 0.863);
        z-index: -1;
        margin-top: 1px;
        border: 3px solid black;
    }
    #dynRectangle2
    {
        width:0px;
        height:12px;
        top: 9px;
        background-color:rgba(0, 0, 255, 0.534);
        z-index: -1;
        margin-top:1px;
        border: 3px solid black;
    }
    body   {background-color:rgba(128,128,128,0.322)}
    h1     {font-size: 40px; color: rgb(156, 5, 5); text-align:center; font-family:calibri}
    h2     {font-size: 25px; color: black; font-family:cursive}
    h3     {font-size: 17px; color:black; font-family:calibri}
    h4     {font-size: 14px; color: black; font-family:Trebuchet MS}
    div.h1 {background-color: whitesmoke;}
    .btn1  
    {
        background-color:#ff3c00b7;
        border: solid 2px rgb(10, 0, 0);
        color: white;
        padding: 4px 16px; 
        font-weight: bold;
        font: 16px arial, sans-serif;
        width: 60px;
        height: 32px;
        line-height: 22px;
        border-radius: 10%;
        opacity: 0.6;
        transition: 0.3s;
        overflow: hidden;
        text-decoration: none;
        cursor: pointer;
    }
    .btn1:hover {opacity: 1}
    .btn2 
    {
        background-color:#002fffa4;
        border: solid 2px rgb(10, 0, 0);
        color: white;
        padding: 4px 16px; 
        font-weight: bold;
        font: 16px arial, sans-serif;
        width: 60px;
        height: 32px;
        line-height: 22px;
        border-radius: 10%;
        opacity: 0.6;
        transition: 0.3s;
        overflow: hidden;
        text-decoration: none;
        cursor: pointer;
    }
    .btn2:hover {opacity: 1}
    span.b1 {float: left; padding: 5px 10px}
    span.b2 {float: left; padding: 5px 10px}
    .msgRect1
    {
        float: left;
        text-align: center;
        margin: 21px 1px;
        padding: 10px 10px;
        height: 10px;
        width: 120px;
        line-height: 10px;
        background-color:white;
        border: 2px solid black;
    }
    .msgRect2
    {
        float: left;
        text-align: center;
        margin: 21px 1px;
        padding: 10px 10px;
        height: 10px;
        width: 120px;
        line-height: 10px;
        background-color:white;
        border: 2px solid black;
    }
    .msgRect3
    {
        float: left;
        text-align: center;
        margin: 21px 1px;
        padding: 10px 10px;
        height: 10px;
        width: 120px;
        line-height: 10px;
        background-color:white;
        border: 2px solid black;
    }
</style>
<!-----------------------------------------HTML----------------------------------------->
<body>
    <h1><div class="h1">ESP32 WebSocket Server<br>DHT22 Temp & Humidity Sensor</div></h1>
    <h2>
        Temperature: <span style="color:rgb(216, 3, 3)" id="Tempvalue">0</span> C<br>
        Humidity&emsp;&emsp;: <span style="color:rgba(0, 0, 255, 0.795)" id="Humvalue">0</span> % 
    </h2>
    <h3>
        0 C &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 50 C
        <div id="dynRectangle1"></div><br>
        0 % &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;
        &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 100 %
        <div id="dynRectangle2"></div>
    </h3>
    <h4>
        <span class="b1">
            Fan<br>
            <button class="btn1" id="FANbtn" onclick="fanONOFF()"> </button>
        </span>
        <span class="b2">
            Humidifier<br>
            <button class="btn2" id="HUMbtn" onclick="humONOFF()"> </button>
        </span>
        <span class="msgRect1" id="msg1""> </span>
        <span class="msgRect2" id="msg2""> </span>
        <span class="msgRect3" id="msg3""> </span>
    </h4>
</body>
<!-------------------------------------JavaScript--------------------------------------->
<script>
  InitWebSocket()
  function InitWebSocket()
  {
    websock = new WebSocket('ws://'+window.location.hostname+':81/');
    websock.onmessage=function(evt)
    {
       JSONobj = JSON.parse(evt.data);
       document.getElementById('Tempvalue').innerHTML = JSONobj.TEMP;
       var temp = parseInt(JSONobj.TEMP * 9.5);
       document.getElementById("dynRectangle1").style.width = temp+"px";
       
       document.getElementById('Humvalue').innerHTML = JSONobj.HUM;
       var hum = parseInt(JSONobj.HUM * 4.8);
       document.getElementById("dynRectangle2").style.width = hum+"px";

       document.getElementById('FANbtn').innerHTML = JSONobj.fanLEDonoff;
       document.getElementById('HUMbtn').innerHTML = JSONobj.humLEDonoff;
       
       document.getElementById('msg1').innerHTML = JSONobj.FANonoff;
       if(JSONobj.FANonoff == 'ON')
       {
        document.getElementById("msg1").innerHTML="Fan ON";
        document.getElementsByClassName("msgRect1")[0].style.backgroundColor="#FFFF33";
       }
       else
       {
        document.getElementById("msg1").innerHTML="Fan OFF";
        document.getElementsByClassName("msgRect1")[0].style.backgroundColor="#00BFFF";
       }
       
       document.getElementById('msg2').innerHTML = JSONobj.HUMonoff;
       if(JSONobj.HUMonoff == 'ON')
       {
        document.getElementById("msg2").innerHTML="Humidifier ON";
        document.getElementsByClassName("msgRect2")[0].style.backgroundColor="#FFFF33";
       }
       else
       {
        document.getElementById("msg2").innerHTML="Humidifier OFF";
        document.getElementsByClassName("msgRect2")[0].style.backgroundColor="#00BFFF";
       }

       document.getElementById('msg3').innerHTML = JSONobj.SWonoff;
       if(JSONobj.SWonoff == 'ON')
       {
        document.getElementById("msg3").innerHTML="Check Server";
        document.getElementsByClassName("msgRect3")[0].style.backgroundColor="#FF0000";
       }
       else
       {
        document.getElementById("msg3").innerHTML="Server OK";
        document.getElementsByClassName("msgRect3")[0].style.backgroundColor="#90EE90";
       }
    }
  }
  //----------------------------------------------------------------------------------
  function fanONOFF()
  {
    FANbtn = 'fanLEDonoff=ON';
    if(document.getElementById('FANbtn').innerHTML == 'ON')
    {
      FANbtn = 'fanLEDonoff=OFF';
    }
    websock.send(FANbtn);
  }
  //-----------------------------------------------------------------------------------
  function humONOFF()
  {
    HUMbtn = 'humLEDonoff=ON';
    if(document.getElementById('HUMbtn').innerHTML == 'ON')
    {
      HUMbtn = 'humLEDonoff=OFF';
    }
    websock.send(HUMbtn);
  }
</script>
</html>
)=====";