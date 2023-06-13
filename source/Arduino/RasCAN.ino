#include <Arduino.h>
#include <mcp_can.h>
//#include <mcp_can_dfs.h>


// -----------------------------------------------------
// Definitions

#define CANint 2
//#define LED2 8
//#define LED3 7

#define PID_PIDS_SUPPORTED_01_20          0x00  //  
#define PID_MONITOR                       0x01  //  
#define PID_FUEL_STATUS                   0x03  //  * 07 E8 04 41 03 02 00 00 00 00 0001D846
#define PID_CALC_ENGINE_LOAD              0x04  //  * 07 E9 03 41 04 80 00 00 00 00 0001DC1A
#define PID_COOLANT_TEMP                  0x05  //  * 07 E8 03 41 05 6F 00 00 00 00 0003E108
#define PID_SHORT_TERM_FUEL_TRIM_1        0x06  //  * 07 E8 03 41 06 7E 00 00 00 00 0002EF49
#define PID_LONG_TERM_FUEL_TRIM_1         0x07  //  * 07 E8 03 41 07 89 00 00 00 00 0003FE53
#define PID_SHORT_TERM_FUEL_TRIM_2        0x08  //  
#define PID_LONG_TERM_FUEL_TRIM_2         0x09  //  
#define PID_FUEL_PRESSURE                 0x0A  //  
#define PID_INTAKE_MANIFOLD_ABS_PRESSURE  0x0B  //  
#define PID_ENGIN_PRM                     0x0C  //  * 07 E8 04 41 0C 14 6B 00 00 00 0007338C
#define PID_VEHICLE_SPEED                 0x0D  //  * 07 E8 03 41 0D 36 00 00 00 00 000415C3
#define PID_INTAKE_AIR_TEMP               0x0F  //  * 07 E8 03 41 0F 4F 00 00 00 00 000419BF

#define PID_MASS_AIR_FLOW_RATE            0x10  //  * 07 E8 04 41 10 01 85 00 00 00 00030FBF
#define PID_THROTTLE_POSITION             0x11  //  * 07 E8 03 41 11 2A 00 00 00 00 000529D8
//#define PID_OXYGEN_SENSOR                 0x14 //  
#define PID_OBD_STANDARDS                 0x1C  //  * 07 E9 03 41 1C 09 00 00 00 00 00020C2C
                                                //  * 07 E8 03 41 1C 03 00 00 00 00 00020C30
#define PID_OXYGEN_SENSOR_PRESENT         0x1D  //  
#define PID_RUN_TIME_SINCE_START          0x1F  //  * 07 E8 04 41 1F 00 AA 00 00 00 0002140B

#define PID_PIDS_SUPPORTED_21_40          0x20  //  
#define PID_DISTANCE_TRAVELED_MIL_ON      0x21  //  * 07 E8 04 41 21 00 00 00 00 00 0003272F
#define PID_FUEL_RAIL_PRESSURE_MANIFOLD   0x22  //  
#define PID_FUEL_RAIL_PRESSURE_GAUGE      0x23  //  * 07 E8 04 41 23 00 E1 00 00 00 00032EEB
//#define PID_OXYGEN_SENSOR                 0x24  //  
#define PID_COMMANDED_ERG                 0x2C  //  
#define PID_FUEL_TANK_LEVEL               0x2F  //  * 07 E8 03 41 2F 75 00 00 00 00 00054D00

#define PID_DISTANCE_SINCE_CODES_CLEARED  0x31  //  * 07 E8 04 41 31 08 9E 00 00 00 00033AA3
#define PID_EVAP_SYSTEM_VAPOR_PRESSURE    0x32  //  * 07 E8 04 41 32 FF 77 00 00 00 000662D9
#define PID_BARAMETRIC_PRESSURE           0x33  //  * 07 E9 03 41 33 64 00 00 00 00 0002371D
//#define PID_OXYGEN_SENSOR                 0x34  //  
#define PID_CATALYST_TEMP_BANK_1_SENSOR_1 0x3C  //  * 07 E8 04 41 3C 19 A3 00 00 00 00066801
#define PID_CATALYST_TEMP_BANK_2_SENSOR_1 0x3D  //  
#define PID_CATALYST_TEMP_BANK_1_SENSOR_2 0x3E  //  
#define PID_CATALYST_TEMP_BANK_2_SENSOR_2 0x3F  //  

