FROM ubuntu:latest
RUN apt update && apt install -y gcc libmysqlclient-dev
WORKDIR /game
COPY . /game
RUN sed -i 's/localhost/db/g' main.c
RUN gcc main.c -o rpg -I/usr/include/mysql -L/usr/local/include/mysql/lib -lmysqlclient /usr/lib/x86_64-linux-gnu/libmysqlclient.a

FROM ubuntu:latest
RUN apt update && apt install -y libmysqlclient-dev openssh-server && mkdir /game
RUN mkdir /var/run/sshd && useradd -s /game/rpg -M -d /game game && echo "game:game" | chpasswd
WORKDIR /game
COPY --from=0 /game/rpg /game/catalog.txt /game/items.txt /game/
COPY --from=0 /game/maps /game/maps
CMD /usr/sbin/sshd -D
