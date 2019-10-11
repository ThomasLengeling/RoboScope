
# Protocol

Protocol bidirectional communication between server (USB CAN Bus) and client (Motor Controllers).


## Server Protocol

 USB Sender
 Motor information

 - Message includes dir, step of Motor
 -

## Client Protocol

- Process motor control information
- feedback from sensors, send back to USB


## Nodes

Each node is a motor control device which includes:

  - 8 or more motor drivers
  - Unique id
  -

The last node must include 120ohms between CAN HIGH and CAN LOW



### 32 Messages

Message 0 Motor Control
Message 1 LED, Switch, sensors

[0, 1] Motor 0
[2, 3] Motor 1
..
[30, 31] Motor 15
