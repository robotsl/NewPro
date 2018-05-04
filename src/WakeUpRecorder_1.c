char *wake_string(char *instr) {
  int ret = 0;
  char str[20] = " ";
  wiringPiSetup();    // wiringPi库初始化
  pinMode(1, INPUT);  //设置1口为输出模式
  pinMode(0, OUTPUT); //设置0口为输出模式
  for (;;) {
    if ((ret = digitalRead(1)) == 0) {
      // execl("./asr_record_sample","asr_record_sample",NULL);
      if (strcmp((strcpy(instr, retString(str))), '\0') > 0) {
        return instr;
      } else {
        return NULL;
      }
    } else {
      digitalWrite(0, HIGH);
    }
  }
  return NULL;
}
