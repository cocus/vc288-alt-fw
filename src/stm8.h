#ifndef _STH8_H
#define _STH8_H

/* Handy macros for GPIO */
#define CONCAT(a, b)    a##_##b
#define PORT(a, b)      CONCAT(a , b)

// These are (sometimes) optimized by sdcc to use the bset/bres assembly
// instructions.
#define CLRBIT(REG, VALUE) REG &= ~VALUE
#define SETBIT(REG, VALUE) REG |=  VALUE

#define PIN0    (1 << 0)
#define PIN1    (1 << 1)
#define PIN2    (1 << 2)
#define PIN3    (1 << 3)
#define PIN4    (1 << 4)
#define PIN5    (1 << 5)
#define PIN6    (1 << 6)
#define PIN7    (1 << 7)

/* Register addresses */
#define CCR *(volatile unsigned char *)0x7F0A

/* Clock */
#define CLK_ICKR     *(volatile unsigned char *)0x50C0
#define CLK_ECKR     *(volatile unsigned char *)0x50C1
#define CLK_CMSR     *(volatile unsigned char *)0x50C3
#define CLK_SWR      *(volatile unsigned char *)0x50C4
#define CLK_SWCR     *(volatile unsigned char *)0x50C5
#define CLK_CKDIVR   *(volatile unsigned char *)0x50C6
#define CLK_PCKENR1  *(volatile unsigned char *)0x50C7
#define CLK_PCKENR2  *(volatile unsigned char *)0x50CA
#define CLK_CSSR     *(volatile unsigned char *)0x50C8
#define CLK_CCOR     *(volatile unsigned char *)0x50C9
#define CLK_HSITRIMR *(volatile unsigned char *)0x50CC
#define CLK_SWIMCCR  *(volatile unsigned char *)0x50CD

#define CLK_ICKR_REGAH  (1 << 5)
#define CLK_ICKR_LSIRDY (1 << 4)
#define CLK_ICKR_LSIEN  (1 << 3)
#define CLK_ICKR_FHWU   (1 << 2)
#define CLK_ICKR_HSIRDY (1 << 1)
#define CLK_ICKR_HSIEN  (1 << 0)

#define CLK_ECKR_HSERDY (1 << 1)
#define CLK_ECKR_HSEEN  (1 << 0)

#define CLK_SWCR_SWIF   (1 << 3)
#define CLK_SWCR_SWIEN  (1 << 2)
#define CLK_SWCR_SWEN   (1 << 1)
#define CLK_SWCR_SWBSY  (1 << 0)

#define CLK_PCKENR1_TIM1   (1 << 7)
#define CLK_PCKENR1_TIM3   (1 << 6)
#define CLK_PCKENR1_TIM2   (1 << 5)
#define CLK_PCKENR1_TIM5   (1 << 5)
#define CLK_PCKENR1_TIM4   (1 << 4)
#define CLK_PCKENR1_TIM6   (1 << 4)
#define CLK_PCKENR1_CKEN13 (1 << 3)
#define CLK_PCKENR1_CKEN12 (1 << 2)
#define CLK_PCKENR1_SPI    (1 << 1)
#define CLK_PCKENR1_I2C    (1 << 0)

#define CLK_PCKENR2_CAN    (1 << 7)
#define CLK_PCKENR2_ADC    (1 << 3)
#define CLK_PCKENR2_AWU    (1 << 2)

#define CLK_CSSR_CSSD       (1 << 3)
#define CLK_CSSR_CSSDIE     (1 << 2)
#define CLK_CSSR_AUX        (1 << 1)
#define CLK_CSSR_CSSEN      (1 << 0)

#define CLK_CCOR_CCOBSY     (1 << 6)
#define CLK_CCOR_CCORDY     (1 << 5)
#define CLK_CCOR_CCOSEL3    (1 << 4)
#define CLK_CCOR_CCOSEL2    (1 << 3)
#define CLK_CCOR_CCOSEL1    (1 << 2)
#define CLK_CCOR_CCOSEL0    (1 << 1)
#define CLK_CCOR_CCOEN      (1 << 0)

