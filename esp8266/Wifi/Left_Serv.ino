int   l_i = 0;
int   l_w = 0;
int   l_j = 0;
int   l_k = 0;

void wave_left_hand(int *l_wave){
 int z = 0;
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
  l_i = 0;
  while (l_i++ < 200){
    pwm.setPWM(11, 0, 360 + l_i);
    pwm.setPWM(8, 0, 260 - l_i);
    delay(5);
  }
  while (l_j++ < 4){
   if (z <= 0){
    while (z++ <= 100){
      pwm.setPWM(10, 0, 560 - z);
      delay(5); 
    }
  }
  else{
    while (z-- >= -100){
      pwm.setPWM(10, 0, 560 - z);
      delay(5);
    }
  } 
  }
  delay(500);
  while (l_i-- >= 0){
    pwm.setPWM(8, 0, 260 - l_i);
    pwm.setPWM(11, 0, 360 + l_i);
    delay(5);
  }
  pwm.setPWM(10, 0, 560);
  *l_wave = 1;
}
