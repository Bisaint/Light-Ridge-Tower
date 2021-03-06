

/********************************************************/
/*****项目：一代红警光棱塔********************************/
/*****基于：arduino**************************************/
/*****版本：A********************************************/
/*****作者：毕圣-Bisiant（bilibil）***********************/
/*****备注：开源代码不得商用******************************/
/********************************************************/

/********************************************************/
/********************引脚和标志定义***********************/
/********************************************************/

#define RE 2
#define key 8
#define bb A0
int light[6] = {3, 5, 6, 10, 11, 9};
int keya = 0;

/********************************************************/
/********************闪烁一次*****************************/
/********************************************************/

void bk1()
{
  for (int k = 0; k < 6; k++)
  {
    digitalWrite(light[k], HIGH);
  }
  delay(100);
  for (int k = 0; k < 6; k++)
  {
    digitalWrite(light[k], LOW);
  }
  delay(100);
}

/********************************************************/
/********************循环一圈*****************************/
/********************************************************/

void tk1(int n)
{
  for (int k = 0; k < 6; k++)
  {
    for (int i = 0; i < 255; i += 5)
    {
      analogWrite(light[k], i);
    }
    for (int i = 255; i >= 0; i -= 5)
    {
      analogWrite(light[k], i);
      delay(n);
    }
  }
}

/********************************************************/
/********************启动执行函数*************************/
/********************************************************/

void start()
{
  /******************/
  /***上电行为*******/
  /******************/
  digitalWrite(RE, HIGH);
  for (int i = 0; i <= 3; i++)
  {
    tk1(1);
  }
  for (int i = 0; i <= 3; i++)
  {
    bk1();
  }
  /******************/
  /***等待按键按下***/
  /******呼吸灯******/
  while (digitalRead(key) == HIGH)
  {
    for (int i = 0; i < 255; i += 5)
    {
      for (int k = 0; k < 6; k++)
      {
        analogWrite(light[k], i);
      }
      delay(analogRead(bb) / 15);
    }
    for (int i = 255; i >= 0; i -= 5)
    {
      for (int k = 0; k < 6; k++)
      {
        analogWrite(light[k], i);
      }
      delay(analogRead(bb) / 15);
    }
  }
}

/********************************************************/
/***********************按键监测函数**********************/
/********************************************************/

void akb()
{
  switch (keya)
  {
  case 0:    //按键记录为0
    while (digitalRead(key) == HIGH)
    {
      for (int k = 0; k < 6; k++)
      {
        digitalWrite(light[k], LOW);
      }
    }
    keya = 1;
    break;
  case 1:    //按键记录为1
    while (digitalRead(key) == HIGH)
    {
      for (int k = 0; k < 6; k++)
      {
        for (int i = 0; i < 255; i += 5)
        {
          analogWrite(light[k], i);
          delay(analogRead(bb) / 50);
        }
        for (int i = 255; i >= 0; i -= 5)
        {
          analogWrite(light[k], i);
          delay(analogRead(bb) / 50);
        }
      }
    }
    keya = 2;
    break;
  case 2:    //按键记录为2
    while (digitalRead(key) == HIGH)
    {
      for (int i = 0; i < 255; i += 5)
      {
        for (int k = 0; k < 6; k++)
        {
          analogWrite(light[k], i);
        }
        delay(analogRead(bb) / 15);
      }
      for (int i = 255; i >= 0; i -= 5)
      {
        for (int k = 0; k < 6; k++)
        {
          analogWrite(light[k], i);
        }
        delay(analogRead(bb) / 15);
      }
    }
    keya = 3;
    break;
  case 3:    //按键记录为3
    while (digitalRead(key) == HIGH)
    {
      int i = analogRead(bb) / 4;
      for (int k = 0; k < 6; k++)
      {
        analogWrite(light[k], i);
      }
    }
    keya = 4;
    break;
  case 4:    //按键记录为4
    while (digitalRead(key) == HIGH)
    {
      for (int k = 0; k < 6; k++)
      {
        digitalWrite(light[k], HIGH);
      }
    }
    keya = 0;
    break;
  }
}

/********************************************************/
/***********************用于拓展的at函数******************/
/********************************************************/

void at()
{
  akb();
  Serial.println(keya);
}

/********************************************************/
/********************只执行一次的主函数*******************/
/********************************************************/

void setup()
{
  pinMode(light, OUTPUT);
  pinMode(RE, OUTPUT);
  pinMode(key, INPUT_PULLUP);
  Serial.begin(9600);
  start();
}

/********************************************************/
/********************会一直循环的主函数*******************/
/********************************************************/

void loop()
{
  at();
  delay(1000);
}
