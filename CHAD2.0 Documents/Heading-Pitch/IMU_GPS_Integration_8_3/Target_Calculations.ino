//functions to display the target coordinates, find required bearing to veiw target from current position, and finding distance from current position to target along that bearing

//funciton to display targets current coordinates as specified by the user
void displayTargetCoordinates() {
  Serial.println("Target's Coordinates (LLA):\nLat:\tLon:\tAlt(f):");
  Serial.println(String(targetLat, 5) + "\t" + String(targetLon, 5) + "\t" + String(targetAlt, 2));
}

/*funciton calculates the bearing angle from current location to target location Math found here:
   https://www.igismap.com/formula-to-find-bearing-or-heading-angle-between-two-points-latitude-longitude/
   Function returns the change in heading required to to make our current heading -> required bearing
   default variable currHeading is assuming that our current heading is pointing north */
double calcBearingAngle(double targetLat, double targetLon, double currLat = currLatitude, double currLon = currLongitude, double currHeading = 0)
{
  Serial.println("\nCalculating bearing between " + String(currLat, 5) + "," + String(currLon, 5) + " and " + String(targetLat, 5) + "," + String(targetLon, 5) + " With heading: " + String(currHeading));

  //finding the change in longitude from current point to target point
  double deltaLon = targetLon - currLon;

  //convery all quantities into rad for trig
  currLat *=  PI / 180.0;
  currLon *=  PI / 180.0;
  targetLat *=  PI / 180.0;
  targetLon *=  PI / 180.0;
  deltaLon *=  PI / 180.0;

  //bearing will equal bearing = arcTan2(X,Y), where...
  double x = cos(targetLat) * sin(deltaLon);
  double y = cos(currLat) * sin(targetLat) - sin(currLat) * cos(targetLat) * cos(deltaLon);
  double reqBearing = atan2(x, y);

  Serial.println("Bearing that is calculated is on scale from -180 -> 180");
  reqBearing *= 180.0 / PI;
  Serial.println("Bearing degrees: " + String(reqBearing, 5));
  Serial.println("Required change in heading (degrees): " + String(headingDiff(currHeading, reqBearing)));
  Serial.println();
  return headingDiff(currHeading, reqBearing);  //calling function that will return bearing angle req between current heading (assumed zero unless specified)
}

/// The difference of two headings in degrees such that it is always in the range.
/// (-180, 180]. A negative number indicates [h2] is to the left of [h1].
double headingDiff(double h1, double h2) {
  double left = h1 - h2;
  double right = h2 - h1;
  if (left < 0) left += 360;
  if (right < 0) right += 360;
  return left < right ? -left : right; //checks is the left difference is less than the right, if true return left difference w/ neg for left and if false return right diff
}


double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = lat1d * PI / 180.0;
  lon1r = lon1d * PI / 180.0;
  lat2r = lat2d * PI / 180.0;
  lon2r = lon2d * PI / 180.0;
  u = sin((lat2r - lat1r) / 2);
  v = sin((lon2r - lon1r) / 2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
