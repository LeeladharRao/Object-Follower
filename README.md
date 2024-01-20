# Object Tracking Robot using compound eye

The function of this robot is simple, tracking the objects infront.
It uses dagu compound eye to detect objects, and the two pan and tilt servos are used to track the object.


## Motivation

A compound eye is a type of eye commonly found in arthropods, including many insects. It has a mesh-like appearance because it consists of thousands of small lens-capped optical units. Each unit has its cornea, lens, and photoreceptor cells for distinguishing brightness and color. The ommatidia are packed side by side into bulges that create a wider field of vision. As each unit is orientated in a slightly different direction, the eyes create an image which, although is poor at picking out detail but excellent at detecting movement.

Compared with single-aperture eyes, such as the human eye, compound eyes have a very large angle of view and the ability to detect fast movement and, in some cases, the polarization of light. Compound eyes generally allow only a short range of vision. For example, flies and mosquitoes can see only a few millimeters in front of them with any degree of resolution, although within this short-range they can see details that we could only see with a microscope.

So we wanted to create a model similar to that of the compound eyes seen in arthropods, because of its detection of minute details even in the harsh visibility conditions. We wanted to minimize the use of energy and since devices such as cameras and radars require the image to be processed it uses more energy for its computation. 


## Compund Eye Scematics

![image](https://github.com/LeeladharRao/Object_Follower/assets/52621705/d3f32c09-18f7-4049-8cfb-d1331d6a9334)

The eye consists of 2 pairs of IR LEDs and 4 pairs of phototransistors. The IR LEDs are connected to a general-purpose transistor which is used to switch the states of the LEDs. 

The LEDs and the phototransistor pairs are connected in parallel to increase their sensitivity. The phototransistor pairs are then connected to your analog inputs because the lens on the phototransistors is sensitive to light. 


## Robot Scematics

![image](https://github.com/LeeladharRao/Object_Follower/assets/52621705/1e77d41e-d3bc-4c10-8f30-6b849441a107)



## Working of Robot

![image](https://github.com/LeeladharRao/Object_Follower/assets/52621705/e8766b7a-dcc7-4cb3-aa34-cd6afdc04fc6)


## Expaination and more details can be found in documentaion
- Project Documentaion - [Docs](https://docs.google.com/document/d/1PrKL2NWZ1TO5HQHxZ-eH9C8yuVaONiERhi69CGsALjQ/edit?usp=sharing)

## Sources

- cyaninfinite - [Blog Post](https://cyaninfinite.com/hand-tracking-using-infrared-compound-eye/#:~:text=Infrared%20Compound%20Eye%E2%80%9D.-,How%20it%20works%3F,back%20to%20the%20arduino%20board.)
- robotshop - [Forums](https://www.robotshop.com/community/forum/)
- Ardiuno Nano Foums - [Forums](https://forum.arduino.cc/index.php?board=14.0)
- Robots-R-Us - [Page](https://www.robot-r-us.com)
- DistiBERT Documentaion - [Docs](https://huggingface.co/distilbert-base-uncased-finetuned-sst-2-english)


**Free Software, Hell Yeah!**
