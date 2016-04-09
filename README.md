# QSDK-QEmu
This branch contains the 2.5-stable QEmu release with the QSDK addons.
Details about the project can be found here: https://github.com/gabriel-cr/pgback

# Compile and run
Compile:

```
./configure_qsdk.sh
make
```

Launch qemu-system-arm -machine help to list the machines. The Arduino board should be listed as 'arduino_board'.

 ```./arm-softmmu/qemu-system-arm -machine help```
 
Run QEmu with the demo found in device-repository. Make sure to point the -kernel argument to a binary file generated from Arduino

 ```./arm-softmmu/qemu-system-arm -M arduino_board -nographic -kernel ~/arduino_due.bin```
