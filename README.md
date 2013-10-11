CHESSINATOR
===========

A chess ai for use with [xboard](http://www.gnu.org/software/xboard/).

Goal is to keep the engine part modular so that anyone can fork the project and begin writing a chess ai without all the 
extra stuff like gui and crap taking time and space.


Running
-------
Compile the source using **make**, if this doesn't work you are likely missing something vital, like a compiler (gcc) or similar.
Make sure you have xboard installed and then run **xboard -debug -fd . -fcp './chess'**

Development
-----------
Logs are written from both xboard and this program if you run it with the command above, filenames are **io.log** and **xboard.debug**.

### Structure and execution
- The Chess class is the entry point with the main method.
- Chess calls for IoCommunicator to get a stdin input command (IoCommand)
- If IoCommand is a Move it should be parsed to the engine? (not done)
- If IoCommand is a Command it is passed to CommandHandler
- CommandHandler analyses command and should handle command aptly. (Just dummies so far)
- After handling the IoCommand CommandHandler returns a response IoCommand
- Chess gives this to IoCommunicator for sending to client (xboard) if command is not empty

### Documentation
This program so far has very little documentation. If this is to be added in some serious way I would suggest Doxygen. Used that before and it is rather simple.

Documentation for the protocol that xboard uses can be found here [http://www.gnu.org/software/xboard/engine-intf.html](http://www.gnu.org/software/xboard/engine-intf.html).

### Syntax
Try to keep to the syntax that is being used already.
When in doubt fall back to this: [google style recomendations](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml) 
it seems pretty decent and clean. That's what I do.

### Testing
We are using cppunit. If you provide code write test for it. Try to make as much code as possible testable
since minor bugs can be devastating in this kind of project/löogic.

### TODO:
- Enabled generating moves for both colors
- Board evaluation
- Transposition table?
- Better name for program?
