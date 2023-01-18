FROM debian

# Install packages
RUN apt-get update -y && \
	apt-get install -y grub2 && \
	apt-get install -y xorriso && \
	apt-get install -y grub-common

# Entry point loop
ENTRYPOINT ["tail", "-f", "/dev/null"]
