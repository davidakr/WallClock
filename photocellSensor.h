#ifndef PhotoCellSensor_h
#define PhotoCellSensor_h

class PhotoCellSensor {
public:
  int red;
  int blue;
  int green;
  int brightness;
  void readPhotocell();
};

#endif
