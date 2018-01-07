#include <MySomfy.h>
MySomfy MySomfy(A4); //Instanciation de MySomfy avec le port TX utilisé
long rcTelecommande;
int telecommande;

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch(); //Instantation de RCSwitch pour la reception

#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  Serial.println("Commandes : ");
  Serial.println("lst : Liste des telecommandes ");
  Serial.println("lrc : Liste des rolling code ");
  Serial.println("teln : Selectionner une telecommande (tel1, tel2 ...) ");
  Serial.println("actm : 1 - Monter  ");
  Serial.println("actd : 2 - Descendre  ");
  Serial.println("acts : 3 - My (stop)  ");
  Serial.println("actp : 4 - Programmer  "); 
  Serial.println("actq : 5 - Deprogrammer (RC=0) ");
}

void loop() {
  if (mySwitch.available()) {
    Serial.println("---------------------------------------------------------------");
    Serial.print("Code reçu : ");
    Serial.println( mySwitch.getReceivedValue() );
    
    String entreeRF = String( mySwitch.getReceivedValue() ); // Code RF
    String act = entreeRF.substring(4,5); // Prend le 5eme caractére du code RF
    String telecommande = entreeRF.substring(3,4); // Prend le 4eme caractére du code RF

    cfgTel(telecommande.toInt());
    action(act.toInt());
    
    mySwitch.resetAvailable();
  }
} 

void serialEvent() {
  if(Serial.available()){
    String entreeSerie = Serial.readString();
    String commande = entreeSerie.substring(0,3);
    String valeur = entreeSerie.substring(3);
    
    if(commande == "tel"){
      cfgTel(valeur.toInt());
    }

    if(commande == "lrc"){
      Serial.println("---------------------------------------------------------------");
      for (int i = 1; i < 10; i++) {
        Serial.print("Tel " );
        Serial.print(i);
        Serial.print(" : ");
        Serial.println(EEPROMReadlong(i*10));
      }
    }
    
    if(commande == "act"){
      char retvaleur = valeur[0];
      rcTelecommande=EEPROMReadlong(telecommande*10);
      if(retvaleur == 'q'){
        EEPROMWritelong(telecommande*10, 0);
      }else{
        EEPROMWritelong(telecommande*10, rcTelecommande+1);
      }
      MySomfy.action(retvaleur, rcTelecommande);
      
    }
    if(commande == "lst"){
      menu(); 
    }
  }
}

void action(int valeur){
  rcTelecommande=EEPROMReadlong(telecommande*10);
  EEPROMWritelong(telecommande*10, rcTelecommande+1);
  switch (valeur) {
    case 1:
      MySomfy.action('m', rcTelecommande);
      break;
    case 2:
      MySomfy.action('d', rcTelecommande);
      break;
    case 3:
      MySomfy.action('s', rcTelecommande);
      break;
    case 4:
      MySomfy.action('p', rcTelecommande);
      break;
    case 5:
      EEPROMWritelong(telecommande*10, 0);
      MySomfy.action('q', rcTelecommande);
      break;
    default :
      MySomfy.action('s', rcTelecommande);
      break;
  }
}

void menu(){
  Serial.println("1 - BCDB01");
  Serial.println("2 - BCDB02");
  Serial.println("3 - BCDB03");
  Serial.println("4 - BCDB04");
  Serial.println("5 - BCDB05");
  Serial.println("6 - BCDB06");
  Serial.println("7 - BCDB07");
  Serial.println("8 - BCDB08");
  Serial.println("9 - BCDB09");
}

void cfgTel(int valeur){
  switch (valeur) {
    case 1:
      MySomfy.telecommande(0xBC, 0xDB, 0x01);
      telecommande = valeur;
      break;
    case 2:
      MySomfy.telecommande(0xBC, 0xDB, 0x02);
      telecommande = valeur;
      break;
    case 3:
      MySomfy.telecommande(0xBC, 0xDB, 0x03);
      telecommande = valeur;
      break;
    case 4:
      MySomfy.telecommande(0xBC, 0xDB, 0x04);
      telecommande = valeur;
      break;
    case 5:
      MySomfy.telecommande(0xBC, 0xDB, 0x05);
      telecommande = valeur;
      break;
    case 6:
      MySomfy.telecommande(0xBC, 0xDB, 0x06);
      telecommande = valeur;
      break;
    case 7:
      MySomfy.telecommande(0xBC, 0xDB, 0x07);
      telecommande = valeur;
      break;
    case 8:
      MySomfy.telecommande(0xBC, 0xDB, 0x08);
      telecommande = valeur;
      break;
    case 9:
      MySomfy.telecommande(0xBC, 0xDB, 0x09);
      telecommande = valeur;
      break;
    default :
      Serial.print("Telecommande inexistante reportez vous aux menu ci-dessous : ");
      Serial.println( valeur );
      menu();
    break;
  }
}

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWritelong(int address, long value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      }

//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to address + 3.
long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
      }
