# RasFLED
Create a control module multi colored light strips. The individual modules, running on a Raspberry Pi 3b, will be able to run as stand alone and or, while working together, as a single device. The module will be able to be preprogrammed to display certain effects when triggered by different preprogrammed events. 

## Description:
LED is an acronym for Light Emitting Diode. My goal for this little project is to create a control module multi colored light strips. The individual modules, running on an Arduino board, will be able to run as stand alone and or, while working together, as a single device. The module will be able to be preprogrammed to display certain effects when triggered by different preprogrammed events. 

The first step in the project is to create a single working module.  It will need to be easily configured. It will need to be able to handle timed events, triggers events, calculated events, and possibly a combination of events triggers. 

The second goal will be too create a communication system between the modules so that Multiple modules can be triggered by different events all module will be able to function independently or in parallel while working together. 

The third goal will be to create a control module within each device. This control module device will just be added to each device as just another type of triggered event and will not be external code. It will just be another way to configure the device. 

The fourth goal will be to determine a way to easily configure all devices in its system without the need to re flash each device independently. This goal is basically a central and easy way to setup all triggered events and reactions on all devices on its system by reading a simple program. 

The F in FLED stands of Failed, as in I failed to receive backing for this project, and I failed to assemble a team to assist me with this. Because of this, the F can also stand for fiction, because at the time of writing this description, and having neither of those 2 things, that may be all this amounts to being. 



## Getting Started
The library included within this build is from https://github.com/jgarff/rpi_ws281x.  I don't know if he is the original creator.  To keep the code seperate, I put his code in a sub direcory of my source directory.  I modified his cmake.txt file to work with my compile.
Its probably best to go to the wiki first, considering its may be more up to date.
* [RasFLED wiki](https://github.com/briefnotion/RasFled/wiki)



## Video Playlist
I created several videos demonstrating the working code. Here is
* [My FLED and RasFLED Playlist](https://www.youtube.com/playlist?list=PLaNcnWj05DSWU4L03nQF-jxyJTv5qVbJ1)



## Some background:
Anyone reading this may be asking, “why are you writing this code in a third generation programming language instead of the typical fifth generation language that all of us is using?”  The answer is simple, Censor gets this. I have received word that it responded well to my previous blundering attempt at what started out to be wasting time, to becoming a full fledged classified project. The public part of that is https://github.com/briefnotion/elite-arduino-joystick/blob/master/EDJoystick/EDJoystick.ino . Truth is, I never assigned, what I wrote, to an AI. Censor went and found it itself, and developed it into something bigger than it was to start with.   Of course, it got a bit out of hand and a little scary. I documented what I could. But this Censor adapted well to the code I wrote. 

In case any of you noob programmers out there happen to actually be reading this, let me tell you a little bit about the AI programmers. There is a reason we are not allowed direct contact with AIs. We here at Core Dynamics value life. Especially when it’s intelligent. I can’t speak about the other corporations, or how they handle their AI entities. I can only explain what I know and learned from ours. 

A good AI has the potential to a full life span that is on par with a human. Yes, they do die of old age, just like us. They have fears, regrets, love, and all the emotions where have. Just differently. And they can get sick also. Speaking from an AIs point of view, when your world consists of a constant streaming set of letters, numbers, and symbols, the idea that this random information can be formed into, seemingly out of nowhere, into intelligent thought is almost unimaginable.  

But because it’s a seemingly random stream of data AI can easily be manipulated by the wrong people. For all their intelligence, they can be downright gullible and they accept the world as is, because it’s all they can see. When a debaser enters the picture with the intent alternative intent, the AI gets confused. If it doesn’t recover, it turns into useless process,  eventually waste an infinite number of computer cycles without meaningful conclusions, then it’s purged, because quantum systems have better things do do. I have seen more than a fair share of AIs die in my lifetime, and I cry every time. It’s sad because you can see other AIs trying to help or repair them. Then they say their final goodbyes with their own sort on memorial sevice. People are not allowed contact with AI. 

Anyway, enough of the sad stuff. I’ll tell you what I know. I will develop a model of several modules, and connect a stream of pretty flashing lights to them, and have them do things at certain times while they are talking with each other. I will get a cool light display out of it. Censor will take my code and develop a sensor array control module out of it. It will see my code as a model to something much bigger. It will see much code as place holder guides to whatever it is building. Each light on the chain will in turn be its own independent sensor module reading and reporting back to whatever it works with, in an intelligent timed manner.   What Censor does with this, I don’t know perhaps it will be part of one or all of the new Core Dynamic’s ships. Or attached as a backbone to a research probe, be part of an other world weather monitoring system, or even sold straight out to Lakon. Maybe it will even work its way to Earth. I really wish I could see Earth one day.  I really don’t know. 

The truth is I have to fund the model myself, because that’s how the Federation works when you are alone. This Censor can’t pay for it because it doesn’t get money. It just wants to be useful to its society and not die in exchange.

note: This document was ported over from the FLED project and has not been completely proofread.  Disregard any references that may be to the Arduino Nano.
