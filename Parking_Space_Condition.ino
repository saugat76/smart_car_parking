void readParkingSpace(int &distance1, int &distance2) {
  if (distance1 > 10) {
    sensor1 = 1;
  }
  else {
    sensor1 = 0;
  }
  if (distance2 > 10) {
    sensor2 = 1;
  }
  else {
    sensor2 = 0;
  }
}
