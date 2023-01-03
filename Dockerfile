FROM debian
COPY targets/x86/iso /iso

# Install packages
RUN apt-get update -y && \
	apt-get install -y xorriso && \
	apt-get install -y grub-common

# Build ISO
RUN grub-mkrescue -o kernel.iso iso 2>/dev/null

# Entry point loop
ENTRYPOINT ["tail", "-f", "/dev/null"]
