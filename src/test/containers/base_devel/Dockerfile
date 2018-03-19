FROM ubuntu:16.04
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8842CE5E
RUN echo deb http://ppa.launchpad.net/Dealtoken/Dealtoken/ubuntu xenial main >/etc/apt/sources.list.d/Dealtoken.list
RUN apt-get update
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get install -y git build-essential g++ libboost-all-dev libdb4.8++-dev libqrencode-dev libssl-dev
