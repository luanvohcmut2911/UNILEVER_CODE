# UNILEVER_CODE
Code for rapsberry pi 4, includes :
- Control LED face
- face recognition for camera
- Run web on the screen 
- Send signal to the gift bag (send to arduino mega)
# USE RASPBERRYI PI 4 Model B
- Connect to power supply
- Wait until green led turn on constantly
- If not, check the link:
```bash
https://pimylifeup.com/raspberry-pi-red-green-lights/
```
# BAG_SIGNAL_TRANSMISSION
Replace STATUS with "on" or "off" 
```bash
cd ./BAG_SIGNAL_TRANSMISSION
python3 serial-link.py STATUS
```  

# FACE_LED
See video https://youtu.be/xSwoM3M24W8?t=489 to install rpi-rgb-led-matrix library
```bash
cd ./FACE_LED
python3 LEDMatrix.py
```

# FACE_RECOGNITION
```bash
cd ./FACE_RECOGNITION
python3 final-code.py
```
