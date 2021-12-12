# Multi-Sensor-Fall-Detection-Device
## What is it?
The Multi-Sensor Fall Detection Device (MSFDD) is an innovation on current fall detection alternatives on the market. It attacks three main concerns that are not addressed by the current options: the user not being able to push a button; the technology being too complicated; and the user forgetting to wear the device. The device is powered by an Arduino Uno Wifi, and reads inputs from an accelerometer and microphone.
</br>
 ![image](https://user-images.githubusercontent.com/67702022/145734057-3c87310b-5151-4662-b973-66608a5eb3ae.png)

## Why is the Problem Important?
According to the CDC, over 25% of people above the age of 65 fall every year, and over 20% of those falls lead to serious injury. However, the problem does not stop there as less than half of seniors who experience falls notify healthcare workers of the incident. This could prove fatal in some cases, such as if blood thinners are continually used following a head injury. It is common for the fear of falling to develop for seniors. In fact, in a study conducted on 487 elderly subjects living independently, 32% of those who fell reported the development of a fear of falling.  

## How Does it Work?
When the device is active and attached to the user's wrist, the accelerometer begins reading the user's acceleration and compares the magnitude to a predefined threshold. If that magnitude exceeds it, then a fall is deemed to have occurred. Using this method, the device has an 80% success rate for accurately detecting falls, with a mere 3% false negative rate. After a fall is detected, the LCD's countdown sequence begins, which provides a 10s window for users to reset the device on false positives.</br>
After the countdown sequence ends, the Arduino contacts an SMTP server whcih then sends an email to designated emergency contacts, notifying them that a fall has occurred and help is potentially needed.</br>
If the device is active, but not being worn (acceleration would read 0), the microphone's fall detection algorithm is active. With this, falls are detected as excessive differences between consecutive audio samples with a 10% false negative rate. If a fall is detected, then the LCD and SMTP process is executed in the same way as the accelerometer.

## Future Iterations
There is a lot of work that needs to be completed before the MSFDD can be market-ready. These include:
- Converting the Arduino-based prototype into a microchip and custom PCB to increase efficiency and decrease size
- Implementing machine learning to detect falls instead of using the threshold algorithms to increase the success rate
- Increasing sampling rate for the microphone to get clearer input and increase consistency of catching falls
- Using an SMS API instead Email to increase urgency of notification
- Designing custom housing for the MSFDD to allow for easy transportation and to protect it from accidental damage 