#define PID_PIDS_SUPPORTED_41_60          0x40  //  
#define PID_MONITOR_STATUS_DRIVE_CYCLE    0x41  //  
#define PID_CONTROL_VOLTAGE               0x42  //  * 07 E8 04 41 42 36 17 00 00 00 00070902
#define PID_ABSOLUTE_LOAD                 0x43  //  * 07 E8 04 41 43 00 1C 00 00 00 00046644
#define PID_COMMANDED_AIR_FUEL_RATIO      0x44  //  * 07 E8 04 41 44 70 A3 00 00 00 00046A22
#define PID_RELATIVE_TROTTLE_POS          0x45  //  
#define PID_AMBIENT_AIR_TEMPERATURE       0x46  //  * 07 E8 03 41 46 4C 00 00 00 00 00057D0B
#define PID_ABSOLOUTE_TROTTLE_POSITION_B  0x47  //  * 07 E8 03 41 47 2B 00 00 00 00 00068C53
#define PID_ABSOLOUTE_TROTTLE_POSITION_C  0x48  //  
#define PID_ACCELERATORE_PEDAL_POSITION_D 0x49  //  * 07 E9 03 41 49 27 00 00 00 00 00026486
#define PID_ACCELERATORE_PEDAL_POSITION_E 0x4A  //  * 07 E8 03 41 4A 14 00 00 00 00 0006980A
#define PID_ACCELERATORE_PEDAL_POSITION_F 0x4B  //  
#define PID_COMMANDED_THROTTLE_ACTUATOR_E 0x4C  //  * 07 E8 03 41 4C 14 00 00 00 00 00069FE5
#define PID_TIME_RUN_WITH_MIL_ON          0x4D  //  
#define PID_TIME_SINCE_TROUBLE_CODES_CLEARED                0x4E  //  
#define PID_MAX_VAL_FUEL_AIR_RATIO_OV_OCUR_MAN_ABS_PRESS    0x4F  //  

#define PID_MAX_VAL_AIR_FLOW_RATE_SENSOR  0x50  //  
#define PID_ABS_EVAP_PRESSURE             0x53  //  
#define PID_EVAP_PRESSURE                 0x54  //  
#define PID_FUEL_RAIL_ABS_PRESSURE        0x59  //  
#define PID_REL_ACCELERATORE_PEDAL_POS    0X5A  //  
#define PID_ENGINE_OIL_TEMP               0x5C  //  
#define PID_ENGINE_FUEL_RATE              0x5E  //  

#define PID_PIDS_SUPPORTED_61_80          0x60  //  
#define PID_DRIVERS_DEMAND_ENGINE_TORQUE  0x61  //  
#define PID_ACTURAL_DEMAND_ENGINE_TORQUE  0x62  //  
#define PID_REFERENCE_ENGINE_TORQUE       0x63  //  
#define PID_ENGINE_PERCENT_TORQUE_DATA    0x64  //  
#define PID_MASS_AIR_FLOW_SENSOR          0x66  //  
#define PID_ENGINE_COOLANT_TEMPERATURE    0x67  //  
#define PID_INTAKE_AIR_TEMPERATURE_SENSOR 0x68  //  
#define PID_EXHAST_GAS_RECIRC_TEMP         0x6B  // 

#define PID_PIDS_SUPPORTED_81_A0          0x80  //  
#define PID_MANIFOLD_SURFACE_TEMP         0x84  //  

