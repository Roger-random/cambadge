# Hackaday Superconference 2017 Camera Badge project

This is a copy/fork/(whatever term you prefer) of the camera badge firmware running on the camera badge of Hackaday Superconference 2017.

https://hackaday.io/project/27427-camera-badge-for-supercon-2017

---

I was going to have a separate working document to note interesting things in code, to-do list, etc. But decided I'm going to do this right out in the open right in the README.md

---

*Needs research*:

What's constraining the image size of what we've captured from the camera sensor? If it is frame-to-frame time - can we leverage the time available between time-lapse frames to capture higher resolution images?

*globals.h*:

* **powerdowntimer** - In order to prevent the camera from powering down from "lack of activity" while taking a time lapse, zero this out in our loop.
* **tick** - system tick seems to be the only way we have to measure time. (Approx. once every 20ms.) Time between each frame will have to be translated into number of ticks. And later (if we get the stretch goal of stepper integration) the stepper duration will also have to be in terms of ticks.
