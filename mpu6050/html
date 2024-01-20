/*
  ESP32 HTML WebServer Page Code
  http:://www.electronicwings.com
*/

const char html_page[] PROGMEM = R"RawString(
<!DOCTYPE html>
<html>
  <style>
    body {font-family: sans-serif;}
    h1 {text-align: center; font-size: 30px;}
    p {text-align: center; color: #4CAF50; font-size: 30px;}
  </style>

<body>
  <h1>MPU6050 with ESP32 Web Socket </h1>
  <p>Acceleration X = <span id="x_acceleration">0</span> m/s&sup2</p>
  <p>Acceleration Y = <span id="y_acceleration">0</span> m/s&sup2</p>
  <p>Acceleration Z = <span id="z_acceleration">0</span> m/s&sup2</p><br>
 
  <p>Gyro X = <span id="x_gyro">0</span> rad/s</p>
  <p>Gyro Y = <span id="y_gyro">0</span> rad/s</p>
  <p>Gyro Z = <span id="z_gyro">0</span> rad/s</p><br>
 
  <p>Temperature = <span id="temp">0</span> &#8451;</p>

<script>
  setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        const text = this.responseText;
        const myArr = JSON.parse(text);
       document.getElementById("x_acceleration").innerHTML = myArr[0];
        document.getElementById("y_acceleration").innerHTML = myArr[1];
       document.getElementById("z_acceleration").innerHTML = myArr[2];
       document.getElementById("x_gyro").innerHTML = myArr[3];
       document.getElementById("y_gyro").innerHTML = myArr[4];
       document.getElementById("z_gyro").innerHTML = myArr[5];
       document.getElementById("temp").innerHTML = myArr[6];
      }
    };
    xhttp.open("GET", "read_Web_MPU6050", true);
    xhttp.send();
  },100);
</script>
</body>
</html>
)RawString";