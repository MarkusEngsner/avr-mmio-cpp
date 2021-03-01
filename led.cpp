//#define _SFR_ASM_COMPAT 1
#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>
#include <stdint.h>
//#include <type_traits>  // for is_standard_layout
#include <util/delay.h> // for _delay_ms()

typedef uint8_t volatile dev_reg;

class GPIO {
public:
  void SetIO(uint8_t val) {ddr = val;}
  void SetReg(uint8_t val) { port = val; }

private:
  dev_reg pin;
  dev_reg ddr;
  dev_reg port;
};

//static_assert(is_standard_layout<GPIO>::value, "GPIO isn't standard layout");

int main(void) {
  // Register<reinterpret_cast<volatile uint8_t*>(0x27)> ddrc{};
  // Register<0x27> ddrc{};
  // volatile unsigned int *ptr = (volatile unsigned int*)0x27;
  // typedef uint8_t volatile dev_reg;
  // dev_reg &PORTC = *reinterpret_cast<dev_reg *>(0x27);
  // uint8_t &PORTC = *reinterpret_cast<uint8_t *>(0x27);
  // THIS WORKS!!!
//  gpio &gpio1 = *reinterpret_cast<gpio *>(0x25);
//  gpio &ddrb = *reinterpret_cast<gpio *>(0x24);
  GPIO &portB = *reinterpret_cast<GPIO *>(0x23);
  portB.SetIO(1 << 5);
//  ddrb.SetReg(1 << 5);
  // Register<(volatile uint8_t *)0x27> ddrc{};
  // Register<PORTC> portc{};
  // ddrc.set_bits<0x01>();
  while (1) {
    // // LED on
    // PORTC = 0b00000001;            // PC0 = High = Vcc
//    gpio1.SetReg(1 << 5);
    portB.SetReg(1 << 5);
    _delay_ms(500); // wait 500 milliseconds

    // //LED off
    // PORTC = 0b00000000;            // PC0 = Low = 0v
//    gpio1.SetReg(0b0);
    portB.SetReg(0);
    _delay_ms(500); // wait 500 milliseconds
  }
}
