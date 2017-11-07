#include "motorDC.h"
#include "capture.h"
using namespace Math;
void prt(String Name, double v, String Endl = "")
{
  //Serial.print(Name + "(" + String(v) + ") " + Endl);
}

fVec moveFnx(const fVec &value)
{
  float 
    dr = FVec::dot(value, fVec(1, 0)),
    du = FVec::dot(value, fVec(0, 1));
  prt("dr", dr);  prt("du", du);  prt("l", value.length());
  prt("\y\tx", value.x); prt("y", value.y);

  float 
    m1 = 0,
    m2 = 0;


  m1 = (FVec::dot(value, fVec(1, 0))) + (FVec::dot(value, fVec(0, 1))*value.length());
  m2 = (FVec::dot(value, fVec(-1, 0))) + (FVec::dot(value, fVec(0, 1))*value.length());
  prt("\tm1", m1); prt("m2", m2, "\n");
  Serial.print(m1);
  Serial.print(" ");
  Serial.println(m2);
  return value;
}


capture t;
void setup() {
  Serial.begin(9600);
  t.setup(A0, A1, fVec(-1,-1));
}
void loop() {  
  fVec vf = moveFnx(t.getData());  
  //vf *=254;
}
