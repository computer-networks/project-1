# Project-1-Handout-Gradescope

## 1. Files
- `15-441-project-1/` : source codes for the handout
- `DockerFile` : the script to build the docker image for this project's environment

## 2. Environment Setup
1. install docker
2. open terminal and change working directory to this folder
3. run `docker build -t 15441project1:latest -f ./DockerFile .`
4. run `docker run -it -v <absolute_path_to_current_folder>/15-441-project-1/:/home/15-441-project-1/ --name <name_for_your_container> project1 /bin/bash`
5. handout codes are available at `/home/15-441-project-1/` (in the container) and `<absolute_path_to_current_folder>/15-441-project-1/` (on your machine), and modify in one place will also affect the other one. That is to say, a mapping is established between the two folders, which means you can use IDE to write codes on your machine and test them in the container easily.

6. In order to test your server with a browser on your machine, you need to set up port mapping for the docker container. Simply add a command line argument, such as, `-p 8888:15441` to the command in 4, and a mapping from `127.0.0.1:15441`(in container) to `127.0.0.1:8888`(on your machine) is established. Then you can use the URL `127.0.0.1:8888` in your browser like Chrome to test your server which is bound to port 15441 in the container.
7. To enable both HTTP port and HTTPS port, you need to add another mapping to the command. For example, `docker run -it -p 8888:15441 -p 9999:15641 -v <absolute_path_to_current_folder>/15-441-project-1/:/home/15-441-project-1/ --name <name_for_your_container> project1 /bin/bash`. Also, do not forget to install the certificate in your browser.