#define PID_ENGINE_FUEL_RATE              0x9D  //  
#define PID_ENGINE_EXHAST_FLOW_RATE       0x9E  //  
#define PID_FUEL_SYSTEM_PERCENTAGE_USED   0x9F  //  

#define PID_PIDS_SUPPORTED_A1_C0          0xA0  //  
#define PID_TRANS_ACUTAL_GEAR             0xA4  //  
#define PID_ODOMETER                      0xA6  //  
#define PID_ABS_DISABLE_SWITCH_STATE      0xA9  //  

// ---

#define CAN_ID_PID                        0x7DF //  *


// -----------------------------------------------------
// Control Class
class CONTROL
{
  // Read Byte Characteristics
  // p = Stop Read
  // s = Continue Read
  // r = Send Can Data
  // t = Send Test Data

  public:
  int version = 0;
  
  bool test = false;
  bool start = true;
  bool filter = true;

  bool restart = false;

  bool send_command = false;
  unsigned char command;

  read(String read_string)
  {
    read_string.trim();

    if (read_string == "p")
    {
      // Command to pause and unpause input
      if (start == false)
      {
        start = true;
      }
      else
      {
        start = false;
      }
    }
    else if (read_string == "t")
    {
      // Command to send test or stop sending test data
      if (test == true)
      {
        test = false;
      }
      else
      {
        test = true;
      }
    }
    else if (read_string == "f")
    {
      // Command to filter pids on or off
      if (filter == true)
      {
        filter = false;
      }
      else
      {
        filter = true;
      }
    }
    else if (read_string == "q")
    {
      // Command to restart
      restart = true;
    }
    else if (read_string == "v3")
    {
      version = 3;
      restart = true;
    }
    else if (read_string == "v4")
    {
      version = 4;
      restart = true;
    }

    // version 3 and version == 4 commands
    if (version == 3 || version == 4)
    {
      // 00 - 0F
      if (read_string == "00")
      {
        command = PID_PIDS_SUPPORTED_01_20;
        send_command = true;
      }
      else if (read_string == "01")
      {
        command = PID_MONITOR;
        send_command = true;
      }
      else if (read_string == "03")
      {
        command = PID_FUEL_STATUS;
        send_command = true;
      }
      else if (read_string == "04")
      {
        command = PID_CALC_ENGINE_LOAD;
        send_command = true;
      }
      else if (read_string == "05" || read_string == "temp")
      {
        command = PID_COOLANT_TEMP;
        send_command = true;
      }
      else if (read_string == "06")
      {
        command = PID_SHORT_TERM_FUEL_TRIM_1;
        send_command = true;
      }
      else if (read_string == "07")
      {
        command = PID_LONG_TERM_FUEL_TRIM_1;
        send_command = true;
      }
      else if (read_string == "08")
      {
        command = PID_SHORT_TERM_FUEL_TRIM_2;
        send_command = true;
      }
      else if (read_string == "09")
      {
        command = PID_LONG_TERM_FUEL_TRIM_2;
        send_command = true;
      }
      else if (read_string == "0A")
      {
        command = PID_FUEL_PRESSURE;
        send_command = true;
      }
      else if (read_string == "0B")
      {
        command = PID_INTAKE_MANIFOLD_ABS_PRESSURE;
        send_command = true;
      }
      else if (read_string == "0C" || read_string == "temp")
      {
        command = PID_ENGIN_PRM;
        send_command = true;
      }
      else if (read_string == "0D" || read_string == "speed")
      {
        command = PID_VEHICLE_SPEED;
        send_command = true;
      }
      else if (read_string == "0F")
      {
        command = PID_INTAKE_AIR_TEMP;
        send_command = true;
      }

      // 10 - 1F
      else if (read_string == "10")
      {
        command = PID_MASS_AIR_FLOW_RATE;
        send_command = true;
      }
      else if (read_string == "11")
      {
        command = PID_THROTTLE_POSITION;
        send_command = true;
      }
      else if (read_string == "1C")
      {
        command = PID_OBD_STANDARDS;
        send_command = true;
      }
      else if (read_string == "1D")
      {
        command = PID_OXYGEN_SENSOR_PRESENT;
        send_command = true;
      }
      else if (read_string == "1F")
      {
        command = PID_RUN_TIME_SINCE_START;
        send_command = true;
      }

      // 20 - 2F
      else if (read_string == "20")
      {
        command = PID_PIDS_SUPPORTED_21_40;
        send_command = true;
      }
      else if (read_string == "21")
      {
        command = PID_DISTANCE_TRAVELED_MIL_ON;
        send_command = true;
      }
      else if (read_string == "22")
      {
        command = PID_FUEL_RAIL_PRESSURE_MANIFOLD;
        send_command = true;
      }
      else if (read_string == "23")
      {
        command = PID_FUEL_RAIL_PRESSURE_GAUGE;
        send_command = true;
      }
      else if (read_string == "2C")
      {
        command = PID_COMMANDED_ERG;
        send_command = true;
      }
      else if (read_string == "2F")
      {
        command = PID_FUEL_TANK_LEVEL;
        send_command = true;
      }

      // 30 - 3F
      else if (read_string == "31")
      {
        command = PID_DISTANCE_SINCE_CODES_CLEARED;
        send_command = true;
      }
      else if (read_string == "32")
      {
        command = PID_EVAP_SYSTEM_VAPOR_PRESSURE;
        send_command = true;
      }
      else if (read_string == "33")
      {
        command = PID_BARAMETRIC_PRESSURE;
        send_command = true;
      }
      else if (read_string == "3C")
      {
        command = PID_CATALYST_TEMP_BANK_1_SENSOR_1;
        send_command = true;
      }
      else if (read_string == "3D")
      {
        command = PID_CATALYST_TEMP_BANK_2_SENSOR_1;
        send_command = true;
      }
      else if (read_string == "3E")
      {
        command = PID_CATALYST_TEMP_BANK_1_SENSOR_2;
        send_command = true;
      }
      else if (read_string == "3F")
      {
        command = PID_CATALYST_TEMP_BANK_2_SENSOR_2;
        send_command = true;
      }

      // 40 - 4F
      else if (read_string == "40")
      {
        command = PID_PIDS_SUPPORTED_41_60;
        send_command = true;
      }
      else if (read_string == "41")
      {
        command = PID_MONITOR_STATUS_DRIVE_CYCLE;
        send_command = true;
      }
      else if (read_string == "42")
      {
        command = PID_CONTROL_VOLTAGE;
        send_command = true;
      }
      else if (read_string == "43")
      {
        command = PID_ABSOLUTE_LOAD;
        send_command = true;
      }
      else if (read_string == "44")
      {
        command = PID_COMMANDED_AIR_FUEL_RATIO;
        send_command = true;
      }
      else if (read_string == "45")
      {
        command = PID_RELATIVE_TROTTLE_POS;
        send_command = true;
      }
      else if (read_string == "46")
      {
        command = PID_AMBIENT_AIR_TEMPERATURE;
        send_command = true;
      }
      else if (read_string == "47")
      {
        command = PID_ABSOLOUTE_TROTTLE_POSITION_B;
        send_command = true;
      }
      else if (read_string == "48")
      {
        command = PID_ABSOLOUTE_TROTTLE_POSITION_C;
        send_command = true;
      }
      else if (read_string == "49")
      {
        command = PID_ACCELERATORE_PEDAL_POSITION_D;
        send_command = true;
      }
      else if (read_string == "4A")
      {
        command = PID_ACCELERATORE_PEDAL_POSITION_E;
        send_command = true;
      }
      else if (read_string == "4B")
      {
        command = PID_ACCELERATORE_PEDAL_POSITION_F;
        send_command = true;
      }
      else if (read_string == "4C")
      {
        command = PID_COMMANDED_THROTTLE_ACTUATOR_E;
        send_command = true;
      }
      else if (read_string == "4D")
      {
        command = PID_TIME_RUN_WITH_MIL_ON;
        send_command = true;
      }
      else if (read_string == "4E")
      {
        command = PID_TIME_SINCE_TROUBLE_CODES_CLEARED;
        send_command = true;
      }
      else if (read_string == "4F")
      {
        command = PID_MAX_VAL_FUEL_AIR_RATIO_OV_OCUR_MAN_ABS_PRESS;
        send_command = true;
      }

      // 50 - 5F
      else if (read_string == "50")
      {
        command = PID_MAX_VAL_AIR_FLOW_RATE_SENSOR;
        send_command = true;
      }
      else if (read_string == "53")
      {
        command = PID_ABS_EVAP_PRESSURE;
        send_command = true;
      }
      else if (read_string == "54")
      {
        command = PID_EVAP_PRESSURE;
        send_command = true;
      }
      else if (read_string == "59")
      {
        command = PID_FUEL_RAIL_ABS_PRESSURE;
        send_command = true;
      }
      else if (read_string == "5A")
      {
        command = PID_REL_ACCELERATORE_PEDAL_POS;
        send_command = true;
      }
      else if (read_string == "5C")
      {
        command = PID_ENGINE_OIL_TEMP;
        send_command = true;
      }
      else if (read_string == "5E")
      {
        command = PID_ENGINE_FUEL_RATE;
        send_command = true;
      }

      // 60 - 6F
      else if (read_string == "60")
      {
        command = PID_PIDS_SUPPORTED_61_80;
        send_command = true;
      }
      else if (read_string == "61")
      {
        command = PID_DRIVERS_DEMAND_ENGINE_TORQUE;
        send_command = true;
      }
      else if (read_string == "62")
      {
        command = PID_ACTURAL_DEMAND_ENGINE_TORQUE;
        send_command = true;
      }
      else if (read_string == "63")
      {
        command = PID_REFERENCE_ENGINE_TORQUE;
        send_command = true;
      }
      else if (read_string == "64")
      {
        command = PID_ENGINE_PERCENT_TORQUE_DATA;
        send_command = true;
      }
      else if (read_string == "66")
      {
        command = PID_MASS_AIR_FLOW_SENSOR;
        send_command = true;
      }
      else if (read_string == "67")
      {
        command = PID_ENGINE_COOLANT_TEMPERATURE;
        send_command = true;
      }
      else if (read_string == "68")
      {
        command = PID_INTAKE_AIR_TEMPERATURE_SENSOR;
        send_command = true;
      }
      else if (read_string == "6B")
      {
        command = PID_EXHAST_GAS_RECIRC_TEMP;
        send_command = true;
      }

      // 70 - 7F

      // 80 - 8F
      else if (read_string == "80")
      {
        command = PID_PIDS_SUPPORTED_81_A0;
        send_command = true;
      }
      else if (read_string == "84")
      {
        command = PID_MANIFOLD_SURFACE_TEMP;
        send_command = true;
      }
      

      // 90 - 9F
      else if (read_string == "9D")
      {
        command = PID_ENGINE_FUEL_RATE;
        send_command = true;
      }
      else if (read_string == "9E")
      {
        command = PID_ENGINE_EXHAST_FLOW_RATE;
        send_command = true;
      }
      else if (read_string == "9F")
      {
        command = PID_FUEL_SYSTEM_PERCENTAGE_USED;
        send_command = true;
      }

      // A0 - AF
      else if (read_string == "A0")
      {
        command = PID_PIDS_SUPPORTED_A1_C0;
        send_command = true;
      }
      else if (read_string == "A4")
      {
        command = PID_TRANS_ACUTAL_GEAR;
        send_command = true;
      }
      else if (read_string == "A6")
      {
        command = PID_ODOMETER;
        send_command = true;
      }
      else if (read_string == "A9")
      {
        command = PID_ABS_DISABLE_SWITCH_STATE;
        send_command = true;
      }

      // B0 - BF

    }
  }

