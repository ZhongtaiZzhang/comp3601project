# COMP3601project
UNSW comp3601 project (i2s speaker and microphone)

## Group Members

1. Yuanxu Sou (z5292226)
2. Zhongtai Zhang (z5330019)
3. Thenuja Wijesuriya (z5343238)

## Hardware Components Used 

1. Pre-flashed Petalinux image with configured software and example bitstreams on SD card
2. KriaKV260andpower supply, ethernet cable, USB cable
3. UNSWCSEDesignProject A/B PMODboard 
4. Adafruit I2S MEMS microphone
5. Output Specker (Will be connected later for Hardware Audio Output project extension)


## Software Pre-requisites 

1. Vitis Vivado 2021.1
   - During installation, you need to choose to install the full Vitis package as it will be needed later in this course.
2. IfUbuntu: minicom, if Windows: Putty

## Project Description 

This project includes the comp3601 basic project requirement code, where we capture audio input from a microphone channel in out Hardware Kria KV260 Board and convert it to a .wav file and export it to the computer to be played. In our project extension we plan on connecting a speaker to output the sound captured directly from the hardware and also be able to play the sound from a .wave file.

As of now the comp3601 basic requirements have been almost completed. We have come across some issues with the sound not being played clearly on the computer but are working on fixing the bugs as soon as possible by the next project update.

## Startup Instructions (Hardware)

1. Open Vivado. Click on Create Project and click Next.

   <img width="696" alt="Screenshot 2024-10-23 at 3 19 51 pm" src="https://github.com/user-attachments/assets/f0441d73-b2fb-4bd6-9864-2ec730e9fdaa">

2. Set Project name and Project location and click Next.

<img width="529" alt="Screenshot 2024-10-23 at 3 20 06 pm" src="https://github.com/user-attachments/assets/75a75adc-89c9-48b2-9380-7c6902aab32b">

3. Select RTL Project. We will add the sources later so tick Do not specify sources at this time. Click Next.

<img width="532" alt="Screenshot 2024-10-23 at 3 20 20 pm" src="https://github.com/user-attachments/assets/3a1e4737-e914-409e-bd80-ff2fd1a2477e">

4. In the Default Part section, click on the Boards tab and type "kv" in the search bar. Select Kria KV260 Vision AI Starter Kit and click Next.

<img width="516" alt="Screenshot 2024-10-23 at 3 20 35 pm" src="https://github.com/user-attachments/assets/50e6c13a-4168-4647-b6f2-f5bd19764e5f">

5. Click Finish to create your project.

6. Once the project has been created click on 'Add Sources' + and import all our hardware code files and design one by one including the KRIA contraints.
   
## Startup Instructions (Software)

1. Use VScode or any other compatible code editor and copy our code files from the repository to the computer.
   
2. Copy all files in the software section including the 'include' folder and 'src' folder.
   
3. Once everything is read use a USB drive an copy the .c files from the computer to the USB drive.


## Conecting the USB drive to KRIA KV260 BOARD 

A normal USB drive would not be comptible with our KRIA KV260 board, so please watch this youtube tutorial linked below to help convert the USB drive to FAT32 format.

[Click here to watch the USB drive format conversion video](https://www.youtube.com/watch?v=abc123xyz](https://www.youtube.com/watch?v=s4EX5DMEZH0&t=223s)









