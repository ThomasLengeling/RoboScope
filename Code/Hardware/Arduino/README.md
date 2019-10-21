# CAN Bus Protocol

Data Structure:

https://github.com/collin80/FlexCAN_Library

## Message Structure

### Sever Msg

  - Board id
    - [id] -> uint32_t
    - ````4 bytes -> [0-4294967295] or [0x00000000-0xFFFFFFFF]````
  - Message
    - buf[8] -> uint8_t array length 8
    - ````1 byte -> [0-255] or [0x00-0xFF]````
      - [0] - Motor id - 0 - 255
      - [1] - Motor dir - up/down
      - [2] - Motor step  - number of steps
      - [3] - Motor enable/sleep/activation
      - [4] - Motor limit switches
          - Limit switch up   (U)   ```[0000000U]```
             - On  - ```[00000001]```
             - Off - ```[00000000]```
          - Limit switch down (D)    ```[000000DU]```
             - On  - ```[00000010]```
             - Off - ```[00000000]```
      - [5] - Motor push/pull
      - [6] - Motor sensor 0
      - [7] - Motor sensor 1

### Flex CAN CAN_message_t

````
typedef struct CAN_message_t {
    uint32_t id;          // can identifier
    uint16_t timestamp;   // FlexCAN time when message arrived
    struct {
        uint8_t extended:1; // identifier is extended (29-bit)
        uint8_t remote:1;   // remote transmission request packet type
        uint8_t overrun:1;  // message overrun
        uint8_t reserved:5;
    } flags;
    uint8_t len;          // length of data
    uint8_t buf[8];
} CAN_message_t;
````
