/*****************************************

  medidor de la conductividad del suelo con sonda capacitiva
  v_1.0-20130304
  
  este es un algoritmo para medir condensadores de pequeño valor
  se basa en cargar Cx y transferir a C1 hasta llegar a Vh
  y luego medir el tiempo de descarga de C1+Cx en R1
  si C1>>Cx podemos calcular aproximadamente Cx y C1 :
  
  constantes que dependen del sistema:
  unidad de tiempo de descarga en R1 definido en inicializar_TCNT1()
  dT_us=0.5 us 
  B1=ln(Vc/(Vc-Vh))
  B2=dT_us/(R1*ln(Vh/Vl))

  a partir de las medidas:
  C1=B2*D_media
  Cx=C1*(B1/C_T_media)
  
  medidas:
  la sonda son 2 trozos de cable de 7cm y 2mm de sección
  con su aislante y sellados por el extremo libre
  (yo lo he hecho con pegamento imedio!)
  
  para medir pequeños condensadores es muy eficiente, y con la
  sonda en el aire sólo acercarla a una parte metálica o
  acercarle la mano ya se nota la diferencia de lectura (se
  puede usar como detector de proximidad)
  
  cuando se mete en el agua el cálculo ya no vale, ya que no se
  tiene en cuenta que el nuevo aislante no tiene una resistencia
  "infinita" como podríamos suponer del aire, sino que tiene una
  resistencia en paralelo y además influye el aislante del cable,
  en mi caso PVC de K=3
  cuando el aislante era aire, la inflencia del PVC es muy
  pequeña, pero con un aislante con K>>3 ya tiene efecto
  
  si aumenta la capacidad, el número de carga-transfer necesario
  disminuye (mas carga Q en cada ciclo y se llega antes
  al límite Vh), pero la resistividad del aislante disminuye
  y hay una parte de la carga que se va y a partir de un cierto
  valor vuelve a necesitar más ciclos para llegar al Vh
  en realidad lo que medimos es la transferencia de una carga Q
  mediante la impedancia de carga Cx||Rx
  
  tengo que analizar mejor el sistema para ver si puedo sacar
  unas ecuaciones guapas
  las que hay puestas son las que se usarían para medir condensadores
  cerámicos normales en la zona de pF/nF.
  
  algunos datos que he medido:
   sin sonda mide 49.57pF (capacidades parásitas del montaje)

   con sonda al aire C_T=38842 -> 76pF

   sonda en agua del grifo C_T=34046  -> 86pF
 
   sonda en agua con sal C_T=35150 -> 84pF
   hay que compensar las fugas por lo que hay que hacer más ciclos
  
******************************************/

// terminales del ARDUINO-UNO que utilizo en este programa
// según el esquema medidorConductividadCapacitivo.sch

// anular pull-ups
#define  PUD            4
#define  PULL_UPS_OFF   bitSet(MCUCR,PUD)
#define  PULL_UPS_ON    bitClear(MCUCR,PUD)

// el PIN-8 es el B0 del port B
#define  PIN_Vc         0
#define  Vc_OUT         bitSet(DDRB,PIN_Vc)
#define  Vc_FLOAT       bitClear(DDRB,PIN_Vc)
#define  Vc_HIGH        bitSet(PORTB,PIN_Vc)
#define  Vc_LOW         bitClear(PORTB,PIN_Vc)

// poner R1 a GND
#define  PIN_G_R        5
#define  G_R_OUT        bitSet(DDRD,PIN_G_R)
#define  G_R_FLOAT      bitClear(DDRD,PIN_G_R)
#define  G_R_GND        bitClear(PORTD,PIN_G_R)

// poner C1 a GND
#define  PIN_G_C        4
#define  G_C_OUT        bitSet(DDRD,PIN_G_C)
#define  G_C_FLOAT      bitClear(DDRD,PIN_G_C)
#define  G_C_GND        bitClear(PORTD,PIN_G_C)

// pins del comparador
// AIN0 *
// AIN1 -
#define  PIN_AIN1      7
#define  PIN_AIN0      6

// activar el comparador
// AIN0 es entrada positiva
#define  ACTIVAR_COMPARADOR ACSR=0

// AIN1 es la entrada negativa
#define  ACME          6
#define  SET_AIN1      bitClear(ADCSRB,ACME)

#define  ACO           5
#define  COMPARADOR_ON bitRead(ACSR,ACO)

// referencia comparador
int  E_referencia      = A0;  // solo se usa al inicio, luego se anula
int  Ref_H;
int  Ref_L;

#define  PIN_V1        3
#define  V1_OUT        bitSet(DDRD,PIN_V1)
#define  V1_GND        bitClear(PORTD,PIN_V1)
#define  V1_Vc         bitSet(PORTD,PIN_V1)
 
#define  PIN_V0        2
#define  V0_OUT        bitSet(DDRD,PIN_V0)
#define  V0_GND        bitClear(PORTD,PIN_V0)
#define  V0_Vc         bitSet(PORTD,PIN_V0)

