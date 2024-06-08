#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// CONSTANTs
#define	key24  false
#define	key44  true

#if key24
#define	IR_BPLUS  0xF700FF	//
#define	IR_BMINUS 0xF7807F	//
#define	IR_OFF 	  0xF740BF	//
#define	IR_ON 	  0xF7C03F	//
#define	IR_R 	    0xF720DF	//
#define	IR_G 	    0xF7A05F	//
#define	IR_B 	    0xF7609F	//
#define	IR_W 	    0xF7E01F	//
#define	IR_B1	    0xF710EF	//
#define	IR_B2	    0xF7906F	//
#define	IR_B3	    0xF750AF	//
#define	IR_FLASH  0xF7D02F	//
#define	IR_B4	    0xF730CF	//
#define	IR_B5	    0xF7B04F	//
#define	IR_B6	    0xF7708F	//
#define	IR_STROBE 0xF7F00F	//
#define	IR_B7	    0xF708F7	//
#define	IR_B8	    0xF78877	//
#define	IR_B9	    0xF748B7	//
#define	IR_FADE   0xF7C837	//
#define	IR_B10	  0xF728D7	//
#define	IR_B11	  0xF7A857	//
#define	IR_B12	  0xF76897	//
#define	IR_SMOOTH 0xF7E817	//
#endif

#if key44
#define	IR_BPlus  0xFF3AC5	//
#define	IR_BMinus 0xFFBA45	//
#define	IR_ON 	  0xFF827D	//
#define	IR_OFF 	  0xFF02FD	//
#define	IR_R 	    0xFF1AE5	//
#define	IR_G 	    0xFF9A65	//
#define	IR_B  	  0xFFA25D	//
#define	IR_W 	    0xFF22DD	//
#define	IR_B1	    0xFF2AD5	//
#define	IR_B2	    0xFFAA55	//
#define	IR_B3	    0xFF926D	//
#define	IR_B4	    0xFF12ED	//
#define	IR_B5	    0xFF0AF5	//
#define	IR_B6	    0xFF8A75	//
#define	IR_B7	    0xFFB24D	//
#define	IR_B8	    0xFF32CD	//
#define	IR_B9	    0xFF38C7	//
#define	IR_B10	  0xFFB847	//
#define	IR_B11	  0xFF7887	//
#define	IR_B12	  0xFFF807	//
#define	IR_B13	  0xFF18E7	//
#define	IR_B14	  0xFF9867	//
#define	IR_B15	  0xFF58A7	//
#define	IR_B16	  0xFFD827	//
#define	IR_UPR 	  0xFF28D7	//
#define	IR_UPG 	  0xFFA857	//
#define	IR_UPB 	  0xFF6897	//
#define	IR_QUICK  0xFFE817	//
#define	IR_DOWNR  0xFF08F7	//
#define	IR_DOWNG  0xFF8877	//
#define	IR_DOWNB  0xFF48B7	//
#define	IR_SLOW   0xFFC837	//
#define	IR_DIY1   0xFF30CF	//
#define	IR_DIY2   0xFFB04F	//
#define	IR_DIY3   0xFF708F	//
#define	IR_AUTO   0xFFF00F	//
#define	IR_DIY4   0xFF10EF	//
#define	IR_DIY5   0xFF906F	//
#define	IR_DIY6   0xFF50AF	//
#define	IR_FLASH  0xFFD02F	//
#define	IR_JUMP3  0xFF20DF	//
#define	IR_JUMP7  0xFFA05F	//
#define	IR_FADE3  0xFF609F	//
#define	IR_FADE7  0xFFE01F	//
#endif


//
// VARIABLES
//
    int codeType = -1;                // The type of received code
    unsigned long codeValue;          // The code value if not raw

//
// IR initialization
//
IRrecv irrecv(IR_PIN);
decode_results results;


