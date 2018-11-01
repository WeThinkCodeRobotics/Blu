void  LED(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}
int z = 0;
void neck(){

  pwm.setPWM(6, 0, 160);
}

void sit(){
  pwm.setPWM(6, 0, 300);
  pwm.setPWM(12, 0, 560);
  pwm.setPWM(4, 0, 360);
  pwm1.setPWM(3, 0, 600);
  pwm1.setPWM(6, 0, 400);
  pwm1.setPWM(4, 0, 360);
}

void nod(){
  int   x = 0;
  int   y = 0;
  int   z = 0;
  while (z++ < 4){
    if (x <= 0){
      while (x++ <= 50){
        pwm.setPWM(6, 0, 300 + x);
        delay(5); 
    }
  }
  else{
    while (x-- >= 0){
      pwm.setPWM(6, 0, 300 + x);
      delay(5);
    }
  }
  }
}

void  twist_left(){
  int   x = 0;
  int   y = 0;
  int   z = 0;
  if (x <= 0){
    while (x++ <= 100){
      pwm1.setPWM(6, 0, 400 - x);
      delay(5); 
  }
  //delay(200);
}
else{
  while (x-- >= 0){
    pwm1.setPWM(6, 0, 400 - x);
    delay(5);
  }
}
}

void  twist_right(){
  int   x = 0;
  int   y = 0;
  int   z = 0;
  if (x <= 0){
    while (x++ <= 100){
      pwm1.setPWM(6, 0, 400 + x);
      delay(5); 
  }
  //delay(200);
}
else{
  while (x-- >= 0){
    pwm1.setPWM(6, 0, 400 + x);
    delay(5);
  }
}
}
