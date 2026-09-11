# M5Stack Basic V2.7 + CardKB2 Terminal

A simple terminal demo for M5Stack Basic V2.7 and CardKB2.

Typed characters on the CardKB2 are displayed on the M5Stack screen.

## Hardware

- M5Stack Basic V2.7
- M5Stack CardKB2
- Grove cable

Connect CardKB2 to the red Grove Port A (I2C).

## CardKB2 mode

Set CardKB2 to I2C mode:

Fn + Sym + 1

The white LED should blink once.

## Arduino IDE

Board:

M5Core

Required libraries:

- M5Unified
- M5UnitUnified
- M5Unit-KEYBOARD

## Features

- Character input
- Backspace
- Enter/new line
- Simple on-screen terminal

## Wiring

M5Stack Basic V2.7 Port A:

- SDA: GPIO21
- SCL: GPIO22

