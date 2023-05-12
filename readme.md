# Drone Simulation System

This directory contains the support code needed to visualize the drone simulation system.

## Getting Started

Here is a quick overview of how to run the visualization (If you are using ssh, navigate to ssh category below):

```bash
# Go to the project directory
cd /path/to/repo/project

# Build the project
make -j

# Run the project (./build/web-app <port> <web folder>)
./build/bin/transit_service 8081 apps/transit_service/web/
```
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.


# Using Docker
Unless your running Ubuntu 20.0.4, this simulation probably won't run properly, so in that case we use Docker

## Prerequisites
You should already have Docker installed, as well as an account on Docker Hub
If you haven't already, visit https://hub.docker.com, and create an account.  When this is done, type this command in your terminal and put in your login credentials:
```
docker login
```
From here on, make sure your actual docker daemon is running.  To start it, just open up the Docker app and it should automatically run the daemon.

## Relevant Commands
This workshop introduces a lot of new concepts and commands, so I created a cheat sheet that goes somewhat in-depth on all the commands you may (or may not) need to complete this workshop.

You can find this cheat sheet [here](https://github.come/fmgornick/drone-sim/blob/main/cheatsheet.md).

## Running a Docker Image
To make sure everything works properly on your end, try typing:
```bash
docker run --rm -d -p 80:80 docker/getting-started
```
It may say that it's unable to find the image locally, that's fine as long as it still pulls the image down.

Check to see that your container is running with:
```bash
docker ps
```

If there's a container listed, then that means everything works!  You can now end this container process with:
```bash
docker kill <CONTAINER ID>
```
`<CONTAINER ID>` can be copied from the result of your previous `docker ps` call

## Writing the Dockerfile
In this repository, we've provided a `Dockerfile` containing a bit of setup code and a couple comments for guidance.  You're tasked will adding the last few necessary instructions to allow for the creation of a runnable docker image.

The instructions you will need are as follows:
```Dockerfile
RUN <command>     # allows you to run any linux command like you 
                  # would on a labs machine (if using ubuntu image)

COPY <src> <dest> # copies files on local computer to specified 
                  # location in our docker image

WORKDIR <path>    # changes the directory in the docker image 
                  # (similar to how "cd" works in linux)

CMD [ "list", "of", "args" ] # command the container executes when
                             # launching our built image
```
A more detailed description of these instructions can be found in this [cheat sheet](https://github.com/fmgornick/drone-sim/blob/main/cheatsheet.md).

## Building the Docker Image
To build a docker image, you must navigate to the directory containing your Dockerfile, then run:
```bash
docker build -t <image_name> <path_to_files>
```

This call invokes the commands outlined in the Dockerfile and builds our image.  The `-t` flag specifies that we want to name our image, and `<path_to_files>` is the relative file path that will be used in our Dockerfile.  Since our Dockerfile is in the root of our project, and we just want to copy this whole project onto our docker image, `<path_to_file>` will always just be `.`

The command you should use to build your image is:
```bash
docker build -t <docker_username>/drone_sim .
```
The naming convention for this image MUST start with your docker username followed by '/', this is the only way (that i'm aware of) Docker will allow you to push your image up to Docker Hub for the workshop 5 submission.

For example, if my docker username was "corey123", then my image name would be "corey123/drone_sim" and my build command is:
```bash
docker build -t fmgornick/drone_sim .
```

If you get errors during the build process, you may need to tweak your `Dockerfile`.  It could also be the case that your `Dockerfile` is in the wrong folder relative to your project, or you're not in the same directory as your `Dockerfile`.

## Running the Docker Image
Once you've made the necessary changes to the Dockerfile, and your image builds without issue, it's finally time to see if it works.

The command you will use to run the docker image is:
```bash
docker run --rm -it -p <local_port>:<container_port> <image_name>
```
For the specifics of each flag this command uses, you can see a detailed description of each one used in the cheat sheet [here](https://github.com/fmgornick/drone-sim/blob/main/cheatsheet.md).

If your having trouble terminating your docker container, you can hit `CTRL`+`P`+`Q` to detach your container, then type `docker ps -q | xargs docker kill` to actually terminate it.

