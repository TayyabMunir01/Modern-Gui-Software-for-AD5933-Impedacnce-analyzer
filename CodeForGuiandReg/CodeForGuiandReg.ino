#include<Wire.h>
#define slave_addr  0x0D
#define ptr_cmd    0xB0 //or 0b10110000 
#define status_reg 0x8F
#define reset 0x10               
//#define standby_mode 0xB1    


int16_t real1,real2,imag1,imag2;
double  real = 0;
double  imag = 0;
double  magnitude=0;
double  impedance=0;
double  phase=0;
double gain = 0.000000000546;

#define sizeOfAvgArr 5

double realArray[sizeOfAvgArr];
double imagArray[sizeOfAvgArr];
double  magArray[sizeOfAvgArr];
float   phaseArray[sizeOfAvgArr];

float  realAvg=0;
float  imagAvg=0;
double magAvg=0;
float  phaseAvg=0;
double Magnitude1=0;
double Phase1=0;

int8_t  status_reg_val =0;


int reg80_v_g;
int init_start_freq;
int start_freq_sweep;
int inc_freq;
int standby_mode;
int power_down_mode;
int repeat_frequency;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  Wire.begin();
}

void loop() {
  if(Serial.available()>0)
  {serialread();}
}

void serialread(){
  String whichReg = Serial.readStringUntil('\n');
  if(whichReg == "1"){ setstartfreq(); }
  if(whichReg == "2"){ setdeltafreq(); }
  if(whichReg == "3"){ noofincement(); }
  if(whichReg == "4"){ settlingtime(); }
  if(whichReg == "5"){ Reg81val_clock(); }
  if(whichReg == "6"){ Reg80val_v_g(); }
  if(whichReg == "7"){ start_sweep(); }
  if(whichReg == "8"){ get_gain_val(); }
}

void setstartfreq(){

  while(Serial.available()<=0);
    String dataforreg1 = Serial.readStringUntil('\n');
    int data1 = dataforreg1.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x82); // register address
  Wire.write(data1); // data/byte you want to write to the register
  Wire.endTransmission(); 
  
  while(Serial.available()<=0);
    String dataforreg2 = Serial.readStringUntil('\n');
    int data2 = dataforreg2.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x83); // register address
  Wire.write(data2); // data/byte you want to write to the register
  Wire.endTransmission(); 

  while(Serial.available()<=0);
    String dataforreg3 = Serial.readStringUntil('\n');
    int data3 = dataforreg3.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x84); // register address
  Wire.write(data3); // data/byte you want to write to the register
  Wire.endTransmission(); 
}

void setdeltafreq(){
  
  while(Serial.available()<=0);
    String dataforreg1 = Serial.readStringUntil('\n');
    int data1 = dataforreg1.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x85); // register address
  Wire.write(data1); // data/byte you want to write to the register
  Wire.endTransmission(); 
  
  while(Serial.available()<=0);
    String dataforreg2 = Serial.readStringUntil('\n');
    int data2 = dataforreg2.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x86); // register address
  Wire.write(data2); // data/byte you want to write to the register
  Wire.endTransmission(); 

  while(Serial.available()<=0);
    String dataforreg3 = Serial.readStringUntil('\n');
    int data3 = dataforreg3.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x87); // register address
  Wire.write(data3); // data/byte you want to write to the register
  Wire.endTransmission();
}

void noofincement(){
  
  while(Serial.available()<=0);
    String dataforreg1 = Serial.readStringUntil('\n');
    int data1 = dataforreg1.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x88); // register address
  Wire.write(data1); // data/byte you want to write to the register
  Wire.endTransmission(); 
  
  while(Serial.available()<=0);
    String dataforreg2 = Serial.readStringUntil('\n');
    int data2 = dataforreg2.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x89); // register address
  Wire.write(data2); // data/byte you want to write to the register
  Wire.endTransmission(); 
}

void settlingtime(){
    while(Serial.available()<=0);
      String dataforreg1 = Serial.readStringUntil('\n');
    int data1 = dataforreg1.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x8A); // register address
  Wire.write(data1); // data/byte you want to write to the register
  Wire.endTransmission(); 
  
  while(Serial.available()<=0);
    String dataforreg2 = Serial.readStringUntil('\n');
    int data2 = dataforreg2.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x8B); // register address
  Wire.write(data2); // data/byte you want to write to the register
  Wire.endTransmission();
}


