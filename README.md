

<div style="text-align:center">
	<img src="./images/ji_logo.png" alt="Jilogo" style="zoom:60%;" />
</div>
<center>
	<h2>
		VG101 Intro to Computer
	</h2>
</center> 
<center>
	<h3>
		Project 3 OpenGL Part
	</h3>
</center>
<center>
   <h4>
       FA 2018
    </h4> 
</center>


------------------------------------------

### Abstract

This project is used to help our VG101 Project team work together. 

Once we open the source code for `18FA VG101 Project 3` and if you want to refer to our work, please follow the Joint Institute’s honor code and don’t plagiarize these codes directly.

### Introduction

#### PART1

This code can realize all the function required in milestone1 & milestone2 and milestone3.

We also add some extra designs such as the plate of each car, the type of each car and the slots specified for each type of vehicle. Every ticket printed contains many useful information and  the interface is redesigned to get a better visual effect. All the information demonstrated in the interface is rather clear and elegant compared with that in last version. We apply a virtual time system to our project this time since using real time makes the overall effect quite unrealistic and may cause confusion to anyone who is looking at our codes.

#### PART2

In the OpenGL part, all the basic functions have been implemented, as well as some bonus part.
1. We add a small flag to each car, the flag can move up and down when the car is still moving.(When the car stops in a slot, the flag will stop moving)
2. We add the track of each vehicle: the track will be demonstrated on the screen before the vehicle stops in a slot)
3. The car on the up-left corner can be controlled by operating on the keyboard(Please use the up, down, left and write buttons on the keyboard)
4. The animation of rockets and UFOs can only be seen when they are still moving(The animation will stop as soon as they stop in slots)
5. If you want to stop the whole animation, please press "Esc" on your keyboard.
6. The transporting gate is randomly set in the parking lot. If a car drives on into  transporting gate, it will be randomly sent to another slot.(This is NOT AVAILABLE for the car on the up-left corner!)
7. The number of the all the car is randomly set, but it won't be too big, which means it won't be painful for you to finish
watching the whole animation.

### The Basic Structure & Some Functions

#### PART1

As you can see, the basic structure is loop combined with linked-lists.

We implement two linked-lists in our code. The first one is for the slots in the parking lot; The second one is for the cars in the waiting line; Using linked-list improves the efficiency of our code and reduce some unnecessary workload. We write a special virtual time function to simulate the time flow instead of using real time directly. Actually, the mechnism is quite simple. It works by accelerating the flow of time. By doing so, we can make sure that the duration time printed on the tickets of each car in the parking lot won't be too small and cause trouble calculating the price. We also classify the slots into different types, corresponding to different types of vehicles. A function generating plates for each vehicle is also implemented.

#### PART2

The basic figures are all written using vector. The movement of the vehicles is realized by storing many tiny vectors.

### Future Works

1. Due to the rather urgent time, the name of several functions may contain spelling mistakes;
2. We believe there must be some underlying bugs and demerits there and we sincerely need your guidance.
3. The car on the up-left corner:
4. The animation is a little bit rough when we are manipulating it using keyboard. 
5. The size of our parking lot is fixed, we don't have enough time to make a better version with various choices of the size.

--------------------------------------------------------------------------------------------

Thanks for your time reading this file and evaluating our codes!