
![IMG_4081](https://github.com/user-attachments/assets/98cea8a1-c04d-40e2-a1be-492f0e9fd885)

<img width="1180" height="643" alt="diagram" src="https://github.com/user-attachments/assets/a9851d84-312a-4a64-b1a0-32f0bf883d37" />

https://github.com/user-attachments/assets/afe560ff-7553-4b6f-b921-8f97e99f1ca4

https://github.com/user-attachments/assets/b9686ed6-812e-49c9-8ad5-d8d04812141b


# Blinky Project for TB-S3A3

## Overview
This project demonstrates a multi-threaded embedded application using ThreadX RTOS.
A total of 16 threads are implemented to control LEDs, process button inputs, handle serial communication, manage interrupts, monitor the watchdog timer, and perform message transmission tasks.

I made this project to learn and demonstrate RTOS concepts such as task scheduling, thread management, event handling, and peripheral control in an embedded system environment.

## Thread Configuration
- LED Control Thread 1-10
- Button Input Thread
- Messege Transmission Thread
- Messege Transmission Thread2
- Interrrupt Handlig Thread
- Watchdog Monitoring Thread
- SeialCommunication Thread

## Thread Description
- **LED Control Thread 1-10**
  - Independently control the ON/OFF state of each LED.
  - When the event flag is set, LEDs 1-10 blink sequentially.
  - Each LED turns on for 1 second, off for 30ms, then triggers the next LED via an event flag.
  
- **Button Input Thread**
  - The button input is evaluated based on press duration.
  - A long press (≥ 3 seconds) sets the event flag for the Message Transmission 2 thread, while a short press (< 3 seconds) sets the event flag for the LED1 control thread.
  
- **Messege Transmission Thread**
  - The Message Transmission thread sets an event flag every 3 seconds.
  - When triggered, the Serial Communication thread sends the string “abcd” via UART, which is displayed on Tera Term 5.
  
- **Messege Transmission Thread2**
  - When the button is pressed, the Message Transmission 2 thread is triggered by an event flag and transmits the string “efgh” via UART.
   - The data is received by the Serial Communication thread and displayed on Tera Term 5.
  
- **Interrrupt Handlig Thread**
  - An interrupt occurs every 3 seconds.
  - On the first interrupt, the timestamp is saved only (no transmission).
  - From the second interrupt onward, the elapsed time is calculated using the previous timestamp.
  - The calculated time difference is transmitted via UART and displayed on Tera Term 5.
    
- **Watchdog Monitoring Thread**
  - Runs every 4 seconds.
  - Checks the status of all threads.
  - Refreshes the watchdog timer only when all threads are operating normally.
  - If any thread fails to respond, the watchdog timer times out and the system is reset.
    
- **Seial Communication Thread**
  - Implements UART communication using mutex and semaphore control.
  - Mutex protects shared access for character and numeric data receiving functions.
  - Semaphore is used to control transmission timing to Tera Term 5.
  - Ensures thread-safe communication between multiple tasks.

  
## Development Environment
- **Board:** Renesas Synergy TB-S3A3
- **Sub Board:** Renesas Synergy PK-S5D9
- **IDE:** e² studio  
- **Framework:** Renesas FSP (RTOS-based)  
- **Language:** C
- **Serial Terminal:** Tera term 5
