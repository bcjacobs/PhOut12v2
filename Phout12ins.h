#ifndef phout12ins  // always here. give a unique name for this library
#define phout12ins  // always here. give a unique name for this library

#if (ARDUINO >=100)  // always here
  #include "Arduino.h"  // always here. always this name.
#else  // always here. always this name.
  #include "WProgram.h"  // always here. always this name
#endif  // always here. always this name.

class Phout12ins  { // usually named the same as the header but it's not necessary
  public: // which functions do we want available to call from another program
    // Constructor -- when you create this object this is the thing to run
    Phout12ins(bool displayMsg=false); // false sets the default if there is no parameter entered. constructor must be the same name as the class
    const int switch_wait_time = 50;
    // Methods - the main code that runs. all methods need to be defined here
    void begin(int baudRate=9600);
    int readPin(int pin, int pedalType);
    String type(); 
    void toMidi(int controllerNumber, int channel);

  private: // to be used in the cpp but cannot be called in the main sketch. Also declare variables here (like count).
    bool _msg; // starting with an underscore is just a conventions for all private variables
    float varCounter();
    int _n0;
    int _scaled_n0;
    int _previous_n0;
    int _previous_scaled_n0;
    int _counter;
    int _typeValueHold;
    int _typeValue;
    String _type;
};
#endif  // always ends