  reset()
  {
    test = false;
    start = true;
    filter = true;
    restart = false;
  }
};


// -----------------------------------------------------
// Global Variables

unsigned char len = 0;
unsigned char buf[8];
unsigned long ID = 0;
unsigned long CAN_ID = 0;
unsigned long MESSAGE_TIME = 0;

MCP_CAN CAN0(17); // Set CS to pin 17

CONTROL ctrl;

// -----------------------------------------------------
// Setup Variables

unsigned long time;
void setup() 
{
  // Set Default Version
  ctrl.version = 4;

  // Prep Serial
  Serial.begin(115200);
  
  while (!Serial) 
  {
    Serial.print("I will wait for serial connect");
    delay(1000);
  };
  
  // Prep Pins
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH); // led

  //pinMode(LED2, OUTPUT);
  //pinMode(LED3, OUTPUT);
  pinMode(CANint, INPUT);
  //digitalWrite(LED2, LOW);
    
  // Prep CAN Bus
  Serial.println("CAN init:");

  if (CAN0.begin(CAN_500KBPS) == CAN_OK) 
  {
    Serial.println("Can Init Success");
  } 
  else 
  {
    Serial.println("Can Init Failed");
    while (1) 
    {
      Serial.print("I will wait here forever...");
      delay(1000);
    }
  }

  Serial.println("Good to go!");

  digitalWrite(23, LOW); // led
}