int  S_led_1            = 13;    // PB5 = led piloto

// almacen de medidas
#define  MAX_LECTURAS  10

unsigned long alm_C_T[MAX_LECTURAS];
unsigned long alm_D[MAX_LECTURAS];
unsigned long C_T_media;
unsigned long D_media;

// para calcular Cx

float dT_us=0.5;
float R1 = 2200.0;
float B_1;
float B_2;
float C1;

void setup()
{
  // port serie, del que solo se usa la salida
  Serial.begin(9600);
  // led auxiliar
  pinMode(S_led_1, OUTPUT);
  digitalWrite(S_led_1,LOW);
}

void loop() {
   int display=0;
   
   inicializar_TCNT1();
   calibrarComparador();
   ACTIVAR_COMPARADOR;
   SET_AIN1;
   while(true){   
     digitalWrite(S_led_1,HIGH);
     medirCapacidad();
     digitalWrite(S_led_1,LOW);
     display++;
     if(display>10){
       digitalWrite(S_led_1,LOW);
       Serial.print("R_h="),
       Serial.println(Ref_H);
       Serial.print("R_l="),
       Serial.println(Ref_L);
       Serial.print("C_T="),
       Serial.println(C_T_media);
       Serial.print("D  ="),
       Serial.println(D_media);
       Serial.print("C1 ="),
       Serial.print(calcular_C1());
       Serial.println(" uF");
       Serial.print("Cx ="),
       Serial.print(calcular_Cx());
       Serial.println(" pF\n"),
       display=0;
     }
     espera_0_5us(10000);
   }
}

void inicializar_TCNT1(){
  
  TCCR1A=0;
  TCCR1B=2;    // cada unidad=16MHz/8=2MHz-> 0.5us
  // 1=clk 2=clk/8 3=clk/64 4=clk/256 5=clk/1024
  TCCR1C=0;
  TIFR1=0;
}

void espera_0_5us(unsigned int t){
   
  TCNT1=0;
  while(TCNT1 < t);
}

void calibrarComparador(){

  resetMedida();
  V1_Vc;
  V0_GND;
  espera_0_5us(100);  
  Ref_H=analogRead(E_referencia);
  V1_GND;
  V0_Vc;  
  espera_0_5us(100);  
  Ref_L=analogRead(E_referencia);
  // calcular constantes de la medida
  B_1=log(1023.0/(1023.0-(float)Ref_H))*1e6;  // medir en pF
  B_2=dT_us/(R1*log((float)Ref_H/(float)Ref_L));
  resetMedida();
}

void guardar_medidas(unsigned long n_C_T,unsigned long n_D){
  int i;
  
  C_T_media=0L;
  D_media=0L;
  for(i=0;i<MAX_LECTURAS-1;i++){
    alm_C_T[i]=alm_C_T[i+1];
    C_T_media += alm_C_T[i];
    alm_D[i]=alm_D[i+1];
    D_media += alm_D[i];
  }
  alm_C_T[i]=n_C_T;
  C_T_media += n_C_T;
  C_T_media /= MAX_LECTURAS;
  alm_D[i]=n_D;
  D_media += n_D;
  D_media /= MAX_LECTURAS;
}

void medirCapacidad(){
  unsigned long n_C_T;
  unsigned long n_D;
  
  resetMedida();
  espera_0_5us(4000);
  n_C_T=carga_transfer();
  n_D=descarga();
  resetMedida();
  guardar_medidas(n_C_T,n_D);
}

void resetMedida(){
  
  PULL_UPS_OFF;
  Vc_LOW;
  Vc_OUT;
  G_R_GND;
  G_R_OUT;
  G_C_GND;
  G_C_OUT;
  V1_GND;
  V1_OUT;
  V0_GND;
  V0_OUT;
}

unsigned long carga_transfer(){
  unsigned long n;
  
  n=0L;
  Vc_HIGH;
  G_R_FLOAT;
  G_C_FLOAT;
  V1_Vc;
  V0_GND;
  while(true){
    Vc_OUT;                // carga Cx a Vc
    espera_0_5us(4);
    Vc_FLOAT;
    G_C_OUT;               // transfer de Cx a Ci
    espera_0_5us(4);
    n++;
    G_C_FLOAT;
    if(!COMPARADOR_ON)  break;  // hasta que llega a Vh
  }
  return n;
}

unsigned int descarga(){
  
  Vc_FLOAT;
  V1_GND;
  V0_Vc;
  G_C_OUT;
  G_R_OUT;
  TCNT1=0;
  while(true){
    if(COMPARADOR_ON)  break;  // descarga hasta que llega a Vl
  }
  return TCNT1;    // pulsos traanscurridos en la descarga
}

// calculo de las capacidades a partir de las lecturas
float calcular_C1(){
  
  C1=B_2*(float)D_media;
  return C1;
}

float calcular_Cx(){
  
  return (C1*B_1/(float)C_T_media);
}

