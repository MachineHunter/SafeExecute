# SafeExecute Samurai (English Version)

## Summary
### SafeExecute Samurai is an software checker that Restrict and Visualize application execution.
SafeExecute provides safe execution to some unknown executable files and notify users with major Windows API calls used in some malware during their runtime. 
User is able to either continue it or interrupt it when any hook occurs. It's also possible to learn what API has been used on any applications you want to test with SafeExecute!

<span style=“color:green;”> text goes here</span>
### English GUI Interface is not yet implemented!

## Installation
1. Unzip our [latest released](https://github.com/MachineHunter/SafeExecute/releases) ".zip" file.
2. Start "SafeExecutorGUI.exe"

## Usage

![](./img/GUI_example.png)

1. Open "SafeExecutorGUI.exe"
2. Select your target executable file. If any argument is needed, you can input them in the second line. In the (1) part of above image.
4. Choose Mode. There are Normal mode with stdout, Error mode with stderr, and Interactive mode with messagebox showing, Interactive mode is suggested.
5. Click on the Windows API type you interested in.
6. Click "Run" and start!

<details>
   <summary>what is argument?</summary>
   
For example:
```sh
echo.exe "arg1"
```
After selecting echo.exe, you need to put the argument in the arguments section.
</details>




## Features
* Runtime Analysis
* Portable
* Self-Determination
* Understand Program Content
* User-Friendly Suggestion System

Compared to Anti-Malware or Anti-Virus system which often scan and detect executables in your computer, SafeExecute is a portable tool that does dynamic detection without using any dataset and Internet to support its functioning. For instance, Anti-Malware software may able to erase files when detect something malicious, however, the software does not tell the reason being suspicious, so if user wants to learn more about some malicious files, SafeExecute is the best choice that protect user by assisting user during the execution and provide an option to interrupt the target executables when found suspicious Windows API being called, also they can decide whether to continue or not by themselves, without any third-party's suggestions or judgements.
It's also a good tool for experienced researchers and programmers to investigate Windows executables!

## Important Files
* SafeExecute's Directory
    * **SafeExecute.dll**: Contains our hook methods, Windows API will be detected by our code and will not execute without the user's confirmation.
    * **SafeExecutor.exe**: A program combining hook methods and target executables with arguments, we can consider it as an input machine. Users can just use "SafeExecutorGUI.exe" when using!
    * **SafeExecutorGUI.exe**: GUI interface for SafeExecute.

* User Setting Directory (C:\Users\<username>\AppData\Local\安全実行侍～俺を信じろ～)
    * **logs/logs.csv**: Recorded execution results of every use.
    * **rules/mode.txt**: For command line users, 0 for normal mode, 1 for debug mode, 2 for interactive mode which is suggested. 
    * **rules/rules.csv**: For command line users, it shows every Windows API that can be hooked by SafeExecute. 1 for turn-on mode, 0 for turn-off mode.

## Command Line Usage
```sh
./SafeExecutor.exe SafeExecute.dll <path-to-executables>
```

## Showcase
Here is an example of executing a program that wants to open a url of Github. And we tried to allow all the APIs by clicking "yes".
As we can see, when we run this malicious application, it showed a warning about it's attemping to open a url by Windows API InternetOpenUrl and also its destination.

![](./img/InternetExample01.gif)

And here is the part when we reject its execution, the process stopped before Windows API call.

![](./img/InternetExample02.gif)

Here is an example of executing a fake ransomware we made that tries to encrypt all the ".txt" files in the path of input argument. And we all the APIs by clicking "yes".
As we can see, there are many pop up messages showing Windows API methods such as Encrypting, File Iteration, and Write Files, and there are also further information around these Windows API calls. Users can easily see what's happening and decide whether to continue or not before anything changes.

![](./img/FakeRansom01.gif)

And here is the part when we reject its execution, nothing happened to our files. Saved the day!

![](./img/FakeRansom02.gif)

## Behind the Scenes
SafeExecute uses an API hook to monitor target executable. Users are able to decide whether to continue or not when SafeExecute hooks any Windows API user select.
About how we produced this technique, here is an example code we programmed similar to our released code. Let's see through this example executable "hello.exe":

```c++
#include <windows.h>
#include <cstdio>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MessageBoxA(NULL, "Hello World!", "Info", MB_YESNO);
    return 0;
}
```

This program is really simple. It'll show a message box by calling Windows API "MessageBoxA", and this API is from library "user32.dll", so the process during runtime will look like the image below.

![](./img/callMessageBoxA.png)

About what we try to do in SafeExecute is that instead of getting the real "MessageBoxA", we covered the address of "MessageBoxA_Hook" ,which is our contribution in SafeExecute.dll, over the address of "MessageBoxA". The process during runtime will become like the image below.

![](./img/callHookedMessageBoxA.png)

You may somehow wonder what is inside "MessageBoxA_Hook", before calling the real "MessageBoxA" we added a message box that contains "yes" and "no" with some knowledge about the function calls being hooked, in that case users can figure out whether to continue or not by themselves, without any third-party's suggestions or judgements. If the user chooses not to continue, SafeExecute will easily call "ExitProcess" at that moment and end the process.

In many cases, SafeExecute will hook out many Windows APIs because of the wide variety of functionalities in a program or executable. You can still continue running by clicking "yes" every time a hook pops up, to make it personalize we also added a checklist which users can choose what kind of Windows API should be hooked, and the others will not.

I hope you enjoy using SafeExecute. Good Luck!




