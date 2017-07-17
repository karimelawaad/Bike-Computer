# Bike_Computer
A wireless bike computer, displays current speed and total distance travelled.
The computer consists of two parts:
  1- A magnetic reed switch connected to an arduino, that is used to detect a magnet placed attached to one of the spokes of the        front wheel. The arduino is used to measure the number of cycles per second then this number is sent to the other controller        using IR.
  2- An arduino that receives the number of cycles per seconds using a TSOP transceiver, calculates the current speed and displays      it on a Nokia 5110 LCD.

  
