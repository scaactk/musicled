# 看到下面代码，请不要怂，老规矩，你只需要修改有注释的地方
# 其他未备注的地方，看得懂代码的人，请自行修改，需要需要了解numpy,pyaudio

#conding = utf8
from __future__ import print_function
from __future__ import division
import os

DEVICE = 'esp8266'


if DEVICE == 'esp8266':
# 下面是你刚才在Arduino中为ESP8266设置的IP地址，不要填错了。
    UDP_IP = '192.168.2.150'
   
    UDP_PORT = 7777
  
    SOFTWARE_GAMMA_CORRECTION = False
 

if DEVICE == 'pi':
    LED_PIN = 18
   
    LED_FREQ_HZ = 800000
   
    LED_DMA = 5
   
    BRIGHTNESS = 255

    LED_INVERT = True
   
    SOFTWARE_GAMMA_CORRECTION = True
  

if DEVICE == 'blinkstick':
    SOFTWARE_GAMMA_CORRECTION = True
    

USE_GUI = True


DISPLAY_FPS = True

# 下面是你LED灯的数量，这个也不能搞错，错了，程序就运行出错！
N_PIXELS = 120


GAMMA_TABLE_PATH = os.path.join(os.path.dirname(__file__), 'gamma_table.npy')


MIC_RATE = 44100


FPS = 60

_max_led_FPS = int(((N_PIXELS * 30e-6) + 50e-6)**-1.0)
assert FPS <= _max_led_FPS, 'FPS must be <= {}'.format(_max_led_FPS)

MIN_FREQUENCY = 200


MAX_FREQUENCY = 12000


N_FFT_BINS = 24


N_ROLLING_HISTORY = 2


MIN_VOLUME_THRESHOLD = 1e-7

