//funciton to calibrate the raw mag field data

//array of the 'b' is hard iron correction vector, these values come from calibration

double bX = -586.089408750580;
double bY = 749.769125777733;
double bZ = 803.321146745311;



double b[3] = { bX, bY, bZ}; //b is a 1x3 matrix

//array 'A' is the soft iron correction vector. Vector is symetric about the diagonal

double Axx = 0.987840276579987;
double Axy = 0.0323982568982308;
double Axz = 0.00172137390605034;
double Ayx = Axy;
double Ayy = 0.991298519731660;
double Ayz = 0.00442474176756341;
double Azx = Axz;
double Azy = Ayz;
double Azz = 1.02231337125352;
double A[3][3] = { {Axx, Axy, Axz} , {Ayx, Ayy, Ayz}, {Azx, Azy, Azz} };



void magCal(){ //we have imu.mx -> imu.mz
  //I am doing the math on the car data before it is "calibrated" <== ?? to by in the units gauss
  //this calibrated raw data will be converted into gauss where 1gauss = 100 uT
  double D[3] = {imu.mx, imu.my, imu.mz}; // D is a 1x3 matrix

  //get D-b
  for(int i = 0; i <3; i++){
    D[i] = D[i] - b[i];
    //also set all of m = 0
    m[i] = 0;
  }

  //now getting m = D * A
  for(int mRow = 0; mRow < 3; mRow++){
    for(int col = 0; col<3; col++){
      m[mRow] += D[col] * A[col][mRow];  //i am aware that the col and mRow are opposite for A. because of matrix multiplication A changes different than D
    }
  }
  
}//end magCal
