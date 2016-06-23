from microbit import *

counter = 0
counterTriggered = False

while True:
    pin0_reading = pin0.read_analog()
    
    if pin0_reading > 0 and pin0_reading <= 100:
        display.show(Image.ARROW_N)
        counterTriggered = False
        
    if pin0_reading > 100 and pin0_reading <= 200:
        display.show(Image.HAPPY)
        counterTriggered = False
        
    if pin0_reading > 200 and pin0_reading <= 300:
        display.show(Image.ARROW_S)
        counterTriggered = False
        
    if pin0_reading > 300 and pin0_reading <= 400:
        if not counterTriggered:
            counter += 1
            counterTriggered = True

        display.scroll(str(counter))

    if pin0_reading > 400:
        display.show(Image.CONFUSED)

    sleep(40)
    