# webioOP

Incomplete webiopi clone for OrangePi-PC/OrangePi-ZERO.

---

# Install WiringPi-Python-OP for OrangePi-PC
It also works with Orangepi-ONE / Orangepi-Lite / OrangePi-PC Plus.   
```
$ git clone --recursive https://github.com/lanefu/WiringPi-Python-OP.git
$ sudo apt install python-dev python-setuptools swig
$ cd WiringPi-Python-OP
$ cd WiringPi/
$ sudo ./build
$ cd ..
```


You need to modify "bindings.i" partially.


```
// Header file WiringPi/wiringPi/wiringPiSPI.h
int wiringPiSPIGetFd     (int channel) ;
int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
#int wiringPiSPISetupMode (int channel, int speed, int mode) ;
#int wiringPiSPISetup     (int channel, int speed) ;
```


In swig3, comments by # at the beginning of the line are no longer allowed. Change the above part as follows.

```
// Header file WiringPi/wiringPi/wiringPiSPI.h
int wiringPiSPIGetFd     (int channel) ;
int wiringPiSPIDataRW    (int channel, unsigned char *data, int len) ;
//int wiringPiSPISetupMode (int channel, int speed, int mode) ;
//int wiringPiSPISetup     (int channel, int speed) ;
```

If you modify "bindings.i", swig will pass.

```
$ swig -python wiringpi.i
$ sudo python setup.py install
$ cd tests
$ sudo python ./test.py
```

---

# Install WiringOP-Zero-Python for OrangePi-ZERO

```
$ git clone --recursive https://github.com/xpertsavenue/WiringOP-Zero-Python
$ sudo apt install python-dev python-setuptools swig
$ cd WiringOP-Zero-Python
$ cd WiringOP-Zero
$ sudo ./build
$ cd ..
$ swig -python wiringpi.i
$ sudo python setup.py install
$ cd tests
$ sudo python ./test.py
```

---

# Install flask

```
$ sudo apt install python3-pip python3-setuptools
$ python -m pip install -U pip
$ python -m pip install -U wheel
$ python -m pip install flask
```

---

# Execute webioOP for OrangePi-PC

```
$ git clone https://github.com/nopnop2002/webioOP
$ cd webioOP
$ sudo python ./webioOP.py
```

![webioOP-1](https://user-images.githubusercontent.com/6020549/62622407-3db4d580-b959-11e9-8427-8089cd5225b0.jpg)

---

# Execute webioOP for OrangePi-ZERO

```
$ git clone https://github.com/nopnop2002/webioOP
$ cd webioOP
$ sudo python ./webioOP-Zero.py
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