void Reg81val_clock(){
  while(Serial.available()<=0);
      String dataforreg = Serial.readStringUntil('\n');
    int data = dataforreg.toInt();
  delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x81); // register address
  Wire.write(data); // data/byte you want to write to the register
  Wire.endTransmission();
}

void Reg80val_v_g(){
    while(Serial.available()<=0);
      String dataforreg = Serial.readStringUntil('\n');
     reg80_v_g = dataforreg.toInt();
       delay(100);
  Wire.beginTransmission(slave_addr); //slave address
  Wire.write(0x80); // register address
  Wire.write(reg80_v_g); // data/byte you want to write to the register
  Wire.endTransmission();
}








void start_sweep(){
    int i=1;
//    Serial.print("global value ");------------------------------------------------latest delete
//    Serial.println(reg80_v_g);----------------------------------------------------latest delete
    init_start_freq = reg80_v_g+16;
    start_freq_sweep = reg80_v_g+32;
    inc_freq = reg80_v_g+48;
    standby_mode = reg80_v_g+176;
    power_down_mode = reg80_v_g+160;
    repeat_frequency = reg80_v_g+64;
    
//    Serial.print(init_start_freq);------------------------------------------------latest delete
//    Serial.print("  ");           ------------------------------------------------latest delete
//    Serial.print(start_freq_sweep);-----------------------------------------------latest delete
//    Serial.print("  ");           ------------------------------------------------latest delete
//    Serial.println(inc_freq);     ------------------------------------------------latest delete
        //enter standby mode by setting the reset
  Wire.beginTransmission(slave_addr);
  Wire.write(0x81);
  Wire.write(reset);
  Wire.endTransmission();  
  
    //enter standby mode manually
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(standby_mode);
  Wire.endTransmission(); 
  
  //initialize with start frequency
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(init_start_freq);
  Wire.endTransmission();
  //delay(100);------------------------------------------------------------------latest delete
  //start frequency sweep
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(start_freq_sweep);
  Wire.endTransmission();

//  Serial.println();------------------------------------------------------------------latest delete
//  Serial.println("Code Check 1 2 3");------------------------------------------------latest delete

  
  again_read_value:
  //delay(50);-------------------------------------------------------------------------------------------------------------latest delete
  //now reading part ,checking bit D1 of register 0x8f, pointer to status regiter 8f
  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(status_reg);
  Wire.endTransmission();
    //again_read_value:
  
  //reading from the pointer/ the data register
  Wire.requestFrom(slave_addr,1,true);
  status_reg_val = Wire.read();
  Wire.endTransmission();


  if((status_reg_val&0b00000010)>>1)
  {
  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(0x94);
  Wire.endTransmission();
  Wire.requestFrom(slave_addr,1,true);
  real1 = Wire.read();
  Wire.endTransmission();
  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(0x95);
  Wire.endTransmission();
  Wire.requestFrom(slave_addr,1,true);
  real2 = Wire.read();
  Wire.endTransmission();

  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(0x96);
  Wire.endTransmission();
  Wire.requestFrom(slave_addr,1,true);
  imag1 = Wire.read();
  Wire.endTransmission();
  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(0x97);
  Wire.endTransmission();
  Wire.requestFrom(slave_addr,1,true);
  imag2 = Wire.read();
  Wire.endTransmission();
  
  real = (real1<<8) | real2;
  imag = (imag1<<8) | imag2;

  magnitude = sqrt(real*real + imag*imag);
  impedance = 1/(gain*magnitude);

  if(real>0 && imag>0)   {phase = atan(imag/real)*(180/3.14);}
  if(real<0 && imag>0)   {phase = 180+(atan(imag/real)*(180/3.14));}
  if(real<0 && imag<0)   {phase = 180+(atan(imag/real)*(180/3.14));}
  if(real>0 && imag<0)   {phase = 360+(atan(imag/real)*(180/3.14));}

  phase = phase-96.38;
//  Serial.print(i);
//  Serial.print("    ");
//  Serial.print("Impedance: ");
//  Serial.print(impedance);
//  Serial.print("    ");
//  Serial.print("phase: ");
//  Serial.print(phase);
//  Serial.print("    ");
//  Serial.print("magnitude: ");
//  Serial.println(magnitude);
//  Serial.print("    ");
//  Serial.print("real: ");
//  Serial.print(real);
//  Serial.print("    ");
//  Serial.print("Imaginary: ");
//  Serial.println(imag);
//  delay(1000);

Serial.println(String(i)+","+String(impedance)+","+String(phase));

//    Serial.println(String(i)+"    "+"Impedance: "+String(impedance)+"    "+"phase: "+String(phase)+"    "+------------------------------------------------latest delete
//                  "magnitude: "+String(magnitude)+"    "+"real: "+String(real)+"    "+"Imaginary: "+String(imag));----------------------------------------latest delete

 //original line for graphs----------------------------------------------------------------------------
// Serial.println(String(impedance)+","+String(phase));
//  delay(100);
  //Serial.print("\n");
  //delay(50);
  i=i+1;
  //gain = gain+0.0000009;
  }
  else
  {goto again_read_value;}

  
  
  //checking if sweep is complete
  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(status_reg);
  Wire.endTransmission();
  Wire.requestFrom(slave_addr,1,true);
  status_reg_val = Wire.read();
  Wire.endTransmission();

  if (!((status_reg_val&0b00000100)>>2))
  {
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(inc_freq);
  Wire.endTransmission();
  
  goto again_read_value;
  }
  if(((status_reg_val&0b00000100)>>2))//else here it was else only
  {
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(power_down_mode);
  Wire.endTransmission();
//  Serial.println("sweep is complete");------------------------------------------------latest delete
  }
//  Wire.beginTransmission(slave_addr);
//  Wire.write(0x80);
//  Wire.write(reg80_v_g);
//  Wire.endTransmission(); 
}


