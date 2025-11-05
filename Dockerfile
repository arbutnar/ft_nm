FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    build-essential \
    valgrind \
    git

WORKDIR /app/ft_nm

# correctio
# COPY . .

CMD ["sleep", "infinity"]