Fall 2022 ECE 411 Practicum Project 

<ins>Group 11 Team Members/Project Authors</ins> 
* Cesar Ordaz-Coronel
* Charles Nasser
* Anthony Bruno

# NERD BOX - A Handheld Video Game Console
<p align="center">
  <img src="https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/blob/main/411documents/unrendered_nerdboxenclosure.PNG">
</p>
  
## Description:
This practicum project is for the development of a **Handheld Video Game Console**. This gaming device has buttons for users to interact with the device electronics and view game graphics/animations on the console's display. This device was designed for beginner-electronics users who want to code their own games (also build/modify/customize their own portable game console). The handheld game console is a portabe device with a simple interface for users.

<p align="center">
  <img src="https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/blob/main/411documents/nerdboxPCB3D_edited.png">
</p>

This handheld game console was designed with a simple user interface and at a affortable cost. The device contains 4 direction/navigation buttons, 2 action buttons, power switch, and a [QWIIC I2C](https://www.sparkfun.com/qwiic) connector for adding accessory sensors and devices such as an [accelerometer](https://www.sparkfun.com/products/17589) for motion control with the Handheld Video Game Console. The system uses a 3.7V 2000mah LiPo battery that is rechargable through the USB connection. The USB connection serves to not only charge the LiPo battery but also for user to upload their own coded games. This device uses the Arduino IDE (Processing language) to code games and upload/interact with the system electronics hardware. The gaming device has a 3D printed enclosure that can be modified for customized enclosure designs.

## Overview of Repository Folders/Files/Sections

* 411documents - contains all documentation for the this project over the course of 10 weeks. This folder contains Level 1 and Level 0 functional decomposition block diagrams for the device, Bill of Materials, Proposed project schedule (Ghantt Chart), Test plans, project ideas, the Product Design Specification (PDS), device electrical schematics, device PCB layout, and 3D printed CAD files.

* code - This folder contains any code that was generated to run the device, test the device, and debug the device during development. The software in this folder includes test programs, UI code for user, prototype code, and device video game code examples.

* hardware/console-hardware - This folder contains all electrical schematics, PCB layout, components, CAD project, and mechanical CAD files. This is the main folder for DIY building, fabrication, modifications, or reworking this prjoect.

* media - this folder contains all media related to this project. This includes test videos, debugging videos, test images and protoype images, demonstration videos, photos, etc.

* LICENSE file - The current license of this practicum project is CREATIVE COMMONS ZERO V1.0 UNIVERSAL. This is an Open-Source License and this project is dedicated to the public domain. This project can be copied, modified, distributed, and performance of work (including commercial purposes) without asking for permission. For more information on CC0 1.0 Universal - Public Domain Dedication, please follow this link: https://creativecommons.org/publicdomain/zero/1.0/

* README.md file - A markdown file (this file) that explains a majority of the files and folders of this practicum project. 

* Team Information - A markdown file that contains information about the team members of this practicum project.

## System Architecture - Block Diagrams
For more system architecture details, go to the [411documents](https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/tree/main/411documents) folder in this repsitory and view the [G11_L1blockDiagram.pdf](https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/blob/main/411documents/G11_L1_blockDiagrams.pdf) 

<p align="center">
  <img src="https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/blob/main/411documents/toplevel(level0)blockdiagram.drawio.png">
</p>

## [Demonstration & Operations Video Link](https://www.youtube.com/playlist?list=PLfQtabAE1AbKebFBLS851gg_HdHH0sS15)

## License
The current license of this practicum project is CREATIVE COMMONS ZERO V1.0 UNIVERSAL. This is an Open-Source License and this project is dedicated to the public domain. This project can be copied, modified, distributed, and performance of work (including commercial purposes) without asking for permission. For more information on CC0 1.0 Universal - Public Domain Dedication, please follow this link: https://creativecommons.org/publicdomain/zero/1.0/

## How to Download Project & Tools to Use
1) Go to the project [Repository](https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11)