/*void get_gain_val(){
        Wire.beginTransmission(slave_addr);
        Wire.write(0x80);
        Wire.write(0x11);
        Wire.endTransmission();

        Wire.beginTransmission(slave_addr);
        Wire.write(0x80);
        Wire.write(0x21);
        Wire.endTransmission();
        
        again_read_statReg_val:
        //checking for the value of status register
        Wire.beginTransmission(slave_addr);
        Wire.write(ptr_cmd);
        Wire.write(status_reg);
        Wire.endTransmission();
        Wire.requestFrom(slave_addr,1,true);
        status_reg_val = Wire.read();
        Wire.endTransmission();
      
              if((status_reg_val&0b00000010)>>1){
            
                  for(int i=0; i<sizeOfAvgArr; i++){

                        thislocation:
                        Wire.requestFrom(slave_addr,1,true);
                        status_reg_val = Wire.read();
                        Wire.endTransmission();

                          if((status_reg_val&0b00000010)>>1){                          
                        Wire.beginTransmission(slave_addr);
                        Wire.write(ptr_cmd);
                        Wire.write(0x94);
                        Wire.endTransmission();
                        Wire.requestFrom(slave_addr,1,true);
                        real1 = Wire.read();
                        Wire.endTransmission();
                        Wire.beginTransmission(slave_addr);
                        Wire.write(ptr_cmd);
                        Wire.write(0x95);
                        Wire.endTransmission();
                        Wire.requestFrom(slave_addr,1,true);
                        real2 = Wire.read();
                        Wire.endTransmission();
                      
                        Wire.beginTransmission(slave_addr);
                        Wire.write(ptr_cmd);
                        Wire.write(0x96);
                        Wire.endTransmission();
                        Wire.requestFrom(slave_addr,1,true);
                        imag1 = Wire.read();
                        Wire.endTransmission();
                        Wire.beginTransmission(slave_addr);
                        Wire.write(ptr_cmd);
                        Wire.write(0x97);
                        Wire.endTransmission();
                        Wire.requestFrom(slave_addr,1,true);
                        imag2 = Wire.read();
                        Wire.endTransmission();
                        
                        realArray[i] = (real1<<8) | real2;
                        imagArray[i] = (imag1<<8) | imag2;
                        
                        magArray[i] = sqrt(real*real + imag*imag);
  
                        if(realArray[i] && imagArray[i])   {phaseArray[i] = atan(imagArray[i]/realArray[i])*(180/3.14);}
                        if(realArray[i] && imagArray[i])   {phaseArray[i] = 180+(atan(imagArray[i]/realArray[i])*(180/3.14));}
                        if(realArray[i] && imagArray[i])   {phaseArray[i] = 180+(atan(imagArray[i]/realArray[i])*(180/3.14));}
                        if(realArray[i] && imagArray[i])   {phaseArray[i] = 360+(atan(imagArray[i]/realArray[i])*(180/3.14));}

                        if (!((status_reg_val&0b00000100)>>2)){
                              Wire.beginTransmission(slave_addr);
                              Wire.write(0x80);
                              Wire.write(0x41);
                              Wire.endTransmission();
                              }

                        Serial.println(String(magArray[i])+","+String(phaseArray[i]));
                        
                        }

                        else {goto thislocation;}
                        }
                  for(int i=0; i<sizeOfAvgArr; i++){
                          realAvg  = realAvg + realArray[i];
                          imagAvg  = imagAvg + imagArray[i];
                          magAvg   = magAvg  + magArray[i];
                          phaseAvg = phaseAvg + phaseArray[i];
                        }
  
                  Serial.println(String(magAvg)+","+String(phaseAvg));
//                        magAvg=0;
//                        phaseAvg=0;
                  }
        else {goto again_read_statReg_val;}
  
  }*/




