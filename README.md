### Сборка

#### Без тестов

``` bash
mkdir build
cd build
cmake ..
make -j
```

#### С тестами

Для тестов используется [Cpputest](https://cpputest.github.io/).

Установка Cpputest:

```bash
sudo apt install cpputest
```

Сборка:

```bash	
mkdir build
cd build
cmake .. -DTAPE_SORTER_TESTS=ON
make -j
```

### Запуск

Запуск тестов:
```bash
# из директории с собранными тестами
./tape_sorter_test
```

Запуск сервиса
```bash
# из директории с собранными тестами
./tape_sorter_service <src_file> <res_file> -c <cfg_path=/tmp/>
```

, где

<code><src_file></code> - Файл, содержащий ленту, которая подлежит сортировке

<code><res_file></code> - Путь к файлу, в который будет записана отсортированная лента

<code><cfg_path></code> - Путь к файлу с конфигруцией

Пример:
```bash
./tape_sorter_service some_tape.tape sorted.tape -c ../config/tape_cfg.json
```

### Формат конфигурационного файла

``` json
{
    "write_delay" : <зарежка по записи в миллисекундах>,
    "read_delay"  : <задержка по чтению в миллисекундах>,
    "move_delay"  : <задержка по перемещению в миллисекундах>,
    "tmp_path"    : "<путь к папке для размещени временных лент>"
}
```

