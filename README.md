Чтобы собрать программу должна быть установлена SFML(ubuntu: libsfml-dev, arch linux: sfml).
Можно собрать при помощи cmake. Либо вручную, слинковав с sfml(например так: 
g++ -std=c++11 main.cpp core/src/*.cpp graphics/src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system
).
В папке с исполняемым файлом должен находиться файл input.txt с конфигурацией дорожной схемы. В репозитории уже есть один для примера.