// -----------------------------------------------------
// Blink and time
void blink(bool Blink)
{
  // -----------------------------------------------------
  // If system is paused then blink the lights
  if(Blink)
  {
    digitalWrite(23, HIGH);  // LED OFF
    delay(100); 
    digitalWrite(23, LOW); // LED ON
    delay(900); 
  }
}

// -----------------------------------------------------
// Read from host
String read_com()
{
  String read_string = Serial.readStringUntil('\n');
  read_string.trim();
  return read_string;
}

// -----------------------------------------------------
// Convert char to string hex

void print_hex(unsigned char value)
{
  if(value<16)
  {
    Serial.print('0');
    Serial.print(value,HEX);
  }
  else
  {
    Serial.print(value,HEX);    
  }
  Serial.print(" ");
}

void print_hex_UL(unsigned long value)
{
  if(value == 0)
  {
    Serial.print("00000000");
  }
  else if(value < 16)
  {
    Serial.print("0000000");
    Serial.print(value, HEX);
  }
  else if (value < 256)
  {
    Serial.print("000000");
    Serial.print(value, HEX);    
  }
  else if (value < 4096)
  {
    Serial.print("00000");
    Serial.print(value, HEX);    
  }
  else if (value < 65536)
  {
    Serial.print("0000");
    Serial.print(value, HEX);    
  }
  else if (value < 1048576)
  {
    Serial.print("000");
    Serial.print(value, HEX);    
  }
  else if (value < 16777216)
  {
    Serial.print("00");
    Serial.print(value, HEX);    
  }
  else if (value < 268435456)
  {
    Serial.print("0");
    Serial.print(value, HEX);    
  }
  else
  {
    Serial.print(value, HEX);    
  }
  
  Serial.print(" ");
}

