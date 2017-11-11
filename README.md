# Hackaday Superconference 2017 Camera Badge project

This is a copy/fork/(whatever term you prefer) of the camera badge firmware running on the camera badge of Hackaday Superconference 2017.

https://hackaday.io/project/27427-camera-badge-for-supercon-2017

---

I was going to have a separate working document to note interesting things in code, to-do list, etc. But decided I'm going to do this right out in the open right in the README.md

---

*Needs research*:

* What's constraining the image size of what we've captured from the camera sensor? If it is frame-to-frame time - can we leverage the time available between time-lapse frames to capture higher resolution images? The camera buffer (declared in cambadge.h) is small, not clear whether it can be bigger.

* Should we keep the live camera view on the screen while taking the time lapse? What additional information might we want to display?

*cambadge.h*:

* **cambufsize** defined to be **dispwidth** by **dispheight**, which is right now 128x128. What's the reasoning behind these values? "That's the resolution of the screen"? "That's all the memory we have"? Other?
* Asked Mike Harrison for answer: memory. That's ~80% of what we have available on the PIC that can work at the speed required to keep up with the camera's DMA transfers. Since it was also the resolution of the screen, it was good enough. For higher resolutions we'd need to shuffle the memory out of the PIC and into other storage. This was the intent of the SRAM on the board, but Mike ran out of time to make that work. Right now, the SRAM is only accessed as part of the self-test. Not all hope is lost - the camera could be under-clocked to slow it down so the PIC can keep up with data processing. The bar code reader applicaton can be used as reference for this task.

*globals.h*:

* **powerdowntimer** - In order to prevent the camera from powering down from "lack of activity" while taking a time lapse, zero this out in our loop.
* **tick** - system tick seems to be the only way we have to measure time. (Approx. once every 20ms.) Time between each frame will have to be translated into number of ticks. And later (if we get the stretch goal of stepper integration) the stepper duration will also have to be in terms of ticks.
* **cam_enable** to start the camera, then **cam_grabenable** to start populating **cambuffer**. I see **cam_grabdisable** but I don't see a **cam_disable** or is it cam_enable(cammode_off)?
