FROM ubuntu:22.04 as base

LABEL description="Build container for azure-sdk-for-cpp-demo"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    nano git curl \
    make cmake pkg-config g++ linux-libc-dev \
    libcurl4-openssl-dev libssl-dev libxml2-dev
