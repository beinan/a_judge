FROM ubuntu:14.04

MAINTAINER Phil Pratt-Szeliga version: 0.2.0

ENV DEBIAN_FRONTEND noninteractive

RUN useradd exec
RUN apt-get update
RUN apt-get install unzip
ADD ./CppGrader /
ADD ./binary_files.zip /
RUN unzip binary_files.zip