void sendPid(unsigned char __pid) {
    unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0};
    CAN0.sendMsgBuf(CAN_ID_PID, 0, 8, tmp);
}

void serial_send(unsigned long ID, byte len, byte buf[])
{
  if(ID >= 0)
  {
    unsigned char IDl = ID % 256;
    unsigned char IDu = (ID - IDl) / 256;

    print_hex(IDu);
    print_hex(IDl);
  }
  else
  {
    Serial.print("-- -- ");
  }
  
  for(int i = 0; i<8; i++) 
  { 
    // Output 8 Bytes of data regradless of size.
    if(i<len)
    {
      print_hex(buf[i]);
    }
    else if(i>len)
    {
      print_hex(0);        
    }      
  }

  Serial.println();
}


void serial_send_2(unsigned long Message_ID, byte Message_len, byte Message_buf[], unsigned long Message_timestamp)
{
  unsigned char IDl = Message_ID % 256;
  unsigned char IDu = (Message_ID - IDl) / 256;

  print_hex(IDu);
  print_hex(IDl);

  print_hex(Message_buf[0]);
  print_hex(Message_buf[1]);
  print_hex(Message_buf[2]);
  print_hex(Message_buf[3]);
  print_hex(Message_buf[4]);
  print_hex(Message_buf[5]);
  print_hex(Message_buf[6]);
  print_hex(Message_buf[7]);

  print_hex_UL(Message_timestamp);

  Serial.println();
}

