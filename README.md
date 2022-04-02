# webioOP

An incomplete webiopi clone of the Orange-Pi series.

# Install flask on root

```
$ sudo apt install python3-flask
$ sudo apt install python3-pip python3-setuptools
$ sudo python3 -m pip -V
pip 18.1 from /usr/lib/python3/dist-packages/pip (python 3.7)
$ sudo python3 -m pip install -U pip
$ sudo python3 -m pip -V
pip 22.0.4 from /home/orangepi/.local/lib/python3.7/site-packages/pip (python 3.7)
$ sudo python3 -m pip install -U wheel
$ sudo python3 -m pip install flask
```

# Install WiringOP library provided by xunlong
Install from [here](https://github.com/orangepi-xunlong/wiringOP).


# Build python wrapper
```
$ sudo apt install python3-dev python3-pip
$ git clone https://github.com/nopnop2002/webioOP
$ cd webioOP
$ python3 setup.py build
$ sudo python3 setup.py install
$ python3 -m pip list -l | grep Gpio
GpioMethod          1.0
```

# Test python wrapper
```
$ sudo python3 ./gpio_test.py
```


# For OrangePi-PC

```
$ cd $HOME/webioOP
$ sudo python3 ./webioOP.py
```

![webioOP-1](https://user-images.githubusercontent.com/6020549/62622407-3db4d580-b959-11e9-8427-8089cd5225b0.jpg)

---

# Other than Orange Pi-PC
Edit this.
```
$ vi webioOP.py
import opi_pc
#import opi_pc2
#import opi_pc3
#import opi_pc4
#import opi_zero
#import opi_lite2

PINS = opi_pc.PINS
#PINS = opi_pc2.PINS
#PINS = opi_pc3.PINS
#PINS = opi_pc4.PINS
#PINS = opi_zero.PINS
#PINS = opi_lite2.PINS
```

![webioOP-ZERO-1](https://user-images.githubusercontent.com/6020549/63645268-3c472380-c735-11e9-9ecd-2ee9aac2cfcc.jpg)

---

# Change look & feel

```
$ cd template
$ cp webioOP.html.btn webioOP.html
$ cd ..
$ sudo python ./webioOP.py

```

![webioOP-2](https://user-images.githubusercontent.com/6020549/62622408-3db4d580-b959-11e9-853a-9339ca9ad983.jpg)



```
$ cd template
$ cp webioOP.html.icon webioOP.html
$ cd ..
$ sudo python ./webioOP.py

```

![webioOP-3](https://user-images.githubusercontent.com/6020549/62622406-3d1c3f00-b959-11e9-8c49-7dd4d99e4b32.jpg)

