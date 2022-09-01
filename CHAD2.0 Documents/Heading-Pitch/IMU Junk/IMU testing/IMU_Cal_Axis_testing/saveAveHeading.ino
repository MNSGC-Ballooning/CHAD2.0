

double saveAveHeading(float newHeading) { // there is a ~5s delay in the calculation of Ave heading because it takes last 50 heading with new data every 10th of a second

  for (int i = (aveHeadingLength - 1); i > 0; i--) { //aveHeadingLength -1 is last spot bc nth spot is array[n-1]
    aveHeading[i] = aveHeading[i - 1];
  }
  aveHeading[0] = newHeading;

  double out = 0;


  for (int i = 0; i < aveHeadingLength; i++) {
    out += aveHeading[i];
  }
  out /= double(aveHeadingLength);

  return out;
}
