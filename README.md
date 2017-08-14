# php-mystem

Интерфейс к библиотеке [Yandex.Mystem](https://tech.yandex.ru/mystem/).

## Сборка и установка

```bash
$ wget https://github.com/yandex/tomita-parser/releases/download/v1.0/libmystem_c_binding.so.linux_x64.zip
$ unzip libmystem_c_binding.so.linux_x64.zip
$ sudo cp libmystem_c_binding.so /usr/local/lib64/
$ sudo ln -s /usr/local/lib64/libmystem_c_binding.so /usr/local/lib64/libmystem_c_binding.so.1
$ sudo apt-get -y install libicu-dev
$ phpize
$ ./configure
$ make
$ sudo make install
# прописать 'extension=mystem.so' в php.ini
```

## Использование

    Mystem\lemma(string word): array

    Mystem\form_info(string word, bool gram_info_as_string = false): array

    Mystem\generate_forms(string word, bool gram_info_as_string = false): array

    Mystem\gram_name(int gram_value): string

Константы грамматических меток находятся в неймспейсе `Mystem\GramInfo`. Названия этих констант возвращает функция `Mystem\gram_name`.
