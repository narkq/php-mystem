FROM ubuntu:xenial

RUN apt-get -y update && \
    apt-get -y install unzip pkg-config php-dev php-cli

ADD https://github.com/yandex/tomita-parser/releases/download/v1.0/libmystem_c_binding.so.linux_x64.zip ./

RUN unzip ./libmystem_c_binding.so.linux_x64.zip -d /usr/local/lib64 && \
    rm ./libmystem_c_binding.so.linux_x64.zip && \
    mv /usr/local/lib64/libmystem_c_binding.so /usr/local/lib64/libmystem_c_binding.so.1 && \
    ln -s /usr/local/lib64/libmystem_c_binding.so.1 /usr/local/lib64/libmystem_c_binding.so

RUN apt-get -y install libicu-dev

COPY . /home/docker/mystem-src
WORKDIR /home/docker/mystem-src

RUN phpize && \
    ./configure && \
    make install

RUN echo 'extension=mystem.so' > /etc/php/7.0/mods-available/mystem.ini

RUN ln -s /etc/php/7.0/mods-available/mystem.ini /etc/php/7.0/cli/conf.d/20-mystem.ini