#define CLK_SWIMCCR_SWIMCLK (1 << 0)

/* GPIO */
#define PA_ODR *(volatile unsigned char *)0x5000
#define PA_IDR *(volatile unsigned char *)0x5001
#define PA_DDR *(volatile unsigned char *)0x5002
#define PA_CR1 *(volatile unsigned char *)0x5003
#define PA_CR2 *(volatile unsigned char *)0x5004

#define PB_ODR *(volatile unsigned char *)0x5005
#define PB_IDR *(volatile unsigned char *)0x5006
#define PB_DDR *(volatile unsigned char *)0x5007
#define PB_CR1 *(volatile unsigned char *)0x5008
#define PB_CR2 *(volatile unsigned char *)0x5009

#define PC_ODR *(volatile unsigned char *)0x500A
#define PC_IDR *(volatile unsigned char *)0x500B
#define PC_DDR *(volatile unsigned char *)0x500C
#define PC_CR1 *(volatile unsigned char *)0x500D
#define PC_CR2 *(volatile unsigned char *)0x500E

#define PD_ODR *(volatile unsigned char *)0x500F
#define PD_IDR *(volatile unsigned char *)0x5010
#define PD_DDR *(volatile unsigned char *)0x5011
#define PD_CR1 *(volatile unsigned char *)0x5012
#define PD_CR2 *(volatile unsigned char *)0x5013

#define EXTI_CR1 *(volatile unsigned char *)0x50A0
#define EXTI_CR2 *(volatile unsigned char *)0x50A1

/* Flash */
#define FLASH_CR1 *(volatile unsigned char*)0x505A
#define FLASH_CR2 *(volatile unsigned char*)0x505B
#define FLASH_NCR2 *(volatile unsigned char*)0x505C
#define FLASH_FPR *(volatile unsigned char*)0x505D
#define FLASH_NFPR *(volatile unsigned char*)0x505E
#define FLASH_IAPSR *(volatile unsigned char*)0x505F
#define FLASH_PUKR *(volatile unsigned char*)0x5062
#define FLASH_DUKR *(volatile unsigned char*)0x5064

#define FLASH_IAPSR_HVOFF (1 << 6)
#define FLASH_IAPSR_DUL (1 << 3)

/* UART */
#define UART1_SR *(volatile unsigned char *)0x5230
#define UART1_DR *(volatile unsigned char *)0x5231
#define UART1_BRR1 *(volatile unsigned char *)0x5232
#define UART1_BRR2 *(volatile unsigned char *)0x5233
#define UART1_CR1 *(volatile unsigned char *)0x5234
#define UART1_CR2 *(volatile unsigned char *)0x5235
#define UART1_CR3 *(volatile unsigned char *)0x5236
#define UART1_CR4 *(volatile unsigned char *)0x5237
#define UART1_CR5 *(volatile unsigned char *)0x5238
#define UART1_GTR *(volatile unsigned char *)0x5239
#define UART1_PSCR *(volatile unsigned char *)0x523A

#define UART_SR_TXE (1 << 7)
#define UART_SR_TC (1 << 6)
#define UART_SR_RXNE (1 << 5)
#define UART_SR_IDLE (1 << 4)
#define UART_SR_OR (1 << 3)
#define UART_SR_NF (1 << 2)
#define UART_SR_FE (1 << 1)
#define UART_SR_PE (1 << 0)

#define UART_CR1_R8 (1 << 7)
#define UART_CR1_T8 (1 << 6)
#define UART_CR1_UARTD (1 << 5)
#define UART_CR1_M (1 << 4)
#define UART_CR1_WAKE (1 << 3)
#define UART_CR1_PCEN (1 << 2)
#define UART_CR1_PS (1 << 1)
#define UART_CR1_PIEN (1 << 0)

