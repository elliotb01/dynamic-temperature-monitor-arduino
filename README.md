<h1>Year 1 Semester 2 Coursework README</h1> 

<p align="center">
  <img src="https://miro.medium.com/v2/resize:fit:1400/0*fxa2PVq7rnWwv0RA" alt="arduinoreadmeimage" width="500" height="200">


Student ID: F424221

Full Name: Elliot Boberg

</p>

<h2>Dynamically Optimised Temperature Monitoring System using Arduino</h2>

<h3>Coursework Background:</h3>

<p>
  
In smart homes and IoT systems, temperature monitoring is ***essential*** for
energy efficiency.

When we using Arduino to collect data, we collect a fixed number
temperature data within a second, i.e., a fixed sampling rate. But a high
sampling rate wastes power when the temperature is stable.

Dynamic sampling optimizes energy use by adjusting the frequency of
readings.

This system will consist of three modes:

* Active Mode: The system enters this mode when rapid temperature
fluctuations are detected. In this state, the sampling frequency is
high, allowing for quick responses to environmental changes.

* Idle Mode: When temperature fluctuations are minor, the system
reduces its sampling frequency to a moderate level.

* Power Down Mode: If the temperature remains stable over an
extended period in Idle, the system further reduces its sampling
frequency to the lowest level

**My Goal:** *Design an adaptive system that intelligently adjusts sampling
rate and reduces energy consumption without losing accuracy*

<h3> **Explanation of my approach to the project** </h3>

I find when coding that I like to take an approach that revolves around block-based coding. I find this to be the best way for me to code as it keeps my workspace clear and concise while keeping all function that it needs. I have also found this to be a good
approach as it means that I make use of local variables, which makes good use of memory within my project.

Another method I find highly effective when working on larger projects that can be hard to follow are comments. I encorporated comments in each of my functions to detail what it does and what any confusing parts of the block do. I find this to be helpful as it
means that I can follow back through it whenever I need to without getting stuck on what a certain part of the assignment means. I find this to be a good habit to get into as it can help with how I think different parts of the project through when I have to go
back through it at a later date to change parts of it. (For example with Task 3 where I needed to add more code to my apply_dft() function at a later time.

</p>

This document will consist of sections documenting each task that I completed within my assignment

This will include both what I found difficult and what I found trouble-free.

<h1> SECTION 1 </h1>

<h2> Task 1 </h2>

<p> I got through Task 1 with relative ease due to researching about it before starting my coursework over Easter. I found this extrememly helpful as it meant I wasn't looking at different parts of GitHub coding for the first time. 

I did find Task 1.4 challenging due to it being hard to verify with more limited knowledge of GitHub however I found I learnt a lot completing this task.

</p>

<h3> Task 1.1 </h3>

I found Task 1.1 fairly simple as I followed the instructions then researched each question through online resources and lecturers.

<h3> Task 1.2 </h3>

I had no trouble with Task 1.2 as I followed the instructions and verified that it was working in correct fashion before moving forward.

<h3> Task 1.3 </h3>

Having done research into CodeSpaces I found Task 1.3 to be straightforward. It made sense to me as it was to check which branch you are currently on, move to a different branch, then delete the branch you were on a moment before.

<h3> Task 1.4 </h3>

I found Task 1.4 the most tricky as it was about merge conflicts which I had not seen before. I found it challenging but key to understanding how GitHub works.

<h2> Task 2 </h2>

<p> I found Task 2 to be quite uncomplicated due to it being based of taught knowledge. Because of this I was able to move through it fairly quickly. </p>

<h2> Task 3 </h2>

<p> I found Task 3 to be very challenging as it was using knowledge from a different module that was also quite difficult and putting them together. I found that understanding each formula and variable and exactly what they did within the equations and the code to be key to my solution. As mentioned above, I mainly use block-based coding to keep my work clear and concise with specific formatting meaning that you can see where each statement starts and ends as clearly as possible. </p>

<h3> Task 3.1 </h3>

<p> I found Task 3.1 very straight forward out of Task 3 as it was using code and knowledge that we already had used and implemented. </p>

<h3> Task 3.2 </h3>

<p> I found using the Discrete Fourier Transform to be confusing to immplement at first but rewarding once I had as it deepened my knowledge as I was working through each Task and seeing how it reacted to each variable I changed. </p>

<h3> Task 3.3 </h3>

<p> I found send_data_to_pc to be the easiest of the Tasks as it is using a for loop to print out each of the pieces of data in a suitable format. This was very straight forward and I found it the easiest to complete to a high standard. </p>

<h3> Task 3.4 </h3>

<p> I found decide_power_mode to be challenging as it meant I needed to add a lot of code to existing code as it required me to change the sample rate as different variables changed. </p>

<h3> Task 3.5 </h3>

<p> As this task was mostly covered in a lecture I made notes and had no problem completing this task. </p>

<h3> Task 3.6 </h3>

<p> Out of each of the Tasks I found 3.6 to be surprisingly challening due to my inexperience in python. I found this difficult because I have lots of experience in other langugaes such as Java and C whereas I haven't used python. Because of this I found it harder than the other tasks as it required a lot of research and looking at past lecturers/slides that were uploaded to get it right. </p>

<h2> Task 4 </h2>

<p> </p>
