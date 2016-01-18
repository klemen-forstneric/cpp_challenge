# cpp-challenge setup

**Guide assumes Ubuntu Server 14.04.3 is freshly installed.**

First we add these PPA's to get more recent versions of ZeroMQ and OpenCV:

`sudo add-apt-repository ppa:chris-lea/zeromq`

`sudo add-apt-repository ppa:chris-lea/libpgm`

`sudo add-apt-repository ppa:amarburg/opencv3`

We install the compilers, Git, OpenCV, ZeroMQ, OpenCV, Google Test and everything they depend on:

`sudo apt-get update && sudo apt-get install g++ gcc build-essential git libgtest-dev cmake libzmq3-dev libzmq3 libopencv3 libopencv3-dev`

Ubuntu stopped distributing a prebuilt version of Google Test so we must build it ourselves:

`cd /usr/src`

`cp -R gtest ~/`

`cd ~/gtest`

`mkdir build && cd build`

`cmake ..`

`make`

Now that it's built, we need to copy the two libraries to `/usr/lib`, so they'll become visible to the linker:

`sudo cp libg* /usr/lib/`

We switch to our home directory,

`cd ~/`

clone the repository containing the cpp challenge source code,

`git clone https://github.com/klemen-forstneric/cpp_challenge.git`

and build it:

`cd cpp_challenge`

`mkdir build && cd build`

`cmake ..`

`make`

Now that it's built, we can run the tests using the command `./server_tests`, and afterwards the server with `./server` (it binds to `tcp://*:5555`). 

We open another terminal, switch to cpp_challenge directory (`cd ~/cpp_challenge/`), and execute `python test.py tcp://10.211.55.8:5555`.

Done!
