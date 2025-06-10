For this project i am switching the board from the nuclio to the esc1, it can currently use the serial and i2c interfaces.

Importing and using the AS5600 lib works great i had to change the  i2c data and clock pins

```
    Wire.setSCL(PB8);
    Wire.setSDA(PB7);
    Wire.setClock(400000);
    Wire.begin();
```