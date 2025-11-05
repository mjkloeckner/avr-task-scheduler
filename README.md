# Arduino Bare Metal Task Scheduler

This is a simple program that implements a task scheduler. It executes a series
of tasks attached to the scheduler after their specified task period (in
milliseconds) has passed.

In the example, four leds are controlled: two blink at different rates, and the
other two controlled by buttons.

## Dependencies

* `avr-gcc` and `avr-libc` to compile the code
* `avrdude` for uploading the program to the microcontroller

## Compile and upload to the board

Having the dependencies installed, compile the code running `make` or:

```console
$ make compile
```

Then with the board connected to the computer, check the port with:

```console
$ ls /dev/tty*
```

Often appears as `/dev/ttyUSB*` or `/dev/ttyACM*`, by default `/dev/ttyUSB0` is
used, to override this execute make assigning the corred port to the `PORT`
shell variable, for example:

```console
$ PORT=/dev/ttyUSB1 make upload
```
