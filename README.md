# Overview

<img align="right" width="150" src="./img.png">

WorkGround (wg) is a console tool that helps saving the currently open programs and files as a WorkGround and provides the ability to reopen all of them later with only one command.




# The main cocept explained
The main motivation for making this tool is to cut down on the time spent reopening programs and files that are usually used togather. Also, to make it easier to get back to work after restarting the PC for updates or after the "blue death screen".

# Real life example
Let's take, for example, a CS student, who studies math sometimes and develops c++ apps othertimes. So when studying math he would open the WorkGround named MATH102 which opens a calculus book on a pdf reader, professor leonard youtube channel,and the homework website on the browser, and maybe a scientific calculator program as well. However, when coding, he would switch to the WorkGround called CODETIME which would open VSCODE and his github page and c++ docs page on the browser and some music on media player.

Here wg makes all this happen with only one command : `wg switch MATH102 CODETIME`

# Usage
- `wg add wgName taskName taskPath`           \\\\ adds a task (Program) to a WorkGround
- `wg add wgName taskName fileName filePath`  \\\\ adds a file to be opened with the specified task (program)
- `wg run wgName`
- `wg swich currentWG otherWG`

# Feedback and contribution
If you are interested in the project's idea and have some feedback please drop them by on the issues page. Also if you are a developper interested in contributing to the project please do a pull request :)

*Note : to learn more about our progress please make sure to check [Project](https://github.com/mohasarc/WorkGround/projects/1) page as well as [Issues](https://github.com/mohasarc/WorkGround/issues) page.*