bool filter(unsigned long ID)
{
  bool ret_pass = false;

  switch (ID)
  {
    case (0x10):
      ret_pass = true;
      break;

    //case (0x70):
    //  ret_pass = true;
    //  break;

    case (0x80):
      ret_pass = true;
      break;

    case (0x90):
      ret_pass = true;
      break;

    case (0xC0):
      ret_pass = true;
      break;

    case (0xC8):
      ret_pass = true;
      break;

    case (0xD0):
      ret_pass = true;
      break;

    case (0xF0):
      ret_pass = true;
      break;

    case (0x130):
      ret_pass = true;
      break;

    case (0x190):
      ret_pass = true;
      break;

    case (0x200):
      ret_pass = true;
      break;

    case (0x360):
      ret_pass = true;
      break;

    case (0x380):
      ret_pass = true;
      break;

    // Messages on PIDs with:
    case (0x7E8):
      ret_pass = true;
      break;

    case (0x7E9):
      ret_pass = true;
      break;

    case (0x7EA):
      ret_pass = true;
      break;

    case (0x7EB):
      ret_pass = true;
      break;
  }

  return ret_pass;
}

// -----------------------------------------------------
// Version 3

void version_3()
{
  unsigned long recv_canid = 0;

  unsigned long fake_two_byte_counter = 0;
  char fake_one_byte_counter = 0;

  ctrl.reset();
  
  Serial.println("Version 3");

  while (ctrl.restart == false)
  {
    if (ctrl.start == true && CAN_MSGAVAIL == CAN0.checkReceive() ||
          ctrl.start == true && ctrl.test == true)
    {
      MESSAGE_TIME = millis();

      // Check to see whether data is read
      if (ctrl.test == false)
      {
        // Get Can Data
        CAN0.readMsgBufID(&ID, &len, buf);    // Read data  
      }
      else
      {
        // Get Test Data
        ID = fake_two_byte_counter;
        len = 8;
        buf[0] = fake_one_byte_counter;
        buf[1] = fake_one_byte_counter;
        buf[2] = fake_one_byte_counter;
        buf[3] = fake_one_byte_counter;
        buf[4] = fake_one_byte_counter;
        buf[5] = fake_one_byte_counter;
        buf[6] = fake_one_byte_counter;
        buf[7] = fake_one_byte_counter;
        
        fake_two_byte_counter++;
        fake_one_byte_counter++;

        if (fake_two_byte_counter > (256*256)-1)
        {
          fake_two_byte_counter = 0;                    
        }
        
        if (fake_one_byte_counter > 255)
        {
          fake_one_byte_counter = 0;                    
        }

        delay (5);
      }

      //if (filter(ID) == true)
      if (true == true)
      {
        digitalWrite(23, HIGH); // LED ON
        serial_send_2(ID, len, buf, MESSAGE_TIME);
        digitalWrite(23, LOW);  // LED OFF
      }
    }
    
    // Read from host
    if(Serial.available() > 0)
    {
      //Serial.println("-");
      ctrl.read(read_com());
    }

    // send command to CAN
    if (ctrl.send_command == true)
    {
      digitalWrite(23, HIGH); // LED ON

      ctrl.send_command = false;

      if (ctrl.command == PID_VEHICLE_SPEED)
      {
        sendPid(PID_VEHICLE_SPEED);
      }
      else if (ctrl.command == PID_ENGIN_PRM)
      {
        sendPid(PID_ENGIN_PRM);
      }
      else if (ctrl.command == PID_COOLANT_TEMP)
      {
        sendPid(PID_COOLANT_TEMP);
      }

      //sendPid(ctrl.command);
      
      digitalWrite(23, LOW);  // LED OFF
    }

    // Blink and Time
    blink(ctrl.start == false);
  }
}

