void PIDnControl()
{
  LastXval = rawMapFixX(kalAngleX);
  if(LastXval<0){LastXval=0;}else if(LastXval>180){LastXval=180;}
  LastYval = rawMapFixY(kalAngleY);
  if(LastYval<0){LastYval=0;}else if(LastYval>180){LastYval=180;}
  
  InputL = LastXval;
  myPIDL.Compute();
  left.write(LastXval);
  InputR = LastYval;
  myPIDR.Compute();
  right.write(LastYval);
}
