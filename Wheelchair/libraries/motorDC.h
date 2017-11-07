class motor
{
  int pA, pB;
  public:
  motor()
  {}
  void setup(int pA, int pB)
  {
    this->pA = pA;
    this->pB = pB;


    pinMode(pA, OUTPUT);
    pinMode(pB, OUTPUT);
    analogWrite(pA, 0);
    analogWrite(pB, 0);
  }
  void setVelocity(float value)
  {
    if(value != 0)
    {
      if(value > 0)
      {        
        analogWrite(pA, value);
        analogWrite(pB, 0);
      }
      else
      {        
        analogWrite(pA, 0);
        analogWrite(pB, (-value));
      }
    }
    else
    {
      analogWrite(pA, 0);
      analogWrite(pB, 0);
    }
  }
};