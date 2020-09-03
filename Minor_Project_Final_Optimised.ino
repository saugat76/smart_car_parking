//Library Decleration for WiFi and Message Publishing and Subscribing

#include "WiFi.h"
//#include "PubSubClient.h"
#include "HTTPClient.h"


//Defining Ultrasonic Pin

#define ULTRASONIC_TRIG_PIN1 13
#define ULTRASONIC_TRIG_PIN2 14
#define ULTRASONIC_ECHO_PIN1 12
#define ULTRASONIC_ECHO_PIN2 27


//Variables Decleration for the Ultrasonic Sensors
long duration;
int distance;
int distance1;
int distance2;
int sensor1;
int sensor2;


//WiFi variable Decleration
const char* ssid = "Saugat's WiFi";
const char* password = "***********";

//An important point to note is that there is an extern variable defined in the header file called WiFi.
//This is a variable of WiFi class and as we will see, we will use it to access much of the WiFi functionality.

void setup() {

  Serial.begin(115200);


  //WiFi Connection and Setup
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to the WiFi......");
  }

  Serial.print("Connected to the WiFi Network");
  Serial.println(ssid);
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());


  //PinMode Decleration

  pinMode(ULTRASONIC_TRIG_PIN1, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN1, INPUT);
  pinMode(ULTRASONIC_TRIG_PIN2, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN2, INPUT);

}


void loop() {

  distance1 = readSensor(ULTRASONIC_TRIG_PIN1, ULTRASONIC_ECHO_PIN1);
  distance2 = readSensor(ULTRASONIC_TRIG_PIN2, ULTRASONIC_ECHO_PIN2);
  readParkingSpace(distance1, distance2);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;

    http.begin("http://sandkrox1996.000webhostapp.com/upload.php");                //Specify destination for HTTP request
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");     //Specify content-type header

    int httpResponseCode = http.POST("A1=" + String(sensor1) + "&B2=" + String(sensor2));    //Send the actual POST request and store the reutrned int value for error checking

    if (httpResponseCode > 0) {

      String response = http.getString();   //Get the response to the request

      Serial.println(httpResponseCode);     //Print the return code
      Serial.println(response);             //Print the request answer

    }
    else  {
      Serial.print("Error in Sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end(); //Free the resource

    
    //For debugging purposes
    Serial.println(distance1);
    Serial.println(distance2);
    Serial.println("Parking Space A1 " + String(sensor1));
    Serial.println("Parking Space B2 " + String(sensor2));
  }
  else  {
    Serial.println("Error in WiFi Connection");
  }

  delay(12000); // Sends request every 12 Seconds
}
