FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    build-essential \
    valgrind \
    sudo \
    git

WORKDIR /app/ft_nm

# correction
COPY . .

CMD ["sleep", "infinity"]