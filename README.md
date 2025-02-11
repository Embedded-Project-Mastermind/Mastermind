# Mastermind

## Table of Contents
- [Introduction](#introduction)
- [Project Layout](#project-layout)
- [Software and Hardware Requirements](#software-and-hardware-requirements)
  - [Hardware Requirements](#hardware-requirements) 
  - [Software Requirements](#software-requirements)
- [Installation and Configuration](#installation-and-configuration)
  - [Setup IDE](#setup-ide)
  - [Import Project](#import-project)
  - [Import Libraries](#import-libraries)
  - [Run Project](#run-project)
- [Code Overview](#code-overview)
  - [Software Algorithm](#software-algorithm)
  - [Menu](#menu)
  - [Connectivity Sensors and MPS432](#connectivity-sensors-and-MSP432)
- [Work Contribution](#work-contribution)
- [Future Integrations](#future-integrations) 
- [Contacts](#contacts)
  
---

# Introduction
- Present the purpose of the project and its main functionalities<br>
The purpose of the project is to develop a simple version of the game Mastermind. It is a simple and funny game, where the user has to guess a sequence of colors within a certain number of attempts. Some settings for the game can be chosen wia an intuitive GUI, like the dimension of the sequence to guess, the difficulty, the number of tentatives and the presence of doubles. Then, after a summary page, the game starts and at every sequence inserted, the system tells wheter each color is in the right position([X]), is in the sequence but in the wrong position([O]), and if it isn't present at all ([!]). The clues given are also based on the difficulty levels, which are three. For the easiest mode, one all of these three are displayed, for the medium mode, the results are displayed as the correct number of O and X but in a casual order, while for the difficult there are onle X and ! and the X are put starting from the left for the number that is present in the entered sequence.
- Describe shortly how the MSP432 is used<br><br>
The MSP432 board is used to take the input of 8 buttons setted up on an external breadboard with a very simple circuit. each button has the pin which it's connected to and then it is connected to gtound on the other side. So when the button is released the internal pull-up resistor will put the value to high, while when the button is pressed the value will be low as it is connected to the ground.

Disegno del circuito e tabella con i pin
For the left side of the board, the connected pins related to the colors are the following:
<table>
  <tr>
    <th>Color</th>
    <th>Ground</th>
    <th>Orange</th>
    <th>Green</th>
    <th>Cyan</th>
  </tr>
  <tr>
    <th>Pin</th>
    <th>GND</th>
    <th>3.3</th>
    <th>4.7</th>
    <th>5.4</th>
  </tr>
</table>

For the right side the pins are:
<table>
  <tr>
    <th>Color</th>
    <th>Red</th>
    <th>White</th>
    <th>Purple</th>
    <th>Blue</th>
    <th>Yellow</th>
  </tr>
  <tr>
    <th>Pin</th>
    <th>3.0</th>
    <th>5.6</th>
    <th>6.6</th>
    <th>5.2</th>
    <th>3.6</th>
  </tr>
</table>

<img src="images/board_configuration.jpg" alt="Alt Text" align="right" width="200">

[Back to top](#table-of-contents)

---

# Project Layout

```
Mastermind
┣ .github/workflows                        
┣ .vscode                              
┣ LcdDriver
┣ html
┣ latex
┣ general                                  # All the source code
┃ ┣ bitmap.h                               # Link between peripherals and the microcontroller
┃ ┣ buttons.c                              # Manage physical buttons + "back" and "next" buttons
┃ ┣ buttons.h                              # Headers for buttons.c
┃ ┣ chronology.c                           # Manage the interface to show on screen the chronology of previous tentatives
┃ ┣ chronology.h                           # Headers for chronology.c
┃ ┣ difficulty.c                           # Manage the interface to select the difficulty of the game (from easy to hard)
┃ ┣ difficulty.h                           # Headers for difficulty.c
┃ ┣ dimension.c                            # Manage the interface to select 
┃ ┣ dimension.h                            # Headers for dimension.c
┃ ┣ doubles.c                              # Manage the interface to able/disable doubles in the sequence
┃ ┣ doubles.h                              # Headers for doubles.c
┃ ┣ end.c                                  # Manage the last interface, that can vary from a winning one to a losing one
┃ ┣ end.h                                  # Headers for end.c
┃ ┣ fsm.h                                  # Defines states, structures, and global variables for the finite state machine implementation
┃ ┣ game.c                                 # Manage the main interface where the user can guess the sequence
┃ ┣ game.h                                 # Headers for game.c
┃ ┣ gamelogic1.c                           # First part of the basic logic, with the password generation
┃ ┣ gamelogic1.h                           # Headers for gamelogic1.c
┃ ┣ gamelogic2.c                           # Second part of the basic logic, with the input management
┃ ┣ gamelogic2.h                           # Headers for gamelogic2.c
┃ ┣ gamelogic3.c                           # Third part of the basic logic, with the input and result elaboration
┃ ┣ gamelogic3.h                           # Headers for gamelogic3.c
┃ ┣ graphics.h                             # Defines graphics states, UI elements, colors, and structures for rendering on an MSP432 display
┃ ┣ implementations.c                      # Basic functions for the right functioning of all the interfaces
┃ ┣ implementations.h                      # Headers for implementations.c
┃ ┣ info.c                                 # Manage the interface that summarize all the game characteristics
┃ ┣ info.h                                 # Headers for info.c
┃ ┣ input.c                                # Handles input processing, port configuration, interrupt handling, and array management for the system
┃ ┣ input.h                                # Headers for input.c
┃ ┣ joystick.c                             # Handles joystick input, screen navigation, timer, delay, and ADC for embedded system joystick control
┃ ┣ joystick.h                             # Headers for joystick.c
┃ ┣ main.c                                 # Calls the various states in out state machine 
┃ ┣ start.c                                # Manage the first interface, with the start button and the logo
┃ ┣ start.h                                # Headers for start.c
┃ ┣ tentatives.c                           # Manage the interface to select the number of tentatives you want to have to guess the sequence
┃ ┗ tentatives.h                           # Headers for tentatives.c
┣ src                                      # Obsolete version, with only the basic logic and with console response
┃ ┣ fsm.h                                  # old version, but very similar to the newer one
┃ ┣ gamelogic1.c                           # Old version, with the password generation
┃ ┣ gamelogic1.h                           # Headers for gamelogic1.c
┃ ┣ gamelogic2.c                           # Old version, with the input management from the console
┃ ┣ gamelogic2.h                           # Headers for gamelogic2.c
┃ ┣ gamelogic3.c                           # Third part of the basic logic, with the input elaboration and result print on console
┃ ┣ gamelogic3.h                           # Headers for gamelogic3.c
┃ ┗ main.c                                 # Old version, calls the various states in out state machine
┗ read_me.txt                              # Implementations' instructions 
```

[Back to top](#table-of-contents)

---

# Software and Hardware Requirements
## Hardware Requirements
• MSP432P401R + BoosterPack (Link the documentation)<br>
• Breadboard<br>
• Buttons for Breadboard<br>
• Wires<br><br>
Suggested connection - Considering that the connections are done in order to avoid conflicts with other input sensors is recommended to use the ones below. To customize the color, you can modify it in the appropriate section in input.c, function ... lines...<br>
<table>
  <tr>
    <th>MSP432 pin</th>
    <th>Color</th>
  </tr>
  ...
</table>
- Description and image of how to build a working pressable button<br><br>

[Back to top](#table-of-contents)

---

## Software Requirements
• Code Composer Studio (Link)
Code Composer Studio (CCS) is an integrated development environment (IDE) designed for embedded systems, particularly for programming and debugging microcontrollers and processors. Developed by Texas Instruments, CCS supports a wide range of TI’s hardware, offering tools for writing, compiling, and testing code.
- Really brief description of what this is<br><br>

[Back to top](#table-of-contents)

---

# Installation and Configuration

## Setup IDE

After the installation of CCS, version 12.8.0, open the file `ccs_setup_12.8.0.00012.exe`.
On the opened window, press `next` one time. Accept the agreement and press `next` again four times.
Then, in `Select Components` select `SimpleLink™ MSP432™ low power + performance MCUs`.
In `Install debug probes` leave it as it clicking `next`.
To conclude, press `next` until the launcher begins the download.

(da finire)

[Back to top](#table-of-contents)

---

## Import Project

- How to import this project from GitHub to CCS<br><br>

[Back to top](#table-of-contents)

---

## Import Libraries

- How to import the necessary library to make the code work, the imports that prof told us<br><br>
The SIMPLELINK-MSP432-SDK library is needed to run the program. Download it at the following link:

[SIMPLELINK-MSP432-SDK Download](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)
 
1. Extract `simplelink_msp432p4_sdk_3_40_01_02.zip` file.  
2. Open **Code Composer Studio (CCS)** and left-click on the **Project Folder** to select **Properties**.  
3. Select **CCS Build**.  
4. Click **ARM Compiler** and then **Include Options**.  
   - 4.1 Add `"simplelink_msp432p4_sdk_3_40_01_02/source"` directory to the `"Add dir to #include search path"` window.  
5. Click **ARM Linker** and then **File Search Path**.  
   - 5.1 Add `"simplelink_msp432p4_sdk_3_40_01_02/source/ti/devices/msp432p4xx/driverlib/ccs/msp432p4xx_driverlib.lib"` to the `"Include library file..."` window.  


[Back to top](#table-of-contents)

---

## Run Project

- How to run the project on CCS<br><br>

[Back to top](#table-of-contents)

---

# Code Overview

## Software Algorithm

- FMS that we developed<br><br>

[Back to top](#table-of-contents)

---

## Menu

- FMS for the menu<br><br>

[Back to top](#table-of-contents)

---

## Connectivity Sensors and MSP432

- Sensors used<br>
- How they interface and react based on the system<br><br>

[Back to top](#table-of-contents)

---

# Work Contribution
🟢 - Complete<br>
🟡 - To finish<br>
🔴 - To start<br><br>
This is referred to the TODO section, search TODO in those files and fill the missing information<br>
<table>
  <tr>
    <th>Topic/Section</th>
    <th>Responsible Member</th>
    <th>Helper Member</th>
    <th>Maintainer Member</th>
    <th>Comments .c</th>
    <th>Integration .h</th>
  </tr>
  <tr>
    <th>buttons.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>chronology.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>Gottardelli Matteo</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>difficulty.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>dimension.c</th>
    <th>Benassi Alessandro</th>
    <th>-</th>
    <th>Benassi Alessandro</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>doubles.c</th>
    <th>Calvo Daniele</th>
    <th>Benassi Alessandro</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>end.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>game.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Benassi Alessandro & Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic1.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic2.c</th>
    <th>Benassi Alessandro & Calvo Daniele</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic3.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>implementations.c</th>
    <th>Gottardelli Matteo</th>
    <th>Cristoforetti Niccolò</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>info.c</th>
    <th>Calvo Daniele</th>
    <th>Gottardelli Matteo</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
   <tr>
    <th>input.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>joystick.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>main.c</th>
    <th>All</th>
    <th>-</th>
    <th>All</th>
    <th>🔴</th>
    <th>NONE</th>
  </tr>
  <tr>
    <th>start.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>Gottardelli Matteo</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>tentatives.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
    <th>🟢</th>
  </tr>
</table>

[Back to top](#table-of-contents)

---

# Future Integrations

- The possible integration the project could have<br>
• Connection with an ESP32 in order to display the game on another device<br>
• Sound Emition explaining how the combination gone<br>
• Theme customization<br>
...<br><br>

[Back to top](#table-of-contents)

---

# Contacts

- **Alessandro Benassi**  
  Email: [alessandro.benassi@studenti.unitn.it](mailto:name.surname@email.com)
- **Daniele Calvo**  
  Email: [daniele.calvo@studenti.unitn.it](mailto:name.surname@email.com)
- **Niccolò Cristoforetti**  
  Email: [n.cristoforetti@studenti.unitn.it](mailto:name.surname@email.com)
- **Matteo Gottardelli**  
  Email: [matteo.gottardelli@studenti.unitn.it](mailto:name.surname@email.com)
  
[Back to top](#table-of-contents)

---
