# Design Diary
Use this space to talk about your process.  For inspiration, see [my prompts](../../../docs/sample_reflection.md) 

In order to keep track of the characters got from the file I stored them in a 2d vector. The storing of characters in the 2d vector was the most time consuming issue for me in this current milestone. I had never used a 2d vector before and the 2d concept was hard for me to comprehend at first. But after doing research on vectors and really understanding that I was creating a vector to hold vectors, then I was able to make progress. I read in the individual characters into the 1d vector and once a '\n' character was pushed back then the 1d vector was pushed back into the 2d vector. The 1d vector was then cleared and the next characters would be pushed into it. With this method I was able to easily get rows of characters into the 2d vector. 

For a future student, my advice would be too start early. I worked on this for at least couple hours everyday the past few days and I'm thankful that I did. This milestone took me four days to really understand how to implement it's requirements into my program. Also, take time to really think about all the logic involved in this program. Recording the contents of a file into a 2d vector, and especially adding those contents to the window, involved a lot of moving numbers around and keeping track of them. Scrolling also involved dealing with a lot of numbers and knowing where to put them logically. 

The most fun aspect of this project, and this is true for me for all projects, was chipping my way towards what I want the project to accomplish. But specifically for this project, I think scrolling was teh most fun part of the project to implement. I felt that scrolling was the easiest part of the milestone and I did it last, so all the heavy lifting was out of the way. However, understanding how to use the 2d vector was the most satisfying part of the project. It took me hours of thinking and experimenting to figure that one out. Plus, now that the characters are stored in a data structure I can manipulate them and do cool things such as scrolling.

Below is my gif:

projects/TextEditor/docs/images/Text Editor Milestone 2.gif
