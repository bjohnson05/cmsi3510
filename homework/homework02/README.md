# CMSI 3510: Homework Assignment #2
## Problems Focusing on Threading and Synchronization
### Assignment Due: Friday 2021-03-11 [Friday of week 10]

<blockquote>
Learning Outcomes: Students will:
    
1. do some thought experiments about thread states, locking, and synchronization
1. experiment with the <code>bounded buffer</code>
1. check out some virtual addressing concepts
1. implement some virtual addressing code experiments
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

### Problems for Assignment #1
1. In the mutex-locking pseudocode of Figure 4.10 on page 111, there are two consecutive steps that remove the current thread from the runnable threads and then unlock the spinlock. Because spinlocks should be held as briefly as possible, we ought to consider whether these steps could be reversed, as shown in Figure 4.28 [on page 148]. Explain why reversing them would be a bad idea by giving an example sequence of events where the reversed version malfunctions.
1. Suppose the first three lines of the audit method in Figure 4.27 on page 144 were replaced by the following two lines:
   <blockquote>
      int seatsRemaining = state.get().getSeatsRemaining();<br />
      int cashOnHand = state.get().getCashOnHand();
   </blockquote>
   Explain why this would be a bug.

3. <strong>IN JAVA</strong>: Write a test program in Java for the BoundedBuffer class of Figure 4.17 on page 119 of the textbook.
1. <strong>IN JAVA</strong>: Modify the BoundedBuffer class of Figure 4.17 [page 119] to call notifyAll() only when inserting into an empty buffer or retrieving from a full buffer. Test that the program still works using your test program from the previous exercise.
1. Suppose T1 writes new values into x and y and T2 reads the values of both x and y. Is it possible for T2 to see the old value of x but the new value of y? Answer this question three times: once assuming the use of two-phase locking, once assuming the read committed isolation level is used and is implemented with short read locks, and once assuming snapshot isolation. In each case, justify your answer.
1. Assume a page size of 4 KB and the page mapping shown in Figure 6.10 on page 225. What are the virtual addresses of the first and last 4-byte words in page 6? What physical addresses do these translate into?
1. At the lower right of Figure 6.13 on page 236 are page numbers 1047552 and 1047553. Explain how these page numbers were calculated.
1. Write a program that loops many times, each time using an inner loop to access every 4096th element of a large array of bytes. Time how long your program takes per array access. Do this with varying array sizes. Are there any array sizes when the average time suddenly changes? Write a report in which you explain what you did, and the hardware and software system context in which you did it, carefully enough that someone could replicate your results.
1. Figure 7.20 [page 324] contains a simple C program that loops three times, each time calling the fork() system call. Afterward it sleeps for 30 seconds. Compile and run this program, and while it is in its 30-second sleep, use the ps command in a second terminal window to get a listing of processes. How many processes are shown running the program? Explain by drawing a family tree of the processes, with one box for each process and a line connecting each (except the first one) to its parent.