#define UART_CR2_TIEN (1 << 7)
#define UART_CR2_TCIEN (1 << 6)
#define UART_CR2_RIEN (1 << 5)
#define UART_CR2_ILIEN (1 << 4)
#define UART_CR2_TEN (1 << 3)
#define UART_CR2_REN (1 << 2)
#define UART_CR2_RWU (1 << 1)
#define UART_CR2_SBK (1 << 0)

#define UART_CR3_LINEN (1 << 6)
#define UART_CR3_STOP2 (1 << 5)
#define UART_CR3_STOP1 (1 << 4)
#define UART_CR3_CLKEN (1 << 3)
#define UART_CR3_CPOL (1 << 2)
#define UART_CR3_CPHA (1 << 1)
#define UART_CR3_LBCL (1 << 0)

/* Timers */
#define TIM1_CR1 *(volatile unsigned char *)0x5250
#define TIM1_CR2 *(volatile unsigned char *)0x5251
#define TIM1_SMCR *(volatile unsigned char *)0x5252
#define TIM1_ETR *(volatile unsigned char *)0x5253
#define TIM1_IER *(volatile unsigned char *)0x5254
#define TIM1_SR1 *(volatile unsigned char *)0x5255
#define TIM1_SR2 *(volatile unsigned char *)0x5256
#define TIM1_EGR *(volatile unsigned char *)0x5257
#define TIM1_CCMR1 *(volatile unsigned char *)0x5258
#define TIM1_CCMR2 *(volatile unsigned char *)0x5259
#define TIM1_CCMR3 *(volatile unsigned char *)0x525A
#define TIM1_CCMR4 *(volatile unsigned char *)0x525B
#define TIM1_CCER1 *(volatile unsigned char *)0x525C
#define TIM1_CCER2 *(volatile unsigned char *)0x525D
#define TIM1_CNTRH *(volatile unsigned char *)0x525E
#define TIM1_CNTRL *(volatile unsigned char *)0x525F
#define TIM1_PSCRH *(volatile unsigned char *)0x5260
#define TIM1_PSCRL *(volatile unsigned char *)0x5261
#define TIM1_ARRH *(volatile unsigned char *)0x5262
#define TIM1_ARRL *(volatile unsigned char *)0x5263
#define TIM1_RCR *(volatile unsigned char *)0x5264
#define TIM1_CCR1H *(volatile unsigned char *)0x5265
#define TIM1_CCR1L *(volatile unsigned char *)0x5266
#define TIM1_CCR2H *(volatile unsigned char *)0x5267
#define TIM1_CCR2L *(volatile unsigned char *)0x5268
#define TIM1_CCR3H *(volatile unsigned char *)0x5269
#define TIM1_CCR3L *(volatile unsigned char *)0x526A
#define TIM1_CCR4H *(volatile unsigned char *)0x526B
#define TIM1_CCR4L *(volatile unsigned char *)0x526C
#define TIM1_BKR *(volatile unsigned char *)0x526D
#define TIM1_DTR *(volatile unsigned char *)0x526E
#define TIM1_OISR *(volatile unsigned char *)0x526F

/* Note these are for STM8S103 and STM8S003
   STM8S105,104/207/208 are different */