void get_gain_val(){
 
    //enter standby mode by setting the reset
  Wire.beginTransmission(slave_addr);
  Wire.write(0x81);
  Wire.write(0x10);
  Wire.endTransmission(); 
  //enter standby mode manually
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(0xB1);
  Wire.endTransmission(); 
  //initialize with start frequency
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(0x11);
  Wire.endTransmission();
  //start frequency sweep
  Wire.beginTransmission(slave_addr);
  Wire.write(0x80);
  Wire.write(0x21);
  Wire.endTransmission();

  Wire.beginTransmission(slave_addr);
  Wire.write(ptr_cmd);
  Wire.write(status_reg);
  Wire.endTransmission();

    for(int i=0;i<sizeOfAvgArr;i++){
      delay(25);
      again_read_value:
    Wire.requestFrom(slave_addr,1,true);
    status_reg_val = Wire.read();
    Wire.endTransmission();

    if((status_reg_val&0b00000010)>>1)
    {
    Wire.beginTransmission(slave_addr);
    Wire.write(ptr_cmd);
    Wire.write(0x94);
    Wire.endTransmission();
    Wire.requestFrom(slave_addr,1,true);
    real1 = Wire.read();
    Wire.endTransmission();
    Wire.beginTransmission(slave_addr);
    Wire.write(ptr_cmd);
    Wire.write(0x95);
    Wire.endTransmission();
    Wire.requestFrom(slave_addr,1,true);
    real2 = Wire.read();
    Wire.endTransmission();
  
    Wire.beginTransmission(slave_addr);
    Wire.write(ptr_cmd);
    Wire.write(0x96);
    Wire.endTransmission();
    Wire.requestFrom(slave_addr,1,true);
    imag1 = Wire.read();
    Wire.endTransmission();
    Wire.beginTransmission(slave_addr);
    Wire.write(ptr_cmd);
    Wire.write(0x97);
    Wire.endTransmission();
    Wire.requestFrom(slave_addr,1,true);
    imag2 = Wire.read();
    Wire.endTransmission();
    
    realArray[i] = (real1<<8) | real2;
    imagArray[i] = (imag1<<8) | imag2;
  
    magArray[i] = sqrt(realArray[i]*realArray[i] + imagArray[i]*imagArray[i]);
        
    if(realArray[i]>0 && imagArray[i]>0)   {phaseArray[i] = atan(imagArray[i]/realArray[i])*(180/3.14);}
    if(realArray[i]<0 && imagArray[i]>0)   {phaseArray[i] = 180+(atan(imagArray[i]/realArray[i])*(180/3.14));}
    if(realArray[i]<0 && imagArray[i]<0)   {phaseArray[i] = 180+(atan(imagArray[i]/realArray[i])*(180/3.14));}
    if(realArray[i]>0 && imagArray[i]<0)   {phaseArray[i] = 360+(atan(imagArray[i]/realArray[i])*(180/3.14));}

//    Serial.println(String(magArray[i])+","+String(phaseArray[i]));
   
    }
    else
    {goto again_read_value;}
  
    
  
    //checking if sweep is complete
    Wire.beginTransmission(slave_addr);
    Wire.write(ptr_cmd);
    Wire.write(status_reg);
    Wire.endTransmission();
    Wire.requestFrom(slave_addr,1,true);
    status_reg_val = Wire.read();
    Wire.endTransmission();
    
     if (!((status_reg_val&0b00000100)>>2)){
    Wire.beginTransmission(slave_addr);
    Wire.write(0x80);
    Wire.write(0x41);
    Wire.endTransmission();
        
    }
    }

          for(int i=0; i<sizeOfAvgArr; i++){
                          magAvg   +=  magArray[i];
                          phaseAvg += phaseArray[i];
                        }
                  magAvg/=sizeOfAvgArr;
                  phaseAvg /=sizeOfAvgArr;

         Serial.println(String(magAvg)+","+String(phaseAvg));        

               magAvg=0;
  phaseAvg=0;
                
  
}
