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
The purpose of the project is to develop a simple version of th egame Mastermind(...) where the user can choose some settings for the game, like the dimension of the sequence to guess, the difficulty, the number of tentatives and the precence of doubles. Then the game starts and the purpose is to guess the sequence within the number of tries previously chosen. At every sequence inserted the system tells wheter the color is in the right position(O???), is in the sequence but in the wrong position(!???), and if it isn't present at all X???. 
- Describe shortly how the MSP432 is used<br><br>
The MSP432 board is used to take the input of 8 buttons setted up on an external breadboard with a very simple circuit

[Back to top](#table-of-contents)

---

# Project Layout

```
Mastermind
┣ general
┃ ┗ ...
┣ src
┃ ┗ ...
┗ ...
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

- Really brief description of what this is<br><br>

[Back to top](#table-of-contents)

---

# Installation and Configuration

## Setup IDE

- Customization of CCS after installation<br><br>

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
[X] - Complete<br>
[?] - To finish<br>
[!] - To start<br>
[*] - Consider expanding briefs<br><br>
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
    <th>X</th>
    <th>X</th>
  </tr>
  <tr>
    <th>chronology.c</th>
    <th>Cristoforetti Niccolò</th>
    <th>Gottardelli Matteo</th>
    <th>Cristoforetti Niccolò & Gottardelli Matteo</th>
    <th>?</th>
    <th>!</th>
  </tr>
  <tr>
    <th>difficulty.c</th>
    <th>Gottardelli Matteo</th>
    <th>-</th>
    <th>Gottardelli Matteo</th>
    <th>X</th>
    <th>X</th>
  </tr>
  <tr>
    <th>dimension.c</th>
    <th>Benassi Alessandro</th>
    <th>-</th>
    <th>Benassi Alessandro</th>
    <th>X*</th>
    <th>!</th>
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