#define TIM2_CR1 *(volatile unsigned char *)0x5300
#define TIM2_CR2 *(volatile unsigned char *)0x5301
#define TIM2_SMCR *(volatile unsigned char *)0x5302
#define TIM2_IER *(volatile unsigned char *)0x5303
#define TIM2_SR1 *(volatile unsigned char *)0x5304
#define TIM2_SR2 *(volatile unsigned char *)0x5305
#define TIM2_EGR *(volatile unsigned char *)0x5306
#define TIM2_CCMR1 *(volatile unsigned char *)0x5307
#define TIM2_CCMR2 *(volatile unsigned char *)0x5308
#define TIM2_CCMR3 *(volatile unsigned char *)0x5309
#define TIM2_CCER1 *(volatile unsigned char *)0x530A
#define TIM2_CCER2 *(volatile unsigned char *)0x530B
#define TIM2_CNTRH *(volatile unsigned char *)0x530C
#define TIM2_CNTRL *(volatile unsigned char *)0x530D
#define TIM2_PSCR *(volatile unsigned char *)0x530E
#define TIM2_ARRH *(volatile unsigned char *)0x530F
#define TIM2_ARRL *(volatile unsigned char *)0x5310
#define TIM2_CCR1H *(volatile unsigned char *)0x5311
#define TIM2_CCR1L *(volatile unsigned char *)0x5312
#define TIM2_CCR2H *(volatile unsigned char *)0x5313
#define TIM2_CCR2L *(volatile unsigned char *)0x5314
#define TIM2_CCR3H *(volatile unsigned char *)0x5315
#define TIM2_CCR3L *(volatile unsigned char *)0x5316

/* Note these are for STM8S103 and STM8S003
   STM8S105,104/207/208 are different */
#define TIM4_CR1 *(volatile unsigned char *)0x5340
#define TIM4_CR2 *(volatile unsigned char *)0x5341
#define TIM4_SMCR *(volatile unsigned char *)0x5342
#define TIM4_IER *(volatile unsigned char *)0x5343
#define TIM4_SR *(volatile unsigned char *)0x5344
#define TIM4_EGR *(volatile unsigned char *)0x5345
#define TIM4_CNTR *(volatile unsigned char *)0x5346
#define TIM4_PSCR *(volatile unsigned char *)0x5347
#define TIM4_ARR *(volatile unsigned char *)0x5348

#define TIM_IER_BIE (1 << 7)
#define TIM_IER_TIE (1 << 6)
#define TIM_IER_COMIE (1 << 5)
#define TIM_IER_CC4IE (1 << 4)
#define TIM_IER_CC3IE (1 << 3)
#define TIM_IER_CC2IE (1 << 2)
#define TIM_IER_CC1IE (1 << 1)
#define TIM_IER_UIE (1 << 0)

#define TIM_CR1_APRE (1 << 7)
#define TIM_CR1_CMSH (1 << 6)
#define TIM_CR1_CMSL (1 << 5)
#define TIM_CR1_DIR (1 << 4)
#define TIM_CR1_OPM (1 << 3)
#define TIM_CR1_URS (1 << 2)
#define TIM_CR1_UDIS (1 << 1)
#define TIM_CR1_CEN (1 << 0)

#define TIM_CR2_MMS2 (1 << 6)
#define TIM_CR2_MMS1 (1 << 5)
#define TIM_CR2_MMS0 (1 << 4)

#define TIM_IER_UIE (1 << 0)

#define TIM_SR1_BIF (1 << 7)
#define TIM_SR1_TIF (1 << 6)
#define TIM_SR1_COMIF (1 << 5)
#define TIM_SR1_CC4IF (1 << 4)
#define TIM_SR1_CC3IF (1 << 3)
#define TIM_SR1_CC2IF (1 << 2)
#define TIM_SR1_CC1IF (1 << 1)
#define TIM_SR1_UIF (1 << 0)

/* SPI */
#define SPI_CR1 *(volatile unsigned char *)0x5200
#define SPI_CR2 *(volatile unsigned char *)0x5201
#define SPI_ICR *(volatile unsigned char *)0x5202
#define SPI_SR *(volatile unsigned char *)0x5203
#define SPI_DR *(volatile unsigned char *)0x5204
#define SPI_CRCPR *(volatile unsigned char *)0x5205
#define SPI_RXCRCR *(volatile unsigned char *)0x5206
#define SPI_TXCRCR *(volatile unsigned char *)0x5207

