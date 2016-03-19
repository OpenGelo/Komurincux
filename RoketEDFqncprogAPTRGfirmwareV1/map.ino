float rawMapFixX(float Vx)
{
  float LastXval = mapfloat(Vx, ValueMinInX, ValueMaxInX, ValueMinOutX, ValueMaxOutX);
  return LastXval;
}
float rawMapFixY(float Vy)
{
  float LastYval = mapfloat(Vy, ValueMinInY, ValueMaxInY, ValueMinOutY, ValueMaxOutY);
  return LastYval;
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
