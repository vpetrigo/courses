На этом шаге от вас потребуется создать `Dockerfile` для образа,
который будет удовлетворять следующим свойствам:

```
Базовый образ – ubuntu:16.04
Установлен текстовый редактор nano
Переменная окружения $EDITOR устанавливает nano в качестве редактора по умолчанию
В качестве рабочей директории установлен каталог /home/stepik
При запуске контейнера открывается nano, файл автоматически сохраняется в файловую систему хоста, даже если при запуске опции монтирования не указаны
Владельцем файла на хосте назначается пользователь с uid=1000, если при сборке не указываются дополнительные аргументы, или пользователь с uid, который был задан аргументом UID при сборке
Именно этот пользователь (uid=1000/uid=UID) должен быть основным в контейнере.
```

### Пример для пользователя с UID=1000:

```bash
id -u $(whoami)
> 1000
docker build -t dockerfile-extended .
docker run -it --rm -v $(pwd):/home/stepik dockerfile-extended
# Nano is opened, we write some text, closing editor and specifying a filename as 'test'

ls -l test
> -rw-r--r-- 1 <username> <group> 7 марта 11 17:20 test
# Where <username> is the name of the user with uid=1000
```

### Пример для пользователя с произвольным UID:

```bash
docker build -t dockerfile-extended --build-arg UID=1001 .
# Doing the same...
> -rw-r--r-- 1 <username> <group> 7 марта 11 17:20 test
# Where <username> is the name of the user with uid=1001
```

Для получения кода проверки в папке с `Dockerfile`, содержащим ответ, выполните:

```bash
docker run --rm -v $(pwd)/Dockerfile:/mnt/Dockerfile -v /var/run/docker.sock:/var/run/docker.sock parseq/stepik-dockerfile-extended
```