#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SPE (1 << 6)
#define SPI_CR1_BR(br) ((br) << 3)
#define SPI_CR1_MSTR (1 << 2)
#define SPI_CR1_CPOL (1 << 1)
#define SPI_CR1_CPHA (1 << 0)

#define SPI_CR2_BDM (1 << 7)
#define SPI_CR2_BDOE (1 << 6)
#define SPI_CR2_CRCEN (1 << 5)
#define SPI_CR2_CRCNEXT (1 << 4)
#define SPI_CR2_RXONLY (1 << 2)
#define SPI_CR2_SSM (1 << 1)
#define SPI_CR2_SSI (1 << 0)

#define SPI_ICR_TXIE (1 << 7)
#define SPI_ICR_RXIE (1 << 6)
#define SPI_ICR_ERRIE (1 << 5)
#define SPI_ICR_WKIE (1 << 4)

#define SPI_SR_BSY (1 << 7)
#define SPI_SR_OVR (1 << 6)
#define SPI_SR_MODF (1 << 5)
#define SPI_SR_CRCERR (1 << 4)
#define SPI_SR_WKUP (1 << 3)
#define SPI_SR_TXE (1 << 1)
#define SPI_SR_RxNE (1 << 0)

/* I2C */
#define I2C_CR1 *(volatile unsigned char *)0x5210
#define I2C_CR2 *(volatile unsigned char *)0x5211
#define I2C_FREQR *(volatile unsigned char *)0x5212
#define I2C_OARL *(volatile unsigned char *)0x5213
#define I2C_OARH *(volatile unsigned char *)0x5214
#define I2C_DR *(volatile unsigned char *)0x5216
#define I2C_SR1 *(volatile unsigned char *)0x5217
#define I2C_SR2 *(volatile unsigned char *)0x5218
#define I2C_SR3 *(volatile unsigned char *)0x5219
#define I2C_ITR *(volatile unsigned char *)0x521A
#define I2C_CCRL *(volatile unsigned char *)0x521B
#define I2C_CCRH *(volatile unsigned char *)0x521C
#define I2C_TRISER *(volatile unsigned char *)0x521D
#define I2C_PECR *(volatile unsigned char *)0x521E

/* ADC */
#define ADC_DB0RH *(volatile unsigned char *)0x53E0
#define ADC_DB0RL *(volatile unsigned char *)0x53E1
#define ADC_DB1RH *(volatile unsigned char *)0x53E2
#define ADC_DB1RL *(volatile unsigned char *)0x53E3
#define ADC_DB2RH *(volatile unsigned char *)0x53E4
#define ADC_DB2RL *(volatile unsigned char *)0x53E5
#define ADC_DB3RH *(volatile unsigned char *)0x53E6
#define ADC_DB3RL *(volatile unsigned char *)0x53E7
#define ADC_DB4RH *(volatile unsigned char *)0x53E8
#define ADC_DB4RL *(volatile unsigned char *)0x53E9
#define ADC_DB5RH *(volatile unsigned char *)0x53EA
#define ADC_DB5RL *(volatile unsigned char *)0x53EB
#define ADC_DB6RH *(volatile unsigned char *)0x53EC
#define ADC_DB6RL *(volatile unsigned char *)0x53ED
#define ADC_DB7RH *(volatile unsigned char *)0x53EE
#define ADC_DB7RL *(volatile unsigned char *)0x53EF
#define ADC_DB8RH *(volatile unsigned char *)0x53F0
#define ADC_DB8RL *(volatile unsigned char *)0x53F1
#define ADC_DB9RH *(volatile unsigned char *)0x53F2
#define ADC_DB9RL *(volatile unsigned char *)0x53F3

