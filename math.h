namespace Math
{
  #define pi 3.141592
  #define radToDegrees 180/pi
  template<typename type>
  class Vector2
  {
  private:
    typedef Vector2<type> tType;
  public:
    type x, y;
    Vector2()
    {
      x = 0;
      y = 0;
    }
    Vector2(type x, type y)
      : x(x), y(y)
    {}

    void operator=(const tType &value)
    {
      this->x = value.x;
      this->y = value.y;
    }
    void operator=(type value)
    {
      x = y = value;
    }

    void operator+=(const tType &value)
    {
      x += value.x;
      y += value.y;
    }
    void operator-=(const tType &value)
    {
      x -= value.x;
      y -= value.y;
    }
    void operator*=(const tType &value)
    {
      x *= value.x;
      y *= value.y;
    }
    void operator/=(const tType &value)
    {
      x /= value.x;
      y /= value.y;
    }
    tType operator+(const tType &value)
    {
      register tType _t(*this);
      _t += value;
      return _t;
    }
    tType operator-(const tType &value)
    {
      register tType _t(*this);
      _t -= value;
      return _t;
    }
    tType operator*(const tType &value)
    {
      register tType _t(*this);
      _t *= value;
      return _t;
    }
    tType operator/(const tType &value)
    {
      register tType _t(*this);
      _t /= value;
      return _t;
    }

    void operator+=(type value)
    {
      x += value;
      y += value;
    }
    void operator-=(type value)
    {
      x -= value;
      y -= value;
    }
    void operator*=(type value)
    {
      x *= value;
      y *= value;
    }
    void operator/=(type value)
    {
      if (value == 0)
      {
        x = 0;
        y = 0;
        return;
      }
      x /= value;
      y /= value;
    }
    tType operator+(type value)
    {
      register tType _t(*this);
      _t += value;
      return _t;
    }
    tType operator-(type value)
    {
      register tType _t(*this);
      _t -= value;
      return _t;
    }
    tType operator*(type value)
    {
      register tType _t(*this);
      _t *= value;
      return _t;
    }
    tType operator/(type value)
    {
      register tType _t(*this);
      _t /= value;
      return _t;
    }


    type magnitude()
    {
      return (sqrt(pow(x, 2)) + sqrt(pow(y, 2)));
    }
    type length()
    {
      return sqrt((pow(x, 2) + (pow(y, 2))));
    }
    tType normalize()
    {
      register tType _t(*this);
      _t /= magnitude();
      return _t;
    }
    void rotate(float angle)
    {
      angle /= radToDegrees;
      float px = x, py = y;
      x = (px*cos(angle)) - (py * sin(angle));
      y = (px*sin(angle)) + (py * cos(angle));
    }
    float angle()
    {
      return (atan2(y, x) * radToDegrees);
    }
    /*tType normalize()
    {
    *this /= magnitude();
    return *this;
    }*/
  };
  template<typename type>
  class Vector
  {
  public:
    static float dot(Vector2<type> v1, Vector2<type> v2)
    {
      Vector2<type> r = (v1 - v2);      
      double dPro = ((v1.x * v2.x) + (v1.y * v2.y));
      double dLengths = v1.length() * v2.length();
      return dPro / dLengths;
    }
    static float cross()
    {}
    static float distance(Vector2<type> &v1, Vector2<type> &v2)
    {
      Vector2<type> r = v1 - v2;
      return r.length();
    }
  };
	typedef Vector2<float> vecf;
	typedef Vector2<double> vecd;
	typedef Vector2<int> veci;
};
