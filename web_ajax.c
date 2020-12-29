void loadAjaxRedirects (void) {
    server.on("/readADC", readADCtoWeb);//To get update of ADC Value only
    server.on("/LED", HTTP_GET, writeLEDfromWeb);  // Call the 'handleLED' function when a GET request is made to URI "/LED"
    //can also do a get with values.. /LED?name1=value1&name2=value2, post is a form value.
    server.on("/setPWMPercent", HTTP_POST, writePWMfromWeb);  // Call the 'handleLED' function when a POST request is made to URI "/LED"
}

void readADCtoWeb(void) {
    int a = analogRead(A0);
    String adcValue = String(a);
    server.send(200, "text/plain", adcValue); //Send ADC value only to client ajax request
}

//also bad for security... binary get 
void writeLEDfromWeb(void) {                          // If a POST request is made to URI /LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  //server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  //server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
  server.send(200, "text/plain", led); //Send ADC value only to client ajax request
}

//this example is horrable for security, but uses forms.
void writePWMfromWeb(void) {                         // If a POST request is made to URI /setValue
  if( ! server.hasArg("io") || ! server.hasArg("freq") || !server.hasArg("channel")
      || server.arg("res") == NULL || server.arg("duty") == NULL) { // If the POST request doesn't have username and password data
    server.send(400, "text/plain", "400: Invalid Request");         // The request is invalid, so send HTTP status 400
    return;
  }
  int loggedIn = 1;
  if (loggedIn = 1) {
    int gpio = server.arg("io").toInt();
    int frequency = server.arg("freq").toInt();
    int channel = server.arg("channel").toInt();
    int resolution = server.arg("res").toInt();
    int dutycycle = 20;
    dutycycle = server.arg("duty").toInt();
    ledcAttachPin(gpio, channel);
    ledcSetup(channel, frequency, resolution);
    ledcWrite(channel, dutycycle);
    server.send(200, "text/html", "<p>set the duty cycle</p>");
  } else {                                                                              // Username and password don't match
    server.send(401, "text/plain", "401: Unauthorized");
  }
}