#define ADC_CSR *(volatile unsigned char *)0x5400
#define ADC_CR1 *(volatile unsigned char *)0x5401
#define ADC_CR2 *(volatile unsigned char *)0x5402
#define ADC_CR3 *(volatile unsigned char *)0x5403
#define ADC_DRH *(volatile unsigned char *)0x5404
#define ADC_DRL *(volatile unsigned char *)0x5405
#define ADC_TDRH *(volatile unsigned char *)0x5406
#define ADC_TDRL *(volatile unsigned char *)0x5407
#define ADC_HTRH *(volatile unsigned char *)0x5408
#define ADC_HTRL *(volatile unsigned char *)0x5409
#define ADC_LTRH *(volatile unsigned char *)0x540A
#define ADC_LTRL *(volatile unsigned char *)0x540B
#define ADC_AWSRH *(volatile unsigned char *)0x540C
#define ADC_AWSRL *(volatile unsigned char *)0x540D
#define ADC_AWCRH *(volatile unsigned char *)0x540E
#define ADC_AWCRL *(volatile unsigned char *)0x540F

#define ADC_CSR_EOC (1 << 7)
#define ADC_CSR_AWD (1 << 6)
#define ADC_CSR_EOCIE (1 << 5)
#define ADC_CSR_AWDIE (1 << 4)
#define ADC_CSR_CH3 (1 << 3)
#define ADC_CSR_CH2 (1 << 2)
#define ADC_CSR_CH1 (1 << 1)
#define ADC_CSR_CH0 (1 << 0)

#define ADC_CR1_SPSEL2 (1 << 6)
#define ADC_CR1_SPSEL1 (1 << 5)
#define ADC_CR1_SPSEL0 (1 << 4)
#define ADC_CR1_CONT (1 << 1)
#define ADC_CR1_ADON (1 << 0)

#define ADC_CR2_EXTTRIG (1 << 6)
#define ADC_CR2_EXTSEL1 (1 << 5)
#define ADC_CR2_EXTSEL0 (1 << 4)
#define ADC_CR2_ALIGN (1 << 3)
#define ADC_CR2_SCAN (1 << 1)

#define ADC_CR3_DBUF (1 << 7)
#define ADC_CR3_OVR (1 << 6)


#define CFG_GCR   *(volatile unsigned char *)0x7F60
#define CFG_GCR_SWD ((uint8_t)0x01) /*!< Swim disable bit mask */
#define CFG_GCR_AL  ((uint8_t)0x02) /*!< Activation Level bit mask */

#define SWIM_CSR  *(volatile unsigned char *)0x7F80
#define SWIM_CSR_PRI (1<<0)
#define SWIM_CSR_HSIT (1<<1)
#define SWIM_CSR_RST (1<<2)
#define SWIM_CSR_OSCOFF (1<<3)
#define SWIM_CSR_HS (1<<4)
#define SWIM_CSR_SWIM_DM (1<<5)
#define SWIM_CSR_NO_ACCESS (1<<6)
#define SWIM_CSR_SAFE_MASK (1<<7)
    
#define CLK_SWIMCCR  *(volatile unsigned char *)0x50CD


/* Interrupt commands */
/*============================== Interrupts ====================================*/
#if defined(_RAISONANCE_ ) || defined(__RCSTM8__)
 #include <intrins.h>
 #define enableInterrupts()    _rim_()  /* enable interrupts */
 #define disableInterrupts()   _sim_()  /* disable interrupts */
 #define __enable_interrupt()  _rim_()  /* enable interrupts */
 #define __disable_interrupt() _sim_()  /* disable interrupts */
 #define rim()                 _rim_()  /* enable interrupts */
 #define sim()                 _sim_()  /* disable interrupts */
 #define nop()                 _nop_()  /* No Operation */
 #define trap()                _trap_() /* Trap (soft IT) */
 #define wfi()                 _wfi_()  /* Wait For Interrupt */
 #define halt()                _halt_() /* Halt */
