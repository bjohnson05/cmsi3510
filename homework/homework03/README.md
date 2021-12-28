# CMSI 3510: Homework Assignment #3
## Problems Focusing on Deadlock, File Access, and Message Passing
### Assignment Due: Friday 2021-04-081 [Friday of week 13]

<blockquote>
Learning Outcomes: Students will:
    
1. Write a version of Dijkstra's <q>Dining Philosophers</q> program
1. Analyze why this version is immune to deadlock
1. Simulate a shell command, writing a <q>mini command line</q>
1. Learn about memory-mapped file handling
1. Experiment with message passing between threads
</blockquote>

### The following guidelines are expected for all homework submissions:

* All homework must be typed. Homework which is not typed will be returned ungraded and will be subject to the late homework guidelines as set out on the syllabus page.
* PLEASE DO NOT scribble something on lined paper and rip it out of your spiral notebook — hanging chads went out with the presidential election in 2000.
* I don't care too much about what font you use or how large your margins are; however, you might want to check out a monospaced font for typing code, as it will be easy to see the indentations.
* Speaking of indenting, **PLEASE DON'T USE TABS TO INDENT YOUR CODE**.  Tabs can often get interpreted differently by different computers and applications, and could make code that is nicely formatted on your computer look <q>all over the map</q> on my computer or printer. **USE SPACES INSTEAD**. You can set up almost every modern text editor to insert spaces whenever you press the TAB key, or you can simply pound the spacebar.
* **Work with a partner**. I can't stress this enough; part of this policy is don't split up the work – **WORK TOGETHER** on the assignment. This activity mimics an industry code development model called "pair programming" which is part of the Extreme Programming software development method. Feel free to collaborate in your pairs as much as you want, doing the entire assignment together.
* **DO NOT share your work between groups**. Doing so will count as plagiarism.  If you wish to discuss solutions with another group over coffee in the Lair, that's fine as long as it is kept at the conceptual and you don't share your code between groups.  Each group needs to turn in its own version of the solutions.
* You only need to turn in one copy per group.
* Submit your homework through GitHub, in your repository, and be sure to make me a contributor so I have been allowed access. I cannot evaluate what I cannot see! If I cannot upload to your repo, you will not get a grade for the assignment.

### Problems for Assignment #2
1. Write an implementation of the Dining Philosophers program, demonstrating deadlock avoidance.
1. Write a short paragraph explaining why your program is immune to deadlock?
1. Modify the file-processes.cpp program from Figure 8.2 on page 338 to simulate this shell command:
   <blockquote>
      tr a-z A-Z < /etc/passwd
   </blockquote>
   Write the code in C, not in C++.
1. Write a program that opens a file in read-only mode and maps the entire file into the virtual-memory address space using mmap. The program should search through the bytes in the mapped region, testing whether any of them is equal to the character X. As soon as an X is found, the program should print a success message and exit. If the entire file is searched without finding an X, the program should report failure. Time your program on files of varying size, some of which have an X at the beginning, while others have an X only at the end or not at all.
1. Read enough of Chapter 10 to understand the following description: In the TopicServer implementation shown in Figures 10.9 and 10.10 on pages 456 and 457, the receive method invokes each subscriber's receive method. This means the TopicServer's receive method will not return to its caller until after all of the subscribers have received the message. Consider an alternative version of the TopicServer, in which the receive method simply places the message into a temporary holding area and hence can quickly return to its caller. Meanwhile, a separate thread running in the TopicServer repeatedly loops, retrieving messages from the holding area and sending each in turn to the subscribers. What Java class from Chapter 4 would be appropriate to use for the holding area? Describe the pattern of synchronization provided by that class in terms that are specific to this particular application.
