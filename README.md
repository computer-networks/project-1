# liso-starter-code

## 1. Files
- `15-441-project-1/`: Source code for the project.
- `DockerFile`: Script to build the docker image for the project's environment.

## 2. Environment Setup
1. Install docker: https://www.docker.com
2. Open a terminal and navigate to this directory.
3. Run ``export DOCKER_DIR=`pwd\` ``
4. Build the docker image: `docker build -t 15441project1:latest -f ./DockerFile .`
5. Run the docker container: `docker run -it -v $DOCKER_DIR/15-441-project-1/:/home/15-441-project-1/ --name <name_for_your_container> 15441project1 /bin/bash`
6. The starter code for the project is available at `/home/15-441-project-1/` in the container and `./15-441-project-1/` on your local machine. To make development easier, a mapping is established between these two folders. Modiying the code in one location will also effect the other one. This means that you can use an IDE to write code on your local machine and then seamlessly test it in the container. 
7. To test your server using a web browser, you need to configure port mapping for the docker container. Simply add the argument `-p 8888:15441` to the `docker run` command to establish a mapping from `127.0.0.1:15441` in the container to `127.0.0.1:8888` on your local machine. Then you can test your server by using a web browser (e.g., Chrome) on your local machine to navigate to the URL `127.0.0.1:8888`.
