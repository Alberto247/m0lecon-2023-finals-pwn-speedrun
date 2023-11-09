FROM ubuntu:22.04

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y socat wget
RUN apt-get install -y libssl-dev

COPY chall /
COPY entrypoint.sh /

RUN chmod +x /chall
RUN chmod +x /entrypoint.sh

CMD ["/entrypoint.sh"]