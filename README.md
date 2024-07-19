Code for the HSTI baby incubator.

Instructions as of 19/07/2024 (This process should remain the same however buttons may be rearranged and called different things) For anyone who needs to download this for, firstly install git and vscode onto your device, or whatever other version control software you would like.

VScode: https://code.visualstudio.com/download git: https://git-scm.com/downloads

You can log in to git using the git command prompt.

For the first person to copy over the code, initialise it into your repository. Add all the participants into this repository (Search YouTube/online how to do this - it should be pretty easy)

Next, clone the repository onto your device (On VScode, 3rd down on the left, the icon which looks like a branch, will say clone repository).
It will prompt you to put the URL of the repository you want to copy in or log in to git to then choose to repository. It will only show the repository as an option if you are added to it as an editor.

This should have downloaded all the code onto your device. Ensure you remember where to download the file to make it easy for yourself! I recommend making a desktop file for ease.

If you haven't already, download the Arduino IDE. (You can try to install the Arduino add-on and use vscode exclusively however I find it easier just to code in Arduino and use vscode to commit and pull code.) 
Now open the code_scratch.ino file. This should open all the .ino Arduino files and the .h file.

Now we need to install all the libraries and be able to run the code.

Step 1: Click Select board -> Select other board and port (It is possible that the board already shows at this stage) -> Arduino Uno -> OK 

Step 2: Installing all the libraries required. (At this stage, if you have used Arduino before consider uninstalling all your previous libraries to make it easier to manage this project).

    On code_scratch.ino, next to all the #includes the library name author and version are stated.
    Some modules have many libraries of specific names so be careful which you download or else it works!
    
    For example the line:
    #include "MAX30100_PulseOximeter.h" //Install <MAX30100_milan by OXullo v1.3.0>
    Look at <MAX30100_milan by OXullo v1.3.0> and search up MAX30100_milan (The words before by)
    
    
    Install all dependencies whenever it prompts you to.
    I have attempted to clarify by adding a comment saying install then the information.
    Install them using the Arduino library manager. (3rd icon down - Looks like books)
    
Step 3: There is none! Click the verify button (The tick) and hope no error occurs.


You can now edit the code in Arduino IDE and commit push/pull using VSCode.
You can now connect the whole board and upload code. COM port may need to be changed.