//#endif /*_RAISONANCE_*/
#elif defined(_COSMIC_) || defined(__CSMC__)
 #define enableInterrupts()    {_asm("rim\n");}  /* enable interrupts */
 #define disableInterrupts()   {_asm("sim\n");}  /* disable interrupts */
 #define __enable_interrupt()  {_asm("rim\n");}  /* enable interrupts */
 #define __disable_interrupt() {_asm("sim\n");}  /* disable interrupts */
 #define rim()                 {_asm("rim\n");}  /* enable interrupts */
 #define sim()                 {_asm("sim\n");}  /* disable interrupts */
 #define nop()                 {_asm("nop\n");}  /* No Operation */
 #define trap()                {_asm("trap\n");} /* Trap (soft IT) */
 #define wfi()                 {_asm("wfi\n");}  /* Wait For Interrupt */
 #define halt()                {_asm("halt\n");} /* Halt */
//#endif /*_COSMIC_*/
#elif defined(_IAR_) || defined(__IAR_SYSTEMS_ICC__)
 #include <intrinsics.h>
 #define enableInterrupts()    __enable_interrupt()   /* enable interrupts */
 #define disableInterrupts()   __disable_interrupt()  /* disable interrupts */
 #define rim()                 __enable_interrupt()   /* enable interrupts */
 #define sim()                 __disable_interrupt()  /* disable interrupts */
 #define nop()                 __no_operation()       /* No Operation */
 #define trap()                __trap()               /* Trap (soft IT) */
 #define wfi()                 __wait_for_interrupt() /* Wait For Interrupt */
 #define halt()                __halt()               /* Halt */
//#endif /*_IAR_*/
#else /**/
 #define __enable_interrupt()  {__asm__("rim\n");}  /* enable interrupts */
 #define __disable_interrupt() {__asm__("sim\n");}  /* disable interrupts */
 #define rim()                 {__asm__("rim\n");}  /* enable interrupts */
 #define sim()                 {__asm__("sim\n");}  /* disable interrupts */
 #define nop()                 {__asm__("nop\n");}  /* No Operation */
 #define trap()                {__asm__("trap\n");} /* Trap (soft IT) */
 #define wfi()                 {__asm__("wfi\n");}  /* Wait For Interrupt */
 #define halt()                {__asm__("halt\n");} /* Halt */
#endif /**/

/*============================== Interrupt vector Handling ========================*/

#if defined(_COSMIC_) || defined(__CSMC__)
 #define ISR(a,b) @far @interrupt void a(void)
 #define ISR_TRAP(a) void @far @interrupt a(void)
 #define INTERRUPT @far @interrupt
//#endif /* _COSMIC_ */
#elif defined(_RAISONANCE_) || defined(__RCSTM8__)
 #define ISR(a,b) void a(void) interrupt b
 #define ISR_TRAP(a) void a(void) trap
//#endif /* _RAISONANCE_ */
#elif defined(_IAR_) || defined(__IAR_SYSTEMS_ICC__)
 #define STRINGVECTOR(x) #x
 #define VECTOR_ID(x) STRINGVECTOR( vector = (x) )
 #define ISR( a, b )  \
 _Pragma( VECTOR_ID( (b)+2 ) )        \
 __interrupt void (a)( void )
 #define ISR_TRAP(a) \
 _Pragma( VECTOR_ID( 1 ) ) \
 __interrupt void (a) (void)  
 #define INTERRUPT __interrupt
//#endif /* _IAR_ */
#else
 #ifndef __SDCC
 #define __interrupt(x)
 #endif
 // Note that the vector counts start from 0, i.e. the (addr_vector - 0x8000) / 4
 // In SDCC however, RESET and TRAP are left out in this count, i.e. IRQ0 is at
 // address 0x8008. So we use this macro to allow the below vector definitions from
 // iostm8s003f3.h to still work.
 #define ISR(name,vector) void name(void) __interrupt(vector)
#endif

/**
  * @brief  ITC Interrupt Lines selection
  */
