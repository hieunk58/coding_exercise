## This is an exercise
Reading from a text file then
* Compute position of all smiley characters
* Find top 10 used words
* Print result based on an option (console, text, xml, etc)

## Setup
Clone this repo to your desktop then install some dependencies.

3rd party library: googletest and pugixml
```
$ cd coding_exercise
$ mkdir lib
$ cd lib
$ git clone https://github.com/google/googletest.git
$ git clone https://github.com/zeux/pugixml.git
```
Create a cmake configuration file for generating code coverage.
First, create a folder `cmake` under project file `coding_exercise`.
Then create a file `CodeCoverage.cmake`.
Go to https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake, copy the content to `CodeCoverage.cmake`.
```
$ cd coding_exercise
$ mkdir cmake
$ cd cmake
$ touch CodeCoverage.cmake
```
Install gcovr in your computer (running Linux), run below command on terminal:
``` 
sudo apt-get install gcovr
```

## Build
Go back to main folder `coding_exercise`, create a `build` folder.
Then run cmake and make command to configure and generate execution files.
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Run app
Output file locates in `coding_exercise/bin`
```
$ cd bin
$ ./bmw_run
```
Enter path to the input file that contains text you want to test:
Ex: `/Users/example_user/Documents/input.txt`
Then select the way you want to see the result.
Ex: type `0` then hit `Enter` to see result in console only.

If you select print result to file (text and/or xml file), they will be generated and located at `coding_exercise/bin` folder with name is: `analyze_text_result.txt` and/or `analyze_text_result.xml`

## Generate Doxygen document
First, install doxygen in your computer (running Linux) by running below command on terminal:
```
sudo apt-get install doxygen
```

Then run below command to generate html document:
```
$ cd build
$ doxygen Doxifile.out
```
In folder `build/docs/html`, open `index.html` in your browser to view the document

## Run unit tests
After running make command above, a file name `unit_tests` is created in folder `build/tests`.
Run it to check unit tests result.

```
$ cd build/tests
$ ./unit_tests
```

## Generate Code coverage
```
$ cd build
$ make coverage
```
In folder `/build/tests/coverage`, open `coverage.html` to view the coverage report.

## Contact
If you have any problems or questions, feel free to drop me an email to khachieunk@gmail.com.









