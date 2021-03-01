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
  // THIS WORKS!!!
  GPIO &portB = *reinterpret_cast<GPIO *>(0x23);
  portB.SetIO(1 << 5);
  while (1) {
    // // LED on
    portB.SetReg(1 << 5);
    _delay_ms(500); // wait 500 milliseconds

    // //LED off
    portB.SetReg(0);
    _delay_ms(500); // wait 500 milliseconds
  }
}