2) Use one of the following options

### Option 1: Download ZIP
1) Click the GREEN "<>Code" dropdown.

2) Click on "Download ZIP".

3) After the download is complete, unzip the folder using [7zip](https://www.7-zip.org/), [PeaZip](https://peazip.github.io/), [WinZip](https://www.winzip.com/en/), or any other ZIP application.

### Option 2: Git Clone
If you know how to use Git/GitHub, you can clone the project repository
1) Click the GREEN "<>Code" dropdown.

2) Copy the https git link.

3) Open git bash on your current machine and move to the directly on your local machine where you would like to clone the project repository to.

4) type the following commands.

```
git clone [the http git link you copied, yoy can use SHIFT + INSERT for this]
```
Now you have a local repository for this project.

You can now access all files and documents of this project

## Tools For this Project
There are a few software tools that you will need in order to build, modify, or view the files in this project.

For the PCB design schematic, PCB layout, and any other items related to the electronics board, you can use any electronics CAD design and automation software. We highly recommend using [KiCAD EDA](https://www.kicad.org/) for this project, a free, open-source electronics CAD EDA.

For the 3D Printed enclosure the project includes STL files and an AutoDesk Fusion 360 Archive file. We recommend you use [Autodesk Fusion360 CAD](https://www.autodesk.com/products/fusion-360/personal) for the 3D printed enclosure, which is free for personal use.

For software development of the device and coding your own games, we recommend you use [Arduino IDE](https://www.arduino.cc/en/software). We also recommend reading the [tutorial for the 2.8" TFT LCD](https://learn.adafruit.com/adafruit-2-8-and-3-2-color-tft-touchscreen-breakout-v2/overview). We also recommend researching some of the libraries used in the original device program for more optimization (i.e [FloppyDerp_with_UI.ino](https://github.com/ECE411-Practicum-Group11/ECE411-PracticumProject-G11/tree/main/code/FloppyDerp_with_UI))

__IMPORTANT NOTE:__ If you plan to use Arduino IDE to upload your own programs and create your own code, you MUST burn the arduino IDE Bootloader to the ATmega32U4 Microcontroller in the project. We HIGHLY recommend you use an Arduino as an ISP for burning the bootloader to the IC. You can follow a tutorial on how to set this up and the burning process at [Arduino as ISP and Arduino Bootloaders](https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoISP).

__IMPORTANT NOTE:__ If you plan to use Arduino IDE to create code and upload to the Nerd Box, PLEASE set the "Board" under "Tools" dropdown to "Arduino Leonardo"!

## POWERING THE DEVICE!
....

## Assembly, Fabrication, Tests Tips & Notes

* We recommend using [Oshpark](https://oshpark.com/) to have your own PCBs fabricated and using [Digi-Key](https://www.digikey.com/) for components.
* If you have a 3D printer or printer service with fine detail/quality, you can modify the 3D enclosure with labels. Otherwise, you can use [decals](https://www.youtube.com/watch?v=YWCaCXiLDwo&t=260s&ab_channel=Tim%27sProjects) on the 3D Prints.
* The recommended screw size and type is a M2.2, self-tapping flat head screw that is roughly 16mm to 19mm in length. Here are some recommendations from McMaster-Carr: [Link 1](https://www.mcmaster.com/catalog/128/3273), [Link 2](https://www.mcmaster.com/catalog/128/3273)
* If you are planning to assemble the PCB yourself, we recommend that you solder a subcircuit first and then test with a bench power supply, then test with the LiPo battery. This ensures that everything will operate as expected. The order we recommend from the design schematics are: 3.3V Linear Regulator, LiPo Charger, USB Input Programming & Power, ATmega32U4 + ICSP, the rest of the components. Solder the LCD LAST! Also the board contains different test points. Reference the schematic on what each one does and utilize them in your testing!
* 
