  #include <Wire.h>
  #include <BH1750.h>
  #include <Adafruit_NeoPixel.h>
  #include <SoftwareSerial.h>
 
  SoftwareSerial mySerial(2, 3);    // RX, TX
  Adafruit_NeoPixel pixels (24, 1, NEO_GRB + NEO_KHZ800);//INCLUIR NOVOS LEDS  
  BH1750 lightMeter;

  const byte  luxMax = 7,// MAX PARA AUMENTAR BRILHO
              luxMin = 5;// MIN PARA DIMINUIR BRILHO
              
  const byte  brilhoMin   = 5, brilhoMax   = 255;                

  byte        Minuto, newMinuto, dezenaM, unidadeM, Hora, dezenaH, unidadeH;
  
  int long    pontoMillis, pixelHue;

  const byte displayConfig[12][7]= {{0,0,1,2,4,5,6},  //Digito 0
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
  mySerial.begin(9600);
  mySerial.setTimeout(20);
  pixels.begin();
  pixels.clear();
  delay(50);
}//END SETUP
//===============================================//
void loop() {       
    if(millis() - pontoMillis >= 1000){
      pontoMillis = millis();
      piscaPonto();     
    }//END MILLIS
    if(mySerial.available() > 0){
      eventoSerial();
    }//END SERIAL AVAILABEL
      
    delay(1);
    display();

}//END LOOP             
//===============================================//
void eventoSerial(){
    String val; 
    String  recebido = mySerial.readStringUntil('\n'); 
    val = recebido.charAt(0);
    dezenaH = val.toInt();
    val = recebido.charAt(1);
    unidadeH = val.toInt();
    val = recebido.charAt(3);
    dezenaM = val.toInt();
    val = recebido.charAt(4);
    unidadeM = val.toInt();
    pixels.clear();
    delay(1);
    display();
    
}//END EVENTO SERIAL
//===============================================//
void luxRead(){
  byte lux;
  bool lux_flag;
  
    lux = lightMeter.readLightLevel();      
    if(lux >= luxMax){
      pixels.setBrightness(brilhoMax);
      //pixelHue = millis();
      lux_flag = true;
    }//END IF LUX MAX
    
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
  bool LED; 
  
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
void display(){    
    for (byte ID = 0; ID < 7; ID++){
      pixels.setPixelColor((displayConfig[unidadeM][ID]), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS UNIDADE DE Minuto
      pixels.setPixelColor((displayConfig[dezenaM][ID]+7), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS DEZENA DE Minuto
      
      pixels.setPixelColor((displayConfig[unidadeH][ID]+15), pixels.gamma32(pixels.ColorHSV(pixelHue)));//LEDS UNIDADE DE Hora
      pixels.setPixelColor((displayConfig[dezenaH][ID]+22), pixels.gamma32(pixels.ColorHSV(pixelHue))); //LEDS DEZENA DE Hora
      pixels.show();
    }
}//END VOID DISPLAY
