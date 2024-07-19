Code for the HSTI baby incubator.

Instructions as of 19/07/2024 (This process should remain the same however buttons may be rearranged and called different things) For anyone who needs to download this for, firstly install git and vscode onto your device, or whatever other version control software you would like.

VScode: https://code.visualstudio.com/download git: https://git-scm.com/downloads

You can login to git using the git command prompt.

For the first person to copy over the code, intialise it into your own repository. Add all the participants into this repository (Search youtube/online how to do this - should be pretty easy)

Next, clone the repository onto your own device (On VScode, 3rd down on the left, the icon which looks like a branch, it will say clone repository). This should have downloaded all the code onto your device. Ensure you remember where download the file to make it easy for yourself! I recommend making a desktop file for ease.

If you havent already, download the arduino IDE. (You can try to install the arduino add-on and use vscode exclusively however I find it easier just to code in arduino and use vscode to commit and pull code.) I recommened opening the code_scratch.ino file. This should open all the .ino arduino files and the .h file.

Now we need to install all the libraries and be able to run the code.

Step 1: Click Select board -> Select other board and port (Its possible that the board already shows at this stage) -> Arduino Uno -> OK Step 2: Installing all the libraries required. (At this stage, if you have used Arduino before consider unistalling all your previous libraries to make it easier to manage this project).

    On code_scratch.ino, next to all the #includes the library name author and version are stated. (Some modules have many libraries of specific names so be carful which you download or else it work!)
    
    For example the line:
    #include "MAX30100_PulseOximeter.h" //Install <MAX30100_milan by OXullo v1.3.0>
    Look at <MAX30100_milan by OXullo v1.3.0> and search up MAX30100_milan (The words before by)
    
    
    Install all dependencies whenever it prompts you to.
    I have attempted to make it clear by adding a comment saying install then the information.
    Install them using the arduino library manager. (3rd icon down - Looks like books)
Step 3: There is none! Click the verify button (The tick) and hope no error occur.