typedef enum {
  ITC_IRQ_TLI            = 0,   /*!< Software interrupt */
  ITC_IRQ_AWU            = 1,   /*!< Auto wake up from halt interrupt */
  ITC_IRQ_CLK            = 2,   /*!< Clock controller interrupt */
  ITC_IRQ_PORTA          = 3,   /*!< Port A external interrupts */
  ITC_IRQ_PORTB          = 4,   /*!< Port B external interrupts */
  ITC_IRQ_PORTC          = 5,   /*!< Port C external interrupts */
  ITC_IRQ_PORTD          = 6,   /*!< Port D external interrupts */
  ITC_IRQ_PORTE          = 7,   /*!< Port E external interrupts */
  
#if defined(STM8S208) || defined(STM8AF52Ax)
  ITC_IRQ_CAN_RX         = 8,   /*!< beCAN RX interrupt */
  ITC_IRQ_CAN_TX         = 9,   /*!< beCAN TX/ER/SC interrupt */
#endif /*STM8S208 or STM8AF52Ax */

#ifdef STM8S903
  ITC_IRQ_PORTF          = 8,   /*!< Port F external interrupts */
#endif /*STM8S903*/

  ITC_IRQ_SPI            = 10,  /*!< SPI interrupt */
  ITC_IRQ_TIM1_OVF       = 11,  /*!< TIM1 update/overflow/underflow/trigger/
                                         break interrupt*/
  ITC_IRQ_TIM1_CAPCOM    = 12,  /*!< TIM1 capture/compare interrupt */
  
#ifdef STM8S903
  ITC_IRQ_TIM5_OVFTRI    = 13,  /*!< TIM5 update/overflow/underflow/trigger/
                                         interrupt */
  ITC_IRQ_TIM5_CAPCOM    = 14,  /*!< TIM5 capture/compare interrupt */
#else  
  ITC_IRQ_TIM2_OVF       = 13,  /*!< TIM2 update /overflow interrupt */
  ITC_IRQ_TIM2_CAPCOM    = 14,  /*!< TIM2 capture/compare interrupt */
#endif /*STM8S903*/

  ITC_IRQ_TIM3_OVF       = 15,  /*!< TIM3 update /overflow interrupt*/
  ITC_IRQ_TIM3_CAPCOM    = 16,  /*!< TIM3 update /overflow interrupt */
  ITC_IRQ_UART1_TX       = 17,  /*!< USART1 TX interrupt */
  ITC_IRQ_UART1_RX       = 18,  /*!< USART1 RX interrupt */
  ITC_IRQ_I2C            = 19,  /*!< I2C interrupt */
  
#if defined(STM8S105) || defined(STM8S005) || defined(STM8AF626x)
  ITC_IRQ_UART2_TX       = 20,  /*!< USART2 TX interrupt */
  ITC_IRQ_UART2_RX       = 21,  /*!< USART2 RX interrupt */
#endif /*STM8S105 or STM8AF626x */

#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8AF52Ax) || defined(STM8AF62Ax)
  ITC_IRQ_UART3_TX       = 20,  /*!< USART3 TX interrupt */
  ITC_IRQ_UART3_RX       = 21,  /*!< USART3 RX interrupt */
  ITC_IRQ_ADC2           = 22,  /*!< ADC2 interrupt */
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#if defined(STM8S105) || defined(STM8S005) || defined(STM8S103) || defined(STM8S003) ||  defined(STM8S903) || defined(STM8AF626x)  
  ITC_IRQ_ADC1           = 22,  /*!< ADC2 interrupt */
#endif /*STM8S105, STM8S103 or STM8S903 or STM8AF626x */

#ifdef STM8S903
  ITC_IRQ_TIM6_OVFTRI    = 23,  /*!< TIM6 update/overflow/underflow/trigger/
                                         interrupt */
#else
  ITC_IRQ_TIM4_OVF       = 23,  /*!< TIM4 update /overflow interrupt */
#endif /*STM8S903*/

  ITC_IRQ_EEPROM_EEC     = 24  /*!< Flash interrupt */
} ITC_Irq_TypeDef;

#endif // _STH8_H