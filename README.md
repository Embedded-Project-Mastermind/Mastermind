<h1 align="center">Mastermind</h1>
<div align="center">
  <img src="images/logo.png" alt="logo" width="250">
</div>

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

| Video 1 | Video 2 |
|---------|---------|
| [![Video 1](https://img.youtube.com/vi/asKY3cJsWYA/0.jpg)](https://www.youtube.com/watch?v=asKY3cJsWYA) | [![Video 2](https://img.youtube.com/vi/Nvdm1BBGjmU/0.jpg)](https://www.youtube.com/watch?v=Nvdm1BBGjmU) |
| <p align="center"><b>Easy Mode Test<b> | <p align="center"><b>Medium Mode Test<b> |


The purpose of the project is to develop a version of the game Mastermind for the MSP432 microcrontroller, with the addition of the boosterpack and of eight external four pins buttons used for the color selection part. This game is intuitive and funny and its purpose is to guess a sequence of colors within a certain number of attempts. The settings for the game can be chosen via an intuitive GUI(Graphical User Interface), shown on the boosterpack's LCD display. These are the dimension of the sequence to guess, the difficulty of the game, the number of tentatives and the doubles option, which allows a color to be present multiple times in the key. Then, after a summary page, the game starts and with the external buttons the colors can be inserted. They will appear in some circles on the display and there is the possibility to withdraw the insertion with the upper button on the boosterpack, while the lower button is used to confirm the sequence when the insertion is terminated. After confirmation, the system tells whether each color is in the right position([X]), is in the sequence but in the wrong position([O]), and if it is not present at all ([!]). The clues given are also based on the difficulty levels, which are three. For the easy mode, all of the three corrections are shown, for the medium mode, the results are displayed as the correct number of X and O but in a quantity manner and in an order that is not associated with the colors like in the easy mode: the first displayed are the X, then O and ! for the remaining. For the hard mode there are only X and ! and they are shown as for the medium mode. The correction will appear under the circles in the main screen and by moving the joystick to the left it is possible to view the chronology of the past tentatives with the relative corrections. If the sequence is correctly guessed, a win screen will appear, otherwise when the user runs out of tentatives the game over interface will be displayed. To restart the game press the reset button on the MSP432 board.

<br><br>


[Back to top](#table-of-contents)

---

# Project Layout

```
Mastermind                   
┣ LcdDriver                                # Library support for GUI part of BoosterPack of MSP432
┣ html                                     # HTML files generated by Doxygen
┣ latex                                    # Latex files genreated by Doxygen
┣ general                                  # All the code that let the project work
┃ ┣ bitmap.h                               # Declaration of color palette and image logo
┃ ┣ buttons.c                              # Manage physical buttons + "back/cancel" and "confirm" buttons
┃ ┣ buttons.h                              # Headers for buttons.c
┃ ┣ chronology.c                           # Manage the interface to show on screen the chronology of previous tentatives
┃ ┣ chronology.h                           # Headers for chronology.c
┃ ┣ difficulty.c                           # Manage the interface to select the difficulty of the game (easy, medium, hard)
┃ ┣ difficulty.h                           # Headers for difficulty.c
┃ ┣ dimension.c                            # Manage the interface to select the dimension of the sequence
┃ ┣ dimension.h                            # Headers for dimension.c
┃ ┣ doubles.c                              # Manage the interface to able/disable color duplicate presence in the sequence
┃ ┣ doubles.h                              # Headers for doubles.c
┃ ┣ end.c                                  # Manage the last interface, that can vary from a winning one to a losing one
┃ ┣ end.h                                  # Headers for end.c
┃ ┣ fsm.h                                  # Defines states, structures, and global variables for the software logic finite state machine
┃ ┣ game.c                                 # Manage the main interface where the user can guess the sequence
┃ ┣ game.h                                 # Headers for game.c
┃ ┣ gamelogic1.c                           # First part of the basic logic, with the password generation
┃ ┣ gamelogic1.h                           # Headers for gamelogic1.c
┃ ┣ gamelogic2.c                           # Second part of the basic logic, with the input management
┃ ┣ gamelogic2.h                           # Headers for gamelogic2.c
┃ ┣ gamelogic3.c                           # Third part of the basic logic, with each tentative user's sequence elaboration
┃ ┣ gamelogic3.h                           # Headers for gamelogic3.c
┃ ┣ graphics.h                             # Defines graphics states, UI elements, colors, structures for rendering on an MSP432 display and graphics finite state machine
┃ ┣ implementations.c                      # Setup of program and general functions that are used by the various GUI interfaces
┃ ┣ implementations.h                      # Headers for implementations.c
┃ ┣ info.c                                 # Manage the interface that summarize all the game characteristics
┃ ┣ info.h                                 # Headers for info.c
┃ ┣ input.c                                # Handles input processing, port configuration and array management for the system
┃ ┣ input.h                                # Headers for input.c
┃ ┣ joystick.c                             # Handles joystick input, screen navigation, interrupt and timer intialization, delay, and ADC for embedded system joystick control
┃ ┣ joystick.h                             # Headers for joystick.c
┃ ┣ main.c                                 # Invokes the GUI state machine, then the software logic state machine and then manages the inputs. Handles the interrupts and the dynamic elements declaration
┃ ┣ start.c                                # Manage the first interface, with the start button and the logo
┃ ┣ start.h                                # Headers for start.c
┃ ┣ tentatives.c                           # Manage the interface to select the number of tentatives with which it is desired to play the game
┃ ┗ tentatives.h                           # Headers for tentatives.c
┣ src                                      # Essential version, with only the basic logic and console response
┃ ┣ fsm.h                                  # Software Version - Defines states, structures, and global variables for the software logic finite state machine
┃ ┣ gamelogic1.c                           # Software Version - First part of the basic logic, with the password generation
┃ ┣ gamelogic1.h                           # Software Version - Headers for gamelogic1.c
┃ ┣ gamelogic2.c                           # Software Version - Second part of the basic logic, with the input management
┃ ┣ gamelogic2.h                           # Software Version - Headers for gamelogic2.c
┃ ┣ gamelogic3.c                           # Software Version - Third part of the basic logic, with the input elaboration and result print on console
┃ ┣ gamelogic3.h                           # Software Version - Headers for gamelogic3.c
┃ ┗ main.c                                 # Software Version - Invokes the software logic state machine
┗ read_me.txt                              # Implementation instructions 
```

[Back to top](#table-of-contents)

---

# Software and Hardware Requirements
## Hardware Requirements
• MSP432P401R + BoosterPack (Link the documentation), we have different documentation for this project:
  1. [Launchpad user's guide](/documentation/Launchpad_MSP432P401R.pdf)
  2. [Microcontroller MSP432 documentation ](/documentation/Microcontroller_MSP432P401R-M.pdf)
  3. [Technical reference manual](/documentation/Technical_reference_manual.pdf)
  4. [DriverLib user's guide](/documentation/MSP432_DriverLib_Users_Guide.pdf)
  5. [Booster pack user's guide](/documentation/BoosterPack_connections.pdf)
  6. [Graphics Library 3.21.00.00 user's guide](/documentation/MSP_Graphics_Library_3.21.00.pdf) <br>
     
• Half size breadboard with 420 points(30 lines and 10 columns)<br>
• 8 Buttons for breadboard<br>
• 9 wires male to female and 8 wires for breadboard(male to male) to connect the buttons with the ground<br><br>
Suggested connection - Considering that the connections are done in order to avoid conflicts with other input sensors is recommended to use the ones below. To customize the color, you can modify it in the appropriate section in input.c file<br>
<table align="center">
  <tr>
    <th>Color</th>
    <th>Ground</th>
    <th>Orange</th>
    <th>Green</th>
    <th>Cyan</th>
    <th>Red</th>
    <th>White</th>
    <th>Pink</th>
    <th>Blue</th>
    <th>Yellow</th>
  </tr>
  <tr>
    <th>MSP432 pin</th>
    <th>GND</th>
    <th>3.3</th>
    <th>4.7</th>
    <th>5.4</th>
    <th>3.0</th>
    <th>5.6</th>
    <th>6.6</th>
    <th>5.2</th>
    <th>3.6</th> 
  </tr>
</table>

<table align="center">
  <tr>
    <td>
      <img src="images/board_configuration.png" alt="Board configuration" width="400">
    </td>
    <td>
      <img src="images/breadboard.png" alt="Board configuration" width="400">
    </td>
  </tr>
</table>
 <br><br>

The image on the right shows the configurations we used for the external buttons, which are related to specifical pins and so to the colors as described in the table above. The buttons used are four pins buttons and to avoid using them incorrectly we decided to wire them in a diagonal way. Each of them is wired to the designed pin with the pull up resistor, providing the 3.3V value and then on the other side it is connected to the ground. With this configuration we have all the pins to high and when we press the button it connects to ground and the value goes from high to low and so we have the input.

<br><br>
 
[Back to top](#table-of-contents)

---

## Software Requirements
**Code Composer Studio (CCS)** is an integrated development environment (IDE) designed for embedded systems, particularly for programming and debugging microcontrollers and processors. Developed by Texas Instruments, CCS supports a wide range of TI’s hardware, offering tools for writing, compiling, and testing code.
<br>

[Back to top](#table-of-contents)

---

# Installation and Configuration
• Install [Code Composer Studio CCS](https://www.ti.com/tool/download/CCSTUDIO/12.8.1) version 12.8.0
## Setup IDE

After the installation of **Code Composer Studio (CCS)**, version 12.8.0
1. Open the file `ccs_setup_12.8.0.00012.exe`.
2. On the opened window, press `next` one time. Accept the agreement and press `next` again four times.
3. Then, in `Select Components` select `SimpleLink™ MSP432™ low power + performance MCUs`.
4. In `Install debug probes` leave it as it clicking `next`.
5. To conclude, press `next` until the launcher begins the download.

[Back to top](#table-of-contents)

---

## Import Project

- How to import this project from GitHub to CCS<br><br>
Create workspace, repository, project from scratch:<br>
1) Create new workspace: File--> Switch worksapce --> Other . Type in or browse the directory name of the new workspace.<br>
2) Create a new project: File --> New--> CCS project:<br>
2.1) Select the target (MSP432 Family - MSP432P401R)
2.2) Select the connection (Texas Instruments XDS110 USB Debug Probe)<br>
2.3) Insert Project Name (Mastermind)<br>
2.4) Select a project template and project name (default will be Empty Project with main.c) --> finish
3) On Github download the project in .ZIP format in Code -> Download ZIP and then drop the files in general folder in the CCS project folder

[Back to top](#table-of-contents)

---

## Import Libraries

The **SIMPLELINK-MSP432-SDK** library is needed to run the program. Download it at the following link:
[SIMPLELINK-MSP432-SDK Download](https://www.ti.com/tool/download/SIMPLELINK-MSP432-SDK/3.40.01.02)
 
1. Run the `simplelink_msp432p4_sdk_3_40_01_02.exe` file.
2. Click `next` 3 times to begin the installation into the ti directory. <br>
      For windows user the folder will be in the C directory, while for MAC users it will be in the Application directory.
4. Open **Code Composer Studio (CCS)** and right-click on the **Project Folder** to select **Properties**.  
5. Select **CCS Build**.  
6. Click **ARM Compiler** and then **Include Options**.  
   - 6.1 Add `"C:\ti\simplelink_msp432p4_sdk_3_40_01_02\source"` (for Windows) directory to the `"Add dir to #include search path"` window. To add click on the icon highligted in green on the image below
7. Click **ARM Linker** and then **File Search Path**.  
   - 7.1 Add `"C:\ti\simplelink_msp432p4_sdk_3_40_01_02\source\ti\devices\msp432p4xx\driverlib\ccs\msp432p4xx_driverlib.lib"` to the `"Include library file..."` window.
   - 7.2 Add `"C:\ti\simplelink_msp432p4_sdk_3_40_01_02\source\ti\grlib\lib\ccs\m4\grlib.a"` to the `"Include library file..."` window.
<div align="center">
  <img src="images/simplelink_setup.PNG" alt="add" width="500">
</div>

[Back to top](#table-of-contents)

---

## Run Project
<div align="center">
  <img src="images/debug_icon.PNG" alt="debug" width="600">
</div>
To debug the project press on the debug button highligted in red in the image.
<div align="center">
  <img src="images/run_icon.PNG" alt="debug" width="600">
</div>
To run the project press the button highlighted in green. After that it is possible to play the game as explained in the [Introduction](#introduction)
<br>

[Back to top](#table-of-contents)

---

# Code Overview

## Software Algorithm
<div align="center">
  <img src="images/FSM.png" alt="fsm" width="400">
</div>

### Finite State Machine (FSM) - Game Flow

<table border="1" cellpadding="10" cellspacing="0" style="border-collapse: collapse; width: 100%;">

  <tr style="background-color: #f2f2f2;">
    <th>State</th>
    <th>Input</th>
    <th>Condition</th>
    <th>Output</th>
    <th>Signal</th>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>START</strong></th>
    <th>-</th>
    <th>Doubles</th>
    <th>🟢KEY_WH_DOUB<br>🔴KEY_WHOUT_DOUB</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      Setup the game by inserting the dimensions, difficulty, the number of attempts, and whether doubles are present in the sequence. Based on the doubles' presence, the next state is determined.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>KEY_WH_DOUB</strong></th>
    <th>START</th>
    <th>-</th>
    <th>RESET_TENT</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      Generate the sequence to guess with the presence of doubles.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>KEY_WHOUT_DOUB</strong></th>
    <th>START</th>
    <th>-</th>
    <th>RESET_TENT</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      Generate the sequence to guess without the presence of doubles.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>RESET_TENT</strong></th>
    <th>KEY_WH_DOUB<br>KEY_WHOUT_DOUB<br>ELABORATE_RESULT</th>
    <th>-</th>
    <th>WAIT_EMPTY</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      Reset the user sequence and start a new attempt for guessing.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WAIT_EMPTY</strong></th>
    <th>RESET_TENT</th>
    <th>-</th>
    <th>INSERT_COLOR</th>
    <th>Button_Input</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the sequence is empty, the user can insert a color into the sequence by clicking a button on the breadboard.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WAIT_NOT_EMPTY</strong></th>
    <th>INSERT_COLOR<br>ELIMINATE_COLOR</th>
    <th>-</th>
    <th>INSERT_COLOR</th>
    <th>Button_Input</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the sequence is not empty, the user can insert a color into the sequence by pressing a button on the breadboard.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>INSERT_COLOR</strong></th>
    <th>WAIT_EMPTY<br>WAIT_NOT_EMPTY</th>
    <th>Full</th>
    <th>🟢WAIT_FULL<br>🔴WAIT_NOT_EMPTY</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      After inserting a color, check if the sequence is full. If it is, go to the state `WAIT_FULL`; if not, go to `WAIT_NOT_EMPTY`.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WAIT_NOT_EMPTY</strong></th>
    <th>INSERT_COLOR<br>ELIMINATE_COLOR</th>
    <th>-</th>
    <th>ELIMINATE_COLOR</th>
    <th>Back</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the sequence is not full, the user can press the "Back" button to eliminate the last color added.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WAIT_FULL</strong></th>
    <th>INSERT_COLOR</th>
    <th>-</th>
    <th>ELIMINATE_COLOR</th>
    <th>Back</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the sequence is full, the user can press the "Back" button to remove the last color added.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>ELIMINATE_COLOR</strong></th>
    <th>WAIT_FULL<br>WAIT_NOT_EMPTY</th>
    <th>Empty</th>
    <th>🟢WAIT_EMPTY<br>🔴WAIT_NOT_EMPTY</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      After eliminating a color, check if the sequence is empty. If it is, transition to `WAIT_EMPTY`; otherwise, remain in `WAIT_NOT_EMPTY`.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WAIT_FULL</strong></th>
    <th>INSERT_COLOR</th>
    <th>-</th>
    <th>ELABORATE_TENTATIVE</th>
    <th>Confirm</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the sequence is full, the user can confirm their sequence. The system will then process the sequence.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>INCREMENT_TENTATIVE</strong></th>
    <th>ELABORATE_TENTATIVE</th>
    <th>Difficulty</th>
    <th>🟢EASY_MODE<br>🟡MEDIUM_MODE<br>🔴DIFFICULT_MODE</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      Increment the number of attempts and adjust the output based on the difficulty level chosen by the user (Easy, Medium, or Hard).
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>EASY_MODE</strong></th>
    <th>INCREMENT_TENTATIVE</th>
    <th>-</th>
    <th>ELABORATE_RESULT</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      The output will include symbols like `X` (correct color and position), `O` (correct color but wrong position), and `!` (color not in the sequence).
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>MEDIUM_MODE</strong></th>
    <th>INCREMENT_TENTATIVE</th>
    <th>-</th>
    <th>ELABORATE_RESULT</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      The output will include the same symbols as in Easy Mode, but colors will not be associated, and the symbols will be arranged in this order: `X`, then `O`, and finally `!`.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>DIFFICULT_MODE</strong></th>
    <th>INCREMENT_TENTATIVE</th>
    <th>-</th>
    <th>ELABORATE_RESULT</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      The output will include only `X` (correct color and position) and `!` (color not in the sequence), arranged in that order.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>ELABORATE_RESULT</strong></th>
    <th>EASY_MODE<br>MEDIUM_MODE<br>DIFFICULT_MODE</th>
    <th>1. Win condition<br>2. Tentative exceeds max</th>
    <th>🟢WIN<br>🔴(2. 🟢GAME_OVER<br>🔴RESET_TENT)</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      If the win condition is met, the player wins. If the maximum number of attempts is exceeded, the game ends, and the user is either reset or the game is over.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>WIN</strong></th>
    <th>ELABORATE_RESULT</th>
    <th>-</th>
    <th>-</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      The player has won the game.
    </td>
  </tr>
  
  <tr style="background-color: #f9f9f9;">
    <th><strong>GAME_OVER</strong></th>
    <th>ELABORATE_RESULT</th>
    <th>-</th>
    <th>-</th>
    <th>-</th>
  </tr>
  <tr>
    <td colspan="5" style="padding: 15px;">
      The player has lost the game.
    </td>
  </tr>
</table>



[Back to top](#table-of-contents)

---

## Menu
<div align="center">
  <img src="images/Workflow_GUI.png" alt="workflow" width="1000">
</div>
- FMS for the menu<br><br>

[Back to top](#table-of-contents)

---

## Connectivity Sensors and MSP432

Sensors used:<br>
- 128x128-pixel TFT LCD <br>
    - Supports display updates up to 20 frames per second (FPS).<br>
    - Controlled through the SPI interface.<br>
    - Has a color depth of 262K colors and a contrast ratio of 350.<br>
- 2 Boosterpack push buttons (upper & lower)<br>
    - Two potentiometers, one for each axis.<br>
    - read the voltage present on the joystick axis to provide the position of the joystick to the application.<br>
- 2-axis joystick<br>
    - are connected to pullup resistors that drive the BoosterPack plug-in module pin high until the button is pressed and the pin is driven low.<br>
- Pin.Port: 3.3, 4.7, 5.4, 3.0, 5.6, 6.6, 5.2, 3.6   [Hardware Requirements](#hardware-requirements) <br><br>

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
    <th>Status</th>
  </tr>
  <tr>
    <th>buttons.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>chronology.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>Gottardelli Matteo</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>difficulty.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>dimension.c</th>
    <th>Benassi Alessandro</th>
    <th>-</th>
    <th>Benassi Alessandro</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>doubles.c</th>
    <th>Calvo Daniele</th>
    <th>Benassi Alessandro</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>end.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>game.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Benassi Alessandro & Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic1.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic2.c</th>
    <th>Benassi Alessandro & Calvo Daniele</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro & Calvo Daniele</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>gamelogic3.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>implementations.c</th>
    <th>Gottardelli Matteo</th>
    <th>Cristoforetti Niccolò</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>info.c</th>
    <th>Calvo Daniele</th>
    <th>Gottardelli Matteo</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
  </tr>
   <tr>
    <th>input.c</th>
    <th>Gottardelli Matteo</th>
    <th>Benassi Alessandro</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>joystick.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>main.c</th>
    <th>All</th>
    <th>-</th>
    <th>All</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>start.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>Gottardelli Matteo</th>
    <th>Calvo Daniele</th>
    <th>🟢</th>
  </tr>
  <tr>
    <th>tentatives.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>-</th>
    <th>Cristoforetti Niccolò</th>
    <th>🟢</th>
  </tr>
</table>

[Back to top](#table-of-contents)

---

# Future Integrations
Possible integration the project could be:<br>
| 🔗 Improvement | 📝 Description |
|--------------|-------------|
| 🎮 **ESP32 Connection** | Connects with an ESP32 to display the game on another device. |
| 🔊 **Sound Emission** | Adds audio feedback explaining the outcome of each combination. |
| 🎨 **Theme Customization** | Allows players to customize the game's appearance. |
| ⏳ **Real-Time Engine** | Implements a system that enables pausing and resuming a game using the embedded system's main memory. |
| 💾 **Memory Extension** | Expands system memory to allow for more attempts (maximum of 8 due to hardware limitations). |


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
