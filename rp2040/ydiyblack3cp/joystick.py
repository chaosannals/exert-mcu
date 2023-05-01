import time
import board
from analogio import AnalogIn

a2 = AnalogIn(board.A0)
a3 = AnalogIn(board.A1)

while True:
    x = a2.value
    y = a3.value
    print(f'{x}, {y}')
    time.sleep(0.4)