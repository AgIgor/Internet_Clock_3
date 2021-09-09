  #include <Wire.h>
  #include <BH1750.h>
  #include <Adafruit_NeoPixel.h>
  
  Adafruit_NeoPixel pixels (24, 1, NEO_GRB + NEO_KHZ800);
    
  BH1750 lightMeter;
  
  int lux,
      luxMax = 10,// MAX PARA AUMENTAR BRILHO
      luxMin = 5;// MIN PARA DIMINUIR BRILHO


  int Segundo;
  int
    Minuto,
    newMinuto,
    dezenaM,
    unidadeM;
  int
    Hora,
    dezenaH,
    unidadeH;
  
  int
    pixelHue,
    brilhoMin   = 5,
    brilhoMax   = 255;
    
  bool lux_flag;
  bool LED;

  int long pontoMillis;
  
  int contSeg = 0,
      contMin = 0,
      contHor = 0;
  
  byte displayConfig[12][7]= {{0,0,1,2,4,5,6},  //Digito 0
                              {0,0,0,0,0,0,4},  //Digito 1
                              {0,0,0,1,3,5,6},  //Digito 2
                              {0,0,0,1,3,4,5},  //Digito 3
                              {0,0,0,0,2,3,4},  //Digito 4
                              {1,1,1,2,3,4,5},  //Digito 5
                              {1,1,2,3,4,5,6},  //Digito 6
                              {0,0,0,0,0,1,4},  //Digito 7
                              {0,1,2,3,4,5,6},  //Digito 8
                              {0,0,1,2,3,4,5},  //Digito 9
                              {0,0,0,0,1,2,3},  //Grau
                              {0,0,0,0,0,3,6}}; //Umidade; 

void setup(){
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
  delay(50);
}//END SETUP
//===============================================//
void loop() {       
    if(millis() - pontoMillis >= 1000){
      pontoMillis = millis();
      piscaPonto();
/*
      if(serial){
        //VERIFICA A SERIAL
        HOR = H;
        MINUTO = M;        
        if(newMinuto != Minuto){
          newMinuto = Minuto;
          luxRead();
          trataDigitos();
        }//END NEW MINUTO
      }//END IF SERIAL
*/      
    }//END MILLIS
    
    delay(1);
    display();//ALTERA CORES DIDPLAY
             
//===============================================//
}//END LOOP
void luxRead(){
    lux = lightMeter.readLightLevel();      
    if(lux >= luxMax){
      pixels.setBrightness(brilhoMax);
      //pixelHue = millis();
      lux_flag = true;
    }//END IF LUX MAX
//===============================================//    
    if(lux <= luxMin){
      pixels.setBrightness(brilhoMin);
      //pixelHue = 0;
      lux_flag = false;
    }//END IF LUX MIN
    if(lux_flag){
      pixelHue = millis();
    }else{
      pixelHue = 0;
    }//END ELSE LUX FLAG    
}//END LUX READ
//===============================================//
void piscaPonto(){  
  LED = !LED; 
    if(LED){
      pixels.setPixelColor(14, pixels.gamma32(pixels.ColorHSV(pixelHue)));
      pixels.show();
    }else{
      pixels.setPixelColor(14, pixels.Color(0, 0, 0));
      pixels.show();
    }
}//END PISCA PONTOS
//===============================================//
void trataDigitos(){
//=========================//Hora//=========================//
    dezenaH = Hora;
    unidadeH = dezenaH;
    dezenaH = dezenaH/10;
    unidadeH = unidadeH % 10;
//=========================//Minuto//=========================//
    dezenaM = Minuto;
    unidadeM = dezenaM;
    dezenaM = dezenaM/10;
    unidadeM = unidadeM % 10;
    pixels.clear();
    display();
}//END TRATA DIGITOS

void display(){    
    for (int ID = 0; ID < 7; ID++){
      pixels.setPixelColor((displayConfig[unidadeM][ID]), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS UNIDADE DE Minuto
      pixels.setPixelColor((displayConfig[dezenaM][ID]+7), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
      pixels.setPixelColor((displayConfig[unidadeH][ID]+15), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
      if(dezenaH > 0){
        pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS DEZENA DE Hora
      }else{
        pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.Color(0, 0, 0)); //LEDS DEZENA DE Hora
      }
      pixels.show();
    }
}//END VOID DISPLAY
