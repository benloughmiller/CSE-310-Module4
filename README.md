# Overview

This program is a task list. It allows you to create tasks, view them, and then complete them. There are two kinds of tasks currently, standard tasks which can be completed once, and tasks that can be completed multiple times. It allows the user to view incomplete and complete tasks, as well as make progress on the tasks, completing them if the number of needed completions is reached. It reads/writes tasks from a csv file, ensuring that data is preserved if the program is closed out. 

The purpose of this software is to show an example of how C++ can be used in app development. It also shows how C++ can read and write to files, interacting with the data contained inside.

[Software Demo Video](https://youtu.be/ZXfED3c0o-E)

# Development Environment

I used VSCode to write this program. I used the C++ language and the MinGW compiler to create and test the program. The creation of this project was AI assisted, mainly in the functions that read/write to the file. 

I used these libraries: vector, string, sstream, iostream, fstream, limits

# Useful Websites

- [CPlusPlus](https://cplusplus.com/doc/tutorial/files/)
- [W3Schools](https://www.w3schools.com/cpp/)

# Future Work

- Add permanent tasks that can be repeated infinitely, with a count of their total completions
- Add daily tasks that refresh each day
- Separate program into multiple class files