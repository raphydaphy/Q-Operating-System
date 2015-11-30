# Q-OS
[![Stories in Ready](https://badge.waffle.io/raphydaphy/Q-Operating-System.png?label=ready&title=Ready)](https://waffle.io/raphydaphy/Q-Operating-System)


Q OS is a versatile operating system designed with the new features of 64 bit "long mode" CPU's in mind that focuses on making everything as simple as possible for the end user. In designing it and, now, coding it, I have taken every aspect of what we consider to be a "Good OS" and removed everything that people find distracting and, in the end, simply useless.

If you just want to try the latest release of Q OS on your own system, click [here](https://github.com/raphydaphy/Q-Operating-System/blob/master/documentation/downloads.md) for some quick download links if you don't want to read this long file about Q OS. Otherwise, keep reading for lots of information about the planned features for Q OS.

By studying inexperienced people using operating systems such as Linux Distributions and the popular Windows and OS X systems through sources such as the OSFirstTimer channel on YouTube, I have decided on three key features that I will implement into Q OS as some of the key differences from current operating systems. Q OS is built from scratch using the Assembly language for the bootloader and parts of the kernel as well as C++ for the most part of the code. The main unique features I will be implementing into Q OS are as follows:


Tiny Files
----------


When we program in the 21st Century, we have so much more processing power and resources available than in the early days of computing that we often waste large portions of storage and CPU power just by writing inefficient and messy code. As computers continue to get more powerful, so will the level of inefficiency in a typical program such as a word processor where the programmers will save time while developing the software by writing - as I mentioned before - inefficient code that has no benifit whatsoever to the end user.


If we, as programmers, continue to let our code become more inefficient just because we are able to with such powerful computers that are available to nearly everybody in the world now, computers will have to cost more than they are actually worth because of the excessive computational power and storage space they will need to cope with such ineficient programming. An example of this incredible waste of storage space can be seen in how an entire program used to fit within a 64KB space on a disk, but now you can't even write a letter in that amount of space using a word processer such as Microsoft Word or Apple's 'Pages'. Obviously, applications have became more advanced, but so have the languages we have available to use to create them with. Theoretically this should allow us to create more advanced programs in only a little more space, but our bad habits as programmers have prevented this from happening.


In Q OS, I aim to solve this problem in two main ways. The first of which is by giving any computer with a freshly installed copy of Q OS (when it is complete) built in programs that suit most people's needs in computing such as a word processor, web browser, presentation and chart creation programs and other typical preinstalled software, but the entire package of built-in apps will all fit within less than a 1GB space. This is not even a very hard goal to acomplish when the right routines and programming habbits are adopted in order to create tiny code files.


Logical Extensions
------------------


For a long time, our files have been appended with what we know as a "File Extension". This is a simple, typically three leter long abbreviation that tells the computer what kind of file it is - for example, .jpg indicates a kind of photo, .mov is a video encoded with Apple's "QuickTime" encoder, .doc is a text document made using the "Microsoft Word" software, and so on.


But to an inexperienced computer user, what do all these extensions mean? I surveyed a random selection of around 100 people living in Melbourne, where I live, and less than 20 of them had any clue what the file extensions after a file actually mean. Even worse, less than 10 were able to translate certain extensions into what they meant!


Obviously this is not an ideal setup. In Q OS I am going to solve this by creating logical file extensions that are easy to understand even to someone who has only just touched a computer for the first time, and store the actual file type in the old format with three leter extensions only in the metadata of the file. Advanced users will be able to see the origional file extensions, but the file type itself is a completely different structure than in current systems so adapting to my design is a much better option if you plan to use Q OS for any extended period of time.


Some examples of my Logical Extensions are .photo for any photo file no matter if it is a photoshop file, a vector image, a .png image or any other kind of still picture, it will have the .photo extension. .movie is for anything that moves. Animations, .gif's, Films, Movies and more are considered a moving picture format and will be .movie. .code is a powerful new extension for us programmers. Whilst some programmers will be apprehensive to use this at first, it lets programmers and developers define the programming language, version and other metadata at the top of the file and also helps make your folders of code look neater and more beautiful with the same extension for every code file, from binary to html. There are many other Logical Extensions that I will be implementing into Q OS and I belive they will make file managment much easier.


Terminal Rethought
------------------


After over a decade of Unix-style terminals, many users will have began to discover the limitations of command line interaction with your computer. In Q OS, I am redesigning the command line interface from the ground up. This begins with over 2000 brand new commands. The most powerful of any of these is arguablely the new <code>do</code> command, however. Here is a brief example of what this powerful command lets you do with the forthcoming Q OS Terminal:


`do js for(i=0;i<10;i++) { console.log(i); }`

This is using the all new `do` command to execute javascript inside the terminal. The syntax for the `do` commmand is as follows:

`do language code`

Although the `do` syntax itself is simple to use, what you can create with `do` is incredible. The Terminal now allows you to create and store variables that are stored in memory until you close the window. But that's not even the best part. The `do` command supports a huge number of programming languages. Examine this command:

`do asm add eax, ebx`

Yes, Q OS even supports running Assembly Language code directly in the Terminal. All this power is possible by intergrating multiple language compilers into the Terminal that run when the correct `do` syntax is supplied by the user and generate an output when nessesary.


Custom Programming Language
---------------------------


Q OS is designed to be unique. It will be the first Operating System that can run on any device. It is the OS equivelant of a responsitive website. Resize the display and the OS will automatically change to suit the display you are using. Due to this, Q OS can be used as a Desktop OS, a Tablet OS, a Printer OS, a Smartwatch OS, a Smart Fridge OS or really an OS for Anything. That's the essense of what we are going to make Q OS become.


This is where we have a problem. There is no currently existing programming language that can execute Assembly-level code that will work on any CPU with any kind of device. This is because Assembly instructions are CPU specific, but Q Instructions are not. Yes - I am making a programming language for Q OS that will allow it to become the most configurable OS ever built if development continues at a steady pace and changes are rapidly made to improve the OS.


You can see the progress made for the Q Language in the [Q Programming Language](https://github.com/raphydaphy/Q-Programming-Language) GitHub repository. It will be a huge project to create the language and in no way is current work on Q OS that is written in C and Assembly going to be wasted - converting C code to simple Q code will be a rather simple process with little manual input required. But the point of Q is not to replace C for OS Development - it is to create an entirely new language that incorporates features seen in the highest level languages like Javascript and Java all the way to the very lowest language - Assembly.


Powerful Virtual Assistant
--------------------------

Q OS comes with a powerful and feature-filled virtual assistant, `Me`. `Me` is capable of doing almost anything that you are able to do on your Q OS computer. `Me` is invoked on the Q OS command line by entering a single and very simple word.

    me

The first time you run this command, `Me` will start the setup process. This is presented to the end user in a set of questions such as `What month were you born in?` and `What continent do you live in?`. Answering these questions is quick and easy, and your data is stored on your own Q OS system securely and never sent to the `Cloud` where it is far easier to hack using conventional methods.

If you want to try using `Me` without going through the (relativly short) setup process, you can do so by entering some quick arguments on the end of the `me` command.

    me setup skipper

This will result in some less accurate answers since they depend on the setup process but allows you to quickly test `Me` if you are in a hurry or don't want to give `Me` your personal information.

`Me` is incredibly intelligent due to one reason. When you ask `Me` a question, it performs six main steps.

* Break the question down into an array of words
* Decide what kind of word each word in the array is (verb, pronoun, adjective, etc..)
* Look at millions of previous questions and find similar ones
* Use this data to determine what words are referring to `important word` categories (locations, people, etc..)
* Look in the users database of information and find more about each `important word`
* Return a similar answer to previous answers of the similar questions found replacing user-sensitive data with that specific to the user that asked the question

This simple yet incredibly complex process used to get the answer of the question asked by the end user allows Me to respond to any question in a natural and advanced manor even if that exact question has never been asked before.
