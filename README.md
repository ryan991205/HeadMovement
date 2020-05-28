[![Build Status](https://travis-ci.com/ryan991205/HeadMovement.svg?branch=master)](https://travis-ci.com/ryan991205/HeadMovement)

# Robotic Head Movement
> functionality to control stepper and servo motors to control a head from a linux or windows embedded pc.



## Installation
- install arduino
- install visual studio code.
- install platformio within visual studio code `https://platformio.org/platformio-ide`
- clone the `code` to get started.

### Clone
- Clone this repo to your local machine using; https://github.com/ryan991205/HeadMovement/archive/master.zip
- Clone GPIO library ; https://github.com/ryan991205/Atmel328P_GPIO_C/archive/master.zip
- Clone tmc26xStepper library; https://github.com/interactive-matter/TMC26XStepper/archive/master.zip
- Clone Pololumaestro library; https://github.com/pololu/maestro-arduino/archive/master.zip

### Setup

- find your arduino library folder used by platformio and add the following librarys that you have cloned;
  - GPIO library
  - tmc26xStepper library
  - Pololumaestro library
- open platformio within visual studio copde and add the project (Headmovement).
  - Go to Platform io (PIO HOME) and click on open project
- when project is loaded switch to projects; here u can see Embedded\Headmovement project tab
  - click on configure to edit settings when needed. 

### Compile/upload
- Code can be compiled with Travis CI `code` 
- to compile simply press Platform IO logo and click build!
  - maybe you do need to select COM port first before uploading!
 
 
 
### Project Dependency 
```javascript
|-- <Communicator>
|   |-- <HeadControl>
|   |   |-- <MotorControl>
|   |   |   |-- <PololuMaestro> 1.0.0
|   |   |   |-- <SoftwareSerial> 1.0
|   |   |   |-- <Atmel328P_GPIO_C-master>
|   |   |   |-- <TMC26XStepper-master>
|   |   |   |   |-- <SPI> 1.0
|-- <MotorControl>
|   |-- <PololuMaestro> 1.0.0
|   |-- <SoftwareSerial> 1.0
|   |-- <Atmel328P_GPIO_C-master>
|   |-- <TMC26XStepper-master>
|   |   |-- <SPI> 1.0
|-- <HeadControl>
|   |-- <MotorControl>
|   |   |-- <PololuMaestro> 1.0.0
|   |   |-- <SoftwareSerial> 1.0
|   |   |-- <Atmel328P_GPIO_C-master>
|   |   |-- <TMC26XStepper-master>
|   |   |   |-- <SPI> 1.0
|-- <Atmel328P_GPIO_C-master>
|-- <PololuMaestro> 1.0.0
|-- <SoftwareSerial> 1.0
|-- <TMC26XStepper-master>
|   |-- <SPI> 1.0`
```
