//#define _SFR_ASM_COMPAT 1
#ifndef F_CPU
#define F_CPU 16000000UL // or whatever may be your frequency
#endif

#include <stdint.h>
#include <util/delay.h> // for _delay_ms()

typedef uint8_t volatile dev_reg;

class GPIO {
public:
  void SetAllIO(uint8_t val) { ddr = val; }
  void SetAsOutput(uint8_t pins) { ddr |= pins; }
  void SetAsInput(uint8_t pins) { ddr &= ~pins; }
  void SetPins(uint8_t pins) { port |= pins; }
  void ResetPins(uint8_t pins) { port &= ~pins; }
  uint8_t Read() { return pin; }

private:
  dev_reg pin;
  dev_reg ddr;
  dev_reg port;
};


int main(void) {
  // THIS WORKS!!!
  GPIO &portB = *reinterpret_cast<GPIO *>(0x23);
  portB.SetAsOutput(1 << 5);
  while (1) {
    // // LED on
    portB.SetPins(1 << 5);
    _delay_ms(500); // wait 500 milliseconds

    // //LED off
    portB.ResetPins(1 << 5);
    _delay_ms(500); // wait 500 milliseconds
  }
}
