#  PCB design

## Boards

### Power

  Circuit that manages power regulation

### Motor

  Circuit that Controls the different motors

### Interface
  Interface Board that manages the mechanical activation of the motors

### Display (LED Box)
  Circuit the has the interaction for each road

### USB Bus
  Input Circuit for the boards.

## v0.2

## v0.1

### Modifications needed

### Motors driver controller.

- Connector between two boards.
- Add more though holes.
- position of the power source interfere with the interface board.
- smaller in the sides.
- Cable going add VCC 3.3 connector for sensor MUX
- Change outputs to the top board so that only one cable has all the signal configurations for the top switches and bottom switches.
- DIP switch incorrect size.
- 12 pin connector longer pads
- pads of motor control longer.
- Better connection for the power board
- Diode for protecting the teensy.
- Switch the VCC_MCU to VCC_M to have the some orientation as the Power Board.

### Power Board

- Possible corner redesign
- Space for the interface connecting board.
- Board is on top of the connectors to goes to the interacting board
- diode for protecting incorrect plug-in
- GND bridge from GND_IN to GND_M


### Box Circuit

- Sensor test on the top

### Interface board

- Design of the Board

### USB CAN Bus input


- Circuit for voltage 3.3 level shifter.
- Add the connection for the 3.3V voltage.
- Add Space between the cherry keys
- Remove one of the 120ohm resistors