// -----------------------------------------------------
// Version 4

void version_4()
{
  unsigned long recv_canid = 0;

  unsigned long fake_two_byte_counter = 0;
  char fake_one_byte_counter = 0;

  ctrl.reset();
  
  Serial.println("Version 4");

  while (ctrl.restart == false)
  {
    if (ctrl.start == true && CAN_MSGAVAIL == CAN0.checkReceive() ||
          ctrl.start == true && ctrl.test == true)
    {
      MESSAGE_TIME = millis();

      // Check to see whether data is read
      if (ctrl.test == false)
      {
        // Get Can Data
        CAN0.readMsgBufID(&ID, &len, buf);    // Read data  
      }
      else
      {
        // Get Test Data
        ID = fake_two_byte_counter;
        len = 8;
        buf[0] = fake_one_byte_counter;
        buf[1] = fake_one_byte_counter;
        buf[2] = fake_one_byte_counter;
        buf[3] = fake_one_byte_counter;
        buf[4] = fake_one_byte_counter;
        buf[5] = fake_one_byte_counter;
        buf[6] = fake_one_byte_counter;
        buf[7] = fake_one_byte_counter;
        
        fake_two_byte_counter++;
        fake_one_byte_counter++;

        if (fake_two_byte_counter > 0x0f00)
        {
          fake_two_byte_counter = 0;
        }

        if (fake_two_byte_counter > (256*256)-1)
        {
          fake_two_byte_counter = 0;                    
        }
        
        if (fake_one_byte_counter > 255)
        {
          fake_one_byte_counter = 0;                    
        }

        delay (5);
      }

      if (ctrl.filter == true)
      {
        if (filter(ID) == true)
        {
          digitalWrite(23, HIGH); // LED ON
          serial_send_2(ID, len, buf, MESSAGE_TIME);
          digitalWrite(23, LOW);  // LED OFF
        }
      }
      else
      {
        digitalWrite(23, HIGH); // LED ON
        serial_send_2(ID, len, buf, MESSAGE_TIME);
        digitalWrite(23, LOW);  // LED OFF
      }
    }
    
    // Read from host
    if(Serial.available() > 0)
    {
      //Serial.println("-");
      ctrl.read(read_com());
    }

    // send command to CAN
    if (ctrl.send_command == true)
    {
      digitalWrite(23, HIGH); // LED ON

      ctrl.send_command = false;
      sendPid(ctrl.command);
      
      digitalWrite(23, LOW);  // LED OFF
    }

    // Blink and Time
    blink(ctrl.start == false);
  }
}

// -----------------------------------------------------
// Main loop

void loop() 
{
  int delay_time = 250;
  
  while(true)
  {
    // pause if in main loop
    delay(delay_time);

    if (ctrl.version == 3)
    {
      version_3();
    }

    // pause if in main loop
    delay(delay_time);

    if (ctrl.version == 4)
    {
      version_4();
    }

    // pause if in main loop
    delay(delay_time);
  }    
}
