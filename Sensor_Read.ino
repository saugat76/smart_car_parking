int readSensor(int ULTRASONIC_TRIG_PIN, int ULTRASONIC_ECHO_PIN) {

  //Clear all the Trigger Pin
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);
  delayMicroseconds(2);

  //Set Trigger Pin for 10 Microseconds
  digitalWrite(ULTRASONIC_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_TRIG_PIN, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH);

  // Calculating the distance
  distance = duration * 0.0343 / 2;

  return distance;
}
