# LPC1967_GPIO_Debugging_Capability
Fundamentals for Building MCU and GPIO Debugging Capability

# Purpose

This lab presents fundamentals for building a prototype board with two essential components, a power unit and CPU module, thereby setting the stage of subsequent labs towards designing a microprocessor system. 

The two objectives for CPU output and input are attained. The former establishes LPC1769 debugging capability by configuring and testing CPU GPIO outputs to turn ON/OFF two LEDs. The latter, continued by configuring and testing CPU GPIO input by enable a pin to read logic “1” and “0” using a toggle switch.

# Design Process

1) Generate Technical Specifications

2) Consult datasheets for Electrical Characteristics and pin configurations

3) Develop schematics for the circuit design

4) Physical implementation through wire wrapping and soldering techniques.

5) Refer to attached diagrams if you decided to use this setup.

# Orignal and Derived Equations:

Resistor-LED KVL circuit equation: V_cc = I_led + RV_led

Resistance to limit current through LED: R = (V_cc - V_led) / I_led

Ohm's Law ;) V = IR.

# Technology Stack

1) LCP1769 CPU module soldered onto prototype board with power unit

2) LPCExpresso IDE to program the device

3) LEDs, IN4003 DIODE

# Provided Headers 

LCP17xx.h and other header files are provided through NPX and the lab.
Refer to guide "Bringing Up LPCXpresso For Ubuntu Linux OS"
