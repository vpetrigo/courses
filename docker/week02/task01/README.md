На этом шаге нам предстоит решить две задачи: поработать 
с проверяющей системой и решить простую задачу по cозданию `Dockerfile`.

### Задача

Вам требуется создать Dockerfile, в котором будет 
описано создание образа со следующими свойствами:

При запуске контейнера из этого образа без аргументов 
он должен вывести строку `Hello World!` и завершить работу 
При запуске контейнера с аргументом `<arg>` должна быть 
выведена строка `Hello <arg>!`, после чего контейнер должен завершить свою работу
Пример того, как должно работать решение:

```bash
# You have created Dockerfile with appropriate instructions

docker build -t test .
# Image named test successfully created

docker run --rm test
> Hello World!

docker run --rm test Universe
> Hello Universe!
```
