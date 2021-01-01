#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

Adafruit_NeoPixel pixels(31, 6, NEO_GRB + NEO_KHZ800);
#include <EEPROM.h>


int clickRate = 0;
int clickRate2 = 0;
int date = 0;
boolean app = true;
int year[366];

void setup() 
{

      for(int i = 0; i<366;i++)
      {
      year[i] = EEPROM.read(i);   
      }
      date = EEPROM.read(370);
   pixels.begin();
   pixels.show();
   pixels.setBrightness(10);
   pinMode(A4, INPUT);
   pinMode(A1, INPUT);
   for(int i = 30; i>=0;i--)
   {
      pixels.clear();
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));  
      pixels.show();
      delay(10);
   }
   pixels.clear();
   ledMonth();
}

void loop() 
{
  while(digitalRead(A4)==1 || digitalRead(A1)==1)
  {
     if(digitalRead(A1)==1 )
     {
      clickRate++;
     }
     if(digitalRead(A4)==1 )
     {
      clickRate2++;
     }
     delay(20);
  }
    if(clickRate2>5 && clickRate>5)
    {
     if(app==true)
     {
      pixels.clear();
      pixels.setPixelColor(30, pixels.Color(255, 255, 255));
      pixels.show();
      app = false;
     }
     else
     {
      ledMonth();
      app = true;
     }
      clickRate = 0;
      clickRate2 = 0;
    }
    if(clickRate2>100)
    {
      look(false);
      ledMonth();
    }
    else if(clickRate2>25)
    {
      rainbow();
      clickRate = 0;
      clickRate2 = 0;
    }
    else if(clickRate2>3)
    {
      revert();
    }
    if(clickRate>17)
    {
      notCompleteToday();
    }
    else if (clickRate>4)
    {
      completeToday(); 
    }
  clickRate = 0;
  clickRate2 = 0;
  delay(20);
}
void look(boolean last)
{
  int count = 0;
  for(int i = 0; i<12;i++)
  {
    pixels.clear();
    for(int j = 0; j<31;j++)
    {
       if(j<month(i))
       {
          if(year[count]==0)
          {
            pixels.setPixelColor(30-j, pixels.Color(0,0,0));
          }
          else if(year[count]==1)
          {
            pixels.setPixelColor(30-j, pixels.Color(31, 150, 42));
          }
          else if(year[count]==2)
          {
            pixels.setPixelColor(30-j, pixels.Color(255, 51, 0));
          }
        count++;
       }
       else
       {
          pixels.setPixelColor(30-j, pixels.Color(255,165,0));
       }
    }
    pixels.show();
    if(digitalRead(A1)==1 && last ==true)
    {
      break;
    }
    delay(1000);
    if(digitalRead(A1)==1 && last ==true)
    {
      break;
    }
  }
}

int month(int count)
{
  int months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
  return months[count];
}

int daysInMonth()
{
  int count = 0;
  int months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
  for(int i = 0;i<12;i++)
  {
    if(date>=count+months[i])
    {
        count+=months[i];
    }
    else
    {
        return months[i];
    }
  }
}
int startOfMonth()
{
  int count = 0;
  int months[] = {31,29,31,30,31,30,31,31,30,31,30,31};
  for(int i = 0;i<12;i++)
  {
    if(date>=count+months[i])
    {
        count+=months[i];
    }
    else
    {
        return count;
    }
  }
  return count;
}

void reset()
{
  for(int i = 0; i<366;i++)
  {
      year[i] = 0;
  }
  date = -1;
  ledMonth();
  for(int i = 0; i<366;i++)
  {
      EEPROM.update(i,0);   
  }
      EEPROM.update(370,0);
  return;
}


void ledMonth()
{
    pixels.clear();
    for(int i =0;i<31;i++)
    {
      if(year[startOfMonth()+i]==1 && i < daysInMonth())
      {
        pixels.setPixelColor(30-i, pixels.Color(31, 150, 42));  
      }
      else if(year[startOfMonth()+i]==2 && i < daysInMonth())
      {
         pixels.setPixelColor(30-i, pixels.Color(255, 51, 0));
      }
      else if(year[startOfMonth()+i]==0 && i < daysInMonth())
      {
         pixels.setPixelColor(30-i, pixels.Color(0, 0, 0));
      }
      else
      {
        pixels.setPixelColor(30-i, pixels.Color(255,165,0));
      }
    }
    pixels.show();
}
void lastDay()
{
  while(digitalRead(A1)!=1)
  {
    look(true);
  }
  reset();
}
void showoff()
{
  delay(100);
  if(date == 30 || date == 59 ||date == 90 || date == 120 ||date == 151 || date == 181 ||date == 212 || date == 243 ||date == 273 || date == 304 ||date == 334||date==365)
  {
    pixels.clear();
    for(int i =0;i<31;i++)
    {
      if(year[startOfMonth()+i]==1 && i < daysInMonth())
      {
        pixels.setPixelColor(30-i, pixels.Color(31, 150, 42));  
      }
      else if(year[startOfMonth()+i]==2 && i < daysInMonth())
      {
         pixels.setPixelColor(30-i, pixels.Color(255, 51, 0));
      }
      else if(year[startOfMonth()+i]==0 && i < daysInMonth())
      {
         pixels.setPixelColor(30-i, pixels.Color(0, 0, 0));
      }
      else
      {
        pixels.setPixelColor(30-i, pixels.Color(255,165,0));
      }
      delay(34);
      pixels.show();
    } 
  }
  delay(100);
  if(date ==365)
  {
    lastDay();
  }
  else
  {
  ledMonth();
  }
}
void completeToday()
{
   year[date] = 1;
   EEPROM.update(date,1);
   ledMonth();
   showoff();
   date++;
   EEPROM.update(370,date);
}
void notCompleteToday()
{
    year[date] = 2;
    EEPROM.update(date,2);
    ledMonth();
    showoff();
    date++;
    EEPROM.update(370,date);
}
void revert()
{
   if(date == 0)
   {
    date++;
   }
   date--;
   year[date] = 0;
   EEPROM.update(date,0);
   EEPROM.update(370,date);
   ledMonth();
}
void rainbow() 
{
  pixels.clear();
  for(long firstPixelHue = 0; firstPixelHue < 65536*2; firstPixelHue += 256) 
  {
    for(int i=0; i<pixels.numPixels(); i++) 
    {
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show(); 
    delay(10);  
  }
  ledMonth();
}
