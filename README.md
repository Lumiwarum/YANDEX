# PSS Homework

This program is the implementation of Yandex taxi program, where [assengers can request a ride and drivers can accept them.

## A version of the program 1.0

### how to run

CLion was used as the IDE for this project. If you have it, you will be able to open this project.
 However, no third-party libraries are used, other than the standard ones.

Version of c++20 were used.

To open it in Clion press File, than Open... and find this directory. Choose it and open.

![PSS%20Homework%2095c2dc4615d94f0589621bc9b42895f1/Untitled.png](PSS%20Homework%2095c2dc4615d94f0589621bc9b42895f1/Untitled.png)

![PSS%20Homework%2095c2dc4615d94f0589621bc9b42895f1/Untitled%201.png](PSS%20Homework%2095c2dc4615d94f0589621bc9b42895f1/Untitled%201.png)

# General ideas of program

program mainly consist from 3 classes:

- System: class that saves ans stores data into file called "Data.txt"
- PassengerGateway class created for passengers to work with program
- DriverGateway class created for driver to work with program

The program also has several files like "persons.h", where it stores classes of passengers and drivers, "WorldData.h" where I did specify special data structures, enums, and other things, that I needed

## features

program has many features, like getting distance of a ride,time, id of persons, but it would take a lot of time to show all of them, therefore i showed only important ones. However, you can check headers file and see how classes are implemented.

## Running program

to see work of the program you need just to run it. After first launch program will print message to the console and update Data.txt with Example.txt

You can check how data is saved into the file, after that rerun program. With each next rerun program will show you new cases of work and show how it work with saved data. After several iteration program will show all examples and will print message about it with names of the users.

As it said in the message - to rerun examples you need change value of the number in file called "Examples.txt" to 0 and rerun program.
