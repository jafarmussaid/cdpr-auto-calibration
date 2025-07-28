# CDPR Autocalibration Tool

This C program implements a simulation of an **autocalibration subsystem for Cable-Driven Parallel Robots (CDPRs)** based on event detection using instrumented cables and inductive sensors.

**Project**: CRAFT – Agile Manufacturing with CDPRs  
**Publication**: "Autocalibration Subsystem for Cable-Driven Parallel Robots" – [arXiv:2012.15586](https://arxiv.org/abs/2012.15586)  
**Author**: Jaâfar Moussaid

## Overview
The system estimates cable length and detects drift using:
- Metallic marks on cables (non-uniform spacing)
- Fixed inductive sensors at varying heights
- Simple event-time computation assuming constant velocity

## How to Compile
```bash
gcc auto_calibration.c -o auto_calibration
./auto_calibration
