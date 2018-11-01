int   i = 0;
int   w = 0;
int   j = 0;
int   k = 0;

//R-HTWT 4
//S-TWT 6
//R-ASS 7

void hands_up(int *down, int *h_up, int *r, int *l){
  pwm1.setPWM(11, 0, 160);
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
 
  pwm.setPWM(11, 0, 140);//140
  pwm.setPWM(10, 0, 560);//120
  pwm.setPWM(9, 0, 280);//260
  while (i++ < 200){
    pwm1.setPWM(8, 0, 240 + i);
    pwm.setPWM(8, 0, 280 - i);
    delay(5);
    Serial.println(i);
  }
  delay(500);
  ///hands_down(h_up, r, l);
  Serial.print("exit");
  *r = 0;
  *l = 0;
  *h_up = 1;
  *down = 0;
}

void hands_down(int *down, int up, int r, int l){
  if (up == 0){
    return ;
  }
  else if (*down == 1){
    return ;
  }
  i = 200;
  Serial.println("Moving arms down.");
  pwm1.setPWM(11, 0, 380);
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
 
  pwm.setPWM(11, 0, 360);//140
  pwm.setPWM(10, 0, 560);//120
  pwm.setPWM(9, 0, 280);//260
  while (i-- > 0){
    pwm1.setPWM(8, 0, 240 + i);
    pwm.setPWM(8, 0, 280 - i);
    delay(5);
  }
  *down = 1;
}

void  idle(){
  int d = 0;
  for(int i = 0; i < 5; i++){
    //hands_down(&d);
    if (raand == 0)
      return ;
    //hands_up();
    if (raand == 0)
      return ;
    //hands_down(&d);
    if (raand == 0)
      return ;
    //wave_right_hand();
  }
}