//
//  AUXILIAR functions
//
// IR auxiliar functions
// matchCode: match IR code with appropriate action
boolean matchCode(decode_results *results) {
  codeType = results->decode_type;
  codeValue = results->value;
  String  mess = "";

  if(codeType != NEC) return false;
  else  {

          switch (codeValue) {
              case IR_BPlus:  if (GAIN <= 230) GAIN +=25; break;                  // Brightness up
              case IR_BMinus: if (GAIN > 25)   GAIN -=25; break;                  // Brightness down (never goes to 0)
              case IR_OFF:    EFX = 0; Light = false; break;                     // OFF
              case IR_ON:     EFX = 0; Light = true; break;                      // ON
              case IR_R:      strcpy(Color,RED); break;                           // Red (H=0)
              case IR_G:      strcpy(Color,GREEN); break;                         // Green (H=120)
              case IR_B:      strcpy(Color,BLUE); break;                          // Blue (H=)
              case IR_W:      strcpy(Color,WHITE); break;                         // White (H=0,S=0)
              case IR_B1:     strcpy(Color,ORANGE); break;                        // #FFA500
              case IR_B2:     strcpy(Color,LIGHT_GREEN); break;                   // #90EE90
              case IR_B3:     strcpy(Color,DEEP_BLUE); break;                     // #000080
              case IR_B4:     strcpy(Color,WARM_WHITE); break;                    // #FF930F
              case IR_B5:     strcpy(Color,DEEP_YELLOW); break;                   // #FFD700
              case IR_B6:     strcpy(Color,CYAN); break;                          // #00FFFF
              case IR_B7:     strcpy(Color,BLUE_PURPLE); break;                   // #9370DB
              case IR_B8:     strcpy(Color,PINK_WHITE); break;                    // #FFC0CB
              case IR_B9:     strcpy(Color,YELLOW); break;                        // #FFFF00
              case IR_B10:    strcpy(Color,LIGHT_BLUE); break;                    // #ADD8E6
              case IR_B11:    strcpy(Color,PURPLE); break;                        // #800080
              case IR_B12:    strcpy(Color,GREEN_WHITE); break;                   // #E0FFE0
              case IR_B13:    strcpy(Color,LIGHT_YELLOW); break;                  // #FFFFD0
              case IR_B14:    strcpy(Color,SKY_BLUE); break;                      // #87CEEB
              case IR_B15:    strcpy(Color,BROWN); break;                         // #A52A2A
              case IR_B16:    strcpy(Color,BLUE_WHITE); break;                    // #E0E0FF
              case IR_AUTO:   EFX = 1; color_set(Color); break;
              case IR_FLASH:  EFX = 2; color_set(Color); break;
              case IR_JUMP3:  EFX = 7; color_set(Color); break;
              case IR_JUMP7:  EFX = 8; color_set(Color); break;
              case IR_FADE3:  EFX = 3; color_set(Color); break;
              case IR_FADE7:  EFX = 4; color_set(Color); break;
              case IR_QUICK:  if (EFX_Interval > 500)  EFX_Interval -=250; break; // IR_SLOW
              case IR_SLOW:   if (EFX_Interval < 2500) EFX_Interval +=250; break; // IR_QUICK
              case IR_UPR:    color_change(10,0,0); break;                        // IR_UPR
              case IR_DOWNR:  color_change(-10,0,0); break;                       // IR_DOWNR
              case IR_UPG:    color_change(0,10,0); break;                        // IR_UPG
              case IR_DOWNG:  color_change(0,-10,0); break;                       // IR_DOWNG
              case IR_UPB:    color_change(0,0,10); break;                        // IR_UPB
              case IR_DOWNB:  color_change(0,0,-10); break;                       // IR_DOWNB
              case IR_DIY1:   EFX = 5; color_set(Color); break;                   // Scan EFX
              case IR_DIY2:   EFX = 6; color_set(Color); break;                   // Rainbow EFX
              case IR_DIY3:   mess="IR_DIY3"; break;                              // IR_DIY3
              case IR_DIY4:   mess="IR_DIY4"; break;                              // IR_DIY4
              case IR_DIY5:   mess="IR_DIY5"; break;                              // IR_DIY5
              case IR_DIY6:   mess="IR_DIY6"; break;                              // IR_DIY6
          }
        }
        return true;
}


//
//  MAIN functions
//
void IR_setup() {
     irrecv.enableIRIn();
}


void IR_loop() {
      if (irrecv.decode(&results)) {
        telnet_println(String(results.value));
        // print() & println() can't handle printing long longs. (uint64_t)
        //serialPrintUint64(results.value, HEX);
        //Serial.println("");
        matchCode(&results);
        irrecv.resume();  // Receive the next value
      }

}
