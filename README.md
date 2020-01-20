# Overview

[![CodeFactor](https://www.codefactor.io/repository/github/mohasarc/workground/badge/master)](https://www.codefactor.io/repository/github/mohasarc/workground/overview/master)

GET https://dev.azure.com/moha981900/moha981900/_apis/build/repos/{repoType}/badge?api-version=5.1-preview.2

WorkGround is a windows application that saves the currently open workground and provides the ability to reopen them later, even after rebooting.

### WorkGround utilities

* Create WorkGround manually
* Automatically save current open tasks
* Switch between WorkGrounds


## Contributing

### You're always welcome to contribute

this is an open source project aiming to improve the open source comunity. Therefore, everyone interested is invited to contribute.

### The main cocept explained
the main motivation to create this application is to cut down on the time spent reopening the apps and files for specific job and the time spent switching from a "WorkGround" that is the set of tasks for a specific job and another WorkGround for another job. using WorkGround the user can store more than one workground, including all programms that the used uses togather and the files opened in each of them, and switch between them very easily. A real life examole might be of a web developper who switches between working on the graphic desgin of a website and the code developpement for the website, so one workground can have all graphic design tools and the other one can have all programmign tools.

### How does that work


### Progress so far ..

So far the app is a console app. it can show a menu. the user chooses an option and preceeds to another menu and so on. the menu is as follows: *tick sign indicated completion*


> Please select a choice (choose 1, 2, .. etc)
> * [X] 1- View and Mpdify WorkGrounds
> * [ ] 2- Switch current WorkGround
> * [ ] 3- Choose a default WorkGround
> * [ ] 4- start automatically after booting up
> * [ ] 5- other settings
> * [ ] 6- about
> * [ ] Q. Quit

through View and modify WorkGround is used to add a new WorkGround and modify existing ones as well as all tasks inside them. it has the following list: 
> Please select a choice (choose a, b, .. etc)
> * [X] a- View WorkGrounds (siplified)
> * [X] b- View WorkGrounds (elaborated)
> * [X] c- Add a WorkGround
> * [X] d- Modify a WorkGround
> * [X] e- Remove a WorkGround
> * [X] r- Return to previous menu

under choice d there is another menu

> select one
> * [X] a - rename WorkGround
> * [X] b - add a task
> * [X] c - remove a task
> * [ ] d - modify a task
> * [X] r - return to the previous menu
