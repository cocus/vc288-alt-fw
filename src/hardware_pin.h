
#ifndef _HARDWARE_PIN_H
#define _HARDWARE_PIN_H

#if defined(BOARD_HW_V1)
 
 #define STPROG_PORT            PD
 #define STPROG_PIN             PIN6

 #define MCD_A_PORT             PD
 #define MCD_A_PIN              PIN1
 
 #define MCD_B_PORT             PA
 #define MCD_B_PIN              PIN3

 #define MCD_C_PORT             PC
 #define MCD_C_PIN              PIN3

 #define MCD_D_PORT             PC
 #define MCD_D_PIN              PIN6

 #define MCD_E_PORT             PC
 #define MCD_E_PIN              PIN7

 #define MCD_F_PORT             PC
 #define MCD_F_PIN              PIN4

 #define MCD_G_PORT             PA
 #define MCD_G_PIN              PIN2

 #define MCD_DP_PORT            PC
 #define MCD_DP_PIN             PIN5

 #define MCD1_AD1_PORT          PD
 #define MCD1_AD1_PIN           PIN4

 #define MCD1_AD2_PORT          PD
 #define MCD1_AD2_PIN           PIN6

 #define MCD1_AD3_PORT          PD
 #define MCD1_AD3_PIN           PIN5

 #define MCD2_AD1_PORT          PB
 #define MCD2_AD1_PIN           PIN5

 #define MCD2_AD2_PORT          PA
 #define MCD2_AD2_PIN           PIN1

 #define MCD2_AD3_PORT          PB
 #define MCD2_AD3_PIN           PIN4

#elif defined(BOARD_HW_V2)

 #define STPROG_PORT            PD
 #define STPROG_PIN             PIN6

 #define MCD_A_PORT             PD
 #define MCD_A_PIN              PIN1
 
 #define MCD_B_PORT             PA
 #define MCD_B_PIN              PIN3

 #define MCD_C_PORT             PC
 #define MCD_C_PIN              PIN3

 #define MCD_D_PORT             PC
 #define MCD_D_PIN              PIN6

 #define MCD_E_PORT             PC
 #define MCD_E_PIN              PIN7

 #define MCD_F_PORT             PC
 #define MCD_F_PIN              PIN4

 #define MCD_G_PORT             PA
 #define MCD_G_PIN              PIN2

 #define MCD_DP_PORT            PC
 #define MCD_DP_PIN             PIN5

 #define MCD1_AD1_PORT          PD
 #define MCD1_AD1_PIN           PIN4

 #define MCD1_AD2_PORT          PD
 #define MCD1_AD2_PIN           PIN6

 #define MCD1_AD3_PORT          PD
 #define MCD1_AD3_PIN           PIN5

 #define MCD2_AD1_PORT          PB
 #define MCD2_AD1_PIN           PIN5

 #define MCD2_AD2_PORT          PB
 #define MCD2_AD2_PIN           PIN4

 #define MCD2_AD3_PORT          PA
 #define MCD2_AD3_PIN           PIN1

#elif defined(BOARD_HW_V3)

 #define STPROG_PORT            PD
 #define STPROG_PIN             PIN6
 
 #define MCD_A_PORT             PD
 #define MCD_A_PIN              PIN1
 
 #define MCD_B_PORT             PB
 #define MCD_B_PIN              PIN5

 #define MCD_C_PORT             PC
 #define MCD_C_PIN              PIN3

 #define MCD_D_PORT             PC
 #define MCD_D_PIN              PIN6
 
 #define MCD_E_PORT             PC
 #define MCD_E_PIN              PIN7

 #define MCD_F_PORT             PC
 #define MCD_F_PIN              PIN4

 #define MCD_G_PORT             PB
 #define MCD_G_PIN              PIN4

 #define MCD_DP_PORT            PC
 #define MCD_DP_PIN             PIN5

 #define MCD1_AD1_PORT          PD
 #define MCD1_AD1_PIN           PIN4

 #define MCD1_AD2_PORT          PD
 #define MCD1_AD2_PIN           PIN6

 #define MCD1_AD3_PORT          PD
 #define MCD1_AD3_PIN           PIN5

 #define MCD2_AD1_PORT          PA
 #define MCD2_AD1_PIN           PIN3

 #define MCD2_AD2_PORT          PA
 #define MCD2_AD2_PIN           PIN2

 #define MCD2_AD3_PORT          PA
 #define MCD2_AD3_PIN           PIN1

#else
 #error Not defined BOARD_HW_V?(1,2,3)!!!
#endif


#endif //_HARDWARE_PIN_H